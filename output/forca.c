#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//Declaração Funções -----------------------------------------------------------------------------------------------------------------------------------------------------------------
//--> Para não precisar se preocupar com a ordem em que chamamos as funções
void header();
void chuta();
void desenhaforca();
void escolhepalavra();
int acertou();
int enforcou ();
int jachutou (char letra);

//Variáveis Globais ------------------------------------------------------------------------------------------------------------------------------------------------------------------
size_t tamanho;
char palavrasecreta[20];
char chutes[26];
int chutesdados = 0;

//Funções ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//--> Header do Jogo
void header(){
    printf("*********************\n");
    printf("*   JOGO DA FORCA   *\n");
    printf("*********************\n");
}

//--> Para pegar a letra digitada pelo user e armazenar na variável chute
void chuta(){
    char chute;
    scanf(" %c", &chute); //Usamos espaço antes do %c para que o scanf entenda que o enter não é um char

    chutes[chutesdados] = chute;
    chutesdados++;
}

//--> Identifica as letras já chutadas
int jachutou(char letra) {
    int achou = 0;
    for(int j = 0; j < chutesdados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }
    return achou;
}

//--> Palavra do jogo
void escolhepalavra(){

    FILE* f;
    f = fopen("palavras.txt","r");//fopen -> função para abrir um arquivo, o primeiro parâmetro é o nome do arquivo, o seguindo é referente ao que queremos fazer com ele, nesse caso "r" para ler

    if(f == 0){
        printf("Desculpe, banco de dados nao disponivel!\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras; //para sortear a palavra do arquivo txt

    for (int i=0; i <= randomico;i++){
        fscanf(f, "%s", palavrasecreta);
    }
    
    tamanho = strlen(palavrasecreta);

    fclose(f);//é necessário fechar o arquivo
}

//--> Desenha Forca e Letras acertadas
void desenhaforca() {

    printf("Voce ja deu %d chutes\n", chutesdados);

    for(int i = 0; i < (int)tamanho; i++) {

        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int acertou(){
    for (int i = 0; i < (int)tamanho; i++){
        if(!jachutou(palavrasecreta[i])){
            return 0;
        }
    }
    return 1;
}

//--> Identifica se o número de chutes foi atingido
int enforcou(){
    int erros = 0;
    for (int i = 0; i < chutesdados; i++){
        int existe = 0;
        
        for (int j = 0; j < (int)tamanho; j++){
            if(chutes[i] == palavrasecreta[j]){
                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }
    return erros >= 5;
}

//Main -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main() {

    escolhepalavra();
    header();

    do{
        desenhaforca();
        chuta();
  
    }while(!acertou() && !enforcou());
}