#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "remote_task.h"

int hpcf_module_lib_init(struct hpcf_processor_module *module)
{
    int ret = 0;
    // 本函数填充 type data 和 callback即可，其它的不用管
    module->type = HPCF_MODULE_TYPE_REMOTE_TASK;
    module->data = NULL;
    module->callback = &remote_task_processor_callback;

    return ret;
}

int remote_task_processor_callback(char *in, int in_size, char **out, int *out_size,
            void **module_data, void **conn_data,
            hpcf_module_get_another_processor_callback_t get_another_processor)
{
    int ret = 0;

    // in 是上层调用构造的请求数据，如果是json的话，这里可能需要在外面加上一个http头
    // 目前这里不加，由上层调用者自己加
    // 此函数内部只负责发送请求和接收响应

    // 1. 创建socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return -1;
    }

    // 2. 连接服务器
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9899);
    // server addr test 127.0.0.1
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        return -1;
    }

    // 3. 发送请求
    if (send(sockfd, in, in_size, 0) < 0) {
        perror("send");
        return -1;
    }

    // 4. 接收响应
    // 一直接收，直到没有数据为止
    char buf[1024] = {0};
    int recv_size = 0;
    int total_size = 0;
    *out = malloc(10);
    while ((recv_size = recv(sockfd, buf, sizeof(buf), 0)) > 0) {
        total_size += recv_size;
        *out = realloc(*out, total_size + 1);
        memset(*out + total_size - recv_size, 0, recv_size + 1);
        memcpy(*out + total_size - recv_size, buf, recv_size);
    }

    *out_size = total_size;

    // 5. 关闭socket
    close(sockfd);

    return ret;
}