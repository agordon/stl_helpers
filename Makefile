
SUBDIRS=src tests


all: $(SUBDIRS)

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@


.PHONY: clean
clean:
	$(MAKE) -C tests clean
	$(MAKE) -C src clean
