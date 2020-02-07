
#include <nuttx/compiler.h>

#include <stdlib.h>

#include <MQTTClient.h>

int
main(int argc, FAR char *argv[])
{
	const char *host;
	const char *port;

	host = argv[1];
	host = argv[2];

	MQTTSocket s;
	MQTTClient c;

	MQTTSocketInit(&s, 0);
	MQTTSocketConnect(&s, host, port);

	return 0;
}
