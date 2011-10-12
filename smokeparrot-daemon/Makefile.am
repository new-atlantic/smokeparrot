bin_PROGRAMS = smokeparrot
smokeparrot_SOURCES = src/smokeparrot.c src/sp_logging.c src/sp_initialize.c
dist_doc_DATA = README NEWS AUTHORS COPYING INSTALL THANKS ChangeLog
LDADD = @LIBINTL@
localedir = $(datadir)/locale
AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\"
# _BSD_SOURCE is required to expose daemon() in unistd.h.
AM_CFLAGS = -D_XOPEN_SOURCE=600 \
            -D_BSD_SOURCE \
            -std=c99 \
            -pedantic \
            -Wall \
            -Wextra \
            -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual \
            -Wpointer-arith -Wformat=2 -Wmissing-declarations -Wlogical-op \
            -Wmissing-include-dirs -Wno-unused-parameter -Wjump-misses-init \
            -Wuninitialized -Wold-style-definition -Wstrict-prototypes \
	    -Wmissing-prototypes -Wno-format-extra-args -Wshadow \
            -Wdouble-promotion -Wbad-function-cast -Wcast-qual -Wconversion

SUBDIRS = po

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = config.rpath m4/ChangeLog
