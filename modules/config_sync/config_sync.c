#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "config_sync.h"
#include "parson.h"

int parse_config_sync_json(char *in, int in_size, struct config_sync_body *body_out)
{
    int ret = 0;

    JSON_Value *root_value = NULL;
    JSON_Object *root_object = NULL;

    root_value = json_parse_string(in);
    if (root_value == NULL) {
        return -1;
    }

    root_object = json_value_get_object(root_value);
    if (root_object == NULL) {
        ret = -1;
        goto out;
    }

    // 解析body
    JSON_Object *body = json_object_get_object(root_object, "Body");
    char *s = (char *)json_object_get_string(body, "Processor");
    if (strcmp(s, "AddOneConfig") == 0) {
        body_out->processor = ADD_ONE_CONFIG;
    } else if (strcmp(s, "DelOneConfig") == 0) {
        body_out->processor = DEl_ONE_CONFIG;
    } else if (strcmp(s, "ModifyOneConfig") == 0) {
        body_out->processor = MODIFY_ONE_CONFIG;
    } else if (strcmp(s, "GetOneConfig") == 0) {
        body_out->processor = GET_ONE_CONFIG;
    } else if (strcmp(s, "GetAllConfig") == 0) {
        body_out->processor = GET_ALL_CONFIG;
    } else if (strcmp(s, "CreadAddOneConfig") == 0) {
        body_out->processor = CREATE_ADD_ONE_CONFIG_REQUEST;
    } else if (strcmp(s, "CreadDelOneConfig") == 0) {
        body_out->processor = CREATE_DEL_ONE_CONFIG_REQUEST;
    } else if (strcmp(s, "CreadModifyOneConfig") == 0) {
        body_out->processor = CREATE_MODIFY_ONE_CONFIG_REQUEST;
    } else if (strcmp(s, "CreadGetOneConfig") == 0) {
        body_out->processor = CREATE_GET_ONE_CONFIG_REQUEST;
    } else if (strcmp(s, "CreadGetAllConfig") == 0) {
        body_out->processor = CREATE_GET_ALL_CONFIG_REQUEST;
    } else {
        body_out->processor = 0;
    }
    s = (char *)json_object_dotget_string(body, "Item.Type");
    strcpy(body_out->type, s);
    s = (char *)json_object_dotget_string(body, "Item.Data");
    if (s != NULL) {
        body_out->data = (char *)malloc(strlen(s) + 1);
        strcpy(body_out->data, s);
    }

out:
    json_value_free(root_value);
    return ret;
}

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

    struct config_sync_body body = {0};

    ret = parse_config_sync_json(in, in_size, &body);

    char *out_buf = NULL;
    int out_buf_size = 0;

    switch(body.processor) {
        case ADD_ONE_CONFIG:
            ret = add_one_config(body.type, body.data, &out_buf, &out_buf_size);
            break;
        case DEl_ONE_CONFIG:
            ret = del_one_config(body.type, body.data, &out_buf, &out_buf_size);
            break;
        case MODIFY_ONE_CONFIG:
            ret = modify_one_config(body.type, body.data, &out_buf, &out_buf_size);
            break;
        case GET_ONE_CONFIG:
            ret = get_one_config(body.type, body.data, out, out_size);
            break;
        case GET_ALL_CONFIG:
            ret = get_all_config(body.type, out, out_size);
            break;
        case CREATE_ADD_ONE_CONFIG_REQUEST:
            ret = create_add_one_config_request(body.type, body.data, &out_buf, &out_buf_size);
            break;
        case CREATE_DEL_ONE_CONFIG_REQUEST:
            ret = create_del_one_config_request(body.type, body.data, &out_buf, &out_buf_size);
            break;
        case CREATE_MODIFY_ONE_CONFIG_REQUEST:
            ret = create_modify_one_config_request(body.type, body.data, &out_buf, &out_buf_size);
            break;
        case CREATE_GET_ONE_CONFIG_REQUEST:
            ret = create_get_one_config_request(body.type, body.data, &out_buf, &out_buf_size);
            break;
        case CREATE_GET_ALL_CONFIG_REQUEST:
            ret = create_get_all_config_request(body.type, &out_buf, &out_buf_size);
            break;
        default:
            ret = -1;
            break;
    }


    if (body.data != NULL) {
        free(body.data);
    }
    return ret;
}