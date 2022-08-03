#ifndef MODULES_LOGIN_AUTHENTICATION_LOGIN_AUTH
#define MODULES_LOGIN_AUTHENTICATION_LOGIN_AUTH

#include "hpcf_module_header.h"
/*
所解析的json格式如下：
1. 客户端发送
{
    "Header": {
        "Version": 1,
        "User": "auser",
        "Announce": "1234567890123456",
        "SessionID": "",
        "RequestType": "Session"
    },
    "Body": {
        "Processor": "SessionRequest1",
        "RequestMessage": "1234567890123456"
    }
}

2. 服务器返回
{
    "Header": {
        "Version": 1,
        "User": "auser",
        "Announce": "1234567890123456",
        "SessionID": "",
        "RequestType": "Session"
    },
    "Body": {
        "Processor": "SessionResponse1",
        "ResponseMessage": {
            "Status": {
                "Code": 0,
                "Message": "OK"
            },
            "Data": "1234567890123456"
        }
    }
}

*/

struct login_auth_header {
    int version;
    char user[32];
    char announce[32];
    char session_id[32];
    char request_type[32];
};

struct login_auth_req {
    struct login_auth_header h;
    struct req_body {
        char processor[32];
        struct req_data {
            char req_msg[1024];
        }d;
    }b;
};

struct login_auth_result {
    struct login_auth_header h;
    struct res_body {
        char processor[32];
        struct status {
            int result;
            char result_msg[1024];
        }s;
        struct res_data {
            char ran_or_sess[64];
        }d;
    }b;
};

int hpcf_module_lib_init(struct hpcf_processor_module *module);

int login_auth_processor_callback(char *in, int in_size, char *out, int *out_size,
            void **module_data, void **conn_data,
            hpcf_module_get_another_processor_callback_t get_another_processor);

int login_auth_parse_req(char *in, int in_size, struct login_auth_req *req);

int login_auth_construct_result(struct login_auth_result *result, char **out, int *out_size);

int login_auth_get_sessionid(struct login_auth_req *req, void *module_data, void *conn_data, char *out, int *out_size);

int login_auth_verify_sessionid(struct login_auth_req *req, char *session_id, void *module_data, char *out, int *out_size);

int login_auth_gen_32_random_string(char *data);

#endif /* MODULES_LOGIN_AUTHENTICATION_LOGIN_AUTH */
