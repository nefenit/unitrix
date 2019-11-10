#define PROGRAM_NAME         "uname"
#define PROGRAM_VERSION      "1.0"
#define PACKAGE_NAME         "Unitrix bin"
#define COPYRIGTH_HOLDER     "Bartosz Mierzynski"
#define COPYRIGTH_YEAR       "2019"
#define LICENSE_ABBREVIATION "none"
#define LICENSE_LINE         ""

#include <getopt.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/utsname.h>

enum {
	FLAG_MACHINE  = 1 << 0,
	FLAG_NODENAME = 1 << 1,
	FLAG_RELEASE  = 1 << 2,
	FLAG_SYSNAME  = 1 << 3,
	FLAG_VERSION  = 1 << 4,
	FLAG_ALL      = FLAG_MACHINE
	              | FLAG_NODENAME
	              | FLAG_RELEASE
	              | FLAG_SYSNAME
	              | FLAG_VERSION
} flags;

void usage(int status) {
	printf("usage: %s [-amnrsv]\n", PROGRAM_NAME);
	exit(status);
}

void version(const char* program_name, const char* program_version) {
	printf("%s (%s) %s\n"
	"Copyright (C) %s %s\n"
	"License %s: %s\n"
	"This is free software: you are free to change and redistribute it.\n"
	"There is NO WARRANTY, to the extent permitted by law.\n",
	program_name,
	PACKAGE_NAME,
	program_version,
	COPYRIGTH_YEAR,
	COPYRIGTH_HOLDER,
	LICENSE_ABBREVIATION,
	LICENSE_LINE);
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
	const struct option longopts[] = {
	{"all",            no_argument, NULL, 'a'},
	{"machine",        no_argument, NULL, 'm'},
	{"nodename",       no_argument, NULL, 'n'},
	{"kernel-release", no_argument, NULL, 'r'},
	{"kernel-name",    no_argument, NULL, 's'},
	{"kernel-version", no_argument, NULL, 'v'},
	{"help",           no_argument, NULL, CHAR_MIN-2},
	{"version",        no_argument, NULL, CHAR_MIN-3},
	{NULL,             0,           NULL, 0}
	};
	struct utsname u;
	int c, sp = 0;
	
	setlocale(LC_ALL, "");
	
	while((c = getopt_long(argc, argv, "amnrsv", longopts, NULL)) != -1) {
		switch(c) {
		case 'a':
			flags |= FLAG_ALL;
			break;
		case 'm':
			flags |= FLAG_MACHINE;
			break;
		case 'n':
			flags |= FLAG_NODENAME;
			break;
		case 'r':
			flags |= FLAG_RELEASE;
			break;
		case 's':
			flags |= FLAG_SYSNAME;
			break;
		case 'v':
			flags |= FLAG_VERSION;
			break;
		case CHAR_MIN-2:
			usage(EXIT_SUCCESS);
			break;
		case CHAR_MIN-3:
			version(PROGRAM_NAME, PROGRAM_VERSION);
			break;
		case '?':
		default:
			usage(EXIT_FAILURE);
		}
	}
	
	if(optind != argc)
		usage(EXIT_FAILURE);
	
	if(uname(&u)){
		perror("uname");
		return EXIT_FAILURE;
	}
	
	if(!flags)
		flags = FLAG_SYSNAME;
	
	if(flags & FLAG_SYSNAME) {
		++sp;
		fputs(u.sysname, stdout);
	}
	
	if(flags & FLAG_NODENAME) {
		if(sp++)
			putchar(' ');
		fputs(u.nodename, stdout);
	}
	
	if(flags & FLAG_RELEASE) {
		if(sp++)
			putchar(' ');
		fputs(u.release, stdout);
	}
	
	if(flags & FLAG_VERSION) {
		if(sp++)
			putchar(' ');
		fputs(u.version, stdout);
	}
	
	if(flags & FLAG_MACHINE) {
		if(sp++)
			putchar(' ');
		fputs(u.machine, stdout);
	}
	
	putchar('\n');
	
	return EXIT_SUCCESS;
}
