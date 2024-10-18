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
    int dano;
}habilidade;

typedef struct {
    char nome[maxCaracter];
    char tipo[maxCaracter];
    int vida;
    habilidade habilidades[qntSkills];
    int danoHabilidades[qntSkills];
} pokemon;

typedef struct {
    char nome[maxCaracter];
    pokemon pokemonsEscolhidos[qntPokemon];
    int jaEscolhido[qntPokemon];
    pokemon pokemonEmCampo;
} jogador;

typedef struct
{
    pokemon* pokemons;
    int tamanho;
} listaDePokemonsEnfretados;

listaDePokemonsEnfretados inicializarLista() {
    listaDePokemonsEnfretados lista;
    lista.pokemons = NULL;  // Inicialmente sem pokemons
    lista.tamanho = 0;      // Tamanho inicial é zero
    return lista;
}

// Função para inicializar uma habilidade
void inicializarHabilidade(habilidade* h, const char* nome, const char* tipo, int dano) {
    strcpy(h->nome, nome);
    strcpy(h->tipo, tipo);
    h->dano = dano;
}


// Tabela de efetividade dos tipos
float tabelaEfetividade[totalTipos][totalTipos] = {
    // Normal, Fogo, Água, Planta, Elétrico, Gelo, Lutador, Venenoso, Terra, Voador, Psíquico, Inseto, Rocha, Fantasma, Dragão, Sombrio, Fada
    { 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Normal
    { 1,   1,   3,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1 }, // Fogo
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

// Função para obter a efetividade do ataque
float obterEfetividade(const char* tipoAtacante, const char* tipoDefensivo) {
    int indiceAtacante = encontrarTipo(tipoAtacante);
    int indiceDefensivo = encontrarTipo(tipoDefensivo);

    if (indiceAtacante != -1 && indiceDefensivo != -1) {
        printf("Índice do tipo atacante (%s): %d\n", tipoAtacante, indiceAtacante);
        printf("Índice do tipo defensivo (%s): %d\n", tipoDefensivo, indiceDefensivo);
        return tabelaEfetividade[indiceAtacante][indiceDefensivo];
    }
    return 1; // Retorna 1 se não encontrar algum dos tipos
}

//Função que adiciona os pokemons derrotados pelo jogador em uma lista para printar depois
void adicionarPokemonDerrotado(listaDePokemonsEnfretados* lista, pokemon novoPokemon){
    lista->tamanho++;
    lista->pokemons = (pokemon*)realloc(lista->pokemons, lista->tamanho * sizeof(pokemon));
    if (lista->pokemons == NULL)
    {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
    lista->pokemons[lista->tamanho - 1] = novoPokemon;   
}

void inicializarPokemon(pokemon pokemons[]) {
    // Inicializando o primeiro Pokémon
    strcpy(pokemons[0].nome, "Nome1");
    strcpy(pokemons[0].tipo, "Fogo");
    pokemons[0].vida = 100;
    inicializarHabilidade(&pokemons[0].habilidades[0], "Habilidade 1", "Fogo", 40);
    inicializarHabilidade(&pokemons[0].habilidades[1], "Habilidade 2", "Agua", 30);
    inicializarHabilidade(&pokemons[0].habilidades[2], "Habilidade 3", "Terra", 20);

    // Inicializando o segundo Pokémon
    strcpy(pokemons[1].nome, "Nome2");
    strcpy(pokemons[1].tipo, "Tipo2");
    pokemons[1].vida = 100;
    inicializarHabilidade(&pokemons[1].habilidades[0], "Habilidade 1", "Vento", 35);
    inicializarHabilidade(&pokemons[1].habilidades[1], "Habilidade 2", "Eletrico", 25);
    inicializarHabilidade(&pokemons[1].habilidades[2], "Habilidade 3", "Gelo", 15);

    // Inicializando o terceiro Pokémon
    strcpy(pokemons[2].nome, "Nome3");
    strcpy(pokemons[2].tipo, "Tipo3");
    pokemons[2].vida = 100;
    inicializarHabilidade(&pokemons[2].habilidades[0], "Habilidade 1", "Fogo", 50);
    inicializarHabilidade(&pokemons[2].habilidades[1], "Habilidade 2", "Agua", 40);
    inicializarHabilidade(&pokemons[2].habilidades[2], "Habilidade 3", "Terra", 30);
}


void imprimirPokemons(pokemon pokemons[], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Pokemon %d: \nNome: %s - Tipo: %s - Vida: %d \nHabilidades: ", 
                i + 1, pokemons[i].nome, pokemons[i].tipo, pokemons[i].vida);
        for (int j = 0; j < qntSkills; j++) {
            printf("%s (Dano: %d)", pokemons[i].habilidades[j].nome, pokemons[i].habilidades[j].dano);
            if (j < qntSkills - 1) {
                printf(", ");  // Adiciona uma vírgula entre as habilidades, mas não após a última
            }
        }
        printf("\n\n");
    }
}



void escolherPokemon(jogador *player, pokemon pokemonsDisponiveis[], int totalDisponiveis) {
    int escolha, numEscolhas = 0;


    // Reseta o array de controle para o jogador atual
    for (int i = 0; i < totalDisponiveis; i++) {
        player->jaEscolhido[i] = 0;
    }

    while (numEscolhas < qntPokemon) {
        printf("%s, escolha seu Pokémon %d:\n", player->nome, numEscolhas + 1);
        imprimirPokemons(pokemonsDisponiveis, totalDisponiveis);
        printf("Digite o número do Pokémon que deseja escolher (1 a %d): ", totalDisponiveis);
        scanf("%d", &escolha);

        if (escolha < 1 || escolha > totalDisponiveis) {
            printf("Escolha inválida, tente novamente.\n");
        } else if (player->jaEscolhido[escolha - 1]) {
            printf("Você já escolheu este Pokémon, escolha outro.\n");
        } else {
            // Armazena a escolha do Pokémon
            player->pokemonsEscolhidos[numEscolhas] = pokemonsDisponiveis[escolha - 1];
            player->jaEscolhido[escolha - 1] = 1; // Marca o Pokémon como já escolhido para este jogador
            numEscolhas++;
            printf("Você escolheu: %s\n\n", pokemonsDisponiveis[escolha - 1].nome);
        }
    }
}


void pokemonEmCampo(jogador* player) {
    int escolha = 0;
    imprimirPokemons(player->pokemonsEscolhidos, qntPokemon);
    printf("Jogador %s escolha o pokemon em Campo (1 a %d): ", player->nome, qntPokemon);
    scanf("%d", &escolha);

    // Corrige o acesso ao índice
    if (escolha >= 1 && escolha <= qntPokemon) {
        player->pokemonEmCampo = player->pokemonsEscolhidos[escolha - 1];
        printf("O jogador %s escolheu o pokemon %s\n", player->nome, player->pokemonEmCampo.nome);
    } else {
        printf("Escolha inválida.\n");
    }
}


void pausar() {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');  // Limpa qualquer caractere residual no buffer
    getchar();  // Aguarda o Enter do usuário
}


void combate(jogador* player1, jogador* player2) {
    printf("--------------------------------------------------------\n                  FASE DE COMBATE\n--------------------------------------------------------\n\n");
    
    printf("Jogador %s ataca com %s\n", player1->nome, player1->pokemonEmCampo.nome);
    printf("Escolha qual ataque fazer:\n");
    for (int i = 0; i < qntSkills; i++) {
        printf("%d: %s (Dano: %d)\n", i + 1, player1->pokemonEmCampo.habilidades[i].nome, player1->pokemonEmCampo.habilidades[i].dano);
    }

    int escolhaAtaque;
    scanf("%d", &escolhaAtaque);
    
    if (escolhaAtaque < 1 || escolhaAtaque > qntSkills) {
        printf("Escolha de ataque inválida.\n");
        return;
    }

    // Aqui você pode aplicar o dano ao Pokémon do adversário
    int multiplicador = obterEfetividade(player1->pokemonEmCampo.habilidades->tipo, player2->pokemonEmCampo.tipo);
    player2->pokemonEmCampo.vida -= player1->pokemonEmCampo.habilidades->dano * multiplicador;
    
    printf("O Pokémon %s sofreu %d de dano!\n", player2->pokemonEmCampo.nome, player1->pokemonEmCampo.habilidades->dano * multiplicador);

    printf("Vida do pokemon em campo de %s: %d", player2->nome, player2->pokemonEmCampo.vida);
}


int main() {
    jogador player1, player2;
    listaDePokemonsEnfretados pokemonsDerrotados = inicializarLista();
    pokemon pokemonsDisponiveis[totalPokemons];
    int jaEscolhido[totalPokemons] = {0};  // Array para rastrear pokémons já escolhidos

    // Inicializa os pokémons disponíveis
    inicializarPokemon(pokemonsDisponiveis);

    // Defina o nome dos jogadores
    printf("Jogador 1 Digite seu nome: ");
    scanf("%s", player1.nome);
    printf("Jogador 2 Digite seu nome: ");
    scanf("%s", player2.nome);

        // Jogador 1 e Jogador 2 escolhem pokémons alternadamente
    printf("Escolha dos Pokémons\n\n");
    
    escolherPokemon(&player1, pokemonsDisponiveis, totalPokemons);
    escolherPokemon(&player2, pokemonsDisponiveis, totalPokemons);


    // Exibe os pokémons escolhidos pelos jogadores
    printf("\nPokémons escolhidos por %s:\n", player1.nome);
    imprimirPokemons(player1.pokemonsEscolhidos, qntPokemon);

    printf("\nPokémons escolhidos por %s:\n", player2.nome);
    imprimirPokemons(player2.pokemonsEscolhidos, qntPokemon);

    system("clear");

    pokemonEmCampo(&player1);

    pausar();
    system("clear");

    pokemonEmCampo(&player2);

    system("clear");


    combate(&player1, &player2);


    return 0;
}
