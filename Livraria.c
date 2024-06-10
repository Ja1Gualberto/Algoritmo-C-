#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define MAX_LIVROS 10
#define MAX_USUARIOS 10
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

    for(int i = 0; i < num_livros; i++){
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
     char altera_cpf[20];

     printf("Qual e o ID do usuario: ");
     scanf("%d", &idUsuario);

     for(int i = 0;i < num_usuarios; i ++){
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
//Explicando (Char): isso vai troca os itens(x por y)
void troca(livro *x, livro *y){
	livro local = *x;
	*x = *y;
	*y = local;
}
//Explicando(char): Separa em duas partições (letras que vem antes do livro escolhido e letras depois do numero escolhido)
int particiona(livro arr[], int menor, int maior){
	char *pivot = arr[maior].nome_livro;
	int i = menor - 1;
	
	for(int j = menor; j <= maior - 1; j++)
	{
		if(strcmp (arr[j].nome_livro, pivot) < 0)
		{
			i++;
			troca(&arr[i], &arr[j]);
		}
	}
	troca(&arr[i + 1], &arr[maior]);
	return (i + 1);
}
int particionaID(livro arr[], int menor, int maior)
{
    int pivo = arr[maior].id;
    int i = menor - 1;
    
    for (int v = menor; v <= maior - 1; v++)
    {
        if (arr[v].id < pivo)
        {
            i++;
            troca(&arr[i], &arr[v]);
        }
        
    }
    troca(&arr[i + 1], &arr[maior]);
    return (i + 1);
}

void quiacksortID(livro arr[], int menor, int maior)
{
    if (menor < maior)
    {
        int pi = particionaID(arr, menor, maior);

        quiacksortID(arr, menor, pi - 1);
        quiacksortID(arr, pi + 1, maior);
    }

}
void organLivroID()
{
    if (num_livros > 1)
    {
        quiacksortID(livros, 0, num_livros - 1);
    }
    printf("Livros Organizados por ID\n");
    for (int i = 0; i < num_livros; i++)
    {
       printf("%d - %s - %s - %2lf\n", livros[i].id, livros[i].nome_livro, livros[i].autor, livros [i].preco);
    }
    
}
//Explicando (Char): a função que vai organizar usando "particiona""troca"
void quicksort(livro arr[], int menor, int maior){
	if(menor < maior)
	{
		int pi = particiona(arr, menor, maior);
		
		quicksort(arr, menor, pi - 1);
		quicksort(arr, pi + 1, maior);
	}
}
//Explicação (Char): Aqui usa o quicksort
void organLivro(){
    if (num_livros > 1)
    {
        quicksort(livros, 0, num_livros -1);
    }
    printf("Livros organizados por nome\n");
    for (int i = 0; i < num_livros; i++)
    {
        printf("%d - %s - %s - %2lf\n", livros[i].id, livros[i].nome_livro, livros[i].autor, livros[i].preco);
    }
    
}
int main(){
    int op1, op2, op3;
    do {
        printf("--------Menu-Livraria--------\n");
        printf("01-Adicionar\n02-Visualizar\n03-Alterar\n0-Sair\n");
        printf("-----------------------------\n");
        scanf("%i", &op1);
        switch (op1) {
            case 1:
                do 
                {
                    printf("--------Menu-Adicionar--------\n");
                    printf("01-Cadastrar Livros\n02-Cadastrar Usuario\n03-Emprestimo de Livro\n04-Devolver Livros\n0-Voltar\n");
                    printf("--------------------------------\n");
                    scanf("%i", &op2);
                    switch (op2) 
                    {
                        case 1:
                            system("cls");
                            cadastrolivro();
                            break;
                        case 2:
                            system("cls");
                            CadastroUsuario();
                            break;
                        case 3:
                            system("cls");
                            emprestimoLivros();
                            break;
                        case 4:
                            system("cls");
                            devolucaoLivro();
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida\n");
                            break;
                    }
                } while (op2 != 0);
                break;
            case 2:
                do 
                {
                    printf("--------Menu-Visualizar--------\n");
                    printf("01-Visualizar Livros\n02-Visualizar Usuarios\n0-Voltar\n");
                    printf("--------------------------------\n");
                    scanf("%i", &op2);
                    switch (op2) {
                        case 1:
                            do
                            {
                                printf("--------Menu-Visualizar--------\n");
                                printf ("01-Visualizar Livros\n02-Organizar (A-Z)\n03- Organiza por Id\n0-Sair");
                                scanf("%i", &op3);
                                switch (op3)
                                {
                                case 1:
                                    system("cls");
                                    LivrosDisponiveisEstoque();
                                    break;
                                case 2:
                                    system("cls");
                                    organLivro();
                                    break;
                                case 3:
                                    system("cls");
                                    organLivroID();
                                    break;
                                case 0:
                                break;
                                default:
                                    printf("Funçãp não existe");
                                    break;
                                }
                            } while (op3 != 0);
                            
                            break;
                        case 2:
                            system("cls");
                            MostrarUsuariosCadastrados();
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida\n");
                            break;
                    }
                } while (op2 != 0);
                break;
            case 3:
                do 
                {
                    printf("--------Menu-Alterar--------\n");
                    printf("01-Atualizar Livros\n02-Atualizar Usuarios\n03-Excluir Livros\n04-Excluir Usuarios\n0-Voltar\n");
                    printf("-----------------------------\n");
                    scanf("%i", &op2);
                    switch (op2) {
                        case 1:
                            system("cls");
                            atualizarLivro();
                            break;
                        case 2:
                            system("cls");
                            atualizarUsuario();
                            break;
                        case 3:
                            system("cls");
                            excluirLivro();
                            break;
                        case 4:
                            system("cls");
                            excluirUsuario();
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida\n");
                            break;
                    }
                } while (op2 != 0);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    } while (op1 != 0);
    
    return 0;
}
