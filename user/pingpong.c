#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc > 1){
        fprintf(2,"pingpong too many arguments\n");
        exit(1);
    }
    int c2p[2],p2c[2];

    pipe(c2p);
    pipe(p2c);

    if(fork() == 0){
        //child
        //received ping
        char s[20];
        close(p2c[1]);
        read(p2c[0],s,4);
        close(p2c[0]);
        fprintf(1,"%d: received %s\n",getpid(),s);
        //send pang
        close(c2p[0]);
        write(c2p[1],"pong",4);
        close(c2p[1]);        

    }
    else{
        //parent

        //send ping
        close(p2c[0]);
        write(p2c[1],"ping",4);
        close(p2c[1]);

        //received pong
        char s[20];
        close(c2p[1]);
        read(c2p[0],s,4);
        close(c2p[0]);
        fprintf(1,"%d: received %s\n",getpid(),s);


    }


    exit(0);
}