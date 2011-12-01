/*
 * =====================================================================================
 *
 *       Filename:  http-server.h
 *
 *    Description:  receive POST and RESPONE it
 *
 *        Version:  1.0
 *        Created:  11/30/2011 09:46:32 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YueYang (feinno), yueyang@feinno.com
 *        Company:  FCT
 *
 * =====================================================================================
 */

#ifndef _HTTP_SERVER_H_
#define _HTTP_SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/keyvalq_struct.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "log.h"

#define	PORT 8888			/* Listening port */

static void test_request_cb(struct evhttp_request *req, void *arg);
static void other_cb(struct evhttp_request *req, void *arg);
static int gen_data(char **r_data);

#endif
