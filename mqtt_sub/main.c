
#include <nuttx/compiler.h>

#include <stdarg.h>
#include <stdlib.h>

#include <MQTTClient.h>
#include <MQTTConnect.h>

static void
xerrx(int eval, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

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
	const char *host = xgetenv("MQTT_HOST");
	const unsigned int port = xgetenv_int("MQTT_PORT");
	const char *user = xgetenv("MQTT_USERNAME");
	const char *topic = xgetenv("MQTT_TOPIC");

	unsigned int timeout = 1000; /* in ms */
	int rc;

	MQTTSocket s;
	MQTTClient c;

	MQTTSocketInit(&s, 0);
	MQTTSocketConnect(&s, host, port);

	unsigned char sendbuf[256];
	unsigned char recvbuf[256];
	MQTTClientInit(&c, &s, timeout, sendbuf, sizeof(sendbuf),
				   recvbuf, sizeof(recvbuf));

	MQTTPacket_connectData conndata = MQTTPacket_connectData_initializer;
	conndata.username.cstring = user;
	rc = MQTTConnect(&c, &conndata);
	printf("MQTTConnect: %d\n", rc);

	rc = MQTTSubscribe(&c, topic, QOS0, onMessage);
	printf("MQTTSubscribe: %d\n", rc);

	for (;;) {
		rc = MQTTYield(&c, timeout);
		printf("MQTTYield: %d\n", rc);
	}

	/* NOTREACHED */
	return 0;
}