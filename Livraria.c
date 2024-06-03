#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LIVROS 10
#define MAX_EMPRESTIMOS 3
#define PRAZO_DEVOLUCAO 15

typedef struct {
    int id;
    time_t emprestimo_data;
    int disponivel;
    char nome_livro[1000];
    char autor[1000];
    double preco;

}livro;

typedef struct {
    int id;
    char cpf[20];
    int livros_emprestados[MAX_EMPRESTIMOS];
    int num_livros_emprestado;
    char nome_usuario[100];
    time_t datas_emprestimos;
}Usuario;

livro livros[MAX_LIVROS];
Usuario usuarios[MAX_LIVROS];
int num_livros = 0;
int num_usuarios = 0;

void cadastrolivro(){
    if (num_livros < MAX_LIVROS){
            livro novolivro;
            novolivro.id = num_livros + 1;

            printf("Informe o nome do livro: \n");
            scanf("%s", novolivro.nome_livro);
            printf("Informe o valor do livro: \n");
            scanf("%lf", &novolivro.preco);
            printf("Informe o nome do autor: \n");
            scanf("%s", novolivro.autor);

            novolivro.disponivel = 1;
            time(&novolivro.emprestimo_data);
            livros[num_livros++] = novolivro;

            printf("Cadastro realizado\n");
         } else {
            printf("Limite maximo de livros atingido\n");
         }
}

void CadastroUsuario(){
    if (num_usuarios < MAX_LIVROS) {
        Usuario usuarioNovo;
        usuarioNovo.id = num_usuarios + 1;

        printf("Informe o nome do usuario: ");
        scanf("%s", usuarioNovo.nome_usuario);

        usuarioNovo.num_livros_emprestado= 0;
        printf("Informe o cpf do usuario: ");
        scanf("%s", usuarioNovo.cpf);

        usuarioNovo.num_livros_emprestado = 0;
        usuarios[num_usuarios++] = usuarioNovo;

        printf("Cadastro realizado\n");
    }else{
        printf("Limite de usuarios atingido\n");
    }
}

void emprestimoLivros(){
    printf("Livros disponiveis no estoque:\n");
    for(int i = 0; i< num_livros; i++){
        if(livros[i].disponivel){
        printf("%d - %s\n", livros[i].id, livros[i].nome_livro);
    }
  }
    int idLivro, idUsuario;
    printf("Informe o ID do livro:\n");
    scanf("%d", &idLivro);
    printf("Informe o ID do usuario:\n");
    scanf("%d", &idUsuario);
    if(idLivro < 1 || idLivro > num_livros){
        printf("Livro indisponivel no memento ou ID invalido\n");
        return;
    }
    if(usuarios[idUsuario - 1].num_livros_emprestado >= MAX_EMPRESTIMOS){
        printf("Voce aitigiu o numero maximo de emprestimos\n");
        return;
    }
    livros[idLivro - 1].disponivel = 0;
    usuarios[idUsuario - 1].livros_emprestados[usuarios[idUsuario - 1].num_livros_emprestado] = idLivro;
    time(&usuarios[idUsuario - 1].datas_emprestimos);
    usuarios[idUsuario - 1].num_livros_emprestado++;
    printf("Livro emprestado!\n");
}
void LivrosDisponiveisEstoque(){
    printf("Livros em estoque:\n");
    for(int i = 0; i < num_livros; i ++){
        if (livros[i].disponivel){
            printf("%i - %s - %s - %.2lf\n", livros[i].id, livros[i].nome_livro, livros[i].autor, livros[i].preco);
        }
    }
}

void MostrarUsuariosCadastrados(){
    printf("Usuarios Cadastrados\n");
    for(int i = 0; i < num_usuarios; i++){
     printf("IDs: %d\n", usuarios[i].id);
     printf("Nome: %s\n", usuarios[i].nome_usuario);
     printf("CPF: %s\n", usuarios[i].cpf);
     printf("Numeros de livros emprestados: %d\n", usuarios[i].num_livros_emprestado);
     printf("\n");
    }
}


void atualizarLivro(){
    int idLivro;
    double altera_preco;
    char altera_livro[1000], altera_autor[1000];

    printf("Qual é o ID do livro que deseja alterar\n");
    scanf("%d", &idLivro);

    for(int i = 0; i < MAX_LIVROS; i++){
        if(livros[i].id == idLivro){
         printf("Informe o novo nome do livro: ");
         scanf("%s", altera_livro);
         strcpy(livros[i].nome_livro, altera_livro);

         printf("Informe o novo nome do autor: ");
         scanf("%s", altera_autor);
         strcpy(livros[i].autor, altera_autor);

         printf("Informe o novo valor do livro: ");
         scanf("%lf", &altera_preco);
         livros[i].preco = altera_preco;
         printf("Livro atualizado\n");

         return;
        }
    }printf("Livro não encontrado\n");
    return;
    }

    void atualizarUsuario(){
     int idUsuario;
     char altera_usuario[100];
     char altera_cpf[12];

     printf("Qual e o ID do usuario: ");
     scanf("%d", &idUsuario);

     for(int i = 0;i < MAX_LIVROS; i ++){
        if(usuarios[i].id == idUsuario){
         printf("Informe o novo nome do usuario: ");
         scanf("%s", altera_usuario);
         strcpy(usuarios[i].nome_usuario, altera_usuario);

         printf("Informe o novo CPF do usuario: ");
         scanf("%s", altera_cpf);
         strcpy(usuarios[i].cpf, altera_cpf);

         return;
        }
     }
     printf("Usuario não encontrado");
    }

void excluirLivro(){
    int idLivro;

    printf("Qual é o ID do livro que desseja excluir\n");
    scanf("%d", &idLivro);
    if(idLivro < 1  || idLivro > num_livros || livros[idLivro - 1].disponivel == 0){
        printf("Esse livro não existe\n");
        return;
    }
    for(int i = idLivro - 1; i < num_livros - 1; i++) {
            livros[i] = livros[i + 1];
            livros[i].id --;
    }
    num_livros--;
    printf("Livro excluido com sucesso\n");
}
void excluirUsuario(){
    int idUsuario;

    printf("Qual é o ID do usuario que deseja excluir\n");
    scanf("%d", &idUsuario);
    if(idUsuario < 1 || idUsuario > num_usuarios ){
        printf("Esse usuario nao existe\n");
        return;
    }
    for (int i = idUsuario - 1; i < num_usuarios -1; i++){
        usuarios[i] = usuarios[i + 1];
        usuarios[i].id --;
    }
    num_usuarios --;
    printf("Usuario excluido com sucesso\n");
}
void devolucaoLivro(){
    int idLivro, idUsuario;

    printf("Informe o ID do livro que deseja devolver:\n");
    scanf("%d", &idLivro);

    printf("Informe o ID do usuário que está devolvendo o livro:\n");
    scanf("%d", &idUsuario);

    if(idLivro < 1 || idLivro > num_livros || idUsuario < 1 || idUsuario > num_usuarios){
        printf("ID de livro ou usuário inválido.\n");
        return;
    }

    int encontrado = 0;
    for(int i = 0; i < usuarios[idUsuario - 1].num_livros_emprestado; i++){
        if(usuarios[idUsuario - 1].livros_emprestados[i] == idLivro){
            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        printf("Este usuário não pegou este livro emprestado.\n");
        return;
    }

    livros[idLivro - 1].disponivel = 1;


    for(int i = 0; i < usuarios[idUsuario - 1].num_livros_emprestado; i++){
        if(usuarios[idUsuario - 1].livros_emprestados[i] == idLivro){

            for(int j = i; j < usuarios[idUsuario - 1].num_livros_emprestado - 1; j++){
                usuarios[idUsuario - 1].livros_emprestados[j] = usuarios[idUsuario - 1].livros_emprestados[j + 1];
            }
            usuarios[idUsuario - 1].num_livros_emprestado--;
            break;
        }
    }

    printf("Livro devolvido com sucesso.\n");
}
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(int arr[], int inic, int fim) {
    int pivot = arr[fim];
    int i = (inic- 1);

    for (int j = inic; j <= fim - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[fim]);
    return (i + 1);
}

void quicksort(int arr[], int inic, int fim) {
    if (inic < fim) {
        int pi = particionar(arr, inic, fim);

        quicksort(arr, inic, pi - 1);
        quicksort(arr, pi + 1, fim);
    }
}
void ordenarLivrosPorID() {
    int idsLivros[num_livros];

    for (int i = 0; i < num_livros; i++) {
        idsLivros[i] = livros[i].id;
    }

    quicksort(idsLivros, 0, num_livros - 1);

    // Atualizar os IDs dos livros
    for (int i = 0; i < num_livros; i++) {
        livros[i].id = idsLivros[i];
    }
}

int main(){
    int op;
    do{
     printf("--------Menu-Livraria--------\n");
     printf("0-sair\n1-Cadastrar Livro\n2-Cadastrar Usuario\n3-Livros em Estoque\n4-Usuarios Cadastrados\n\n---------Alteracoes---------\n5-Atualizar Livro\n6-Atualizar Usuario\n7-Excluir Livro\n8-Excluir Usuario\n9-Emprestimo de Livros\n10-Devolução de Livros\n11-Ordenar Livro por ID\n");
     scanf("%i", &op);

    switch(op){
      case 1:
        cadastrolivro();
        break;
      case 2:
        CadastroUsuario();
        break;
      case 3:
        LivrosDisponiveisEstoque();
        break;
      case 4:
        MostrarUsuariosCadastrados();
        break;
      case 5:
        atualizarLivro();
        break;
      case 6:
         atualizarUsuario();
        break;
      case 7:
        excluirLivro();
        break;
      case 8:
        excluirUsuario();
        break;
      case 9:
        emprestimoLivros();
        break;
      case 10:
        devolucaoLivro();
      break;
      case 11:
        ordenarLivrosPorID();
        break;
}}while(op != 0);

    return 0;
}
