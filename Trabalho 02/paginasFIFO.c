#include <stdio.h>
#include <stdlib.h>

int busca(int *ram, int pagina, int tam){
    for(int i = 0; i < tam; i++){
        if(ram[i] == pagina) return 1;
    }
    return 0;

}

int main(){
    int tam_ram, qtde_acessos, qtde_page_f = 0, primeiro = 0, ocupacao = 0;
    scanf("%d", &tam_ram);
    scanf("%d", &qtde_acessos);
    int *ram = malloc(sizeof(int)*(tam_ram));

    for(int i = 0; i < qtde_acessos; i++){
        int pagina;
        scanf("%d", &pagina);
        if(!busca(ram, pagina, ocupacao)){
            qtde_page_f++;
            if(ocupacao == tam_ram) {
                ram[primeiro] = pagina;
                primeiro = (primeiro + 1) % tam_ram;
            }
            else{
                ram[ocupacao] = pagina;
                ocupacao++;
            } 
        }
    }

    printf("%d\n", qtde_page_f);
}