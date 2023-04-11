#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int i;

    if(argc < 2){
        fprintf(2,"Usage: sleep time...\n");
        exit(1);
    }

    for(i = 1; i < argc; i++){
        if(sleep(atoi(argv[i])) < 0){
            fprintf(2,"Usage: sleep time < 0...\n");
            exit(1);
        }
    }



    exit(0);
}