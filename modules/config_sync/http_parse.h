#ifndef MODULES_CONFIG_SYNC_HTTP_PARSE
#define MODULES_CONFIG_SYNC_HTTP_PARSE

#include "../../libhttp/llhttp.h"

struct http_parse_result {
    char *body;
    int body_len;
    llhttp_t parser;
    llhttp_settings_t settings;
};

// 解析http请求报文，就是解析body内容
int config_sync_parse_http_req(char *http_req, int http_req_len, struct http_parse_result *result);

// 构造http请求报文
int config_sync_construct_http_req(char *body, int body_len, char **http_req, int *http_req_len);

#endif /* MODULES_CONFIG_SYNC_HTTP_PARSE */
