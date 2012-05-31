
SUBDIRS=src tests

all: tests

tests: $(SUBDIRS)

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ tests


.PHONY: clean
clean:
	$(MAKE) -C tests clean
	$(MAKE) -C src clean
