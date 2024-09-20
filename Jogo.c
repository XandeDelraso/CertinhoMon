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
    pokemon pokemonEmCampo;
    int escolhasFeitas;
} jogador;

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

void inicializarPokemon(pokemon pokemons[]) {
    strcpy(pokemons[0].nome, "Nome1");
    strcpy(pokemons[0].tipo, "Tipo1");
    pokemons[0].vida = 100;
    strcpy(pokemons[0].habilidades[0], "Habilidade 1");
    strcpy(pokemons[0].habilidades[1], "Habilidade 2");
    strcpy(pokemons[0].habilidades[2], "Habilidade 3");

    strcpy(pokemons[1].nome, "Nome2");
    strcpy(pokemons[1].tipo, "Tipo2");
    pokemons[1].vida = 100;
    strcpy(pokemons[1].habilidades[0], "Habilidade 1");
    strcpy(pokemons[1].habilidades[1], "Habilidade 2");
    strcpy(pokemons[1].habilidades[2], "Habilidade 3");

    strcpy(pokemons[2].nome, "Nome3");
    strcpy(pokemons[2].tipo, "Tipo3");
    pokemons[2].vida = 100;
    strcpy(pokemons[2].habilidades[0], "Habilidade 1");
    strcpy(pokemons[2].habilidades[1], "Habilidade 2");
    strcpy(pokemons[2].habilidades[2], "Habilidade 3");
}

void exibirPokemonsDisponiveis(jogador* jogadorAtual) {
    printf("\nPokémons disponíveis para %s:\n", jogadorAtual->nome);
    for (int i = 0; i < totalPokemons; i++) {
        printf("%d. %s (Tipo: %s, Vida: %d)\n", i + 1, jogadorAtual->pokemonsDisponiveis[i].nome,
               jogadorAtual->pokemonsDisponiveis[i].tipo, jogadorAtual->pokemonsDisponiveis[i].vida);
    }
}

void escolherPokemon(jogador* jogadorAtual, int escolha) {
    jogadorAtual->pokemonEmCampo = jogadorAtual->pokemonsDisponiveis[escolha - 1];
    //printf("\n%s escolheu %s como seu pokémon em campo!\n", jogadorAtual->nome, jogadorAtual->pokemonEmCampo.nome);
}

void exibirPokemonsEscolhidos(pokemon pokemons[], int numPokemons) {
    for (int i = 0; i < numPokemons; i++) {
        printf("  - %s (Tipo: %s, Vida: %d)\n", pokemons[i].nome, pokemons[i].tipo, pokemons[i].vida);
    }
}

void realizarAtaque(jogador* atacante, jogador* defensor) {
    int dano = danoBase; // Pode ser ajustado com base no tipo e habilidades
    defensor->pokemonEmCampo.vida -= dano;
    printf("\n%s atacou %s, causando %d de dano!\n", atacante->pokemonEmCampo.nome, defensor->pokemonEmCampo.nome, dano);
    printf("%s agora tem %d de vida restante.\n", defensor->pokemonEmCampo.nome, defensor->pokemonEmCampo.vida);
}

void jogo(jogador jogador1, jogador jogador2) {
    int escolha1, escolha2;
    int acoes;

    for (int i = 0; i < qntPokemon; i++)
    {
            // Jogadores escolhem seus pokémons
    printf("\n%s, escolha seu pokémon:\n", jogador1.nome);
    exibirPokemonsDisponiveis(&jogador1);
    printf("Escolha (1-%d): ", totalPokemons);
    scanf("%d", &escolha1);
    escolherPokemon(&jogador1, escolha1);

    printf("\n%s, escolha seu pokémon:\n", jogador2.nome);
    exibirPokemonsDisponiveis(&jogador2);
    printf("Escolha (1-%d): ", totalPokemons);
    scanf("%d", &escolha2);
    escolherPokemon(&jogador2, escolha2);
    }

    printf("Jogador %s escolha com qual pokemon irá começar:", jogador1.nome);
    exibirPokemonsEscolhidos(jogador1.pokemonsEscolhidos, qntPokemon);

    
   
    // Loop de batalha
    while (
        (jogador1.pokemonsEscolhidos[0].vida > 0 || jogador1.pokemonsEscolhidos[1].vida > 0) &&
        (jogador2.pokemonsEscolhidos[0].vida > 0 || jogador2.pokemonsEscolhidos[1].vida > 0)
    ) {
        printf("Jogador %s que será sua ação:");
        system("clear");
        printf("=============Escolhas Inválidas farão voce perder a vez=============");
        printf("1. Trocar de Pokemon");
        printf("2. Atacar com o %s", jogador1.pokemonsEscolhidos);
        printf("3. Listar os Ataques do %s", jogador1.pokemonsEscolhidos);
        printf("4. Loja");
        printf("5. Desistir");

        switch (acoes)
        {
        case 1: /* constant-expression */
            //Função de trocar o pokemon escolhido
            break;
        
        case 2:

            break;
        
        case 3:
            
            break;

        case 4:
            
            break;

        case 5:
            
            break;
        default:
            printf("Perdeu a vez");
            break;
        }


            
        // Jogador 1 ataca
        //realizarAtaque(&jogador1, &jogador2);

        // Verifica se o Pokémon do jogador 2 ainda está vivo
        if (jogador2.pokemonEmCampo.vida <= 0) {
            printf("\n%s venceu a batalha!\n", jogador1.nome);
            break;
        }

        // Jogador 2 ataca
        //realizarAtaque(&jogador2, &jogador1);

        // Verifica se o Pokémon do jogador 1 ainda está vivo
        if (jogador1.pokemonEmCampo.vida <= 0) {
            printf("\n%s venceu a batalha!\n", jogador2.nome);
            break;
        }
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

int main() {
    jogador jogador1, jogador2;
    pokemon pokemons[totalPokemons];

    // Inicializando os pokémons disponíveis
    inicializarPokemon(pokemons);

    // Atribuindo os pokémons disponíveis para os jogadores
    for (int i = 0; i < totalPokemons; i++) {
        jogador1.pokemonsDisponiveis[i] = pokemons[i];
        jogador2.pokemonsDisponiveis[i] = pokemons[i];
    }

    jogador1.escolhasFeitas = 0;
    jogador2.escolhasFeitas = 0;

    // Nome dos jogadores
    printf("Jogador 1, insira seu nome: ");
    fgets(jogador1.nome, maxCaracter, stdin);
    jogador1.nome[strcspn(jogador1.nome, "\n")] = 0;

    printf("Jogador 2, insira seu nome: ");
    fgets(jogador2.nome, maxCaracter, stdin);
    jogador2.nome[strcspn(jogador2.nome, "\n")] = 0;

    int opcaoMenu;
    mostrarMenu();
    printf("Escolha uma opção: ");
    scanf("%d", &opcaoMenu);

    switch (opcaoMenu) {
        case 1:
            jogo(jogador1, jogador2);
            break;
        case 2:
            printf("Regras do jogo: Cada jogador escolhe um Pokémon e eles batalham até que um perca toda a vida.\n");
            break;
        case 3:
            printf("Saindo do jogo. Até a próxima!\n");
            break;
        default:
            printf("Opção inválida!\n");
    }

    return 0;
}
