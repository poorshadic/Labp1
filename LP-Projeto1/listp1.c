#define ITEM_TYPE int
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listp1.h"

List cria_lista (void){
    List aux;
    aux = (List) malloc (sizeof (List) * 100);
    if (aux != NULL) {
        aux->info.identificador = 0;
        aux->next = NULL;
    }
    return aux;
}
int lista_vazia(List lista){
    return (lista->next == NULL ? 1 : 0);
}
List destroi_lista (List lista){
    List temp_ptr;
    while (lista_vazia (lista) == 0) {
        temp_ptr = lista;
        lista= lista->next;
        free (temp_ptr);
    }
    free(lista);
    return NULL;
}
int lista_cheia (List lista){
    return 0;
}

void procura_nome_lista (List lista, char* chave, List *ant, List *atual){
    *ant = lista; *atual = lista->next;
    printf("\n");
    while ((*atual) != NULL ){
        if(strcmp((*atual)->info.pessoa, chave) == 0){
            //maybe//
            printf("Identificador: %d\n", (*atual)->info.identificador);
            printf("Prioridade: %d\n", (*atual)->info.prioridade);
            printf("Data Criação: %d/%d/%d\n", (*atual)->info.data_criacao.dia, (*atual)->info.data_criacao.mes, (*atual)->info.data_criacao.ano);
            printf("Descrição: %s", (*atual)->info.descricao);
            if((*atual)->info.prazo.dia !=  0) {
                printf("Data prazo: %d/%d/%d\n", (*atual)->info.prazo.dia, (*atual)->info.prazo.mes, (*atual)->info.prazo.ano);
            }
            if((*atual)->info.data_conclusao.dia != 0) {
                printf("Data conclusão: %d/%d/%d\n", (*atual)->info.data_conclusao.dia, (*atual)->info.data_conclusao.mes, (*atual)->info.data_conclusao.ano);
            }
            printf("\n");
        }
        *ant = *atual;
        *atual = (*atual)->next;
    }

    if ((*atual) != NULL && (strcmp((*atual)->info.pessoa, chave) != 0))
        *atual = NULL; // Se elemento não encontrado
}

void procura_lista (List lista, int chave, List *ant, List *atual){
    *ant = lista; *atual = lista->next;
    while ((*atual) != NULL && (*atual)->info.identificador < chave){
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if ((*atual) != NULL && (*atual)->info.identificador != chave)
        *atual = NULL; /* Se elemento não encontrado*/
}


void elimina_lista (List lista, List it){
    List ant1;
    List atual1;
    procura_lista (lista, it->info.identificador, &ant1, &atual1);
    if (atual1 != NULL) {
        ant1->next = atual1->next;
        free (atual1);
    }
}

void prio_lista (List lista, int chave, List *ant, List *atual){
    *ant = lista; *atual = lista->next;
    while ((*atual) != NULL && (*atual)->info.prioridade >= chave){
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if ((*atual) != NULL && (*atual)->info.prioridade != chave)
        *atual = NULL; /* Se elemento não encontrado*/
}



void insere_lista (List lista, List it){ //ordenado
    List no;
    List ant, inutil;
    no = (List) malloc (sizeof (nodes));
    memcpy(no, it, sizeof(*it));
    if (no != NULL) {

        prio_lista (lista, it->info.prioridade, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}

void apoio_lista (List lista, List it){ //ordenado
    List no;
    List ant, inutil;
    no = (List) malloc (sizeof (nodes));
    memcpy(no, it, sizeof(*it));
    if (no != NULL) {

        procura_lista (lista, it->info.identificador, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}


void pesquisa_nome_lista (List lista, char* it){
    List ant;
    List atual;
    procura_nome_lista (lista, it, &ant, &atual);
}

List pesquisa_lista (List lista, int it){
    List ant;
    List atual;
    procura_lista (lista, it, &ant, &atual);
    return (atual);
}
void imprime_lista (List lista){
    List l = lista->next; /* Salta o header */
    while (l){
        printf("Identificador: %d\n", l->info.identificador);
        printf("Prioridade: %d\n", l->info.prioridade);
        printf("Data Criação: %d/%d/%d\n", l->info.data_criacao.dia, l->info.data_criacao.mes, l->info.data_criacao.ano);
        printf("Descrição: %s", l->info.descricao);
        if(l->info.pessoa[0] == '\0') {
            printf("Pessoa: Por selecionar\n");
            printf("\n");
        }
        else{
            printf("Pessoa: %s\n", l->info.pessoa);
        }
        if(l->info.prazo.dia !=  0) {
            printf("Data prazo: %d/%d/%d\n", l->info.prazo.dia, l->info.prazo.mes, l->info.prazo.ano);
        }
        if(l->info.data_conclusao.dia != 0) {
            printf("Data conclusão: %d/%d/%d\n", l->info.data_conclusao.dia, l->info.data_conclusao.mes, l->info.data_conclusao.ano);
        }
        l=l->next;
    }
}


void name_lista (List lista, char* chave, List *ant, List *atual){
    *ant = lista; *atual = lista->next;
    while ((*atual) != NULL && strcmp((*atual)->info.pessoa, chave) < 0){
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if ((*atual) != NULL && strcmp((*atual)->info.pessoa, chave) != 0)
        *atual = NULL; /* Se elemento não encontrado*/
}



void insere_listadoing (List lista, List it){ //ordenado
    List no;
    List ant, inutil;
    no = (List) malloc (sizeof (nodes));
    memcpy(no, it, sizeof(*it));
    if (no != NULL) {

        name_lista (lista, it->info.pessoa, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}


void done_lista (List lista, List *ant, List *atual){
    *ant = lista; *atual = lista->next;
    while ((*atual) != NULL){
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if((*atual) != NULL){
        *atual = NULL;
    }
}



void insere_listadone (List lista, List it){ //ordenado
    List no;
    List ant, inutil;
    no = (List) malloc (sizeof (nodes));
    memcpy(no, it, sizeof(*it));
    if (no != NULL) {

        done_lista(lista, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}


