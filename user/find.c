#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void findFileInDir(char* dir,char* file){
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(dir,0)) < 0){
        fprintf(2,"find: cannot open %s\n", dir);
        return;
    }

    if(fstat(fd,&st) < 0){
        fprintf(2, "find: cannot stat %s\n", dir);
        close(fd);
        return;
    }

    switch (st.type)
    {
    case T_DIR:
        if(strlen(dir) + 1 + DIRSIZ + 1 > sizeof(buf)){
            printf("find: path too long\n");
            break;
        }
        strcpy(buf, dir);
        p = buf + strlen(buf);
        *p++ = '/';
        while(read(fd,&de,sizeof(de)) == sizeof(de)){
            if(de.inum == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(buf, &st) < 0){
                printf("ls: cannot stat %s\n", buf);
                continue;
            }
            if(st.type == T_DIR){
                if(strcmp(de.name,".") == 0 || strcmp(de.name,"..") == 0){
                    ;
                }
                else{
                    findFileInDir(buf,file);
                }
            }
            else if(st.type == T_FILE){
                if(strcmp(de.name,file) == 0){
                    printf("%s\n",buf);
                }
            }
        }
        break;
    
    default:
        fprintf(2, "find: the first argument need to be a directory\n");
        close(fd);
        return;
    }

    close(fd);


}



int main(int argc, char* argv[]){
    if(argc != 3){
        fprintf(2,"find need two arguments: directory and file\n");
        exit(1);
    }

    findFileInDir(argv[1],argv[2]);

    exit(0);
}