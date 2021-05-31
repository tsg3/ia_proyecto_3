#include "../include/data_manager.h"

int load_data(){
    FILE* f = fopen("data", "r");
    if (f == NULL){
        perror("Error opening the file");
        return -1;
    }

    char x[4];
    char fx[4];
    char c;
    bool mode = false;
    int i = 0;
    while ((c = fgetc(f)) != EOF){
        if(c == ',' || c == '\n'){
            if(c == '\n'){
                add_node(atoi(x), atoi(fx));
                memset(x, 0, 4);
                memset(fx, 0, 4);
                mode = false;
            } else {
                mode = true;
            }
            i = 0;
            continue;
        } else if(mode) {
            fx[i] = c;
        } else {
            x[i] = c;
        }
        i++;
    }

    if(fclose(f) == EOF){
        perror("Error closing the file");
        return -1;
    }

    return 0;
}