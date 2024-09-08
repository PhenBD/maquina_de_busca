#include "../headers/tst.h"

struct node {
    Value *val;
    unsigned char c;
    TST *l, *m, *r;
};

TST *TST_create_node() {
    TST *t = (TST *)malloc(sizeof(TST));
    t->val = NULL;
    t->l = t->m = t->r = NULL;
    return t;
}

TST *rec_insert(TST *t, String *key, Value val, int d) {
    unsigned char c = strings_get_char(key, d);
    if (t == NULL) { t = TST_create_node(); t->c = c;}
    if      (c < t->c) { t->l = rec_insert(t->l, key, val, d); }
    else if (c > t->c) { t->r = rec_insert(t->r, key, val, d); }
    else if (d < strings_get_len(key) - 1) {
        t->m = rec_insert(t->m, key, val, d+1);
    } else { t->val = val;  }
    return t;
}

TST *TST_insert(TST *t, String *key , Value val) {
    return rec_insert(t, key, val, 0);
}

TST* rec_search(TST* t, String* key, int d) {
    if (t == NULL) { return NULL; }
    unsigned char c = strings_get_char(key, d);
    if      (c < t->c) { return rec_search(t->l, key, d); }
    else if (c > t->c) { return rec_search(t->r, key, d); }
    else if (d < strings_get_len(key) - 1) {
        return rec_search(t->m, key, d+1);
    } else { return t; }
}

Value TST_search(TST* t, String* key) {
    t = rec_search(t, key, 0);
    if (t == NULL) { return NULL; }
    else { return t->val; }
}

int TST_contains(TST *t, String *key) {
    return TST_search(t, key) != NULL;
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

        // fix it or not
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
    char *dir = malloc(strlen(filename) + 12);
    strcpy(dir, filename);
    dir = strcat(dir, "/index.txt");

    FILE *f = fopen(dir, "r");
    if (f == NULL) { printf("Directory ""%s"" not found.\n", dir); exit(1); }

    TST *t = NULL;

    char *line = NULL;
    char delimit[] = " \t\n";

    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, f)) != -1) {
        char *pages = malloc(strlen(filename) + strlen(line) + 50);
        strcpy(pages, filename);
        strcat(pages, "/pages/");
        // probably need to fix this
        char *page_name = strtok(line, delimit);
        strcat(pages, page_name);

        FILE *page_file = fopen(pages, "r");
        if (page_file == NULL) { printf("File ""%s"" not found.\n", pages); exit(1); }

        char *line_page = NULL;

        size_t len_page = 0;
        ssize_t read_page;

        while ((read_page = getline(&line_page, &len_page, page_file)) != -1) {
            char *token = strtok(line_page, delimit);
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

        free(line_page);
        fclose(page_file);
        free(pages);
    }
    free(line);
    fclose(f);
    free(dir);
    return t;
}

void TST_destroy(TST *t, DestroyFunc destroy) {
    if (t == NULL) { return; }
    
    TST_destroy(t->l, destroy);
    TST_destroy(t->m, destroy);
    TST_destroy(t->r, destroy);

    if (t->val != NULL) { destroy(t->val); }
    
    free(t);
}


