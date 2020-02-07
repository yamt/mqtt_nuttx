
-include $(TOPDIR)/Make.defs
include $(APPDIR)/external/mqtt/LibIncludes.mk
include $(APPDIR)/external/mbedtls/LibIncludes.mk

DELIM ?= $(strip /)

VPATH += :.

PROGNAME = mqtt_pubsub
PRIORITY = SCHED_PRIORITY_DEFAULT
STACKSIZE = 2048
MODULE = CONFIG_EXTERNALS_MQTT_PUBSUB

MAINSRC = main.c

CFLAGS += -Werror
CFLAGS += -Wno-discarded-qualifiers  # api workaround

include $(APPDIR)/Application.mk
