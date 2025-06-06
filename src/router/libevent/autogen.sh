#!/bin/sh

MAKE=make
if command -v gmake >/dev/null 2>/dev/null; then
  MAKE=gmake
fi
$MAKE maintainer-clean >/dev/null 2>/dev/null

if [ -x "`which autoreconf 2>/dev/null`" ] ; then
   autoreconf -ivf
fi

LIBTOOLIZE=libtoolize
SYSNAME=`uname`
if [ "$SYSNAME" = "Darwin" ] ; then
  LIBTOOLIZE=glibtoolize
fi
aclocal -I m4 && \
	autoheader && \
	$LIBTOOLIZE && \
	autoconf && \
	automake --add-missing --force-missing --copy
