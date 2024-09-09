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

TST *TST_create_stop_words(char *filename) {
    char *dir = malloc(strlen(filename) + 16);
    strcpy(dir, filename);
    dir = strcat(dir, "/stopwords.txt");
    
    FILE *f = fopen(dir, "r");
    if (f == NULL) { printf("Directory ""%s"" not found.\n", dir); exit(1); }

    TST *t = NULL;

    char *line = NULL;
    char delimit[] = " \t\n";

    size_t len = 0;
    ssize_t read;
    
    int count = 0;

    while ((read = getline(&line, &len, f)) != -1) {
        char *key = strtok(line, delimit);
        String *s = strings_create(key);
        int *id = (int *)malloc(sizeof(int));

        if (TST_contains(t, s)) {
            int *aux = TST_search(t, s);
            free(aux);
        }

        *id = count;
        
        t = TST_insert(t, s, id);

        strings_destroy(s);
        count++;
    }
    free(line);
    fclose(f);
    free(dir);
    return t;
}

TST *TST_create_words_table(char *filename, TST *stop_words) {
    ForwardList *list_pages = list_index_pages(filename);

    TST *t = NULL;

    while (forward_list_size(list_pages) > 0) {
        char *page_name = forward_list_pop_front(list_pages);
        char *page_directory = malloc(strlen(filename) + strlen(page_name) + 9);
        strcpy(page_directory, filename);
        strcat(page_directory, "/pages/");
        strcat(page_directory, page_name);

        FILE *page_file = fopen(page_directory, "r");
        if (page_file == NULL) { printf("File ""%s"" not found.\n", page_directory); exit(1); }

        char *line = NULL;
        char delimit[] = " \t\n";

        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, page_file)) != -1) {
            char *token = strtok(line, delimit);
            while (token != NULL) {
                if (token == NULL) { continue; }

                String *s = strings_create(token);
                strings_to_lower(s);
                
                if (!(TST_contains(stop_words, s)))
                {
                    if (!(TST_contains(t, s))) {
                    ForwardList *fl = forward_list_construct();
                    forward_list_push_back(fl, strdup(page_name));
                    t = TST_insert(t, s, fl);
                    }
                    else {
                        ForwardList *fl = TST_search(t, s);

                        if (forward_list_find(fl, page_name, strings_compare) == NULL)
                        {
                            forward_list_push_back(fl, strdup(page_name));
                        }
                    }
                }

                strings_destroy(s);
                token = strtok(NULL, delimit);
            }
        }

        free(line);
        free(page_directory);
        free(page_name);
        fclose(page_file);
    }

    forward_list_destroy(list_pages);
    return t;
}