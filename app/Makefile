include $(TOPDIR)/config.mk

TARGET := entrance

SUBDIRS += $(TOPDIR)/osal/linux
SUBDIRS += $(TOPDIR)/osal
SUBDIRS += $(TOPDIR)/app/sys


OBJ_FILES=$(SUBDIRS:%=%/*.o)
LDFLAGS = -lm -lrt -pthread -lusb-1.0 -L$(LIBDIR)/libudev -ludev

.PHONY: all clean app install
all: app install 

app:
	@for subdir in $(SUBDIRS); do \
		(cd $$subdir && $(MAKE) all) || exit 1; \
	done

	@$(CC) $(OBJ_FILES) $(LDFLAGS) -o $(TARGET)
	$(STRIP) --strip-unneeded  --remove-section=.comment --remove-section=.note $(TARGET)

install:
	cp -f $(TARGET) $(IMAGES_DIR)/
	cp -f $(TARGET) $(TFTP_DIR)/

clean:
	-rm -rf $(TARGET)
	@for subdir in $(SUBDIRS); do \
		(cd $$subdir && $(MAKE) $@) || exit 1; \
	done