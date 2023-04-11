#include "kernel/types.h"
#include "user/user.h"

void childBehavior(int p2c[2]);

int main(int argc, char *argv[]){
    if(argc > 1){
        fprintf(2,"primes too many arguments\n");
        exit(1);
    }

    int l2r[2];
    pipe(l2r);
    int pid = fork();

    if(pid == 0){
        childBehavior(l2r);
    }
    else{
        close(l2r[0]);
        for(int i = 2; i <= 35; i++){
            write(l2r[1],&i,1);
        }
        close(l2r[1]);
    }

    wait(0);

    exit(0);
}


void childBehavior(int p2c[2]){
    close(p2c[1]);
    int num;
    read(p2c[0],&num,1);
    fprintf(1,"prime %d\n",num);
    int l2r[2];
    int i;
    int flag = 0;
    while(read(p2c[0],&i,1) != 0){
        if(i % num != 0){
            if(flag == 0){
                pipe(l2r);
                if(fork() == 0){
                    //child
                    close(p2c[0]);
                    childBehavior(l2r);
                }
                close(l2r[0]);
                write(l2r[1],&i,1);
                flag = 1;
            }
            else{
                write(l2r[1],&i,1);
            }
        }    
    }
    if(flag == 1){
        close(l2r[1]);
    }
    close(p2c[0]);
    wait(0);
    exit(0);
}