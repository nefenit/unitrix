#define PROGRAM_NAME          "false"
#define PROGRAM_VERSION       "1.0"
#define PACKAGE_NAME          "Unitrix bin"
#define COPYRIGTH_HOLDER      "Bartosz Mierzynski"
#define COPYRIGTH_YEAR        "2019"
#define LICENSE_ABBREVIATION  "none"
#define LICENSE_LINE          ""

#define STREQ(a, b)  (strcmp(a, b) == 0)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void usage(int status) {
	printf(
	"usage: %s [--help|--version]\n",
	PROGRAM_NAME);
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

int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL, "");
	
	if(argc == 2) {
		if(STREQ(argv[1], "--version"))
			version(PROGRAM_NAME, PROGRAM_VERSION);
		else if(STREQ(argv[1], "--help"))
			usage(EXIT_SUCCESS);
	}

	return EXIT_FAILURE;
}
