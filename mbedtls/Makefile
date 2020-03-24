-include $(TOPDIR)/Make.defs

SRCDIR=$(APPDIR)/external/mbedtls/library

all:
	$(Q) $(MAKE) -C $(SRCDIR) TOPDIR=$(TOPDIR) $@

context:
	$(Q) $(MAKE) -C $(SRCDIR) TOPDIR=$(TOPDIR) $@

install:
	$(Q) $(MAKE) -C $(SRCDIR) TOPDIR=$(TOPDIR) $@

clean:
	$(Q) $(MAKE) -C $(SRCDIR) TOPDIR=$(TOPDIR) $@

distclean:
	$(Q) $(MAKE) -C $(SRCDIR) TOPDIR=$(TOPDIR) $@

preconfig:
	$(Q) $(MAKE) -C $(SRCDIR) TOPDIR=$(TOPDIR) $@

depend:
	$(Q) $(MAKE) -C $(SRCDIR) TOPDIR=$(TOPDIR) $@
