#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "http_helper.h"
#include "llhttp.h"

int get_body(llhttp_t *parser, const char *at, size_t length)
{
	struct http_parser_t *helper = container_of(parser, struct http_parser_t, parser);

    helper->body = malloc(length + 1);
	memset(helper->body, 0, length + 1);
	strncpy(helper->body, at, length);
    helper->body_size = length;
	// printf("%s\n", aaa->body);
	return 0;
}

int hpcf_http_get_body(char *in, int in_len, struct http_parser_t *helper)
{
    char *body = NULL;

    llhttp_settings_init(&helper->settings);
    llhttp_init(&helper->parser, HTTP_BOTH, &helper->settings);
    helper->settings.on_body = get_body;

    int req_len = in_len;
    enum llhttp_errno err = llhttp_execute(&helper->parser, in, req_len);

    return err;
}


int hpcf_module_lib_init(struct hpcf_processor_module *module)
{
    int ret = 0;

    // 本函数填充 type data 和 callback
    module->type = HPCF_MODULE_TYPE_HTTP_HELPER;
    module->data = NULL;
    module->callback = &http_helper_processor_callback;

    return ret;
}

int http_helper_processor_callback(char *in, int in_size, char **out, int *out_size,
            void **module_data, void **conn_data,
            hpcf_module_get_another_processor_callback_t get_another_processor)
{
    int ret = 0;

    struct http_helper_t *helper = (struct http_helper_t *)in;
    if (helper->type == HTTP_PARSER) {
        // 解析 http 请求
        struct http_parser_t par = {0};
        hpcf_http_get_body(in, helper->data_size, &par);
        *out = malloc(par.body_size + 1);
        memset(*out, 0, par.body_size + 1);
        memcpy(*out, par.body, par.body_size);
        *out_size = par.body_size;

        free(par.body);
    } else {
        // 构造 http 响应
        *out = malloc(helper->data_size + 256);
        memset(*out, 0, helper->data_size + 256);
        char * format = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n"
                        "Content-Length: %d\r\n"
                        "\r\n"
                        "%s";
        sprintf(*out, format, helper->data_size, in);
        *out_size = strlen(*out);
    }

    return ret;
}