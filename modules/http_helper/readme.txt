此模块用来供其他模块对报文进行解析
外部需要将数据填充到以下结构：
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

在调用此模块的回调函数时，将http_helper_t的指针作为参数in传入