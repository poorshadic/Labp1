#define ITEM_TYPE int


typedef struct data{
    int seg;
    int min;
    int hora;
    int dia;
    int mes;
    int ano;
} DATA;

typedef struct nodes* List;

typedef struct Tarefa{
    int identificador;
    int prioridade;
    DATA data_criacao;
    char descricao[100];
    char pessoa[100];
    DATA prazo;
    DATA data_conclusao;
}TAREFA;
typedef struct nodes {
    TAREFA info;
    List next;
} nodes;

//TAREFA* criar_node_lista(void);

List cria_lista (void);

int lista_vazia(List lista);

List destroi_lista (List lista);

int lista_cheia (List lista);

void procura_nome_lista (List lista, char* chave, List *ant, List *atual);

void procura_lista (List lista, int chave, List *ant, List *atual);

//void busca_lista (List lista, int chave, List *ant, List *atual);

void elimina_lista (List lista, List it);

void prio_lista (List lista, int chave, List *ant, List *atual);

void insere_lista (List lista, List it);

//void insere_node_lista (List lista, TAREFA aux);

void pesquisa_nome_lista (List lista, char* it);

List pesquisa_lista (List lista, int it);

void imprime_lista (List lista);

void apoio_lista (List lista, List it);

void name_lista (List lista, char* chave, List *ant, List *atual);

void insere_listadoing (List lista, List it);

void insere_listadone (List lista, List it);

void done_lista (List lista, List *ant, List *atual);