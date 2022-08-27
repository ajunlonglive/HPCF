#ifndef MODULES_CONFIG_SYNC_CONFIG_SYNC
#define MODULES_CONFIG_SYNC_CONFIG_SYNC

#include "hpcf_module_header.h"

/*
报文格式
需要实现4种请求用来满足单条配置的同步：
1. 增加一条配置
2. 删除一条配置
3. 获取一条配置
4. 修改一条配置
5. 获取所有配置

1 2 4 用作本机配置修改后，需要把改动同步到其它设备上
3 用作当本机缺少某条配置时，从其它设备上拉取一条配置
5 用作当某一设备上的服务启动时，从其它设备上拉取一次所有配置

注：在使用以下结构时，要删除其中的注释，标准的json格式不允许有注释

请求报文1
{
    "Header": {
        "Version": 1,
        "User": "auser",
        "Announce": "1234567890123456",
        "SessionID": "1234567890123456",
        "RequestType": "ConfigSync"
    },
    "Body": {
        "Processor": "AddOneConfig",
        "Item": {
            # 指定哪个配置文件
            "Type": "ConfigType",
            # 要增加的数据内容，如：user=chm 或其它内容，此内容的格式由配置库的实现决定
            "Data": "ConfigData"
        }
    }
}
响应报文1
{
    "Header": {
        "Version": 1,
        "User": "auser",
        "Announce": "1234567890123456",
        "SessionID": "1234567890123456",
        "RequestType": "ConfigSync"
    },
    "Body": {
        "Processor": "AddOneConfig",
        "Result": {
            # 0表示成功，其它表示失败
            "Code": 0,
            # 错误信息
            "Message": "OK",
            # 在添加成功时，可返回添加的配置的ID或其它信息，由开发者决定
            "Data": ""
        },
    }
}

=====================================================
请求报文2
{
    "Header": {
        "Version": 1,
        "User": "auser",
        "Announce": "1234567890123456",
        "SessionID": "1234567890123456",
        "RequestType": "ConfigSync"
    },
    "Body": {
        "Processor": "DelOneConfig",
        "Item": {
            # 指定哪个配置文件
            "Type": "ConfigType",
            # 要删除数据的搜索条件或其它信息，如：user=chm 或其它内容，此内容的格式由配置库的实现决定
            # 类似数据库的where语句
            "Data": "ConfigData"
        }
    }
}
响应报文2
{
    "Header": {
        "Version": 1,
        "User": "auser",
        "Announce": "1234567890123456",
        "SessionID": "1234567890123456",
        "RequestType": "ConfigSync"
    },
    "Body": {
        "Processor": "DelOneConfig",
        "Result": {
            # 0表示成功，其它表示失败
            "Code": 0,
            # 错误信息
            "Message": "OK",
            # 在删除成功时，可返回删除的配置的ID或其它信息，由开发者决定
            "Data": ""
        },
    }
}

=====================================================
请求报文3
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
        "Item": {
            # 指定哪个配置文件
            "Type": "ConfigType",
            # 要获取数据的搜索条件或其它信息，如：user=chm 或其它内容，此内容的格式由配置库的实现决定
            # 类似数据库的where语句
            "Data": "ConfigData"
        }
    }
}
响应报文3
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
        "Result": {
            # 0表示成功，其它表示失败
            "Code": 0,
            # 错误信息
            "Message": "OK",
            # 在获取成功时，返回获取的配置的内容，由开发者决定
            "Data": ""
        },
    }
}

=====================================================
请求报文4
{
    "Header": {
        "Version": 1,
        "User": "auser",
        "Announce": "1234567890123456",
        "SessionID": "1234567890123456",
        "RequestType": "ConfigSync"
    },
    "Body": {
        "Processor": "ModifyOneConfig",
        "Item": {
            # 指定哪个配置文件
            "Type": "ConfigType",
            # 要修改数据的搜索条件或其它信息，如：user=chm 或其它内容，此内容的格式由配置库的实现决定
            "Data": "ConfigData"
        }
    }
}
响应报文4
{
    "Header": {
        "Version": 1,
        "User": "auser",
        "Announce": "1234567890123456",
        "SessionID": "1234567890123456",
        "RequestType": "ConfigSync"
    },
    "Body": {
        "Processor": "ModifyOneConfig",
        "Result": {
            # 0表示成功，其它表示失败
            "Code": 0,
            # 错误信息
            "Message": "OK",
            # 在修改成功时，返回修改的配置的ID或其它信息，由开发者决定
            "Data": ""
        },
    }
}

=====================================================
请求报文5
{
    "Header": {
        "Version": 1,
        "User": "auser",
        "Announce": "1234567890123456",
        "SessionID": "1234567890123456",
        "RequestType": "ConfigSync"
    },
    "Body": {
        "Processor": "GetAllConfig",
        "Item": {
            # 指定哪个配置文件
            "Type": "ConfigType",
            # 由于要获取全部配置，此处的Data字段可不填
            "Data": ""
        }
    }
}
响应报文5
{
    "Header": {
        "Version": 1,
        "User": "auser",
        "Announce": "1234567890123456",
        "SessionID": "1234567890123456",
        "RequestType": "ConfigSync"
    },
    "Body": {
        "Processor": "GetAllConfig",
        "Result": {
            # 0表示成功，其它表示失败
            "Code": 0,
            # 错误信息
            "Message": "OK",
            # 在获取成功时，返回获取的配置的内容，由开发者决定
            "Data": ""
        },
    }
}
*/


int hpcf_module_lib_init(struct hpcf_processor_module *module);

// 只应用于少量数据的同步或下载，不然会导致框架阻塞过长
int config_sync_processor_callback(char *in, int in_size, char **out, int *out_size,
            void **module_data, void **conn_data,
            hpcf_module_get_another_processor_callback_t get_another_processor);

#endif /* MODULES_CONFIG_SYNC_CONFIG_SYNC */
