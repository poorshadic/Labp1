#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listp1.h"
#include <time.h>

int checkIfInteger(char *str, int *value){
    *value = -1;
    int size = strlen(str);
    if(size == 0) return 0;
    for(int i = 0; i < size; i++) {
        if (!isdigit(str[i]))
            return 0;
    }
    int base = 1;
    *value = 0;
    for(int i = size-1; i >= 0; i--){
        (*value) += (str[i]-'0') * base;
        base *= 10;
    }
    return 1;
}

int main() {
    //int id = 1;
    int value = -1;
    char *str = (char *) malloc(50 * sizeof(char));
    List to_do = cria_lista();
    List doing = cria_lista();
    List done = cria_lista();
    int ident;//id
    List t;
    t = (List) malloc(sizeof(List));
    List d;
    List apoio = cria_lista();


    //nome da pessoa
    time_t tempo = time(NULL);
    int k, f = 1, id = 1, max = 0; //k = opçao /f = causador do ciclo / id= identificador da tarefa / max = lotaçao de doing
    int i;
    while (f == 1) {
        printf("---------------------MENU---------------------\n");
        printf("1) Inserir nova tarefa.\n");
        printf("2) Iniciar tarefa.\n");
        printf("3) Alterar pessoa responsavel.\n");
        printf("4) Completar tarefa.\n");
        printf("5) Refazer.\n");
        printf("6) Quadro geral.\n");
        printf("7) Tarefas de uma pessoa.\n");
        printf("8) Tarefas por ordem de data de criação.\n");
        printf("9) Sair.\n");
        printf("----------------------------------------------\n");
        //printf("k = ");
        //getchar();
        //scanf(" %d", &k);

        while (value < 1 || value > 9) {
            printf("Escolha uma opção!\nO número da opção escolhida pelo utilizador tem de ser um inteiro entre 1 e 9!\n");
            printf("Nº da opção: ");
            int i = 0, ch;
            while ((ch = fgetc(stdin)) != '\n') {
                str[i++] = (char) ch;
            }
            str[i] = '\0';
            if (!checkIfInteger(str, &value)) value = -1;
        }
        k = value;
        //getchar();
        value = -1;
        switch (k) {
            case 1:
                t->info.identificador = id++;


                struct tm tm = *localtime(&tempo);
                t->info.data_criacao.ano = tm.tm_year + 1900;
                t->info.data_criacao.mes = tm.tm_mon + 1;
                t->info.data_criacao.dia = tm.tm_mday;
                t->info.data_criacao.hora = tm.tm_hour;
                t->info.data_criacao.min = tm.tm_min;
                t->info.data_criacao.seg = tm.tm_sec;


                while (value < 0 || value > 10) {
                    printf("A prioridade tem de ser um inteiro entre 0 e 10!\n");
                    printf("Prioridade: ");
                    int i = 0, ch;
                    while ((ch = fgetc(stdin)) != '\n') {
                        str[i++] = (char) ch;
                    }
                    str[i] = '\0';
                    if (!checkIfInteger(str, &value)) value = -1;

                }

                //printf("Prioridade = %d\n", value);
                t->info.prioridade = value;

                //getchar();

                printf("Descriçao: ");
                fgets(t->info.descricao, sizeof(t->info.descricao), stdin);


                insere_lista(to_do, t);
                apoio_lista(apoio, t);

                value = -1;

                break;


            case 2:

                if (lista_vazia(to_do) || max == 5) {
                    printf("\nOpção inválida!\nNão existem tarefas!\nOU\nSó podem existir 5 tarefas a ser realizadas ao mesmo tempo, é necessário acabar uma delas!\n");
                } else {
                    printf("Nome: ");
                    fgets(to_do->next->info.pessoa, sizeof(to_do->next->info.pessoa), stdin);

                    printf("Deseja inserir prazo?\n");
                    printf("1 - Sim\n");
                    printf("2 - Não\n");
                    int r;
                    scanf("%d", &r);

                    if (r == 1) {
                        printf("Dia: ");
                        scanf("%d", &to_do->next->info.prazo.dia);
                        printf("\n");
                        printf("Mes: ");
                        scanf("%d", &to_do->next->info.prazo.mes);
                        printf("\n");
                        printf("Ano: ");
                        scanf("%d", &to_do->next->info.prazo.ano);
                        printf("\n");
                    }
                    getchar();
                    insere_listadoing(doing, pesquisa_lista(to_do, to_do->next->info.identificador));
                    elimina_lista(to_do, pesquisa_lista(to_do, to_do->next->info.identificador));
                    max++;
                }
                break;


            case 3:

                printf("Qual é o id? ");
                scanf("%d", &ident); //id da tarefa
                getchar();
                printf("Pessoa: ");
                char *pess = (char *) malloc(sizeof(pess));
                fgets(pess, sizeof(pess), stdin);
                d = pesquisa_lista(doing, ident);
                strcpy(d->info.pessoa, pess);

                //arranjar forma de selecionar a tarefa correta e mudar
                //"fgets(t.pessoa, sizeof(t.pessoa), stdin);"
                break;


            case 4:

                printf("Qual é o id? ");
                scanf("%d", &i);
                List pi;
                pi = (List) malloc(sizeof(List));
                pi = pesquisa_lista(doing, i);

                insere_listadone(done, pi);
                struct tm rm = *localtime(&tempo);
                pi->info.data_conclusao.ano = rm.tm_year + 1900;
                pi->info.data_conclusao.mes = rm.tm_mon + 1;
                pi->info.data_conclusao.dia = rm.tm_mday;
                pi->info.data_conclusao.hora = rm.tm_hour;
                pi->info.data_conclusao.min = rm.tm_min;
                pi->info.data_conclusao.seg = rm.tm_sec;
                elimina_lista(doing, pi);
                max--;
                getchar();
                break;

            case 5:
                printf("Qual é o id? ");
                scanf("%d", &ident); //id da tarefa
                List h;
                h = (List) malloc(sizeof(List));
                h = pesquisa_lista(done, ident);
                h->info.pessoa[0] = '\0';
                h->info.data_conclusao.ano = 0;
                h->info.data_conclusao.mes = 0;
                h->info.data_conclusao.dia = 0;
                h->info.data_conclusao.hora = 0;
                h->info.data_conclusao.min = 0;
                h->info.data_conclusao.seg = 0;

                insere_lista(to_do, h);
                elimina_lista(done, h); // eliminar?
                getchar();
                break;

            case 6:
                printf("\n");
                printf("---------------------TO DO--------------------\n");
                imprime_lista(to_do);
                printf("\n");
                printf("---------------------DOING--------------------\n");
                imprime_lista(doing);
                printf("\n");
                printf("---------------------DONE---------------------\n");
                imprime_lista(done);
                printf("\n");

                break;

            case 7:
                //getchar();
                printf("Pessoa: ");
                char *p = (char *) malloc(sizeof(p));
                fgets(p, sizeof(p), stdin);
                printf("---------------------DOING--------------------\n");
                pesquisa_nome_lista(doing, p);
                printf("---------------------DONE---------------------\n");
                pesquisa_nome_lista(done, p);
                break;
            case 8:
                imprime_lista(apoio);
                break;

            case 9:
                f = 0;
                FILE *fc = fopen("to_do.txt", "w+");
                if (!lista_vazia(to_do)) {
                    to_do = to_do->next;
                    while (to_do != NULL) {
                        fprintf(fc, "%d\n", to_do->info.identificador);
                        fprintf(fc, "%d/", to_do->info.data_criacao.dia);
                        fprintf(fc, "%d/", to_do->info.data_criacao.mes);
                        fprintf(fc, "%d\n", to_do->info.data_criacao.ano);
                        fprintf(fc, "%d:", to_do->info.data_criacao.hora);
                        fprintf(fc, "%d:", to_do->info.data_criacao.min);
                        fprintf(fc, "%d\n", to_do->info.data_criacao.seg);
                        fprintf(fc, "%d\n", to_do->info.prioridade);
                        fprintf(fc, "%s", to_do->info.descricao);
                        fprintf(fc, "%s\n", to_do->info.pessoa);
                        to_do = to_do->next;
                    }
                    fclose(fc);
                }
                FILE *dg = fopen("doing.txt", "w+");
                if (!lista_vazia(doing)) {
                    doing = doing->next;
                    while (doing != NULL) {
                        fprintf(dg, "%d\n", doing->info.identificador);
                        fprintf(dg, "%d/", doing->info.data_criacao.dia);
                        fprintf(dg, "%d/", doing->info.data_criacao.mes);
                        fprintf(dg, "%d\n", doing->info.data_criacao.ano);
                        fprintf(dg, "%d:", doing->info.data_criacao.hora);
                        fprintf(dg, "%d:", doing->info.data_criacao.min);
                        fprintf(dg, "%d\n", doing->info.data_criacao.seg);
                        fprintf(dg, "%d\n", doing->info.prioridade);
                        fprintf(dg, "%s", doing->info.descricao);
                        fprintf(dg, "%s\n", doing->info.pessoa);
                        doing = doing->next;
                    }
                    fclose(dg);
                }
                FILE *de = fopen("done.txt", "w+");
                if (!lista_vazia(done)) {
                    done = done->next;
                    while (done != NULL) {
                        fprintf(de, "%d\n", done->info.identificador);
                        fprintf(de, "%d/", done->info.data_criacao.dia);
                        fprintf(de, "%d/", done->info.data_criacao.mes);
                        fprintf(de, "%d\n", done->info.data_criacao.ano);
                        fprintf(de, "%d:", done->info.data_criacao.hora);
                        fprintf(de, "%d:", done->info.data_criacao.min);
                        fprintf(de, "%d\n", done->info.data_criacao.seg);
                        fprintf(de, "%d\n", done->info.prioridade);
                        fprintf(de, "%s", done->info.descricao);
                        fprintf(de, "%s\n", done->info.pessoa);
                        done = done->next;
                    }
                    fclose(de);
                }
                FILE *a = fopen("apoio.txt", "w+");
                if (!lista_vazia(apoio)) {
                    apoio = apoio->next;
                    while (apoio != NULL) {
                        fprintf(a, "%d\n", apoio->info.identificador);
                        fprintf(a, "%d/", apoio->info.data_criacao.dia);
                        fprintf(a, "%d/", apoio->info.data_criacao.mes);
                        fprintf(a, "%d\n", apoio->info.data_criacao.ano);
                        fprintf(a, "%d:", apoio->info.data_criacao.hora);
                        fprintf(a, "%d:", apoio->info.data_criacao.min);
                        fprintf(a, "%d\n", apoio->info.data_criacao.seg);
                        fprintf(a, "%d\n", apoio->info.prioridade);
                        fprintf(a, "%s", apoio->info.descricao);
                        fprintf(a, "%s\n", apoio->info.pessoa);
                        apoio = apoio->next;
                    }
                    fclose(a);
                }
                break;

            default:
                printf("Opção inválida!\n");



        }
    }
}


