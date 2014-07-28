# lsf - find files
# (C)opyright 2014 Konstantin Kliakhandler

include config.mk

SRC = lsf.c
OBJ = ${SRC:.c=.o}

all: options lsf
	@echo finished

options:
	@echo lsf build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

lsf: ${OBJ}
	@echo LD $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}
	@strip $@

clean:
	@echo cleaning
	@rm -f lsf ${OBJ} lsf-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p lsf-${VERSION}
	@cp -R LICENSE Makefile README config.mk ${SRC} lsf-${VERSION}
	@tar -cf lsf-${VERSION}.tar lsf-${VERSION}
	@gzip lsf-${VERSION}.tar
	@rm -rf lsf-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f lsf ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/lsf

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/lsf

.PHONY: all options clean dist install uninstall
