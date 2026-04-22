// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// Esse projeto se trata da PARTE FINAL do jogo WAR, onde implementamos o sistema
// de missões estratégicas, utilizando ponteiros, alocação dinâmica e verificação
// de condições de vitória.
//
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TERR_MAX 5

typedef struct Territorio{
	char nome[30];
	char cor[10];
	int tropas;
}Territorio;

// --- Protótipos ---
void LimparBufferEntrada();
Territorio* alocarMapa();
void inicializarTerritorios(Territorio* mapa);
void exibirMapa(const Territorio* mapa);
void faseDeAtaque(Territorio* mapa);
void simularAtaque(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa, char* missao);

void atribuirMissao(char* destino, char* missoes[], int total);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void exibirMissao(char* missao);

// --- Funções ---
void LimparBufferEntrada(){
	int x; 
	while ((x = getchar()) != '\n' && x != EOF);
}

Territorio* alocarMapa(){
	return (Territorio*) calloc(TERR_MAX, sizeof(Territorio));
}

void inicializarTerritorios(Territorio* expansao){
	for (int i = 0; i < TERR_MAX; i++) {
		printf("\n--- Cadastrando Territorio %d --- \n", (i + 1));
		
		printf("Nome do Territorio:");
		fgets(expansao[i].nome, sizeof(expansao[i].nome), stdin); 
		
		printf("Cor do Exercito:");
		fgets(expansao[i].cor, sizeof(expansao[i].cor), stdin);
		
		expansao[i].nome[strcspn(expansao[i].nome, "\n")] = '\0';
		expansao[i].cor[strcspn(expansao[i].cor, "\n")] = '\0';
		
		printf("Numero de Tropas:");
		scanf("%d", &expansao[i].tropas); 
		
		LimparBufferEntrada();
	}
}

void exibirMapa(const Territorio* expansao){
	printf("\n===== MAPA =====\n");
	for (int i = 0; i < TERR_MAX; i++){
	    printf("\nTERRITORIO %d\n", (i + 1));
	    printf("Nome: %s\n", expansao[i].nome);
	    printf("Cor: %s\n", expansao[i].cor);
	    printf("Tropas: %d\n", expansao[i].tropas);
	}
}

void faseDeAtaque(Territorio* expansao){
	int a, d;

	printf("\nAtacante: ");
	scanf("%d", &a);

	printf("Defensor: ");
	scanf("%d", &d);

	LimparBufferEntrada();

	a--; d--;

	if (a == d) return;

	if (strcmp(expansao[a].cor, expansao[d].cor) == 0) return;

	if (expansao[a].tropas <= 1) return;

	simularAtaque(&expansao[a], &expansao[d]);
}

void simularAtaque(Territorio* atacante, Territorio* defensor){
	int da = rand()%6+1;
	int dd = rand()%6+1;

	printf("\nAtacante rolou %d | Defensor rolou %d\n", da, dd);

	if (da > dd){
		printf("Atacante venceu!\n");

		strcpy(defensor->cor, atacante->cor);

		int tropas = atacante->tropas / 2;
		defensor->tropas = tropas;
		atacante->tropas -= tropas;
	}
	else{
		printf("Defensor venceu!\n");
		atacante->tropas--;
	}
}

// -------- MISSÕES --------

void atribuirMissao(char* destino, char* missoes[], int total){
	int sorteio = rand() % total;
	strcpy(destino, missoes[sorteio]);
}

void exibirMissao(char* missao){
	printf("\n=== SUA MISSAO ===\n%s\n", missao);
}

int verificarMissao(char* missao, Territorio* mapa, int tamanho){

	// Missão simples: conquistar 3 territórios da mesma cor
	int contador = 0;
	char corJogador[10];

	strcpy(corJogador, mapa[0].cor);

	for(int i = 0; i < tamanho; i++){
		if(strcmp(mapa[i].cor, corJogador) == 0){
			contador++;
		}
	}

	if(contador >= 3){
		return 1;
	}

	return 0;
}

void liberarMemoria(Territorio* mapa, char* missao){
	free(mapa);
	free(missao);
}

// --- MAIN ---
int main(){

	srand(time(NULL));

	Territorio* expansao = alocarMapa();

	char* missao = (char*) malloc(100 * sizeof(char));

	char* missoes[] = {
		"Conquistar 3 territorios",
		"Dominar a maior parte do mapa",
		"Eliminar um inimigo",
		"Controlar territorios com mais de 10 tropas",
		"Expandir continuamente"
	};

	printf("============= Bem-vindo ao jogo WAR =============\n");

	inicializarTerritorios(expansao);

	atribuirMissao(missao, missoes, 5);

	exibirMissao(missao);

	int opcao;

do{
    exibirMapa(expansao);

    printf("\nMENU:\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    LimparBufferEntrada();

    switch(opcao){
        case 1:
            faseDeAtaque(expansao);
            break;

        case 2:
            if(verificarMissao(missao, expansao, TERR_MAX)){
                printf("\n*** PARABENS! VOCE JA CUMPRIU SUA MISSAO! ***\n");
            } else {
                printf("\nVoce ainda nao cumpriu a missao... volte a lutar!\n");
            }
            break;

        case 0:
            printf("Encerrando jogo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
    }

    // Verificação automática continua existindo (requisito do desafio)
    if(verificarMissao(missao, expansao, TERR_MAX)){
        printf("\n*** VOCE VENCEU A MISSAO! ***\n");
        break;
    }

    if(opcao != 0){
        printf("\nPressione ENTER para continuar...");
        getchar();
    }

}while(opcao != 0);
	liberarMemoria(expansao, missao);

	return 0;
}
