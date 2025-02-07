# dwm - dynamic window manager

dwm is an extremely fast, small, and dynamic window manager for X.


## Requirements

In order to build dwm you need the Xlib header files.

## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

``` bash
make clean install
```

## Applied patches

- dwm-alwayscenter-20200625-f04cac6.diff
- dwm-bar-height-spacing-6.3.diff
- dwm-cool-autostart-20240312-9f88553.diff
- dwm-ewmhtags-20180101-db22360.diff
- dwm-fsignal-6.2.diff
- dwm-xrdb-6.4.diff

## Running dwm

Refer to the man page.
