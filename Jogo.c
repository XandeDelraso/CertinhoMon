#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxCaracter 50
#define totalPokemons 3
#define qntSkills 3
#define qntPokemon 2
#define totalTipos 18
#define danoBase 2

typedef struct {
    char nome[maxCaracter];
    char tipo[maxCaracter];
    int vida;
    char habilidades[qntSkills][maxCaracter];
} pokemon;

typedef struct {
    char nome[maxCaracter];
    pokemon pokemonsDisponiveis[totalPokemons];
    pokemon pokemonsEscolhidos[qntPokemon];
    int escolhasFeitas; // Adiciona um contador para as escolhas feitas
} jogador;

void inicializarPokemon(pokemon pokemons[]) {
    // Pokemon 1
    strcpy(pokemons[0].nome, "Nome1");
    strcpy(pokemons[0].tipo, "Tipo1");
    pokemons[0].vida = 10;
    strcpy(pokemons[0].habilidades[0], "Nome habilidade1");
    strcpy(pokemons[0].habilidades[1], "Nome habilidade2");
    strcpy(pokemons[0].habilidades[2], "Nome habilidade3");

    // Pokemon 2
    strcpy(pokemons[1].nome, "Nome2");
    strcpy(pokemons[1].tipo, "Tipo2");
    pokemons[1].vida = 10;
    strcpy(pokemons[1].habilidades[0], "Nome habilidade1");
    strcpy(pokemons[1].habilidades[1], "Nome habilidade2");
    strcpy(pokemons[1].habilidades[2], "Nome habilidade3");

    // Pokemon 3
    strcpy(pokemons[2].nome, "Nome3");
    strcpy(pokemons[2].tipo, "Tipo3");
    pokemons[2].vida = 10;
    strcpy(pokemons[2].habilidades[0], "Nome habilidade1");
    strcpy(pokemons[2].habilidades[1], "Nome habilidade2");
    strcpy(pokemons[2].habilidades[2], "Nome habilidade3");
}

void exibirPokemonsDisponiveis(pokemon pokemons[], int numPokemons) {
    for (int i = 0; i < numPokemons; i++) {
        printf("Informações do Pokémon %d: \n", i + 1);
        printf("  Nome: %s\n", pokemons[i].nome);
        printf("  Tipo: %s\n", pokemons[i].tipo);
        printf("  Vida: %d\n", pokemons[i].vida);
        printf("  Habilidades:\n");
        for (int j = 0; j < qntSkills; j++) {
            printf("    - %s\n", pokemons[i].habilidades[j]);
        }
        printf("\n");
    }
}

void exibirPokemonsEscolhidos(pokemon pokemons[], int numPokemons) {
    for (int i = 0; i < numPokemons; i++) {
        printf("  - %s (Tipo: %s, Vida: %d)\n", pokemons[i].nome, pokemons[i].tipo, pokemons[i].vida);
    }
}

void mostrarMenu() {
    printf("=== Bem-vindo ao Jogo de Pokémon ===\n");
    printf("1. Começar Jogo\n");
    printf("2. Regras do Jogo\n");
    printf("3. Sair\n");
}

void menuJogo() {
    printf("1. Escolher Pokémon\n");
    printf("2. Loja\n");
    printf("3. Sair do Jogo\n");
}

void escolherPokemon(jogador* jogador, int i) {
    int escolha;

    printf("Jogador %s, escolha o %dº Pokémon (Digite o número correspondente): \n", jogador->nome, i + 1);
    exibirPokemonsDisponiveis(jogador->pokemonsDisponiveis, totalPokemons);
    scanf("%d", &escolha);

    // Validação da escolha
    if (escolha < 1 || escolha > totalPokemons) {
        printf("Escolha inválida.\n");
        return;
    }

    escolha -= 1;  // Ajusta o índice para começar de 0
    jogador->pokemonsEscolhidos[i] = jogador->pokemonsDisponiveis[escolha];
    printf("Você escolheu o Pokémon %s\n", jogador->pokemonsEscolhidos[i].nome);
    jogador->escolhasFeitas++;
}

void EscolhasDoJogador(jogador* jogador) {
    int i = jogador->escolhasFeitas; // Inicia a escolha pelo número de escolhas feitas
    int opcao2;
    char confirmar;

    while (i < qntPokemon) {
        system("clear");  
        menuJogo();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao2);

        // Limpar o buffer do scanf
        while (getchar() != '\n');

        switch (opcao2) {
            case 1:
                system("clear");  
                escolherPokemon(jogador, i);
                i++;
                break;

            case 2:
                printf("Entrando na loja...\n");
                break;

            case 3:
                do {
                    printf("Você tem certeza que deseja sair do jogo? S/N: ");
                    scanf(" %c", &confirmar); 
                 
                    while (getchar() != '\n');

                    if (confirmar == 's' || confirmar == 'S') {
                        system("clear");  
                        printf("Volte sempre!\n");
                        exit(0); // Sai do programa
                    } else if (confirmar == 'n' || confirmar == 'N') {
                        return; // Retorna ao menu anterior
                    }
                } while (confirmar != 'n' && confirmar != 's' && confirmar != 'S' && confirmar != 'N');
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }
}

// Tabela de efetividade dos tipos
float tabelaEfetividade[totalTipos][totalTipos] = {
    // Normal, Fogo, Água, Planta, Elétrico, Gelo, Lutador, Venenoso, Terra, Voador, Psíquico, Inseto, Rocha, Fantasma, Dragão, Sombrio, Fada
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Normal
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Fogo
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Água
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Planta
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Elétrico
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Gelo
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Lutador
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Venenoso
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Terra
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Voador
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Psíquico
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Inseto
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Rocha
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Fantasma
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Dragão
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Sombrio
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }  // Fada
};



// Função para encontrar o tipo do Pokémon
int encontrarTipo(const char* tipo) {
    const char* tipos[totalTipos] = {
        "Normal", "Fogo", "Água", "Planta", "Elétrico", "Gelo", "Lutador", "Venenoso", "Terra", "Voador",
        "Psíquico", "Inseto", "Rocha", "Fantasma", "Dragão", "Sombrio", "Fada"
    };

    for (int i = 0; i < totalTipos; i++) {
        if (strcmp(tipo, tipos[i]) == 0) {
            return i;
        }
    }
    return -1; // Tipo não encontrado
}

int calcularDano(const pokemon* atacante, const pokemon* defensor) {
    int indiceAtacante = encontrarTipo(atacante->tipo);
    int indiceDefensor = encontrarTipo(defensor->tipo);
    float efetividade;

    if (indiceAtacante == -1 || indiceDefensor == -1) {
        printf("Tipos inexistentes na matriz");
        return danoBase;
    }
    efetividade = tabelaEfetividade[indiceAtacante][indiceDefensor];
    return danoBase * efetividade;
}

void menuBatalha() {
    printf("1. Escolha o pokemon que realizará a função \n");
    printf("2. Listar meus pokemons\n\n");
    printf("Escolha: ");
}

void batalha(jogador jogador1, jogador jogador2){
    while (
        (jogador1.pokemonsEscolhidos[0].vida > 0 || jogador1.pokemonsEscolhidos[1].vida > 0) &&
        (jogador2.pokemonsEscolhidos[0].vida > 0 || jogador2.pokemonsEscolhidos[1].vida > 0)
        )
    {
        if (jogador1.pokemonsEscolhidos[0].vida <= 0 && jogador1.pokemonsEscolhidos[1].vida <= 0)
        {
            system("clear");
            printf("Jogador 2 é o vencedor da batalha!!");
            break;
        }
        else if (jogador2.pokemonsEscolhidos[0].vida <= 0 && jogador2.pokemonsEscolhidos[1].vida <= 0)
        {
            system("clear");
            printf("Jogador 1 é o vencedor da batalha!!");
            break;
        }
        else
        {
            menuBatalha();
            int opcao2;
            printf("Escolha: ");
            scanf("%d", &opcao2);
            while (getchar() != '\n'); // Limpar o buffer

            switch (opcao2)
            {
            case 1:
                // Lógica para escolher o Pokémon que realizará a ação
                break;
            
            case 2:
                // Lógica para listar os Pokémons
                break;

            default:
                printf("Por favor, escolha uma opção válida\n");
                break;
            }
        }
    }
}


void jogo(jogador jogador1, jogador jogador2) {
    while (jogador1.escolhasFeitas < qntPokemon || jogador2.escolhasFeitas < qntPokemon) {
        if (jogador1.escolhasFeitas < qntPokemon) {
            printf("Jogador 1, é sua vez!\n");
            EscolhasDoJogador(&jogador1);
        }

        if (jogador2.escolhasFeitas < qntPokemon) {
            printf("Jogador 2, é sua vez!\n");
            EscolhasDoJogador(&jogador2);
        }
    }

    system("clear");  
    printf("Pokémons escolhidos por %s:\n", jogador1.nome);
    exibirPokemonsEscolhidos(jogador1.pokemonsEscolhidos, qntPokemon);
    printf("Pokémons escolhidos por %s:\n", jogador2.nome);
    exibirPokemonsEscolhidos(jogador2.pokemonsEscolhidos, qntPokemon);
    system("clear");

    batalha(jogador1, jogador2);
}



int main() {
    int opcao;
    jogador jogador1, jogador2;

    printf("Jogador 1, insira seu nome: ");
    fgets(jogador1.nome, sizeof(jogador1.nome), stdin);
    jogador1.nome[strcspn(jogador1.nome, "\n")] = 0;  // Remove newline
    jogador1.escolhasFeitas = 0;  // Inicializa as escolhas feitas como 0

    printf("Jogador 2, insira seu nome: ");
    fgets(jogador2.nome, sizeof(jogador2.nome), stdin);
    jogador2.nome[strcspn(jogador2.nome, "\n")] = 0;  // Remove newline
    jogador2.escolhasFeitas = 0;  // Inicializa as escolhas feitas como 0

    inicializarPokemon(jogador1.pokemonsDisponiveis);
    inicializarPokemon(jogador2.pokemonsDisponiveis);

    system("clear");  
    mostrarMenu();
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            jogo(jogador1, jogador2);
            break;

        case 2:
            printf("Regras do Jogo: ...\n");
            break;

        case 3:
            printf("Saindo do jogo...\n");
            exit(0);

        default:
            printf("Opção inválida!\n");
            break;
    }

    return 0;
}
