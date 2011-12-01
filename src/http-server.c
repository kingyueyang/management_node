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

int
main ( int argc, char *argv[] ) {
    struct event_base *base;
    struct evhttp *http;
    struct evhttp_bound_socket *handle;

    unsigned short port = PORT;

    /* As you konw */
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        return (1);

    /* Create a new base evObject */
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

    /* The /get will be output to 1 and say 200 ok. */
    evhttp_set_cb(http, "/get", test_request_cb, NULL);

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

static void
other_cb(struct evhttp_request *req, void *arg) {
    printf("other path\n");
    evhttp_send_reply(req, 400, "olo", NULL);
}

static void
test_request_cb(struct evhttp_request *req, void *arg) {
    struct evbuffer *buf = evbuffer_new();

    if (EVHTTP_REQ_GET != evhttp_request_get_command(req)) {
        evhttp_send_reply(req, 500, "not support this method", NULL);
        /*log it*/
        printf("inot support this method\n");
        return;
    }

    /*
     *TODO: log received a right GET message
     */
    static char test_char[] = 
        "ok, you get this message";
    char *msg = NULL;
    gen_data(&msg);
    /*printf("%s\n", msg);*/

    evbuffer_add(buf, msg, sizeof(test_char) - 1);
    evhttp_send_reply(req, 200, "OK", buf);
    printf("test get\n");

    free(msg);
    evbuffer_free(buf);
}

static int
gen_data(char **r_data) {
    *r_data = malloc(4);
    /*
     *Test data
     */
    char tmp[] = "yy.";
    sprintf(*r_data, tmp);

    return 0;
}
