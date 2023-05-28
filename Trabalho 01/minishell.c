#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(){
    struct timeval start, end, main_start, main_end;
    int flag = 0, child_status = 0;
    char path[260]; 
    char *args[3];

    args[0] = path;
    args[1] = malloc(sizeof(char)*260);
    args[2] = NULL;

    while(scanf(" %s %s", path, args[1]) != EOF){
        fflush(stdout);
        if(flag == 0){
            gettimeofday(&main_start, NULL);
            flag = 1;
        }    
        gettimeofday(&start, NULL);
        pid_t child = fork();
        if(child == 0){
            execv(path, args);
            if(errno != 0) printf("> Erro: %s\n", strerror(errno));
            fclose(stdin);
            exit(errno);
        }

        if(waitpid(child, &child_status, 0)){
            gettimeofday(&end, NULL);
            child_status = WEXITSTATUS(child_status);
            double child_time = (double) (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec)/1000000.0);
            printf("> Demorou %.1lf segundos, retornou %d\n", child_time, child_status);
        }
    }
    gettimeofday(&main_end, NULL);
    double main_time = (double) (main_end.tv_sec - main_start.tv_sec + (main_end.tv_usec - main_start.tv_usec)/1000000.0);
    printf(">> O tempo total foi de %.1lf segundos\n", main_time);

    return 0;
}