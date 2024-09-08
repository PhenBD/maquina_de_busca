#include "../headers/utils.h"

void TST_id_destroy(void *id) {
    free(id);
}

void TST_foward_list_destroy(void *list) {
    for (int i = 0; i < forward_list_size(list); i++)
    {
        if (forward_list_get(list, i) != NULL)
        {
            free(forward_list_get(list, i));
        }
    }
    forward_list_destroy(list);
}

int strings_compare(data_type data, void *key){
    char *a = (char *)data;
    char *b = (char *)key;

    return strcmp(a, b);
}