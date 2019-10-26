#define PROGRAM_NAME          "sync"
#define PROGRAM_VERSION       "1.0"
#define PACKAGE_NAME          "Unitrix bin"
#define COPYRIGTH_HOLDER      "Bartosz Mierzynski"
#define COPYRIGTH_YEAR        "2019"
#define LICENSE_ABBREVIATION  "none"
#define LICENSE_LINE          ""

#include <stdlib.h>
#include <unistd.h>

int main(void) {
	sync();
	return EXIT_SUCCESS;
}
