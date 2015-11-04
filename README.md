this repository contains all tools necessary for building remote AND online
weather stations using davis vantage vue (or vantage pro) kit.

to be precise, this includes:

* an implementation of the workaround for the infamous "green dot" vendor
lock-in, written in C for a Microchip pic16f88 (without any external
components),

* a data gatherer program (in perl) that fetches the weather readings from a
davis console at configurable intervals, then condenses and uploads the
data to a server on the net,

* a data collector program (in perl) that listens for such uploads and saves the
data in an sqlite database, and optionally uploads it to weather underground
and/or the bom/uk-metoffice weather observations website,

* and a graph generator tool (using gnuplot) and a cgi script to
present readings and graphs. both are written in perl.

there is a little bit of extra documentation on my site at
[http://snafu.priv.at/mystuff/fidobeagle.html](http://snafu.priv.at/mystuff/fidobeagle.html).

all code is (c) 2015 Alexander Zangerl <az@snafu.priv.at>,
and is free and open-source software, licensed under the GPL Version 2.

share and enjoy `:-)`

