#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "hpcf_list_helper.h"
#include "http_parse.h"

int get_body(llhttp_t *parser, const char *at, size_t length)
{
	struct http_parse_result *result = container_of(parser, struct http_parse_result, parser);

    result->body = malloc(length + 1);
	memset(result->body, 0, length + 1);
	strncpy(result->body, at, length);
    result->body_len = length;
	return 0;
}

// 解析http请求报文，就是解析body内容
int config_sync_parse_http_req(char *http_req, int http_req_len, struct http_parse_result *result)
{
    llhttp_settings_init(&result->settings);
    llhttp_init(&result->parser, HTTP_BOTH, &result->settings);
    result->settings.on_body = get_body;
    enum llhttp_errno err = llhttp_execute(&result->parser, http_req, http_req_len);
    return err;
}

// 构造http请求报文
int config_sync_construct_http_req(char *body, int body_len, char **http_req, int *http_req_len)
{
    char *http_req_format = "POST / HTTP/1.1\r\n"
                            "Host: %s\r\n"
                            "Content-Type: application/json\r\n"
                            "Content-Length: %d\r\n"
                            "\r\n"
                            "%s";
    
    *http_req = malloc(strlen(http_req_format) + 128 + body_len);

    sprintf(*http_req, http_req_format, "0.0.0.0:9899", body_len, body);

    *http_req_len = strlen(*http_req);

    return 0;
}