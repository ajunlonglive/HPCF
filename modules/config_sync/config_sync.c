#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "config_sync.h"


int hpcf_module_lib_init(struct hpcf_processor_module *module)
{
    int ret = 0;

    module->type = HPCF_MODULE_TYPE_CONFIG_SYNC;
    // 此模块不需要分配内存
    module->data = NULL;
    module->callback = config_sync_processor_callback;

    return ret;
}

int config_sync_processor_callback(char *in, int in_size, char **out, int *out_size,
            void **module_data, void **conn_data,
            hpcf_module_get_another_processor_callback_t get_another_processor)
{
    int ret = 0;

    return ret;
}