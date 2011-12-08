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

    /*
     * The path /get support get method, it saved sharding configure
     * When GET /get will be return configure xml, and 200 OK
     */
    evhttp_set_cb(http, "/get", get_config_cb, NULL);

    /*
     * The path /post support post method
     * When sharding node need to be grant, it can post request
     */
    evhttp_set_cb(http, "/post", post_grant_cb, NULL);

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
    printf("Other Path\n");
    evhttp_send_reply(req, 400, "olo", NULL);
    return;
}

static void
get_config_cb(struct evhttp_request *req, void *arg) {
    struct evbuffer *buf = evbuffer_new();

    if (EVHTTP_REQ_GET != evhttp_request_get_command(req)) {
        evhttp_send_reply(req, 500, "not support this method", NULL);
        /*log it*/
        printf("/get Not Support This Method\n");
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

static void
post_grant_cb(struct evhttp_request *req, void *arg) {
    struct evbuffer *buf;
    char cbuf[4];
    char *buffer = NULL;

    printf("POST Request\n");

    if (EVHTTP_REQ_POST != evhttp_request_get_command(req)) {
        evhttp_send_reply(req, 500, "not support this method", NULL);
        /*log it*/
        printf("/post not support this method\n");
        return;
    }

    buf = evhttp_request_get_input_buffer(req);
    size_t sz = evbuffer_get_length(buf);

    buffer = malloc(sz);
    if (NULL == buffer) {
        evhttp_send_reply(req, 500, "alloc memroy error", NULL);
        return ;
    }

    /* Init temp buffer */
    memset(buffer, 0, sz);
    while (evbuffer_get_length(buf)) {
        int n;
        n = evbuffer_remove(buf, cbuf, sizeof(buf)-1);
        strcat(buffer, cbuf);
    }
    parser(buffer, sz);

    free(buffer);
    buffer = NULL;

    evhttp_send_reply(req, 200, "OK", NULL);
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

    /* Set seek to beginbing */
    fseek(fp, 0L, SEEK_SET);

    /* Read file */
    size_t rc = fread(*r_data, file_size, 1, fp);

    fclose(fp);
    fp = NULL;

    return 0;
}

static void
parser(char *buf, size_t size) {
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;

    /* Init Root Node */
    xmlKeepBlanksDefault(0);

    doc = xmlParseMemory(buf, size);
    if (NULL == doc) {
        xmlCleanupParser();
    }

    cur = xmlDocGetRootElement(doc);
    if (NULL == cur) {
        xmlFreeDoc(doc);
        xmlCleanupParser();
    }

    /* Init child pointer */
    char *name = NULL;
    xmlChar *content = NULL;

    if (cur->type != XML_ELEMENT_NODE) {
        goto CLEANUP;
    }

    cur = cur->xmlChildrenNode;

    while (cur != NULL) {
        name = (char*)(cur->name); 
        content = xmlNodeGetContent(cur);
        printf("%s:", name);
        printf("%s\n", content);
        cur = cur->next;
    }
    printf("\n");

    /*TODO: insert to queue*/
    /*xmlDocDump(stdout, doc);*/

CLEANUP:
    if (content) {
        xmlFree(content);
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();

    return ;
}

