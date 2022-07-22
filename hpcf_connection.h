#ifndef HPCF_CONNECTION
#define HPCF_CONNECTION

#include "hpcf_event.h"

// 应有一个链表，保存所有的连接
struct hpcf_connection {
    struct list_head list;
    struct hpcf_event *read_event;
    struct hpcf_event *write_event;

    int fd;
    char *buffer;   // 用来存储读取/处理结果的数据
};

struct hpcf_connection *hpcf_new_connection(int fd,
                                             hpcf_event_callback_t read_callback,
                                             hpcf_event_callback_t write_callback,
                                             int accept);

void hpcf_close_connection(struct hpcf_connection *conn);

void hpcf_free_connection(struct hpcf_connection *conn);

#endif /* HPCF_CONNECTION */