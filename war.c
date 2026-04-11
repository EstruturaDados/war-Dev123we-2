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

// Esse projeto se trata da PARTE 1 do famoso jogo chamado WAR, aqui utilizamos e
//   e reforçamos os conceitos da metodologia struct para fazer com que nosso código
//   fique mais organizado e legível. 
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <string.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define TERR_MAX 5 //Necessitei de apenas uma constante.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct Territorio{ // Esta é nossa struct com o apelido territorio, utilizei o typdef
	char nome[30];         // para garantir um código mais legível.
	char cor[10];
	int tropas;
}Territorio;

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:
void LimparBufferEntrada(){ // Função limpar buffer de entrada.
	int x; 
	while ((x = getchar()) != '\n' && x != EOF);
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.
    Territorio expansao[TERR_MAX]; // Array do tipo Territorrio que vamos utilizar para manipular cada
	                               // elemento da struct.
	
	printf("=============================== \n");
	printf("----- Bem-vindo ao jogo War! ----- \n"); // Apresentação do jogo
	printf("=============================== \n\n");

    printf("Vamos cadastrar os 5 territorios inicias do nosso mundo. \n\n");

    // Aqui iniciamos o for responsável por captar os dados dos 5 territórios.
	
	for (int i = 0; i < TERR_MAX; i++) {
		printf("\n--- Cadastrando Territorio %d --- \n", (i + 1));
		
		// Entrada de dados
		printf("Nome do Territorio:");
		fgets(expansao[i].nome, sizeof(expansao[i].nome), stdin); 
		
		printf("Cor do Exercito (ex: Azul, Verde):");
		fgets(expansao[i].cor, sizeof(expansao[i].cor), stdin);
		
		expansao[i].nome[strcspn(expansao[i].nome, "\n")] = '\0'; // O uso do strcspn() para garantir a remoção
		expansao[i].cor[strcspn(expansao[i].cor, "\n")] = '\0';  // dos "\n" de cada fgets.
		
		printf("Numero de Tropas:");
		scanf("%d", &expansao[i].tropas); 

        LimparBufferEntrada();  // a função limpar buffer é essencial nesta parte para garantir
		                        // a remoção do "\n" atribuida pelo scanf.
    }

    printf("\n =============================== \n");
    printf("MAPA DO MUNDO - ESTADO ATUAL \n");
	printf("=============================== \n\n");

    // for responsável pela impressão dos dados.
	for (int i = 0; i < TERR_MAX; i++){
	    printf("\nTERRITORIO %d: \n", (i + 1));
	    printf("  - Nome: %s \n", expansao[i].nome);
	    printf("  - Dominado por: Exercito %s \n", expansao[i].cor);
	    printf("  - Tropas: %d \n", expansao[i].tropas);
	}
    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
