// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.

// Esse projeto se trata da PARTE 2 do famoso jogo chamado WAR, onde ampliamos
// as funcionalidades implementando a mecânica de ataque entre territórios,
// utilizando ponteiros, alocação dinâmica de memória e maior modularização.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
#define TERR_MAX 5

// --- Estrutura de Dados ---
typedef struct Territorio{
	char nome[30];
	char cor[10];
	int tropas;
}Territorio;

// --- Protótipos das Funções ---
void LimparBufferEntrada();
Territorio* alocarMapa();
void inicializarTerritorios(Territorio* mapa);
void exibirMapa(const Territorio* mapa);
void faseDeAtaque(Territorio* mapa);
void simularAtaque(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

// Função utilitária
void LimparBufferEntrada(){
	int x; 
	while ((x = getchar()) != '\n' && x != EOF);
}

// --- Função Principal (main) ---
int main() {

    Territorio* expansao = alocarMapa();

    if (expansao == NULL){
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

	printf("=============================== \n");
	printf("----- Bem-vindo ao jogo War! ----- \n");
	printf("=============================== \n\n");

    printf("Vamos cadastrar os territorios do nosso mundo. \n\n");

    inicializarTerritorios(expansao);

    srand(time(NULL));

    int opcao;

    do {
        exibirMapa(expansao);

        printf("\nMENU:\n");
        printf("1 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        LimparBufferEntrada();

        switch(opcao){
            case 1:
                faseDeAtaque(expansao);
                break;
            case 0:
                printf("Encerrando jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

        if (opcao != 0){
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while(opcao != 0);

    liberarMemoria(expansao);

    return 0;
}

// --- Implementação das Funções ---

Territorio* alocarMapa(){
    return (Territorio*) calloc(TERR_MAX, sizeof(Territorio));
}

void inicializarTerritorios(Territorio* expansao){
	for (int i = 0; i < TERR_MAX; i++) {
		printf("\n--- Cadastrando Territorio %d --- \n", (i + 1));
		
		printf("Nome do Territorio:");
		fgets(expansao[i].nome, sizeof(expansao[i].nome), stdin); 
		
		printf("Cor do Exercito (ex: Azul, Verde):");
		fgets(expansao[i].cor, sizeof(expansao[i].cor), stdin);
		
		expansao[i].nome[strcspn(expansao[i].nome, "\n")] = '\0';
		expansao[i].cor[strcspn(expansao[i].cor, "\n")] = '\0';
		
		printf("Numero de Tropas:");
		scanf("%d", &expansao[i].tropas); 
		
		LimparBufferEntrada();
	}
}

void exibirMapa(const Territorio* expansao){
	printf("\n =============================== \n");
    printf("MAPA DO MUNDO - ESTADO ATUAL \n");
	printf("=============================== \n\n");
	
	for (int i = 0; i < TERR_MAX; i++){
	    printf("\nTERRITORIO %d: \n", (i + 1));
	    printf("  - Nome: %s \n", expansao[i].nome);
	    printf("  - Dominado por: Exercito %s \n", expansao[i].cor);
	    printf("  - Tropas: %d \n", expansao[i].tropas);
	}
}

void faseDeAtaque(Territorio* expansao){
    int atacante, defensor;

    printf("\nEscolha o territorio atacante (numero): ");
    scanf("%d", &atacante);

    printf("Escolha o territorio defensor (numero): ");
    scanf("%d", &defensor);

    LimparBufferEntrada();

    atacante--;
    defensor--;

    if (atacante == defensor){
        printf("Erro: nao pode atacar o mesmo territorio.\n");
        return;
    }

    if (strcmp(expansao[atacante].cor, expansao[defensor].cor) == 0){
        printf("Erro: territorios da mesma cor!\n");
        return;
    }

    if (expansao[atacante].tropas <= 1){
        printf("Erro: tropas insuficientes para atacar!\n");
        return;
    }

    simularAtaque(&expansao[atacante], &expansao[defensor]);
}

void simularAtaque(Territorio* atacante, Territorio* defensor){
	
	int dadoAtacante = rand() % 6 + 1;
	int dadoDefensor = rand() % 6 + 1;
	
	printf("\n--- BATALHA ---\n");
	printf("Atacante (%s) rolou: %d\n", atacante->nome, dadoAtacante);
	printf("Defensor (%s) rolou: %d\n", defensor->nome, dadoDefensor);
	
	if (dadoAtacante > dadoDefensor){
		printf(">> O atacante venceu!\n");
		
		strcpy(defensor->cor, atacante->cor);
		
		int tropasTransferidas = atacante->tropas / 2;
		defensor->tropas = tropasTransferidas;
		atacante->tropas -= tropasTransferidas;
		
	} else {
		printf(">> O defensor resistiu!\n");
		
		if (atacante->tropas > 1){
			atacante->tropas--;
		}
	}
}

void liberarMemoria(Territorio* mapa){
	free(mapa);
}
