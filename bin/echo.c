#define PROGRAM_NAME          "echo"
#define PROGRAM_VERSION       "1.0"
#define PACKAGE_NAME          "bin"
#define COPYRIGTH_HOLDER      "Bartosz Mierzynski"
#define COPYRIGTH_YEAR        "2019"
#define LICENSE_ABBREVIATION  "none"
#define LICENSE_LINE          ""

#if !defined(ECHO_GNU)  \
 || !defined(ECHO_SYSV) \
 || !defined(ECHO_BSD)  \
 || !defined(ECHO_UNIX)
#define ECHO_GNU
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

typedef enum {
	FLAG_TRAILING_NEWLINE  = 1<<0,
	FLAG_SPACES            = 1<<1,
	FLAG_INTERPRET_ESCAPES = 1<<2
} flags_t;

void usage(int status) {
	printf(
#if defined(ECHO_GNU) || defined(ECHO_SYSV)
	"usage: %s [SHORT-OPTION]... [STRING]...\n"
#else
	"usage: %s [STRING]...\n"
#endif /* defined(ECHO_GNU) || defined(ECHO_SYSV) */
#ifdef ECHO_GNU
	"       %s [LONG-OPTION]\n",
#endif /* ECHO_GNU */
	PROGRAM_NAME
#ifdef ECHO_GNU
	, PROGRAM_NAME
#endif /* ECHO_GNU */
	);
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

int isoct(char c) {
	return c >= '0' && c <= '7';
}

int xdigit2int(char c) {
	switch (c) {
	default: 
		return c - '0';
	case 'a':
	case 'A':
		return 10;
	case 'b':
	case 'B':
		return 11;
	case 'c':
	case 'C':
		return 12;
	case 'd':
	case 'D':
		return 13;
	case 'e':
	case 'E':
		return 14;
	case 'f': 
	case 'F':
		return 15;
	}
}

int print_escaped(char *s){
	int c, i, status = 0;
	
	for(i = 0; s[i]; ++i) {
		if(s[i] == '\\') {
			if (s[i+1]) {
				switch(s[i+1]) {
				case 'a':
					c = '\a';
					break;
				case 'b':
					c = '\b';
					break;
				case 'c':
					exit(EXIT_SUCCESS);
					break;
#ifdef ECHO_GNU
				case 'e':
					c = '\033';
					break;
#endif /* ECHO_GNU */
				case 'f':
					c = '\f';
					break;
				case 'n':
					c = '\n';
					break;
				case 'r':
					c = '\r';
					break;
				case 't':
					c = '\t';
					break;
				case 'v':
					c = '\v';
					break;		
				case '\\':
					c = '\\';
					break;
				case '0':
					if(isoct(s[i+2])) {
						if(isoct(s[i+3])) {
							if(isoct(s[i+4])) {
								c =
								((s[i+2] - '0')*8*8)
								+ ((s[i+3] - '0')*8)
								+ (s[i+4] - '0');
								i+=3;
							} else {
								c = 
								((s[i+2] - '0')*8)
								+ (s[i+3] - '0');
								i+=2;
							}
						} else {
							c = s[i+2] - '0';
							++i;
						}
					} else {
						c = '\0';
					}	
					break;
#ifdef ECHO_GNU
				case 'x':
					if(isxdigit(s[i+2])) {
						if(isxdigit(s[i+3])) {
							c =
							(xdigit2int(s[i+2])*16)
							+ xdigit2int(s[i+3]);
							i+=2;
						} else {
							c = xdigit2int(s[i+2]);
							++i;
						}
					} else {
						putchar('\\');
						c = 'x';
					}
					break;
#endif /* ECHO_GNU */
				default:
					/*unknown format*/
					status = 1;
					putchar('\\');
					c = s[i+1];
				}
				++i;
			} else {
				/*expecting format*/
				status = 2;
				c = '\\';
			}
		} else {
			c = s[i];
		}
		putchar(c);
	}
	return status;
}



int main(int argc, char **argv) {
	int i, status = 0;
	flags_t flags = FLAG_SPACES|FLAG_TRAILING_NEWLINE;
#ifdef ECHO_SYSV
	flags |= FLAG_INTERPRET_ESCAPES;
#endif /* ECHO_SYSV */

	setlocale(LC_ALL, "");

	--argc;
	++argv;
	
#if defined(ECHO_GNU)
	if(argc == 1) {
		if(strcmp(argv[0], "--help") == 0)
			usage(EXIT_SUCCESS);	
		else if(strcmp(argv[0], "--version") == 0)
			version(PROGRAM_NAME, PROGRAM_VERSION);	
	}
	while(argc > 0 && *argv[0] == '-') {
		for(i = 1; argv[0][i] && i; ++i) {
			switch(argv[0][i]) {
			case 'E':
			case 'e':
			case 'n':
			case 's':
				break;
			default:
				i = 0;
			}
		}
		
		if(!i)
			break;
		
		for(i = 1; argv[0][i]; ++i)
			switch(argv[0][i]) {
			case 'E':
				flags &= ~FLAG_INTERPRET_ESCAPES;
				break;
			case 'e':
				flags |= FLAG_INTERPRET_ESCAPES;
				break;
			case 'n':
				flags &= ~FLAG_TRAILING_NEWLINE;
				break;
			case 's':
				flags &= ~FLAG_SPACES;
				break;
			}
		
		--argc;
		++argv;
	}
#elif defined(ECHO_BSD)	
	if(argc >= 1)
		if (strcmp(argv[0], "-n") == 0) {
			flags &= ~FLAG_TRAILING_NEWLINE;
			--argc;
			++argv;
		}
#endif
	
	for(i = 0; i < argc; ++i) {
		if(flags & FLAG_INTERPRET_ESCAPES)
			status = print_escaped(argv[i]);	
		else
			status = fputs(argv[i], stdout);
		
		if(flags & FLAG_SPACES)				
			if(i < argc-1)
				putchar(' ');
	}
	
	if(flags & FLAG_TRAILING_NEWLINE)
		putchar('\n');
	
	return status ? status : EXIT_SUCCESS;
}
