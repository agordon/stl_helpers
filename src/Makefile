
HEADERS=$(wildcard *.h)
GCH=$(subst .h,.gch,$(HEADERS))

.PHONY: all
all: $(GCH)

%.gch: %.h
	g++ -o $@ -c $<

.PHONY: clean
clean:
	rm -f *.gch
