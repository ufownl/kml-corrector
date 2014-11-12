CXX = g++
LD = g++
CXXFLAGS = -g -Wall -I../contrib/include
LDFLAGS = -lm

all: kml-corrector

kml-corrector: corrector.o gcj2wgs.o wgs2gcj.o
	$(LD) $^ $(LDFLAGS) -o $@

corrector.o: corrector.cpp gcj2wgs.h
gcj2wgs.o: gcj2wgs.cpp gcj2wgs.h
wgs2gcj.o: wgs2gcj.cpp wgs2gcj.h

clean:
	$(RM) *.o
	$(RM) kml-corrector

.PHONY: all clean
