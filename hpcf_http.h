#ifndef HPCF_HTTP
#define HPCF_HTTP

#include "hpcf_connection.h"

int hpcf_http_get_body(struct hpcf_connection *conn);

int hpcf_http_make_response(struct hpcf_connection *conn, char *body, int body_len);

#endif /* HPCF_HTTP */
