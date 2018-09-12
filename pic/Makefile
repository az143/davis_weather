#!/bin/make -f
all: notdavis.hex

notdavis.hex: notdavis.c
	xc8 --chip=16f88  $^

install: notdavis.hex
	pk2cmd -K -Y -M -Ppic16f88 -F $< 

clean: 
	rm -f startup.* funclist *.o *.hex *.lst *.cod *.sym *.sdb *.pre *.p1 *.hxl *.d *.cof *.as *.cmf
