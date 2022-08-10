#ifndef MODULES_CONFIG_SYNC_CONFIG_SYNC
#define MODULES_CONFIG_SYNC_CONFIG_SYNC

#include "hpcf_module_header.h"

/*
报文格式

最好不要使用GetAllConfig，谁也不知道数据有多大，这样可能内存会不够用，
使用GetMultipleConfig,分段的去拿数据，每次只拿一部分，内存不会太大。
请求报文
{
    "Header": {
        "Version": 1,
        "User": "auser",
        "Announce": "1234567890123456",
        "SessionID": "1234567890123456",
        "RequestType": "ConfigSync"
    },
    "Body": {
        "Processor": "GetOneConfig",
        "Scope": {
            "Start": 0,
            "Count": 1
        }
    }
或
    "Body": {
        "Processor": "GetMultipleConfig",
        "Scope": {
            "Start": 0,
            "Count": 10
        }
    }
或
    "Body": {
        "Processor": "GetAllConfig",
        "Scope": {
            "Start": 0,
            "Count": -1
        }
    }
}

响应报文
{
    "Header": {
        "Version": 1,
        "User": "auser",
        "Announce": "1234567890123456",
        "SessionID": "1234567890123456",
        "RequestType": "ConfigSync"
    },
    "Body": {
        "Processor": "GetOneConfig",
        "Scope": {
            "Start": 0, // 实际位置和实际个数
            "Count": 1
        },
        "ConfigData": "ConfigData"
    }
或
    "Body": {
        "Processor": "GetMultipleConfig",
        "Scope": {
            "Start": 0,
            "Count": 10
        },
        "ConfigData": "ConfigData"
    }
或
    "Body": {
        "Processor": "GetAllConfig",
        "Scope": {
            "Start": 0,
            "Count": -1
        },
        "ConfigData": "ConfigData"
    }
}
*/


int hpcf_module_lib_init(struct hpcf_processor_module *module);

// 只应用于少量数据的同步或下载，不然会导致框架阻塞过长
int config_sync_processor_callback(char *in, int in_size, char **out, int *out_size,
            void **module_data, void **conn_data,
            hpcf_module_get_another_processor_callback_t get_another_processor);

#endif /* MODULES_CONFIG_SYNC_CONFIG_SYNC */
