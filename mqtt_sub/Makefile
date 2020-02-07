
-include $(TOPDIR)/Make.defs
include $(APPDIR)/external/mqtt/LibIncludes.mk
include $(APPDIR)/external/mbedtls/LibIncludes.mk

DELIM ?= $(strip /)

VPATH += :.

PROGNAME = mqtt_sub
PRIORITY = SCHED_PRIORITY_DEFAULT
STACKSIZE = 2048
MODULE = CONFIG_EXTERNALS_MQTT_SUB

# CSRCS += test.c
MAINSRC = test_main.c

include $(APPDIR)/Application.mk
