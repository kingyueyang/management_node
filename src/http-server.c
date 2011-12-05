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
    return;
}

static void
test_request_cb(struct evhttp_request *req, void *arg) {
    struct evbuffer *buf = evbuffer_new();

    if (EVHTTP_REQ_GET != evhttp_request_get_command(req)) {
        evhttp_send_reply(req, 500, "not support this method", NULL);
        /*log it*/
        printf("not support this method\n");
        evbuffer_free(buf);
        return;
    }

    static char test_char[] = 
        "ok, you get this message";
    char *msg = NULL;
    gen_data(&msg);
    printf("out: %s\n", msg);

    evbuffer_add(buf, msg, strlen(msg));
    evhttp_send_reply(req, 200, "OK", buf);
    printf("test get\n");
    printf("====================\n");

    evbuffer_free(buf);
    free(msg);
    msg = NULL;
    return ;
}

static int
gen_data(char **r_data) {
    FILE *fp = NULL;
    long file_size;
    size_t sz; 

    /* Get file size */
    fp = fopen("./data/node_conf.xml", "r");
    if (NULL == fp) {
        fprintf(stderr, "Open file failed.\n");
        return -1;
    }
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);

    *r_data = malloc(file_size+1);

    PRINT(file_size);

    /* Set seek to beginbing */
    fseek(fp, 0L, SEEK_SET);

    /* Read file */
    size_t rc = fread(*r_data, file_size, 1, fp);

    fclose(fp);
    fp = NULL;

    return 0;
}

