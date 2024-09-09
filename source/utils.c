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

ForwardList *list_index_pages(char *filename){
    char *dir = malloc(strlen(filename) + 12);
    strcpy(dir, filename);
    dir = strcat(dir, "/index.txt");

    FILE *f = fopen(dir, "r");
    if (f == NULL) { printf("Directory ""%s"" not found.\n", dir); exit(1); }

    ForwardList *fl = forward_list_construct();

    char *line = NULL;
    char delimit[] = " \t\n";

    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, f)) != -1) {
        char *page_name = strdup(strtok(line, delimit));
        forward_list_push_back(fl, page_name);
    }

    free(dir);
    free(line);
    fclose(f);
    return fl;
}