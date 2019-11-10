# (c) Copyright 2019 Bartosz Mierzynski
# This makefile considers:
#  - GNU Coding Standards
#  - Filesystem Hierarchy Standard (FHS)
#  - Single UNIX Specification (SUS)

########################################
# Table of contents
#  0. Common variables
#    0. Package variables
#    1. (make) Environment variables
#    2. Utility program variables
#    3. FLAGS variables
#    4. INSTALL_* variables
#    5. Directory variables
#  1. Setup targets
#  2. Build targets
#  3. Test targets
#  4. Documentation targets
#  5. Install targets
#  6. Clean targets
#  7. Other targets

########################################
# 0. Common variables

########################################
# 0.0 Package variables

PACKAGE_NAME = bin
VERSION = 1.0
BIN = \
	echo\
	false\
	pwd\
	sleep\
	sync\
	true\
	uname
OBJ = $(BIN:=.o)
SRC = $(BIN:=.c)
MAN = $(BIN:=.1)

########################################
# 0.1 Envirionment variables

# Assignement below is used to avoid problems with systems where SHELL variable 
# is inherited from environment
SHELL=/bin/sh
#COLUMNS
#HOME
#LANG
#LINES
#LOGNAME
#PATH
#PWD
#TERM

# Clears suffixes list and sets new one describing ALL suffixes used in makefile.
# Those newly defined suffixes are target for makefiles implicit rules
# This procedure is done to remove misbehaviour between make programs which work differently
# and have different suffix lists and implicit rules
.SUFFIX:
.SUFFIX: .c .o

# If no default goal is specified then the default goal 
# is the first target from top of file that make encounters
.DEFAULT_GOAL := all

########################################
# Portable utilities that can be used without setting variable for them
# ---------------------------------------------------------------------
#  cat cmp cp diff echo egrep expr false grep install-info ln ls
#  mkdir mv printf pwd rm rmdir sed sleep sort tar test touch tr true
#  chgrp chmod chown mknod
#  --------------------------------------------------------------------
# Only POSIX defined options shall be used and scripts shall use /bin/sh
# For example:
#  mkdir -p 
# is not standard

########################################
# 0.2 Utility programs (those which may need replacement)
#  INSTALL must be defined in every Makefile
AR        = ar
AS        = as
AWK       = awk
BISON     = bison
CC        = cc
CO        = co
CPP       = $(CC) -E
CXX       = c++
FC        = f77
FLEX      = flex
GET       = get
INSTALL   = install
LD        = ld
LDCONFIG  = ldconfig
LINT      = lint
LEX       = lex
M2C       = m2c
MAKE      = make
MAKEINFO  = makeinfo
PC        = pc
RANLIB    = ranlib
TANGLE    = tangle
CTANGLE   = ctangle
TEX       = tex
TEXI2DVI  = texi2dvi
TEXI2HTML = makeinfo --no-split --html
WEAVE     = weave
CWEAVE    = cweave
YACC      = yacc

########################################
# 0.3 FLAGS a.k.a command variables of utility programs
# - general scheme: VARFLAGS
# - there are exceptions to the scheme, mostly compilers

#CC 
# - should be invoked on every CC invocation both those which do compilation or linking
# - should be placed last in compilation command so user can override the other flags
CFLAGS     =-Wall -pedantic -ansi -O2 -g -DPACKAGE_NAME=\"$(PACKAGE_NAME)\"
#c preprocessor
# - use in any compilation command that runs preprocessor
CPPFLAGS   =
#CXX - C++ equivalent to CFLAGS
CXXFLAGS   =
#FC
FFLAGS     =
#GET
GFLAGS     =
#LD
# - use in any compilation command that does linking or directly uses LD
LDFLAGS    = 
#LEX
LFLAGS     =
#PC
PFLAGS     =
# extra flags for Ratfor programs for Fortran compiler
RFLAGS     =
#YACC
YFLAGS     =

########################################
# 0.4 INSTALL_* variables those must be defined in every makefile
# 1. executables
INSTALL_PROGRAM=$(INSTALL)
# 2. non-executables (libraries, images, docs, etc.)
INSTALL_DATA=${INSTALL} -m 644
# DESTDIR must be prepended to each installed target file
# DESTDIR is defined by user and must be absolute path
# DESTDIR is only supported in install* and uninstall* targets
# DESTDIR is forbidden to be set in makefile
# DESTDIR is forbidden to change software operation in any way

#########################################
# 0.5 Directory variables
prefix         = /usr/local
exec_prefix    = $(prefix)
bindir         = $(exec_prefix)/bin
sbindir        = $(exec_prefix)/sbin
libexecdir     = $(exec_prefix)/libexec
datarootdir    = $(prefix)/share
datadir        = $(datarootdir)
sysconfdir     = $(prefix)/etc
sharedstatedir = $(prefix)/com
localstatedir  = $(prefix)/var
runstatedir    = $(localstatedir)/run
includedir     = $(prefix)/include
oldincludedir  = /usr/include

docdir         = $(datarootdir)/doc/yourpkg
infodir        = $(datarootdir)/info
htmldir        = $(docdir)
dvidir         = $(docdir)
pdfdir         = $(docdir)
psdir          = $(docdir)
libdir         = $(exec_prefix)/lib
lispdir        = $(datarootdir)/emacs/site-lisp
localedir      = $(datarootdir)/locale
mandir         = $(datarootdir)/man
man0dir        = $(mandir)/man0
man1dir        = $(mandir)/man1
man2dir        = $(mandir)/man2
man3dir        = $(mandir)/man3
man4dir        = $(mandir)/man4
man5dir        = $(mandir)/man5
man6dir        = $(mandir)/man6
man7dir        = $(mandir)/man7
man8dir        = $(mandir)/man8
man9dir        = $(mandir)/man9
manext         = .1
man0ext        = .0
man1ext        = .1
man2ext        = .2
man3ext        = .3
man4ext        = .4
man5ext        = .5
man6ext        = .6
man7ext        = .7
man8ext        = .8
man9ext        = .9

srcdir         =

#######################################
# 1. Setup targets

#######################################
# 2. Build targets

# - compiles program
# - default target
# - doesn't rebuild any documentation
# - should have -g flag for debugging symbols
.PHONY: all
all: $(BIN)

$(BIN):$(OBJ)

.o:
	@$(CC) -o $@ $< $(LIB) $(LDFLAGS) 

.c.o:
	@$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS) 

#######################################
#  3. Test targets

# - performs self test on built program if any
# - does not perform tests on installed copy but the build
# - user must build the program before tests
.PHONY: check
check:

#######################################
#  4. Documentation targets

# geneates info files needed
.PHONY: info
info:

# - generates documentation in given format
# - must always exist but may be no-op
.PHONY: html
html:

.PHONY: dvi
dvi:

.PHONY: pdf
pdf:

.PHONY: ps
ps:

#######################################
#  5. Install targets		
	
# - compiles program
# - copies executables and libraries where they should reside for actual use
# - may or may not perform simple test
# - doesn't strip executables
# - should not modify anything in directory where target was built (asumes `make all` was done)
# - should create all directiories in which files are to be installed (includes prefixes)
# - the '-' before any command for installing manpage so make will ignore errors
# - installs info files should be done by $(INSTALL_DATA) and then into $(infodir) and then run install-info program
.PHONY: install
install: all info
	$(INSTALL_PROGRAM) $(BIN) $(DESTDIR)$(bindir)/$(BIN)

# - like install but stripes executables while installing them
# - doesn't strip scripts; only binaries
# - doesn't strip executables in build directory; only the copies for installation
.PHONY: install-strip
install-strip: all info
	$(INSTALL_PROGRAM) -s $(BIN) $(DESTDIR)$(bindir)/$(BIN)

	
# - deletes installed files that install and install-* create
# - should not modify directories where compilation is done, only those where files are installed
.PHONY: uninstall
uninstall:
	
		
# - intended to be called explicity by the person
# - installs documentation different than info files
# - should invoke commands for format targets
.PHONY: install-html
install-html: html

.PHONY: install-dvi
install-dvi: dvi

.PHONY: install-pdf
install-pdf: pdf

.PHONY: install-ps
install-ps: ps


#######################################
#  6. Clean targets	

# - like clean but doesn't delete things you don't want to recompile
.PHONY: mostlyclean
mostlyclean:
	@rm $(BIN) $(OBJ) *.tar*

# - deletes ALL(except configuration) files in build directory created by building program includes documentation
# - doesn't have to delete directiories created by makefile
.PHONY: clean
clean: mostlyclean
	
# - deletes ALL(including configuration) files created by makefile
# - doesn't have to delete directiories created by makefile
.PHONY: distclean
distclean: clean


# - deletes everything that can be rebuilt
.PHONY: maintainer-clean
maintainer-clean: distclean
	@echo 'This command is intended for maintainers to use; it'
	@echo 'deletes files that may need special tools to rebuild.'
	
#######################################
#  7. Other targets		

# - creates distribution tar for this program compressed with gzip
# - the filename scheme is: package-versionmajor.versionminor.tar.gz
# - the tar archive should unpack to subdirectory: package-versionmajor.versionminor
.PHONY: dist
dist: all
	@mkdir $(PACKAGE_NAME)-$(VERSION)
	@cp $(BIN) $(PACKAGE_NAME)-$(VERSION)
	@tar -czf $(PACKAGE_NAME)-$(VERSION).tar.gz $(PACKAGE_NAME)-$(VERSION) 
	@rm -rf $(PACKAGE_NAME)-$(VERSION)
	
# updates tags table for this program
.PHONY: TAGS
