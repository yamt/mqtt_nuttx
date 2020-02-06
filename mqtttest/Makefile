
-include $(TOPDIR)/Make.defs
include $(APPDIR)/external/mqtt/LibIncludes.mk
# include $(APPDIR)/external/mbedtls/LibIncludes.mk

DELIM ?= $(strip /)

VPATH += :.

PROGNAME = mqtttest
PRIORITY = SCHED_PRIORITY_DEFAULT
STACKSIZE = 2048
MODULE = CONFIG_EXTERNALS_MQTTTEST

# CSRCS += test.c
MAINSRC = test_main.c

include $(APPDIR)/Application.mk
