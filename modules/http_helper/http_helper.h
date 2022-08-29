#ifndef MODULES_HTTP_HELPER_HTTP_HELPER
#define MODULES_HTTP_HELPER_HTTP_HELPER

#include "hpcf_module_header.h"
#include "llhttp.h"

enum http_helper_type {
    HTTP_PARSER = 0,
    HTTP_BUILDER = 1,
};

struct http_helper_t {
    // 当type为HTTP_PARSER时，in为http报文，out为解析后的body
    // 当type为HTTP_BUILDER时，in为body，out为http报文
    char *data;
    int data_size;
    http_helper_type type;
};

struct http_parser_t {
    llhttp_t parser;
    llhttp_settings_t settings;
    char *body;
    int body_size;
};


int hpcf_module_lib_init(struct hpcf_processor_module *module);

int http_helper_processor_callback(char *in, int in_size, char **out, int *out_size,
            void **module_data, void **conn_data,
            hpcf_module_get_another_processor_callback_t get_another_processor);

#endif /* MODULES_HTTP_HELPER_HTTP_HELPER */
