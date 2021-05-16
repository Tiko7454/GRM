#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"


void loadingBar(){
    char a = '.', b = '*';
    printf("[");
  
    for (int i = 0; i < 26; i++)
        printf("%c", a);
    printf("]");
  
    printf("\r");
    printf("[");
    for (int i = 0; i < 26; i++)
        printf("%c", b);
}


int is_link(char* x){
    if(strlen(x) < 8)
        return 0;
    char prefix[9];
    for(int i = 0; i < 8; i++)
        prefix[i] = x[i];
    prefix[8] = 0;
    return strcmp(prefix, "https://") == 0;
}

// grm install ...
int main(int argc, char** argv){
    char github_prefix[100] = "https://github.com/";
    char clone[1000] = "git clone ";
    char* pull = "git pull";
    char* mode = argv[1];

    if(strcmp(mode, "install") == 0){
        for(int i = 2; i < argc; i++){
            char* arg = argv[i];  // add default github prefix if necessary
            strcat(clone, arg);
            strcat(clone, " ");
            strcat(clone, RPS_LOCATION);
            /* unlinking arg */
            char unlinked_arg[1000] = "";
            if(is_link(arg))
                for(int i = 8; i < strlen(arg); i++)
                    unlinked_arg[i-8] = arg[i];
            else
                strcat(unlinked_arg, arg); //
            /* end */
            strcat(clone, unlinked_arg);
            system(clone);
            //check if clone has done successfully
            /* adding to RPL */
            FILE* RPL;
            RPL = fopen("RPL", "a");
            fprintf(RPL, "%s\n", unlinked_arg); //
            fclose(RPL);
            /* end */

        }
    }
    return 0;
}
