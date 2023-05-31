#include <stdio.h>
#include <stdlib.h>

typedef struct process{
    int pid;
    int exec;
    struct process* next;
    struct process* previous;

}process;

typedef struct head{
    process* first;
    process* last;
    int flag;
}head;

void enfia(head* h, int pid, int exec){
    process* p = malloc(sizeof(process));
    p->pid = pid;
    p->exec = exec*1000;
    p->next = NULL;
    if(h->flag == 0){
        h->first = p;
        h->last = p;
        h->flag++;
    }
    else{
        h->last->next = p;
        p->previous = h->last;
        h->last = p;
    }
}


int main(){
    head h;
    h.flag = 0;
    h.first = NULL;
    h.last = NULL;
    int n, quantum, pid, exec, clock = 0, total = 0, clock_aux = 0;
    scanf("%d", &n);
    scanf("%d", &quantum);

    for(int i = 0; i < n; i++){
        scanf("%d %d", &pid, &exec);
        enfia(&h, pid, exec);
        total += exec*1000;
    }

    h.last->next = h.first;
    h.first->previous = h.last;

    process* current = h.first;
    while(clock < total){
        while(clock_aux < quantum){
            clock++;
            clock_aux++;
            current->exec--;
            if(current->exec == 0){
                printf("%d (%d)\n", current->pid, clock);
                current->previous->next = current->next;
                current->next->previous = current->previous;
                break;
            }
        }
        current = current->next;
        clock_aux = 0;
    }

    return 0;
}