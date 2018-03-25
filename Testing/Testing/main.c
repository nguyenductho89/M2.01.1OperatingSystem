#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include "readcmd.h"


void trace_cmd(struct cmdline *l) {
    
    int i, j;
    
    /* Display each command of the pipe */
    printf("trace_cmd\n");
    for (i=0; l->seq[i]!=0; i++) {
        char **cmd = l->seq[i];
        printf("seq[%d]: ", i);
        for (j=0; cmd[j]!=0; j++) {
            printf("(%s) ", cmd[j]);
        }
        printf("\n");
    }
}


int main()
{
    int spid, status;
    struct cmdline *l;
    char ***seq;
    char **cmd;
    
    while(1) {
        printf("shell> ");
        
        l = readcmd();
        trace_cmd(l);
        seq = l->seq;
        
        if (! *seq) continue;
        
        if(!strcasecmp(**seq, "exit")) {
            return 0;
        }
        
        if(!strcasecmp(**seq, "cd")) {
            char *param = (*seq)[1];
            char *curr_dir = getcwd(NULL, 0);
            char *path;
            if (!param) path = getenv("HOME");
            else if (strncmp(param,"/",1)) {
                path = strcat(curr_dir, "/");
                path = strcat(path, param);
            } else path = param;
            if (chdir(path)) {
                perror ("cd failed");
                chdir(curr_dir);
            }
            continue;
        }
        
        cmd = *seq;
        
        // you should adapt the implementation below in order to create a sequence of piped processes
        if ((spid=fork()) == 0) {
            if (execvp(*cmd,cmd)==-1) {
                perror ("execvp failed");
                exit(1);
            }
        }
        if (waitpid(spid,&status,0)==-1) {
            perror ("waitpid failed");
            exit(1);
        }
        
    }
    return 0;
}

