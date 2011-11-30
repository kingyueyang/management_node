/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  log library
 *
 *        Version:  1.0
 *        Created:  11/30/2011 04:26:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YueYang (feinno), yueyang@feinno.com
 *        Company:  FCT
 *
 * =====================================================================================
 */


#include "log.h"

void
log(const char* tag, const char* message) {
    time_t now;
    time(&now);
    printf("%s [%s]: %s\n", ctime(&now), tag, message);
}

#ifdef DEBUG
int
main ( int argc, char *argv[] ) {
    log("redis", "crash");
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
#endif

