#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "hpcf_http.h"


int get_body(llhttp_t *parser, const char *at, size_t length)
{
	struct hpcf_connection *conn = container_of(parser, struct hpcf_connection, parser);

    conn->body = malloc(length + 1);
	memset(conn->body, 0, length + 1);
	strncpy(conn->body, at, length);
	// printf("%s\n", aaa->body);
	return 0;
}

int hpcf_http_get_body(struct hpcf_connection *conn)
{
    char *body = NULL;

    llhttp_settings_init(&conn->settings);
    llhttp_init(&conn->parser, HTTP_BOTH, &conn->settings);
    conn->settings.on_body = get_body;

    int req_len = strlen(conn->read_buffer);
    enum llhttp_errno err = llhttp_execute(&conn->parser, conn->read_buffer, req_len);

    return err;
}

int hpcf_http_make_response(struct hpcf_connection *conn, char *body, int body_len)
{
    int ret = 0;

    char * format = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "Content-Length: %d\r\n"
                    "\r\n"
                    "%s";

    if (conn->write_buffer != NULL && conn->write_len > 0) {
        free(conn->write_buffer);
        conn->write_buffer = NULL;
        conn->write_len = 0;
    }

    conn->write_buffer = malloc(body_len + 256);
    memset(conn->write_buffer, 0, body_len + 256);

    ret = sprintf(conn->write_buffer, format, body_len, body);

    conn->write_len = strlen(conn->write_buffer);

    return ret;
}