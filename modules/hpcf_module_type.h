#ifndef MODULES_HPCF_MODULE_TYPE
#define MODULES_HPCF_MODULE_TYPE

#define HPCF_MODULE_TYPE_UNKNOWN 0
#define HPCF_MODULE_TYPE_LOGIN_AUTH 1       // 登录认证模块     Session
#define HPCF_MODULE_TYPE_CONFIG_SYNC 2      // 配置同步模块     ConfigSync
#define HPCF_MODULE_TYPE_OPERATION_PROCESS 3    // 运算处理模块，赵忠亮     Operation
#define HPCF_MODULE_TYPE_KEY_MANAGER 4      // 密钥管理模块，赵忠亮     KeyManager
#define HPCF_MODULE_TYPE_USER_MANAGER 5     // 用户管理模块，梁育濣     UserManager
#define HPCF_MODULE_TYPE_REMOTE_TASK 6      // 远程任务模块，程贺明，供其它模块调用，不可直接通过接口派发
#define HPCF_MODULE_TYPE_HTTP_HELPER 7      // http帮助模块，供其它模块调用

#endif /* MODULES_HPCF_MODULE_TYPE */
