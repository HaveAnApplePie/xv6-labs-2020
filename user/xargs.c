#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"



int main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(2,"xargs: need more arguments\n");
        exit(1);
    }

    char *newArgv[MAXARG];
    for(int i = 1; i < argc; i++){
        newArgv[i-1] =  argv[i];
    }


    char ch;
    int nums = 0;
    char *addition[MAXARG],*p;

    for(int i = 0; i < MAXARG; i++){
        addition[i] = (char*)malloc(512*sizeof(char));
    }
    p = addition[nums];

    while(read(0,&ch,1) != 0){
        //printf("read char : %c\n",ch);
        if(ch != ' ' && ch != '\n'){
            *p++ = ch;
        }
        else if(ch == ' '){
            
            *p = 0;
            nums++;
            p = addition[nums];
        }
        else if(ch == '\n'){
            *p = 0;
            int pid = fork();
            if(pid == 0){
                //printf("nums: %d\n",nums);
                for(int i = 0; i <= nums; i++){
                    //printf("addition : %s\n",addition[i]);
                    newArgv[argc-1+i] = addition[i];
                }

                exec(newArgv[0],newArgv);
            }
            else{
                wait(0);
            }

            nums = 0;
            p = addition[nums];
        }
    }

    exit(0);
}