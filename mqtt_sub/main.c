
#include <nuttx/compiler.h>

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#include <MQTTClient.h>
#include <MQTTConnect.h>

static const char *progname;

static void
xerrx(int eval, const char *fmt, ...)
{
	va_list ap;

	fprintf(stderr, "%s: ", progname);
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");

	exit(eval);
}

static const char *
xgetenv(const char *name)
{
	const char *v = getenv(name);
	if (v == NULL) {
		xerrx(1, "%s is not set", name);
	}
	return v;
}

static int
xgetenv_int(const char *name)
{
	// XXX better to use strtoul and check errors
	return atoi(xgetenv(name));
}

static void
onMessage(MessageData* md)
{
	const MQTTMessage* message = md->message;

	printf("onMessage: %.*s",
		(int)message->payloadlen, (char*)message->payload);
}

int
main(int argc, FAR char *argv[])
{
	progname = argv[0];

	const char *host = xgetenv("MQTT_HOST");
	const unsigned int port = xgetenv_int("MQTT_PORT");
	const char *client_id = getenv("MQTT_CLIENTID");
	const char *user = getenv("MQTT_USERNAME");
	const char *pass = getenv("MQTT_PASSWORD");
	const char *topic = xgetenv("MQTT_TOPIC");

	unsigned int timeout = 1000; /* in ms */
	int rc;

	MQTTSocket s;
	MQTTClient c;

	MQTTSocketInit(&s, 0);
	rc = MQTTSocketConnect(&s, host, port);
	printf("MQTTSocketConnect: %d\n", rc);
	if (rc < 0) {
		xerrx(1, "MQTTSocketConnect failed with %d", rc);
	}

	unsigned char sendbuf[256];
	unsigned char recvbuf[256];
	MQTTClientInit(&c, &s, timeout, sendbuf, sizeof(sendbuf),
				   recvbuf, sizeof(recvbuf));

	MQTTPacket_connectData conndata = MQTTPacket_connectData_initializer;
	conndata.clientID.cstring = client_id;
	conndata.username.cstring = user;
	conndata.password.cstring = pass;
	rc = MQTTConnect(&c, &conndata);
	printf("MQTTConnect: %d\n", rc);
	if (rc != SUCCESS) {
		xerrx(1, "MQTTConnect failed with %d", rc);
	}

	rc = MQTTSubscribe(&c, topic, QOS0, onMessage);
	printf("MQTTSubscribe: %d\n", rc);
	if (rc != SUCCESS) {
		xerrx(1, "MQTTSubscribe failed with %d", rc);
	}

	for (;;) {
		rc = MQTTYield(&c, timeout);
		if (rc != SUCCESS) {
			printf("MQTTYield: %d\n", rc);
			sleep(1);
		}
	}

	/* NOTREACHED */
	return 0;
}
