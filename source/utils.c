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

void TST_page_rank_destroy(void *pr) {
    Page_Rank *page_rank = (Page_Rank *)pr;
    page_rank_destroy(page_rank);
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
        strings_to_lower(s);
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

TST *TST_create_pr(char *filename){
    TST *pr = NULL;

    char *dir = malloc(strlen(filename) + 16);
    strcpy(dir, filename);
    dir = strcat(dir, "/graph.txt");
    
    FILE *f = fopen(dir, "r");
    if (f == NULL) { printf("Directory ""%s"" not found.\n", dir); exit(1); }

    int count = 0;
    while (!feof(f))
    {
        char line[256];
        int n;
        fscanf(f, "%s %d", line, &n);
        String *s = strings_create(line);
        if (!(TST_contains(pr, s)))
        {
            Page_Rank *node = page_rank_create();
            for (int i = 0; i < n; i++)
            {
                fscanf(f, "%s", line);
                page_rank_insert_out(node, line);

                String *page = strings_create(line);
                if (!(TST_contains(pr, page)))
                {
                    Page_Rank *aux = page_rank_create();
                    page_rank_insert_in(aux, strings_get_string(s));
                    pr = TST_insert(pr, page, aux);
                }
                else
                {
                    Page_Rank *aux = TST_search(pr, page);
                    page_rank_insert_in(aux, strings_get_string(s));
                }
                strings_destroy(page);
            }
            fscanf(f, "\n");

            pr = TST_insert(pr, s, node);
        }
        else{
            Page_Rank *node = TST_search(pr, s);
            for (int i = 0; i < n; i++)
            {
                fscanf(f, "%s", line);
                page_rank_insert_out(node, line);

                String *page = strings_create(line);
                if (!(TST_contains(pr, page)))
                {
                    Page_Rank *aux = page_rank_create();
                    page_rank_insert_in(aux, strings_get_string(s));
                    TST_insert(pr, page, aux);
                }
                else
                {
                    Page_Rank *aux = TST_search(pr, page);
                    page_rank_insert_in(aux, strings_get_string(s));
                }
                strings_destroy(page);
            }
            fscanf(f, "\n");
        }

        count++;
        strings_destroy(s);
    }

    fclose(f);
    free(dir);
    
    pr = page_ranking(pr, filename);

    return pr;
}

TST *page_ranking(TST *pr, char *filename){
    ForwardList *pages = list_index_pages(filename);
    
    float a = 0.85;
    int n = forward_list_size(pages);
    for (int i = 0; i < n; i++) { 
        char *s = forward_list_get(pages, i);
        String *page = strings_create(s);
        Page_Rank *page_rank = TST_search(pr, page);
        page_rank_set_val(page_rank, 1.0 / n);
        page_rank_set_old_val(page_rank, 1.0 / n);
        strings_destroy(page);
    }

    double E = 0.0;
    int k = 0;
    do{
        // printf("k: %d\n", k);

        for (int i = 0; i < n; i++) {
            char *s = forward_list_get(pages, i);
            // printf("page: %s\n", s);
            String *page = strings_create(s);

            Page_Rank *page_rank = TST_search(pr, page);

            strings_destroy(page);

            // printf("i: %d\n", i);
            
            double sum = 0.0;
            for (int j = 0; j < page_rank_size_in(page_rank); j++)
            {
                ForwardList *in = page_rank_get_in(page_rank);
                char *x = forward_list_get(in, j);
                String *in_page = strings_create(x);
                // printf("in: %s\n", x);
                // printf("j: %d\n", j);

                Page_Rank *in_page_rank = TST_search(pr, in_page);

                // printf("old: %.6f\n", page_rank_get_old_val(in_page_rank));
                // printf("size out: %d\n", page_rank_size_out(in_page_rank));

                sum += page_rank_get_old_val(in_page_rank) / fabs(page_rank_size_out(in_page_rank));
                // printf("sum: %.6f\n", sum);
                strings_destroy(in_page);
            }
            // printf("new 1: %.6f\n", page_rank_get_val(page_rank));
            // printf("old 1: %.6f\n", page_rank_get_old_val(page_rank));

            page_rank_set_old_val(page_rank, page_rank_get_val(page_rank));
            page_rank_set_val(page_rank, (1 - a / n) + (a * sum));

            if(page_rank_size_out(page_rank) == 0){
                page_rank_set_val(page_rank, (1 - a / n) + (a * page_rank_get_old_val(page_rank)) + (a * sum));
            }

            // printf("new 2: %.6f\n", page_rank_get_val(page_rank));
            // printf("old 2: %.6f\n", page_rank_get_old_val(page_rank));
        } 

        double sum_diff = 0.0;
        for (int j = 0; j < n; j++)
        {
            char *s = forward_list_get(pages, j);
            String *page = strings_create(s);
            Page_Rank *page_rank_e = TST_search(pr, page);

            // printf("new: %.6f\n", page_rank_get_val(page_rank_e));
            // printf("old: %.6f\n", page_rank_get_old_val(page_rank_e));
            sum_diff += fabs(page_rank_get_val(page_rank_e) - page_rank_get_old_val(page_rank_e));
            // printf("sum_diff: %.6f\n", sum_diff);
            strings_destroy(page);
        }
        E = (1.0 / n) * sum_diff;
        // printf("E: %.7f\n", E);

        k++;
    } while (E > 0.000001);

    while (forward_list_size(pages) > 0)
    {
        free(forward_list_pop_front(pages));
    }
    forward_list_destroy(pages);

    return pr;
}