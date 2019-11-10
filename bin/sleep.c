#define PROGRAM_NAME         "sleep"
#define PROGRAM_VERSION      "1.0"
#define COPYRIGTH_HOLDER     "Bartosz Mierzynski"
#define COPYRIGTH_YEAR       "2019"
#define LICENSE_ABBREVIATION "none"
#define LICENSE_LINE         ""

#include <getopt.h>
#include <locale.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage(int status) {
	printf("usage: %s time\n", PROGRAM_NAME);
	exit(status);
}

void handle(int sig) {
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
	int c;
	
	setlocale(LC_ALL, "");
	
	signal(SIGALRM, handle);
	
	while ((c = getopt(argc, argv, "")) != -1)
		switch(c) {
		case '?':
		default:
			usage(EXIT_FAILURE);
	}

	argc -= optind;

	if(argc != 1)
		usage(EXIT_FAILURE);

	sleep(strtoul(argv[1], NULL, 0));
	
	return EXIT_SUCCESS;
}
