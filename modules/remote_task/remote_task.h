#ifndef MODULES_REMOTE_TASK_REMOTE_TASK
#define MODULES_REMOTE_TASK_REMOTE_TASK

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hpcf_list_helper.h"
#include "hpcf_module_header.h"

int hpcf_module_lib_init(struct hpcf_processor_module *module);

int remote_task_processor_callback(char *in, int in_size, char **out, int *out_size,
            void **module_data, void **conn_data,
            hpcf_module_get_another_processor_callback_t get_another_processor);

#endif /* MODULES_REMOTE_TASK_REMOTE_TASK */
