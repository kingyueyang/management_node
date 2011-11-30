/*
 * =====================================================================================
 *
 *       Filename:  http_server.c
 *
 *    Description:  receive POST and RESPONE it
 *
 *        Version:  1.0
 *        Created:  11/29/2011 11:23:03 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YueYang (feinno), yueyang@feinno.com
 *        Company:  FCT
 *
 * =====================================================================================
 */

#include "http-server.h"

static void
test_request_cb(struct evhttp_request *req, void *arg) {
    printf("test request\n");
    evhttp_send_reply(req, 200, "OK", NULL);
}

static void
other_cb(struct evhttp_request *req, void *arg) {
    printf("other request\n");
    evhttp_send_reply(req, 200, "OK", NULL);
}

static void
syntax(void) {
    fprintf(stdout, "Syntax: http_server <docroot>\n");
}

int
main ( int argc, char *argv[] ) {
    struct event_base *base;
    struct evhttp *http;
    struct evhttp_bound_socket *handle;

    unsigned short port = PORT;

    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        return (1);

    if (argc < 2) {
        syntax();
        return 1;
    }

    base = event_base_new();
    if (!base) {
        fprintf(stderr, "Couldn't create an event_base: exiting\n");
        return 1;
    }

    /* Create a new evhttp object to handle requests. */
    http = evhttp_new(base);
    if (!http) {
        fprintf(stderr, "couldn't create evhttp. Exiting.\n");
        return 1;
    }

    /* The /post will be output to 1 and say 200 ok. */
    evhttp_set_cb(http, "/post", test_request_cb, NULL);

    /* We want to accept arbitrary requests, so we need to set a "generic"
     * cb.  We can also add callbacks for specific paths. */
    evhttp_set_gencb(http, other_cb, NULL);

    /* Now we tell the evhttp what port to listen on */
    handle = evhttp_bind_socket_with_handle(http, "0.0.0.0", port);

    if (!handle) {
        fprintf(stderr, "couldn't bind to port %d. Exiting.\n",
                (int)port);
        return 1;
    }

    event_base_dispatch(base);

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

