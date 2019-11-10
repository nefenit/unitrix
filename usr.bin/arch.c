#define PROGRAM_NAME         "arch"
#define PROGRAM_VERSION      "1.0"
#define PACKAGE_NAME         "Unitrix usr.bin"
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

void usage(int status) {
	printf(
	"usage: %s [OPTION]\n"
	"Options:\n"
	"  --help     display this help and exit\n"
	"  --version  output version information and exit\n",
	PROGRAM_NAME);
	exit(status);
}

int main(int argc, char *argv[]) {
	const struct option const longopts[] = {
		{"help",    no_argument, NULL, CHAR_MIN - 2},
		{"version", no_argument, NULL, CHAR_MIN - 3},
		{NULL, 0, NULL, 0}
	};
	struct utsname u;
	char c;
	
	setlocale(LC_ALL, "");

	while ((c = getopt_long(argc, argv, "", longopts, NULL)) != -1) {
		switch (c) {
		case CHAR_MIN - 2:
			usage(EXIT_SUCCESS);
			break;
		case CHAR_MIN - 3:
			version(PROGRAM_NAME, PROGRAM_VERSION);
			break;
		case '?':
		default:
			usage(EXIT_FAILURE);
		}
	}

	argc -= optind;
	
	if(argc)
		usage(EXIT_FAILURE);

	if(uname(&u)) {
		perror("uname");
		return EXIT_FAILURE;
	}

	puts(u.machine);
	
	return EXIT_SUCCESS;
}
