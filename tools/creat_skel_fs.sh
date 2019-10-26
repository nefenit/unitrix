#!/bin/sh

for dir in bin boot dev home lib media mnt opt root run sbin srv tmp \
	etc etc/opt etc/X11 etc/sgml etc/xml \
	usr usr/bin usr/include usr/lib usr/libexec usr/local usr/local/share \
	usr/sbin/ usr/share usr/share/color usr/share/dict usr/share/man \
	usr/share/misc usr/share/ppd usr/share/sgml usr/share/xml usr/src \
	var var/account var/cache var/cache/fonts var/cache/man var/crash \
	var/games var/lib var/lib/color var/lib/hwclock var/lib/misc var/lock \
	var/log var/mail var/opt var/run var/spool var/spool/lpd var/spool/rwho \
	var/tmp var/yp
do
	mkdir -p "${1:-.}/$dir"
done
unset dir
