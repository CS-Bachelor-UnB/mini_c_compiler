#include "utilities.h"

extern int errno;

/* void ERROR(char *message, unsigned int lineNum, char systemError) -- prints
 * error message then exits program with status -1
 */
void ERROR(char *message, unsigned int lineNum, char systemError) {
#ifdef DEBUG
	fprintf(stderr, "%u:", lineNum);
#endif
	if (systemError)
		perror(message);
	else
		fprintf(stderr, "ERROR: %s\n", message);

	exit(-1);
}