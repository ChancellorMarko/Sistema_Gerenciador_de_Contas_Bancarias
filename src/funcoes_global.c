/*
Autor: Marcos.
Data: 28/10/24.
Membros: 
    1 - 178292-2024
    2 - 177020-2024
Descrição: Programa para gerenciamento de varias contas bancarias.
*/

// Bibliotecas
#include "global.h"

// Função que conta quantos cadastros estão presentes na lista
int Contar_Elementos_Lista(Lista *lista)
{
    Apontador VariavelAuxiliar;
    int Quant_Intens = 0;

    VariavelAuxiliar = lista->primeiro;

    while (VariavelAuxiliar != NULL) 
    {
        VariavelAuxiliar = VariavelAuxiliar->proximo;
        Quant_Intens++;
    }

    return Quant_Intens;
}

// Função que verifica se o código de funcionario já foi utilizado
Apontador Verificar_Existencia(Lista *lista, int codigo_conta)
{
    //Utilizada para percorrer a lista
    Apontador VariavelAuxiliar;

    // Inicializa o inicio da lista com a variavel criada
    VariavelAuxiliar = lista->primeiro; // lista->primeiro aponta para o primeiro registro da lista de funcionários

    // Realiza um loop para percorrer a lista até chegar ao ultimo registro
    while (VariavelAuxiliar != NULL)
    {
        // Verifica se o codigo procurado é igual ao codigo registrado
        if (VariavelAuxiliar->conteudo.codigo_conta == codigo_conta)
        {
            // Se o código for igual ele retorna o ponteiro da VariavelAuxiliar que aponta para o registro que tem o mesmo código
            return VariavelAuxiliar;
        }

        // Mover o ponteiro para o proximo da lista
        VariavelAuxiliar = VariavelAuxiliar->proximo; // VariavelAuxiliar->proximo apronta para o proximo item da lista
    }

    // Retornar NULL caso nenhum nada for encontrado
    return NULL;
}

// Função para limpar a memória depois de finalizar o programa
void LimparMemoria(Lista *lista)
{
    Apontador lista_auxiliar;

    while(lista->primeiro != NULL)
    {
        lista_auxiliar = lista->primeiro;
        lista->primeiro = lista->primeiro->proximo;
        free(lista_auxiliar);

        lista->primeiro = NULL;
        lista->ultimo = NULL;
    }
}

// Função que inicializa uma lista
Lista InicializarLista()
{
    //Inicializar o começo e fim da lista
    Lista lista;
    lista.primeiro = NULL; //Inicializar a variável com um valor null para não dar ruim ao atribuir algo a ela
    lista.ultimo = NULL; //Inicializar a variável com um valor null para não dar ruim ao atribuir algo a ela

    return lista;
}

// Função Responsável por adicionar contas a lista
void Adicionar_Conta(Lista *lista, Conteudo_Conta conteudo)
{
    Apontador lista_auxiliar;

    lista_auxiliar = (Apontador)malloc(sizeof(Item));

    lista_auxiliar->conteudo = conteudo; // Adicionar conteúdo a lista
    lista_auxiliar->proximo = NULL; // Aterrar o campo que aponta para o proximo

    if(lista->primeiro == NULL)
    {
        lista->primeiro = lista_auxiliar;
        lista->ultimo = lista_auxiliar;
    }
    else
    {
        lista->ultimo->proximo = lista_auxiliar; // Adicionar o item no final da lista
        lista->ultimo = lista_auxiliar; // Mover o apontado par ao ultimo da lista
    } 
}

// Criar o arquivo com os dados da lista
void SalvarLista(Lista *lista)
{
    // Variaveis
    Apontador auxiliar;

    // Criar arquivo
    FILE *banco_de_dados;

    // Abrir o arquivo
    banco_de_dados = fopen("DADOS.dat", "wb");

    if(banco_de_dados == NULL)
    {
        tela();
        limpar_campo_opcao();
        escrever_msg("Erro ao salvar no banco de dados!");
        getch();
        return;
    }
    else 
    {
        auxiliar = lista->primeiro;

        while(auxiliar != NULL)
        {
            // Escrever o conteúdo de cada cadastro um por um no arquivo
            fwrite(&auxiliar->conteudo, sizeof(Conteudo_Conta), 1, banco_de_dados);
            auxiliar = auxiliar->proximo; // ir para o proximo cadastro
        }

        tela();
        limpar_campo_opcao();
        escrever_msg("Salvamento no banco de dados concluido com sucesso!");
        getch();

        // Fechar arquivo
        fclose(banco_de_dados);
    }
}

// Ler o arquivo com os dados da lista
Lista LerLista()
{
    // Variáveis
    Conteudo_Conta conteudo_auxiliar;
    Lista lista;

    FILE *banco_de_dados; // Criar um novo arquivo

    // Criar uma nova lista
    lista = InicializarLista();
    
    // Abrir arquivo
    banco_de_dados = fopen("DADOS.dat", "rb");

    if(banco_de_dados == NULL)
    {
        tela();
        limpar_campo_opcao();
        escrever_msg("Erro ao abrir e ler o banco de dados!");
        getch();
        return lista;
    }
    else 
    {
        // Ler cada conteudo de cadastro um por um
        while (fread(&conteudo_auxiliar, sizeof(Conteudo_Conta), 1, banco_de_dados)) 
        {
            // Adicionar conteudos lido em posições da lista (sempre no final mantendo a ordem anterior)
            Adicionar_Conta(&lista, conteudo_auxiliar);    
        }
    }

    // Fechar o arquivo
    fclose(banco_de_dados);

    return lista;
}