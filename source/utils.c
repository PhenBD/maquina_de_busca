#include "../headers/utils.h"

void TST_id_destroy(void *id) {
    int *aux = (int *)id;
    free(aux);
}

void TST_foward_list_string_destroy(void *list) {
    while (forward_list_size(list) > 0)
    {
        String *aux = forward_list_pop_front(list);
        strings_destroy(aux);
    }
    
    forward_list_destroy(list);
}

void TST_page_rank_destroy(void *pr) {
    Page_Rank *page_rank = (Page_Rank *)pr;
    page_rank_destroy(page_rank);
}

int count_lines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    int count = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }

    fclose(file);
    return count;
}

StringArray *list_index_pages(char *filename){
    char *dir = malloc(strlen(filename) + strlen("/index.txt") + 1);
    strcpy(dir, filename);
    dir = strcat(dir, "/index.txt");

    FILE *f = fopen(dir, "r");
    if (f == NULL) { printf("Directory ""%s"" not found.\n", dir); exit(1); }
    
    StringArray *fl = string_array_create(count_lines(dir));

    char *line = NULL;
    char delimit[] = " \t\n";

    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, f)) != -1) {
        String *page_name = strings_create(strtok(line, delimit));
        string_array_push_back(fl, page_name);
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

    TST *tst_stop_words = NULL;

    char *line = NULL;
    char delimit[] = " \t\n";
    size_t len = 0;
    ssize_t read;
    
    int count = 0;

    while ((read = getline(&line, &len, f)) != -1) {
        char *key = strtok(line, delimit);
        String *s = strings_create(key);
        strings_to_lower(s);

        if (TST_contains(tst_stop_words, s)) { strings_destroy(s); continue;  }
        
        int *id = (int *)malloc(sizeof(int));
        *id = count;
        
        tst_stop_words= TST_insert(tst_stop_words, s, id);

        strings_destroy(s);
        count++;
    }
    free(line);
    fclose(f);
    free(dir);
    return tst_stop_words;
}

TST *TST_create_words_table(char *filename, TST *stop_words, StringArray *index) {
    TST *tst_words_table = NULL;

    for (int i = 0; i < string_array_size(index); i++) {
        String *page = string_array_get(index, i);
        char *page_directory = malloc(strlen(filename) + strings_get_len(page) + strlen("/pages/") + 1);
        strcpy(page_directory, filename);
        strcat(page_directory, "/pages/");
        strcat(page_directory, strings_get_string(page));

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

                String *word = strings_create(token);
                strings_to_lower(word);
                
                if (!(TST_contains(stop_words, word)))
                {
                    if (!(TST_contains(tst_words_table, word))) 
                    {
                        ForwardList *fl = forward_list_construct();
                        String *p = strings_create(strings_get_string(page));
                        forward_list_push_back(fl, p);
                        tst_words_table = TST_insert(tst_words_table, word, fl);
                    }
                    else 
                    {
                        ForwardList *fl = TST_search(tst_words_table, word);

                        if (forward_list_find(fl, page, strings_compare) == NULL)
                        {
                            String *p = strings_create(strings_get_string(page));
                            forward_list_push_back(fl, p);
                        }
                    }
                }
                strings_destroy(word);
                token = strtok(NULL, delimit);
            }
        }
        free(line);
        free(page_directory);
        fclose(page_file);
    }

    return tst_words_table;
}

TST *TST_create_pr(char *filename, StringArray *index){
    TST *pr = NULL;

    pr = TST_create_graph(filename, index);
    pr = page_ranking(pr, filename, index);

    return pr;
}

TST *TST_create_graph(char *filename, StringArray *index){
    TST *graph = NULL;

    char *dir = malloc(strlen(filename) + strlen("/graph.txt") + 1);
    strcpy(dir, filename);
    dir = strcat(dir, "/graph.txt");
    
    FILE *f = fopen(dir, "r");
    if (f == NULL) { printf("Directory ""%s"" not found.\n", dir); exit(1); }

    for (int i = 0; i < string_array_size(index); i++) {
        String *page = string_array_get(index, i);
        Page_Rank *page_rank = page_rank_create();
        graph = TST_insert(graph, page, page_rank);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, f)) != -1) {
        int n;
        fscanf(f, "%s %d", line, &n);
        String *page_in = strings_create(line);

        Page_Rank *node = TST_search(graph, page_in);
        for (int i = 0; i < n; i++)
        {
            fscanf(f, "%s", line);
            page_rank_insert_out(node, line);

            String *page_out = strings_create(line);

            Page_Rank *aux = TST_search(graph, page_out);
            page_rank_insert_in(aux, strings_get_string(page_in));

            strings_destroy(page_out);
        }
        fscanf(f, "\n");

        graph = TST_insert(graph, page_in, node);

        strings_destroy(page_in);
    }
    free(line);
    fclose(f);
    free(dir);

    return graph;
}

TST *page_ranking(TST *graph, char *filename, StringArray *index){
    float a = 0.85;

    int n = string_array_size(index);
    for (int i = 0; i < n; i++) { 
        String *page = string_array_get(index, i);
        Page_Rank *page_rank = TST_search(graph, page);
        page_rank_set_val(page_rank, 1.0 / n);
        page_rank_set_old_val(page_rank, 1.0 / n);
    }

    double E = 0.0;
    int k = 0;
    do{
        #ifdef DEBUG_MODE
        printf("k: %d\n", k);
        #endif
        for (int i = 0; i < n; i++) {
            String *page = string_array_get(index, i);

            #ifdef DEBUG_MODE
            // printf("page: %s\n", strings_get_string(page));
            #endif

            Page_Rank *page_rank = TST_search(graph, page);

            #ifdef DEBUG_MODE
            // printf("i: %d\n", i);
            #endif

            double sum = 0.0;
            // printf("size in: %d\n", page_rank_size_in(page_rank));
            for (int j = 0; j < page_rank_size_in(page_rank); j++)
            {
                ForwardList *in = page_rank_get_in(page_rank);
                char *x = forward_list_get(in, j);
                String *in_page = strings_create(x);

                #ifdef DEBUG_MODE
                // printf("in: %s\n", x);
                // printf("j: %d\n", j);
                #endif

                Page_Rank *in_page_rank = TST_search(graph, in_page);

                #ifdef DEBUG_MODE
                // printf("old: %.6f\n", page_rank_get_old_val(in_page_rank));
                // printf("size out: %d\n", page_rank_size_out(in_page_rank));
                #endif
                sum += page_rank_get_old_val(in_page_rank) / fabs(page_rank_size_out(in_page_rank));

                #ifdef DEBUG_MODE
                // printf("sum: %.6f\n", sum);
                #endif

                strings_destroy(in_page);
            }
            #ifdef DEBUG_MODE
            // printf("new 1: %.6f\n", page_rank_get_val(page_rank));
            // printf("old 1: %.6f\n", page_rank_get_old_val(page_rank));
            #endif
            page_rank_set_old_val(page_rank, page_rank_get_val(page_rank));
            page_rank_set_val(page_rank, ((1 - a) / n) + (a * sum));

            if(page_rank_size_out(page_rank) == 0){
                page_rank_set_val(page_rank, ((1 - a) / n) + (a * page_rank_get_old_val(page_rank)) + (a * sum));
            }
            #ifdef DEBUG_MODE
            // printf("new 2: %.6f\n", page_rank_get_val(page_rank));
            // printf("old 2: %.6f\n", page_rank_get_old_val(page_rank));
            #endif
        } 

        double sum_diff = 0.0;
        for (int i = 0; i < n; i++)
        {
            String *page = string_array_get(index, i);
            Page_Rank *page_rank_e = TST_search(graph, page);

            #ifdef DEBUG_MODE
            // printf("new: %.6f\n", page_rank_get_val(page_rank_e));
            // printf("old: %.6f\n", page_rank_get_old_val(page_rank_e));
            #endif
            sum_diff += fabs(page_rank_get_val(page_rank_e) - page_rank_get_old_val(page_rank_e));

            #ifdef DEBUG_MODE
            // printf("sum_diff: %.6f\n", sum_diff);
            #endif
        }
        E = (1.0 / n) * sum_diff;
        #ifdef DEBUG_MODE
        printf("E: %.7f\n", E);
        #endif
        
        k++;
    } while (E > 0.000001);

    return graph;
}