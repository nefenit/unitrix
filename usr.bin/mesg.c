#define PROGRAM_NAME         "mesg"
#define PROGRAM_VERSION      "1.0"
#define PACKAGE_NAME         "Unitrix usr.bin"
#define COPYRIGTH_HOLDER     "Bartosz Mierzynski"
#define COPYRIGTH_YEAR       "2019"
#define LICENSE_ABBREVIATION "none"
#define LICENSE_LINE         ""

#include <getopt.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>

enum {
	RECEIVING_MSG_ALLOWED     = 0,
	RECEIVING_MSG_NOT_ALLOWED = 1,
	ERROR_OCCURED             = 2
};

void usage(void) {
	fprintf(stderr, "usage: %s [y|n]\n", PROGRAM_NAME);
	exit(ERROR_OCCURED);
}

int main(int argc, char **argv) {
	char *tty;
	struct stat s;
	int c;

	setlocale(LC_ALL, "");

	while((c = getopt(argc, argv, "")) != -1) {
		switch(c) {
		case '?':
		default:
			usage();
		}
	}
	
	argc -= optind;
	argv += optind;

	if((tty = ttyname(STDIN_FILENO)) == NULL
		&& (tty = ttyname(STDOUT_FILENO)) == NULL 
		&& (tty = ttyname(STDERR_FILENO)) == NULL
	){
		perror("ttyname");
		return ERROR_OCCURED;
	}
	
	if(stat(tty, &s) == -1){
		perror(tty);
		return ERROR_OCCURED;
	}
	
	if(*argv == NULL) {
		if(s.st_mode & S_IWGRP) {
			puts("y");
			return RECEIVING_MSG_ALLOWED;
		}
		
		puts("n");
		return RECEIVING_MSG_NOT_ALLOWED;
	}
	
	switch(*argv[0]) {
	case 'y':
		if(chmod(tty, s.st_mode | S_IWGRP) == -1) {
			perror(tty);
			return ERROR_OCCURED;
		}
		return RECEIVING_MSG_ALLOWED;
	case 'n':
		if(chmod(tty, s.st_mode & ~S_IWGRP) == -1) {
			perror(tty);
			return ERROR_OCCURED;
		}
		return RECEIVING_MSG_NOT_ALLOWED;
	}

	usage();
	
	return ERROR_OCCURED;
}
