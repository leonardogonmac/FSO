#include <stdio.h>
#include <stdlib.h>

typedef struct process{
    int pid;
    int exec;
    int end;

}process;

int main(){
    int n, t, pid, exec, clock = 0, total = 0, clock_aux = 0;
    scanf("%d", &n);
    scanf("%d", &t);
    process* v = malloc(sizeof(process)*n);

    for(int i = 0; i < n; i++){
        scanf("%d %d", &pid, &exec);
        v[i].pid = pid;
        v[i].exec = exec*1000;
        total += v[i].exec;
    }

    int swich = 0;
    while(clock < total){
        while(clock_aux < t && v[swich].exec > 0){
            clock++;
            clock_aux++; 
            v[swich].exec--;
            if(v[swich].exec == 0) {
                v[swich].end = clock;
                printf("%d (%d)\n", v[swich].pid, v[swich].end);
                break;
            }
        }
        swich = (swich + 1) % n;
        clock_aux = 0;

    }

    return 0;
}