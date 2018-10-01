#!/bin/make -f
all: notdavis.hex

# old setup:
# CHIP=16f88
CHIP=16f18313

notdavis.hex: notdavis.c
	xc8 --chip=${CHIP} $^

# install: test.hex
install: notdavis.hex
	pk2cmd -B/usr/local/share/pickit2 -K -Y -M -Ppic${CHIP} -F $< 

clean: 
	rm -f startup.* funclist *.o *.hex *.lst *.cod *.sym *.sdb *.pre *.p1 *.hxl *.d *.cof *.as *.cmf

test.hex: test.c
	xc8 --chip=${CHIP} $^
