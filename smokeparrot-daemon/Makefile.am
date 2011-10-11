bin_PROGRAMS = smokeparrot
smokeparrot_SOURCES = src/smokeparrot.c src/sp_logging.c src/sp_initialize.c
dist_doc_DATA = README NEWS AUTHORS COPYING INSTALL THANKS ChangeLog
LDADD = @LIBINTL@
localedir = $(datadir)/locale
AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\"

SUBDIRS = po

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = config.rpath m4/ChangeLog
