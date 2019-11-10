#define PROGRAM_NAME         "pwd"
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
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>

void usage(int status) {
	printf("usage: %s [OPTION]\n", PROGRAM_NAME);
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

char *getlcwd(void) {
	char *pwd = getenv("PWD");
	struct stat cwd, dot;
	
	return (!pwd
	|| pwd[0] != '/'	
	|| strstr(pwd, "/./")
	|| strstr(pwd, "/../")	
	|| stat(pwd, &cwd) == -1
	|| stat(".", &dot) == -1	
	|| cwd.st_dev != dot.st_dev 
	|| cwd.st_ino != dot.st_ino)
	? NULL : pwd;
}

int main(int argc, char **argv) {
	const char *p;
	int c, logical = 0;

	const struct option longopts[] = {
	{"logical",  no_argument, NULL, 'L'},
	{"physical", no_argument, NULL, 'P'},
	{"help",     no_argument, NULL, CHAR_MIN-2},
	{"version",  no_argument, NULL, CHAR_MIN-3},
	{NULL, 0, NULL, 0}
	};

	setlocale(LC_ALL, "");
	
	while ((c = getopt_long(argc, argv, "LP", longopts, NULL)) != -1) {
		switch (c) {
		case 'L':
			logical = 1;
			break;
		case 'P':
			logical = 0;
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
	
	argc -= optind;
	
	if(argc)
		usage(EXIT_FAILURE);
	
	p = logical ? getlcwd() : NULL;
	
	if(!p)
		p = getcwd(NULL, 0);
	
	if(!p){
		perror(NULL);
		return EXIT_FAILURE;
	}
	
	puts(p);
	
	return EXIT_SUCCESS;
}
