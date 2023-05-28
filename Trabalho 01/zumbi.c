#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int CONTADOR = 0;

void handler(int signal_number){
    CONTADOR++;
}

int main(){
    struct sigaction sa;
    sa.sa_handler = &handler;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    int zumbi_criado = 0, zumbi_morto = 0;
    //printf("%d\n", getpid());

    while(CONTADOR < 3){
        pause();
        if(CONTADOR == 1 && zumbi_criado == 0){
            zumbi_criado = 1;
            pid_t id_filho = fork();

            if(id_filho == 0){
                //printf("%d\n", getpid());
                exit(0);
            }
        }

        if(CONTADOR == 2 && zumbi_morto == 0){
            zumbi_morto = 1;
            wait(NULL);
        }

    }

    return 0;
}