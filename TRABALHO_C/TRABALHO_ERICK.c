/*
[ Erick Yuji Hirata                       ]
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>

typedef struct
{
    int  id_questao;           // ID da questão

    char ds_pergunta[100];     // Descrição da Pergunta   
    char ds_alternativa1[100]; // Alternativa 1 (A)
    char ds_alternativa2[100]; // Alternativa 1 (B)
    char ds_alternativa3[100]; // Alternativa 1 (C)
    char ds_alternativa4[100]; // Alternativa 1 (D)

    int  nivel_pergunta;       // Nivel da pergunta 1(Fácil), 2(Médio), 3(Díficil)

    int  resp_ok;              // Qual a Resposta Certa
    
    int  pergunta_feita;       // Indentifica qual questão foi feita
} reg_questoes;

//Apontador
typedef struct TipoItem *TipoApontador;

// Estrutura do Tipo Item
typedef struct TipoItem
{
    TipoApontador anterior;
    reg_questoes conteudo;
    TipoApontador proximo;
} TipoItem;

typedef struct
{
    TipoApontador Primeiro;
    TipoApontador Ultimo;
} TipoLista;

// Função de Cordenadas para o cursor do prof
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Mostra a Tela Padrao SEM A MEIUCA
void tela()
{
    int t;
    system("cls");
    gotoxy(01, 01);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(01, 02);
    printf("| UNICV");
    gotoxy(60, 02);
    printf("Estrutura de Dados |");
    gotoxy(01, 03);
    printf("|");
    gotoxy(20, 02);
    printf("SHOW DO MILHAO MAUWHEEEE  HE  HEEEE");
    gotoxy(79, 03);
    printf("|");
    gotoxy(01, 04);
    printf("+-----------------------------------------------------------------------------+");
    for (t = 5; t < 24; t++)
    {
        gotoxy(01, t);
        printf("|");
        gotoxy(79, t);
        printf("|");
    }
    gotoxy(01, 22);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(02, 23);
    printf("MSG.:");
    gotoxy(01, 24);
    printf("+-----------------------------------------------------------------------------+");
}

// Tela pergunta
void tela_pergunta()
{
    tela();
    gotoxy(07, 05);
    printf("   Codigo da Pergunta....: ");
    gotoxy(07, 07);
    printf("1- Descricao da Pergunta.: ");
    gotoxy(07, 9);
    printf("2- Primeira Alternativa..: ");
    gotoxy(07, 11);
    printf("3- Segunda Alternativa...: ");
    gotoxy(07, 13);
    printf("4- Terceira Alternativa..: ");
    gotoxy(07, 15);
    printf("5- Quarta Alternativa....: ");
    gotoxy(07, 17);
    printf("6- Nivel da Pergunta.....: ");
    gotoxy(07, 19);
    printf("7- Resposta Correta......: ");
}

// Limpa a Tela
void limpa_tela()
{
    int lin;
    int col;
    for (lin = 7; lin < 22; lin++)
    {
        for (col = 2; col < 79; col++)
        {
            gotoxy(col, lin);
            printf(" ");
        }
    }
}

TipoApontador pesquisa(TipoLista *L, int codigo)
{
    TipoApontador aux;
    aux = L->Primeiro;
    while (aux != NULL)
    {
        if (aux->conteudo.id_questao == codigo)
        {
            break;
        }
        aux = aux->proximo;
    }
    return aux;
}

int conta_elementos(TipoLista *L)
{
    int cont;
    TipoApontador aux;
    aux = L->Primeiro;
    cont = 0;
    while (aux != NULL)
    {
        cont = cont + 1;
        aux = aux->proximo;
    }
    return cont;
}

void ordena_codigo(TipoLista *L)
{
    int i;
    int j;
    int qtde;
    reg_questoes reg;
    TipoApontador aux1;
    TipoApontador aux2;

    qtde = conta_elementos(L);
    aux1 = L->Primeiro;
    aux2 = aux1->proximo;
    for (i = 1; i <= qtde - 1; i++)
    {
        for (j = i + 1; j <= qtde; j++)
        {
            if (aux1->conteudo.id_questao > aux2->conteudo.id_questao)
            {
                reg = aux1->conteudo;
                aux1->conteudo = aux2->conteudo;
                aux2->conteudo = reg;
            }
            aux2 = aux2->proximo;
        }
        aux1 = aux1->proximo;
        aux2 = aux1->proximo;
    }
}

void ordena_desc(TipoLista *L)
{
    int i;// o I e o J sao Var de controle para iteração, LEMBRAR
    int j;
    int qtde;
    int result; // Result da comparação de string
    reg_questoes reg;
    TipoApontador aux1; // Ponteiros auxiliares para percorrer a lista
    TipoApontador aux2;

    qtde = conta_elementos(L); // Obter a quantidade de elementos na lista
    aux1 = L->Primeiro;
    aux2 = aux1->proximo;
    for (i = 1; i <= qtde - 1; i++)
    {
        for (j = i + 1; j <= qtde; j++)
        {
            // Comparar as perguntas das questões atuais
            result = strcmp(aux1->conteudo.ds_pergunta, aux2->conteudo.ds_pergunta);
            if (result > 0)
            {
                // Trocar as informações de questao, aqui o filho chora e a mae nao ve de tao confuso
                reg = aux1->conteudo;
                aux1->conteudo = aux2->conteudo;
                aux2->conteudo = reg;
            }

            aux2 = aux2->proximo;
        }
        aux1 = aux1->proximo;
        aux2 = aux1->proximo;
    }
}

char *le_ds_pergunta()
{
    char *ds_pergunta;
    ds_pergunta = malloc(sizeof(char) * 100);
    do
    {
        gotoxy(34, 07);
        printf("                                               ");
        gotoxy(34, 07);
        fgets(ds_pergunta, 100, stdin);

        if ((strlen(ds_pergunta) == 1) && (strcmp(ds_pergunta, "0") == -1))
        {
            gotoxy(07, 23);
            printf("A descricao da pergunta e obrigatoria");
            getch();
            gotoxy(07, 23);
            printf("                              ");
        }
    } while ((strlen(ds_pergunta) == 1) && (strcmp(ds_pergunta, "0") == -1));
    return ds_pergunta;
}

char *le_ds_alternativa(int linha)
{
    char *ds_alternativa;
    ds_alternativa = malloc(sizeof(char) * 100);
    do
    {
        gotoxy(34, linha);
        printf("                                               ");
        gotoxy(34, linha);
        fgets(ds_alternativa, 100, stdin);

        // Verificar se a descrição da pergunta é obrigatória LEMBRAR
        if ((strlen(ds_alternativa) == 1) && (strcmp(ds_alternativa, "0") == -1))
        {
            gotoxy(07, 23);
            printf("A descricao da alternativa e obrigatoria");
            getch();
            gotoxy(07, 23);
            printf("                              ");
        }
    } while ((strlen(ds_alternativa) == 1) && (strcmp(ds_alternativa, "0") == -1));
    return ds_alternativa;
}

int le_nivel_pergunta()
{
    int nivel_pergunta;
    do
    {
        gotoxy(34, 17);
        printf("                                               ");
        gotoxy(34, 17);
        scanf("%d", &nivel_pergunta);
        getchar();
        if (nivel_pergunta == 0)
        {
            gotoxy(07, 23);
            printf("O nivel da pergunta e Obrigatorio");
            getch();
            gotoxy(07, 23);
            printf("                                             ");
        }
    } while (nivel_pergunta <= 0 && nivel_pergunta > 3);
    return nivel_pergunta;
}

int le_resp_ok()
{
    int resp_ok;
    do
    {
        gotoxy(34, 19);
        printf("                                               ");
        gotoxy(34, 19);
        scanf("%d", &resp_ok);
        getchar();
        if (resp_ok == 0)
        {
            gotoxy(07, 23);
            printf("E obrigatorio informar a alternativa correta");
            getch();
            gotoxy(07, 23);
            printf("                                             ");
        }
    } while (resp_ok <= 0 && resp_ok > 4);
    return resp_ok;
}

void leitura(reg_questoes *reg_quest)
{
    strcpy(reg_quest->ds_pergunta, le_ds_pergunta());
    strcpy(reg_quest->ds_alternativa1, le_ds_alternativa(9));
    strcpy(reg_quest->ds_alternativa2, le_ds_alternativa(11));
    strcpy(reg_quest->ds_alternativa3, le_ds_alternativa(13));
    strcpy(reg_quest->ds_alternativa4, le_ds_alternativa(15));
    reg_quest->nivel_pergunta = le_nivel_pergunta();
    reg_quest->resp_ok = le_resp_ok();
}

void mostra_pergunta(reg_questoes reg_quest)
{
    gotoxy(34, 05);
    printf("%d", reg_quest.id_questao);
    gotoxy(34, 07);
    printf("%s", reg_quest.ds_pergunta);
    gotoxy(34, 9);
    printf("%s", reg_quest.ds_alternativa1);
    gotoxy(34, 11);
    printf("%s", reg_quest.ds_alternativa2);
    gotoxy(34, 13);
    printf("%s", reg_quest.ds_alternativa3);
    gotoxy(34, 15);
    printf("%s", reg_quest.ds_alternativa4);
    gotoxy(34, 17);
    printf("%d", reg_quest.nivel_pergunta);
    gotoxy(34, 19);
    printf("%d", reg_quest.resp_ok);
}

void cad_fim(TipoLista *L)
{
    TipoApontador p;
    TipoApontador aux1;
    int resp;
    reg_questoes reg_quest;
    tela_pergunta();
    gotoxy(35, 03);
    printf("CADASTRAR PERGUNTA");
    do
    {
        gotoxy(34, 05);
        printf("           ");
        gotoxy(34, 05);
        scanf("%d", &reg_quest.id_questao);
        getchar();
        aux1 = pesquisa(L, reg_quest.id_questao);
        if (aux1 != NULL)
        {
            gotoxy(07, 23);
            printf("                                            ");
            gotoxy(07, 23);
            printf("Codigo Ja Cadastrado..");
            getch();
            gotoxy(07, 23);
            printf("                                            ");
        }
    } while (aux1 != NULL);

    leitura(&reg_quest);

    gotoxy(07, 23);
    printf("Deseja gravar os dados (1-SIM; 2-NAO).:");
    scanf("%d", &resp);
    if (resp == 1)
    {
        p = (TipoApontador)malloc(sizeof(TipoItem));
        p->conteudo = reg_quest;
        p->anterior = NULL;
        p->proximo = NULL;

        if (L->Primeiro == NULL)
        {
            L->Primeiro = p;
            L->Ultimo = p;
        }
        else
        {
            L->Ultimo->proximo = p;
            p->anterior = L->Ultimo;
            L->Ultimo = p;
        }
    }
}

void consultar_pergunta(TipoLista *L)
{
    TipoApontador p;
    int codigo;
    int qtde;
    p = L->Primeiro;
    if (p == NULL)
    {
        tela();
        gotoxy(8, 23);
        printf("a lista esta vazia!");
        getch();
    }
    else
    {
        do
        {
            tela();
            tela_pergunta();
            gotoxy(25, 03);
            printf("CONSULTAR PERGUNTA ESPECIFICA");
            gotoxy(60, 03);
            qtde = conta_elementos(L);
            printf("Total Perguntas.: %d", qtde);
            gotoxy(34, 05);
            scanf("%d", &codigo);
            p = pesquisa(L, codigo);
            if (p == NULL)
            {
                gotoxy(07, 23);
                printf("Pergunta NAO Cadastrada...");
                getch();
            }
        } while (p == NULL);

        mostra_pergunta(p->conteudo);

        gotoxy(10, 23);
        system("pause");
    }
}

void consultar(TipoLista *L)
{
    TipoApontador p;
    p = L->Primeiro;
    if (p == NULL)
    {
        tela();
        gotoxy(8, 23);
        printf("a lista esta vazia!");
        getchar();
    }
    else
    {
        tela();
        while (p != NULL)
        {
            tela_pergunta();
            gotoxy(35, 03);
            printf("CONSULTAR A PERGUNTA");

            mostra_pergunta(p->conteudo);

            gotoxy(10, 23);
            system("pause");
            p = p->proximo;
        }
    }
}

void cad_inicio(TipoLista *L)
{
    int resp;
    TipoApontador p;
    TipoApontador aux1;
    reg_questoes reg_quest;
    tela_pergunta();
    gotoxy(25, 03);
    printf("cadastrar pergunta NO INICIO");

    do
    {
        gotoxy(34, 05);
        printf("           ");
        gotoxy(34, 05);
        scanf("%d", &reg_quest.id_questao);
        getchar();
        aux1 = pesquisa(L, reg_quest.id_questao);
        if (aux1 != NULL)
        {
            gotoxy(07, 23);
            printf("                                            ");
            gotoxy(07, 23);
            printf("Codigo JA Cadastrado..");
            getch();
            gotoxy(07, 23);
            printf("                                            ");
        }
    } while (aux1 != NULL);

    leitura(&reg_quest);

    gotoxy(07, 23);
    printf("Deseja gravar os dados (1-SIM; 2-NAO).:");
    scanf("%d", &resp);
    if (resp == 1) {
    p = (TipoApontador)malloc(sizeof(TipoItem));
    p->proximo = L->Primeiro;
    p->anterior = NULL;

    if (L->Primeiro != NULL) {
        L->Primeiro->anterior = p;
    } else {
        L->Ultimo = p;
    }

    L->Primeiro = p;

    if (L->Ultimo == NULL) {
        L->Ultimo = L->Primeiro;
        L->Ultimo->proximo = NULL;
    }

    L->Primeiro->conteudo = reg_quest;
    }
}

void cad_posicao(TipoLista *L)
{
    TipoApontador p;
    TipoApontador r;
    TipoApontador aux1;
    reg_questoes reg_quest;
    int resp;
    int Posicao;
    int cont;
    int qtde;
    do
    {
        tela_pergunta();
        gotoxy(20, 03);
        printf("CADASTRAR PERGUNTA EM UMA POSICAO");
        gotoxy(60, 03);
        qtde = conta_elementos(L);
        printf("Total Perguntas.: %d", qtde);

        gotoxy(8, 23);
        printf("Deseja cadastrar EM QUAL POSICAO.: ");
        scanf("%d", &Posicao);
        if (Posicao > qtde)
        {
            gotoxy(07, 23);
            printf("                                                    ");
            gotoxy(8, 23);
            printf("Posicao Maior que a Quantidade Elementos..");
            getch();
        }
    } while (Posicao != 0 && Posicao > qtde);

    if (Posicao > 0)
    {
        do
        {
            gotoxy(34, 05);
            printf("           ");
            gotoxy(34, 05);
            scanf("%d", &reg_quest.id_questao);
            getchar();
            aux1 = pesquisa(L, reg_quest.id_questao);
            if (aux1 != NULL)
            {
                gotoxy(07, 23);
                printf("                                            ");
                gotoxy(07, 23);
                printf("Codigo JA Cadastrado..");
                getch();
                gotoxy(07, 23);
                printf("                                            ");
            }
        } while (aux1 != NULL);

        leitura(&reg_quest);

        gotoxy(07, 23);
        printf("Deseja gravar os dados (1-SIM; 2-NAO).:");
        scanf("%d", &resp);
        if (resp == 1)
        {
            r = (TipoApontador)malloc(sizeof(TipoItem));

            r->conteudo = reg_quest;
            r->anterior = NULL;
            r->proximo = NULL;

            p = L->Primeiro;
            for (cont = 1; cont <= Posicao - 2; cont++)
            {
                p = p->proximo;
            }
            if (Posicao == 1)
            {
                L->Primeiro->anterior = r;
                r->proximo = L->Primeiro;
                L->Primeiro = r;
            }
            else
            {
                r->proximo = p->proximo;
                p->proximo = r;
            }
        }
    }
}

void remove_final(TipoLista *L)
{
    TipoApontador p;
    TipoApontador r;
    p = L->Ultimo;
    int resp;

    if (p == NULL)
    {
        tela();
        gotoxy(8, 23);
        printf("a lista esta vazia!");
        getch();
    }
    else
    {
        tela_pergunta();
        gotoxy(30, 03);
        printf("REMOVER PERGUNTA FINAL");

        mostra_pergunta(p->conteudo);

        gotoxy(07, 23);
        printf("Deseja REMOVER a Pergunta no FINAL? (1=SIM; 2-NAO).:");
        scanf("%d", &resp);
        if (resp == 1)
        {
            if (L->Primeiro->proximo == NULL)
            {
                free(p);
                L->Primeiro = NULL;
                L->Ultimo = NULL;
            }
            else
            {
                L->Ultimo = L->Ultimo->anterior;
                L->Ultimo->proximo = NULL;
                free(p);
            }
            gotoxy(07, 23);
            printf("                                                       ");
            gotoxy(07, 23);
            printf("Registro REMOVIDA com Sucesso.");
            getch();
        }
    }
}

void remove_posicao(TipoLista *L)
{
    TipoApontador p;
    TipoApontador r;
    int resp;
    int Posicao;
    int cont;
    int qtde;
    do
    {
        tela_pergunta();
        gotoxy(20, 03);
        printf("CADASTRAR PERGUNTA EM UMA POSICAO");
        gotoxy(60, 03);
        qtde = conta_elementos(L);
        printf("Total Perguntas.: %d", qtde);

        gotoxy(8, 23);
        printf("Deseja REMOVER em qual Posicao?: ");
        scanf("%d", &Posicao);
        if (Posicao > qtde)
        {
            gotoxy(07, 23);
            printf("                                                    ");
            gotoxy(8, 23);
            printf("Posicao Maior que Qtde Elementos..");
            getch();
        }
    } while (Posicao != 0 && Posicao > qtde);

    if (Posicao > 0)
    {
        if (Posicao == 1)
        {
            r = L->Primeiro;
            p = r;
        }
        else
        {
            r = L->Primeiro;
            p = r->proximo;
            cont = 1;
            while (cont < Posicao - 1)
            {
                cont = cont + 1;
                p = p->proximo;
                r = r->proximo;
            }
        }

        tela_pergunta();
        gotoxy(34, 03);
        printf("REMOVER PERGUNTA POSICAO");

        mostra_pergunta(p->conteudo);

        gotoxy(07, 23);
        printf("Deseja Remover a Pergunta na Posicao [%d] (1=Sim; 2-Nao).:", Posicao);
        scanf("%d", &resp);
        if (resp == 1)
        {
            if (Posicao == 1)
            {
                L->Primeiro = p->proximo;
                L->Primeiro->anterior = NULL;
                free(p);
            }
            else
            {
                p->proximo->anterior = r;
                r->proximo = p->proximo;
                free(p);
            }
        }
    }
}

void remove_inicio(TipoLista *L)
{
    TipoApontador p;
    p = L->Primeiro;
    int resp;

    if (p == NULL)
    {
        tela();
        gotoxy(8, 23);
        printf("a lista esta vazia!");
        getch();
    }
    else
    {
        tela_pergunta();
        gotoxy(30, 03);
        printf("REMOVER PERGUNTA INICIO");

        mostra_pergunta(p->conteudo);

        gotoxy(07, 23);
        printf("Deseja REMOVER a Pergunta no inicio? (1=SIM; 2-NAO).:");
        scanf("%d", &resp);
        if (resp == 1)
        {
            if (p->proximo == NULL)
            {
                free(p);
                L->Primeiro = NULL;
                L->Ultimo = NULL;
            }
            else
            {
                L->Primeiro = p->proximo;
                L->Primeiro->anterior = NULL;
                free(p);
            }
            gotoxy(07, 23);
            printf("                                                       ");
            gotoxy(07, 23);
            printf("Registro REMOVIDO com Sucesso.");
            getch();
        }
    }
}

void consulta_todos(TipoLista *L, char msg[40])
{
    TipoApontador p;
    int lin;
    tela();
    gotoxy(22, 03);
    printf("%s", msg);
    lin = 7;
    gotoxy(02, 05);
    printf("Cd Descricao                                                                 ");
    gotoxy(02, 06);
    printf("-- --------------------------------------------------------------------------");
    p = L->Primeiro;
    if (p == NULL)
    {
        gotoxy(07, 23);
        printf("a lista esta vazia!");
        getch();
    }
    else
    {
        while (p != NULL)
        {
            gotoxy(02, lin);
            printf("%d", p->conteudo.id_questao);
            gotoxy(05, lin);
            printf("%s", p->conteudo.ds_pergunta);
            lin++;
            if (lin > 21)
            {
                gotoxy(07, 23);
                system("pause");
                limpa_tela();
                lin = 7;
            }
            p = p->proximo;
        }
        gotoxy(07, 23);
        system("pause");
    }
}

void altera_pergunta(TipoLista *L)
{
    TipoApontador p;
    reg_questoes reg_quest;
    int codigo;
    int qtde;
    int campo;
    int resp;
    p = L->Primeiro;
    if (p == NULL)
    {
        tela();
        gotoxy(8, 23);
        printf("a lista esta vazia!");
        getch();
    }
    else
    {
        do
        {
            tela();
            tela_pergunta();
            gotoxy(25, 03);
            printf("ALTERACAO DADOS DA PERGUNTA");
            gotoxy(60, 03);
            qtde = conta_elementos(L);
            printf("Total Perguntas.: %d", qtde);
            gotoxy(34, 05);
            scanf("%d", &codigo);
            p = pesquisa(L, codigo);
            if (p == NULL)
            {
                gotoxy(07, 23);
                printf("Pergunta NAO Cadastrada..");
                getch();
            }
        } while (p == NULL);

        mostra_pergunta(p->conteudo);
        reg_quest = p->conteudo;
        do
        {
            gotoxy(07, 23);
            printf("                                               ");
            gotoxy(07, 23);
            printf("Digite o Campo a ser ALTERADO (0=Sair).: ");
            scanf("%d", &campo);
            getchar();
            if (campo > 7)
            {
                gotoxy(07, 23);
                printf("                                           ");
                gotoxy(07, 23);
                printf("Campo invalido..");
                getch();
            }
            switch (campo)
            {
            case 1:
                strcpy(reg_quest.ds_pergunta, le_ds_pergunta());
                break;
            case 2:
                strcpy(reg_quest.ds_alternativa1, le_ds_alternativa(9));
                break;
            case 3:
                strcpy(reg_quest.ds_alternativa2, le_ds_alternativa(11));
                break;
            case 4:
                strcpy(reg_quest.ds_alternativa3, le_ds_alternativa(13));
                break;
            case 5:
                strcpy(reg_quest.ds_alternativa4, le_ds_alternativa(15));
                break;
            case 6:
                reg_quest.nivel_pergunta = le_nivel_pergunta();
                break;
            case 7:
                reg_quest.resp_ok = le_resp_ok();
                break;
            default:
                break;
            }
        } while ((campo != 0));
        gotoxy(07, 23);
        printf("                                             ");
        gotoxy(07, 23);
        printf("CONFIRMAR a ALTERACAO dos Dados (1-SIM;2-NAO).: ");
        scanf("%d", &resp);
        if (resp == 1)
        {
            p->conteudo = reg_quest;
        }
    }
}

void ajuda()
{
    int opc;
    gotoxy(01, 20);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(02, 21);
    printf("1 - Universitarios | 2 - Placas | 3 - Cartas | 4 - Pulos");
    gotoxy(07, 23);
    printf("Escolha uma alternativa.: ");
    scanf("%d", &opc);
}
int conta_elemento_nivel (TipoLista *L, int nivel) {
    TipoApontador p;
    int cont=0;
    p = L->Primeiro;
    while (p != NULL) {
        if (p->conteudo.nivel_pergunta == nivel) {
             cont++;
        }
        p = p->proximo;
    }
    return cont;
}

TipoApontador get_pergunta(TipoLista *L, int pergunta)
{
    TipoApontador p;
    int nivel=0;
    int questao_sort = 0;
    int cont;
    if (pergunta <=5)
    {
        nivel = 1;
    } else
    {
        if (pergunta <= 10) {
        nivel = 2;
        } else {
        nivel = 3;
        }
    }
    do
    {
        srand(time(NULL));
        questao_sort = 1+ rand() % conta_elemento_nivel(L,nivel);

        cont = 0;
        p = L->Primeiro;
        while (p != NULL) {
             if (p->conteudo.nivel_pergunta == nivel)  {
                cont++;
                if (cont  == questao_sort) {
                    break;
                }
             }
              p = p->proximo;
        }
    } while (p->conteudo.pergunta_feita == 1);
    p->conteudo.pergunta_feita = 1;
    return p;
}

void incrementa_valor(float *valor, float *parar, float *errar, int pergunta)
{
    if (pergunta <= 5)
    {
        *valor += 1000;
        *parar = *valor - 1000;
        *errar = *parar / 2;
        return;
    }
    if (pergunta == 6)
    {
        *valor = 10000;
        *parar = 5000;
        *errar = *parar / 2;
        return;
    }
    if (pergunta <= 10)
    {
        *valor += 10000;
        *parar = *valor - 10000;
        *errar = *parar / 2;
        return;
    }
    if (pergunta == 11)
    {
        *valor = 100000;
        *parar = 50000;
        *errar = *parar / 2;
        return;
    }
    if (pergunta <= 15)
    {
        *valor += 100000;
        *parar = *valor - 100000;
        *errar = *parar / 2;
        return;
    }
    if (pergunta == 16)
    {
        *valor = 1000000;
        *parar = 500000;
        *errar = 0;
        return;
    }

}

int ler_opcao(float errar, float parar, float acertar)
{
    int opcao;

    gotoxy(1, 18);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(1, 19);
    printf("|          ERRAR          |");
    gotoxy(12, 21);
    printf("%.2f", errar);

    gotoxy(27, 19);
    printf("|          PARAR          |");
    gotoxy(38, 21);
    printf("%.2f", parar);

    gotoxy(53, 19);
    printf("|         ACERTAR         |");
    gotoxy(63, 21);
    printf("%.2f", acertar);
    gotoxy(1, 20);
    printf("+-----------------------------------------------------------------------------+");

    gotoxy(02, 23);
    printf("0-Parar | 1-Responder | 2-Pular | 3-Cartas | 4-Universitarios | 5-Placas: ");

    scanf("%d", &opcao);
    return opcao;
}

void tela_jogo(TipoLista *L, char *nome[100])
{
    TipoApontador questao;
    int pergunta;

// Var pra valor da pergunta ou resposta correta
float valor, valoraux;

// Var pra Parar o jogo
float parar, pararaux;

// Var pra minha penalidade por respostas ERRADA
float errar, erraraux;

    int pulou = 0;
    int cont_pulos;

    int opcao_invalida = 0;

    int alternativa;

    int cont_cartas = 0;

    int cont_universitaios = 0;

    int cont_placas = 0;

    int quantidade_eliminada;

    for (pergunta = 1; pergunta <= 16; pergunta++){
        tela();
        if (pulou == 0)
        {
            incrementa_valor(&valor, &parar, &errar, pergunta);
        }
        pulou = 0;

        gotoxy(31, 13);
        printf("Atencao %s", nome);

        gotoxy(23, 15);
        printf("Pergunta valendo R$ %.2f Reais", valor);

        gotoxy(10, 23);
        system("pause");

        questao = get_pergunta(L, pergunta);

        tela_questao();
        gotoxy(2,05);
        printf("Pergunta.: %d",pergunta);
        gotoxy(1, 06);
        printf("+-----------------------------------------------------------------------------+");
        mostra_questao(questao->conteudo);

        do
        {
            switch (ler_opcao(errar, parar, valor))
            {
            case 0:
                opcao_invalida = 0;
                tela();
                gotoxy(02, 20);
                printf("Que pena %s", nome);
                gotoxy(02, 21);
                printf("Voce PAROU O JOGO BERG!, seu premio e: %.2f", parar);
                gotoxy(02, 23);
                system("pause");
                return;

            case 1: gotoxy(02, 23);
                    printf("                                                                           ");
                    gotoxy(02, 23);
                    printf("Qual a Resposta.:");
                    scanf("%d", &alternativa);
                    if (alternativa != questao->conteudo.resp_ok)
                    {
                        tela();
                        gotoxy(02, 20);
                        printf("Que pena %s", nome);
                        gotoxy(02, 21);
                        printf("Voce ERROU a resposta, seu premio : %.2f", errar);
                        getch();
                        return;
                    }
                    gotoxy(02, 23);
                    printf("Certa Resposta!.:");
                    getch();
                    break;

            case 2: if (cont_pulos < 3)
                    {
                        opcao_invalida = 0;
                        cont_pulos += pular(&pergunta, &pulou);
                    }
                    else
                    {
                        opcao_invalida = 1;
                        gotoxy(02, 23);
                        printf("Quantidade maxima de pulos atingida, escolha outra opcao                   ");
                        getch();
                    }
                    break;

            case 3: if (cont_cartas < 3)
                    {
                        cartas(questao);
                        cont_cartas++;

                        gotoxy(02, 23);
                        printf("                                                                           ");
                        gotoxy(02, 23);
                        printf("Qual a Resposta.:");
                        scanf("%d", &alternativa);
                        if (alternativa != questao->conteudo.resp_ok)
                        {
                            tela();
                            gotoxy(02, 20);
                            printf("Que pena %s", nome);
                            gotoxy(02, 21);
                            printf("Voce ERROU a resposta, seu premio : %.2f", errar);
                            getch();
                            return;
                        }
                        gotoxy(02, 23);
                        printf("Certa Resposta!.:");
                        getch();
                    }
                    else
                    {
                        opcao_invalida = 1;
                        gotoxy(02, 23);
                        printf("Se JA USOU AS CARTAS, escolha outra opcao                   ");
                        getch();
                    }
                    break;

            case 4: if (cont_universitaios < 3)
                    {
                        universitarios(questao);
                        cont_universitaios++;

                        gotoxy(02, 23);
                        printf("                                                                           ");
                        gotoxy(02, 23);
                        printf("Qual a Resposta.:");
                        scanf("%d", &alternativa);
                        if (alternativa != questao->conteudo.resp_ok)
                        {
                            tela();
                            gotoxy(02, 20);
                            printf("Que pena %s", nome);
                            gotoxy(02, 21);
                            printf("Voce ERROU a resposta, seu premio : %.2f", errar);
                            getch();
                            return;
                        }
                        gotoxy(02, 23);
                        printf("Certa Resposta Joven Gafanhoto!!!:");
                        getch();
                    }
                    else
                    {
                        opcao_invalida = 1;
                        gotoxy(02, 23);
                        printf("Se JA USOU TRAPACA UNIVERSITARIOS, escolha outra opcao                   ");
                        getch();
                    }
                    break;

            case 5: if (cont_placas < 3)
                    {
                        placas(questao);
                        cont_placas++;

                        gotoxy(02, 23);
                        printf("                                                                           ");
                        gotoxy(02, 23);
                        printf("Qual a Resposta:");
                        scanf("%d", &alternativa);
                        if (alternativa != questao->conteudo.resp_ok)
                        {
                            tela();
                            gotoxy(02, 20);
                            printf("Que pena %s", nome);
                            gotoxy(02, 21);
                            printf("Voce ERROU a resposta, seu premio e de: %.2f", errar);
                            getch();
                            return;
                        }
                        gotoxy(02, 23);
                        printf("Certa Resposta Jovem Gafanhoto!!!:");
                        getch();
                    }
                    else
                    {
                        opcao_invalida = 1;
                        gotoxy(02, 23);
                        printf("VC JA USOU AS PLACAS, escolha outra opcao                   ");
                        getch();
                    }
                    break;

            default: opcao_invalida = 1;
                     gotoxy(02, 23);
                     printf("A opcao informada e invalida                                              ");
                     getch();
                     break;
            }
        }
        while (opcao_invalida == 1);
    }
    tela();
    gotoxy(25,13);
    printf("PARABENS VOCE GANHOU 1.000.000 DE REAIS!!!");
    printf("REPITO, VC GANHOU 1 MILHAAOOOOO DE REAIS!!!");
    getch();
}

void placas() {
    int escolhas[4] = {0};

    srand(time(NULL));

    for (int i = 0; i < 50; i++) {
        int resposta_pessoa = rand() % 4;
        escolhas[resposta_pessoa]++;
    }

    float sugestoes[4];

    for (int i = 0; i < 4; i++) {
        float porcentagem = (float)escolhas[i] / 50 * 100;
        sugestoes[i] = porcentagem;
    }

    mostra_placas(sugestoes);
}

void mostra_placas(float sugestoes[4]) {
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD corOriginal;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    corOriginal = consoleInfo.wAttributes;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    gotoxy(40, 9);
    printf("+-------------------------------+");
    gotoxy(40, 10);
    printf("|                               |");
    gotoxy(41, 10);
    printf("       PLACAS - 50 PESSOAS      ");
    gotoxy(40, 11);
    printf("+-------------------------------+");
    gotoxy(40, 12);
    printf("|   1   |");
    gotoxy(48, 12);
    printf("|   2   |");
    gotoxy(56, 12);
    printf("|   3   |");
    gotoxy(64, 12);
    printf("|   4   |");
    gotoxy(40, 13);
    printf("+-------------------------------+");
    gotoxy(40, 14);
    printf("|%.1f%%   |", sugestoes[0]);
    gotoxy(48, 14);
    printf("|%.1f%%   |", sugestoes[1]);
    gotoxy(56, 14);
    printf("|%.1f%%   |", sugestoes[2]);
    gotoxy(64, 14);
    printf("|%.1f%%  |", sugestoes[3]);
    gotoxy(40, 15);
    printf("+-------------------------------+");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), corOriginal);
    getch();
}

void universitarios(TipoApontador questao) {
    int resposta_correta = questao->conteudo.resp_ok;
    int sugestoes[4] = {0};

    int votos_corretos = 2;

    for (int i = 0; i < votos_corretos; i++) {
        int indice = rand() % 4;
        if (sugestoes[indice] == 0) {
            sugestoes[indice] = resposta_correta;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (sugestoes[i] == 0) {
            do {
                sugestoes[i] = rand() % 4 + 1;
            } while (sugestoes[i] == resposta_correta);
        }
    }

    mostra_universitarios(sugestoes);
}


void mostra_universitarios(int sugestoes[4])
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD corOriginal;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    corOriginal = consoleInfo.wAttributes;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    gotoxy(40, 9);
    printf("+-------------------------------+");
    gotoxy(40, 10);
    printf("|                               |");
    gotoxy(41, 10);
    printf("         UNIVERSITARIOS        ");
    gotoxy(40, 11);
    printf("+-------------------------------+");
    gotoxy(40, 12);
    printf("| Univ1 |");
    gotoxy(48, 12);
    printf("| Univ2 |");
    gotoxy(56, 12);
    printf("| Univ3 |");
    gotoxy(64, 12);
    printf("| Univ4 |");
    gotoxy(40, 13);
    printf("+-------------------------------+");
    gotoxy(40, 14);
    printf("|   %d   |", sugestoes[0]);
    gotoxy(48, 14);
    printf("|   %d   |", sugestoes[1]);
    gotoxy(56, 14);
    printf("|   %d   |", sugestoes[2]);
    gotoxy(64, 14);
    printf("|   %d   |", sugestoes[3]);
    gotoxy(40, 15);
    printf("+-------------------------------+");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), corOriginal);
    getch();
}

void cartas(TipoApontador questao)
{
    int opcao;
    int quantidade;
    int esconder;
    int i;
    int alternativasEscondidas[4] = {0};
    int opcao_invalida = 0;

    mostra_cartas(0, 0);
    do
    {
        opcao_invalida = 0;
        gotoxy(02, 23);
        printf("                                                                           ");
        gotoxy(02, 23);
        printf("Escolha uma carta: ");
        scanf("%d", &opcao);

        if (opcao < 0 || opcao > 4) {
            opcao_invalida = 1;
        }

        if (opcao_invalida == 1) {
            gotoxy(02, 23);
            printf("Informe uma opcao valida: ");
            getch();
        }
    } while (opcao_invalida == 1);



    srand(time(NULL));
    quantidade = 1+ rand() % 3;

    mostra_cartas(opcao, quantidade);

    gotoxy(02, 23);
    printf("                                                                           ");
    gotoxy(02, 23);
    printf("Serao eliminidas %d questoes: ", quantidade);


    for (i = 1; i <= quantidade; i++)
    {
        esconder = 0;
        do
        {
            esconder = 1 + rand() % 4;
        } while (esconder == questao->conteudo.resp_ok || alternativasEscondidas[esconder - 1]);
        alternativasEscondidas[esconder - 1] = 1;
        esconde_alternativa(esconder);
    }
    getch();
}

void esconde_alternativa(int alternativa)
{
    switch (alternativa)
    {
    case 1: gotoxy(2, 9);
            printf("                                 ");
            break;

    case 2: gotoxy(2, 11);
            printf("                                 ");
            break;

    case 3: gotoxy(2, 13);
            printf("                                 ");
            break;

    case 4: gotoxy(2, 15);
            printf("                                 ");
            break;
    }
}

int pular(int *pergunta, int *pulou)
{
    *pergunta = *pergunta - 1;
    *pulou = 1;
    return 1;
}

void mostra_cartas(opcao, quantidade)
{
    int carta;
    int col;
    int lin;

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD corOriginal;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    corOriginal = consoleInfo.wAttributes;

    for (carta = 1; carta <= 4; carta++)
    {
        switch(carta)
        {
            case 1: col = 35;
                    lin = 9;
                    break;

            case 2: col = 46;
                    lin = 9;
                    break;

            case 3: col = 35;
                    lin = 13;
                    break;

            case 4: col = 46;
                    lin = 13;
                    break;
        }
        if (opcao == carta)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        }
        gotoxy(col, lin);
        printf("+--------+");
        gotoxy(col,++lin);
        printf("|        |");
        if (opcao != carta)
        {
            gotoxy(col+2,lin);
            printf("Carta%d", carta);
        }
        else
        {
            gotoxy(col+4,lin);
            printf("%d", quantidade);
        }
        gotoxy(col,++lin);
        printf("+--------+");
        if (opcao == carta)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), corOriginal);
        }
    }
}

void tela_questao()
{
    tela();
    gotoxy(1, 8);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(2, 9);
    printf("1 - Alternativa.: ");
    gotoxy(2, 11);
    printf("2 - Alternativa.: ");
    gotoxy(2, 13);
    printf("3 - Alternativa.: ");
    gotoxy(2, 15);
    printf("4 - Alternativa.: ");
}

void mostra_questao(reg_questoes reg_quest)
{
    gotoxy(15,05);
    printf("(%d)", reg_quest.id_questao);
    gotoxy(2, 07);
    printf("%s", reg_quest.ds_pergunta);
    gotoxy(20, 9);
    printf("%s", reg_quest.ds_alternativa1);
    gotoxy(20, 11);
    printf("%s", reg_quest.ds_alternativa2);
    gotoxy(20, 13);
    printf("%s", reg_quest.ds_alternativa3);
    gotoxy(20, 15);
    printf("%s", reg_quest.ds_alternativa4);
}

void jogar(TipoLista *L)
{
    TipoApontador p;
    char nome[100];
    p = L->Primeiro;
    if (conta_elementos(L) < 0)
    {
        tela();
        gotoxy(8, 23);
        printf("NAO TEM BASTANTE PERGUNTA!");
        getch();
    }
    else
    {
        do
        {
            tela();
            mostra_show();
            gotoxy(07, 23);
            printf("Digite o Seu Nome Jogador: ");
            getchar();
            fgets(nome, 100, stdin);
        }
        while (nome == NULL);
        tela_jogo(L, &nome);
    }
}

void le_arquivo(TipoLista *L)
{
    FILE *ptr;
    char *filename = "Perguntas.dat";
    char *modo_gravacao = "rb";
    reg_questoes reg_quest;
    TipoApontador p;
    L->Primeiro = NULL;
    L->Ultimo = NULL;
    tela();
    gotoxy(25, 03);
    printf("carrega dados do arquivo pra lista");

    ptr = fopen(filename, modo_gravacao);
    if (ptr == NULL)
    {
        gotoxy(07, 23);
        printf("Erro ao Abrir o Arquivo .DAT, Apenas Aperte ENTER");
        getch();
    }
    else
    {
        gotoxy(01, 05);
        while (!feof(ptr))
        {
            if (fread(&reg_quest, sizeof(reg_quest), 1, ptr) != 0)
            {
                if (L->Primeiro == NULL)
                {
                    p = (TipoApontador)malloc(sizeof(TipoItem));
                    p->conteudo = reg_quest;
                    p->proximo = NULL;
                    L->Primeiro = p;
                    L->Ultimo = p;
                }
                else
                {
                    p->proximo = (TipoApontador)malloc(sizeof(TipoItem));
                    p = p->proximo;
                    p->conteudo = reg_quest;
                    p->proximo = NULL;
                    L->Ultimo = p;
                }
            }
        }
        fclose(ptr);
        mostra_show();
        gotoxy(07, 23);
        printf("Dados lidos com Sucesso");
        getch();
    }
}

void mostra_show()
{
    gotoxy(15,10);
    printf("SSS  H   H  O O O  W   W    D D  OOO    M   M  I  L     H   H  AAA OOO\n");
    gotoxy(15,11);
    printf("S    H   H  O   O  W   W    D  D O O    MM MM  I  L     H   H  A A O O\n");
    gotoxy(15,12);
    printf("SSS  H H H  O   O  W W W    D  D O O    M M M  I  L     H H H  AAA O O\n");
    gotoxy(15,13);
    printf("  S  H   H  O   O  WW WW    D  D O O    M   M  I  L     H   H  A A O O\n");
    gotoxy(15,14);
    printf(" SSS  H   H  O O O  W   W    D D  OOO    M   M  I  L L L H   H  A A OOO\n");
    gotoxy(01, 22);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(02, 23);
    printf("MSG.:");
    gotoxy(01, 24);
    printf("+-----------------------------------------------------------------------------+");

}

void gravar(TipoLista *L)
{
    FILE *ptr;
    char *filename = "Perguntas.dat";
    char *modo_gravacao = "wb";
    reg_questoes reg_quest;
    TipoApontador p;
    p = L->Primeiro;
    tela();
    gotoxy(25, 03);
    printf("grava dados da listinha do arquivo em disco");
    if (p == NULL)
    {
        gotoxy(07, 23);
        printf("lista esta vazia");
        getch();
    }
    else
    {
        if ((ptr = fopen(filename, modo_gravacao)) == NULL)
        {
            gotoxy(07, 23);
            printf("Erro ao Abrir o Arquivo .DAT, Apenas Aperte ENTER");
            getch();
        }
        else
        {
            while (p != NULL)
            {
                reg_quest = p->conteudo;
                fwrite(&reg_quest, sizeof(reg_quest), 1, ptr);
                p = p->proximo;
            }
            fclose(ptr);
            gotoxy(07, 23);
            printf("Dados Gravados com Sucesso");
            getch();
        }
    }
}

void menu_consultar(TipoLista *L)
{
    int opc;
    do
    {
        tela();
        gotoxy(30, 03);
        printf("SUBMENU CONSULTA");

        gotoxy(25, 8);
        printf("1 - Consultar Todas as Perguntas");

        gotoxy(25, 10);
        printf("2 - Consultar em Ordem de Codigo");

        gotoxy(25, 12);
        printf("3 - Consultar em Ordem Alfabetica");

        gotoxy(25, 14);
        printf("4 - Consultar o Codigo Especifico");

        gotoxy(25, 16);
        printf("5 - Retornar Menu Principal");

        gotoxy(8, 23);
        printf("Digite sua opcao.: ");

        gotoxy(28, 23);
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            consultar(L);
            break;
        case 2:
            ordena_codigo(L);
            consulta_todos(L, "CONSULTA LISTA PERGUNTAS - ORDEM DE CODIGO");
            break;
        case 3:
            ordena_desc(L);
            consulta_todos(L, "CONSULTA LISTA CLIENTES - ORDEM ALFABETICA");
            break;
        case 4:
            consultar_pergunta(L);
            break;
        default:
            break;
        }

    } while (opc != 5);
}

int main()
{
    TipoLista L;
    L.Primeiro = NULL;
    L.Ultimo = NULL;
    int opc;
    system("color A0"); //A0 e cor verde de dinheiro do show do milhao
    setlocale(LC_ALL, "portuguese-brazilian"); //obviamente pro pt-br se nao fica em english
    le_arquivo(&L);
    do
    {
        tela();
        gotoxy(30, 03);
        printf("MENU PRINCIPAL");

        gotoxy(20, 8);
        printf("1 - Cadatrar Pergunta no Inicio");

        gotoxy(20, 9);
        printf("2 - Cadastrar Pergunta no Final");

        gotoxy(20, 10);
        printf("3 - Cadastrar Pergunta em uma Posicao");

        gotoxy(20, 11);
        printf("4 - Remover Pergunta no Inicio");

        gotoxy(20, 12);
        printf("5 - Remover Pergunta no Final");

        gotoxy(20, 13);
        printf("6 - Remover Pergunta em uma Posicao");

        gotoxy(20, 14);
        printf("7 - Consultar Cadastro das Perguntas");

        gotoxy(20, 15);
        printf("8 - Alterar uma Pergunta");

        gotoxy(20, 16);
        printf("9 - Jogar SHOW DO MILHAO");
        
        gotoxy(20, 17);
        printf("10 - Finalizar Programa");

        gotoxy(8, 23);
        printf("Digite sua opcao.: ");

        gotoxy(28, 23);
        scanf("%d", &opc);
        switch (opc)
        {
            case 1:
            {
                cad_inicio(&L);
                break;
            }

            case 2:
            {
                cad_fim(&L);
                break;
            }

            case 3:
            {
                cad_posicao(&L);
                break;
            }

            case 4:
            {
                remove_inicio(&L);
                break;
            }

            case 5:
            {
                remove_final(&L);
                break;
            }

            case 6:
            {
                remove_posicao(&L);
                break;
            }

            case 7:
            {
                menu_consultar(&L);
                break;
            }

            case 8:
            {
                altera_pergunta(&L);
                break;
            }

            case 9:    //JOGAR
            {
                jogar(&L);
                break;
            }
        }
    } while (opc <= 9);
    gravar(&L);
    return 0;
}
