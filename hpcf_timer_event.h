#ifndef HPCF_TIMER_EVENT
#define HPCF_TIMER_EVENT

#define RED        0    // 红色节点
#define BLACK    1    // 黑色节点

typedef unsigned long Type;

struct timer_event{
    Type key;
    void *root;         // 用来指向红黑树的根
    int interval;       // 间隔时间，单位为毫秒
    int count;          // 计数器
    int persisent;      // 是否持久化
    void *data;         // 数据，指向自己
    void (*function)(void *);   // 回调函数，参数为data，并且此函数是在定时器线程中执行的，用来处理是否有下一次定时器
    void (*event_callback)(void *); // 事件回调函数，参数为上面的函数指针，此函数是在主线程中执行的，用来处理业务逻辑
};

// 红黑树的节点
typedef struct RBTreeNode{
    unsigned char color;        // 颜色(RED 或 BLACK)
    Type   key;                    // 关键字(键值)
    struct timer_event t_event; // 定时器事件
    struct RBTreeNode *left;    // 左孩子
    struct RBTreeNode *right;    // 右孩子
    struct RBTreeNode *parent;    // 父结点
}Node, *RBTree;

// 红黑树的根
typedef struct rb_root{
    Node *node;
}RBRoot;

// 创建红黑树，返回"红黑树的根"！
RBRoot* create_rbtree();

// 销毁红黑树
void destroy_rbtree(RBRoot *root);

// 将结点插入到红黑树中。插入成功，返回0；失败返回-1。
int insert_rbtree(RBRoot *root, Type key, struct timer_event *t_event);

// 删除结点(key为节点的值)
void delete_rbtree(RBRoot *root, Type key);


// 前序遍历"红黑树"
void preorder_rbtree(RBRoot *root);
// 中序遍历"红黑树"
void inorder_rbtree(RBRoot *root);
// 后序遍历"红黑树"
void postorder_rbtree(RBRoot *root);

// (递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
int rbtree_search(RBRoot *root, Type key);
// (非递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
int iterative_rbtree_search(RBRoot *root, Type key);

// 返回最小结点的值(将值保存到val中)。找到的话，返回0；否则返回-1。
int rbtree_minimum(RBRoot *root, int *val);
// 返回最大结点的值(将值保存到val中)。找到的话，返回0；否则返回-1。
int rbtree_maximum(RBRoot *root, int *val);

Node* minimum(RBTree tree);
Node* maximum(RBTree tree);

// 打印红黑树
void print_rbtree(RBRoot *root);

// 获取当前时间，转换成微秒
Type hpcf_get_current_time();

// 创建下一个定时任务
void hpcf_create_next_timer_event(void *);

// 查找一个合适的休眼时间
int hpcf_find_sleep_time(RBRoot *root);

// 执行定时器中已经到期的定时器事件
void hpcf_execute_timer_event(RBRoot *root);

#endif /* HPCF_TIMER_EVENT */
