#include <stdio.h>
#include <stdlib.h>

typedef struct page{
    int num;
    struct page *next, *previous;

}page;

typedef struct ram{
    int size;
    int amnt;
    page *lru;
    page *mru;

}ram;

page *search_page(ram *r, int page_num){
    if(r->mru == NULL) return NULL;
    page *aux = r->mru;
    while(aux != NULL && aux->num != page_num){
        aux = aux->next;
    }
    return aux;
}

void load_page(ram *r, int page_num){
    page *new = malloc(sizeof(page));
    new->num = page_num;
    new->next = r->mru;
    new->previous = NULL;
    
    if(r->amnt > 0) r->mru->previous = new;
    else r->lru = new;

    r->mru = new;

    if(r->amnt == r->size){
        page *lixo = r->lru;
        r->lru = lixo->previous;
        lixo->previous->next = NULL;
        free(lixo);
    }
    else r->amnt++;
}

int main(){
    ram r;
    r.amnt = 0;
    r.lru = NULL;
    r.mru = NULL;
    int calls, page_faults = 0;
    scanf("%d", &r.size);
    scanf("%d", &calls);

    for(int i = 0; i < calls; i++){
        int page_num;
        scanf("%d", &page_num);
        page *searched = search_page(&r, page_num);

        if(searched == NULL){
            page_faults++;
            load_page(&r, page_num);
        }
        else{
            if(searched != r.mru){
                searched->previous->next = searched->next;
                if(searched != r.lru) searched->next->previous = searched->previous;
                else r.lru = searched->previous;
                
                searched->next = r.mru;
                r.mru->previous = searched;
                searched->previous = NULL;
                r.mru = searched;
            }
        }
    }

    printf("%d\n", page_faults);

    return 0;

}