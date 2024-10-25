#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maxCaracter 50
#define totalPokemons 3
#define qntSkills 3
#define qntPokemon 2
#define totalTipos 17
#define danoBase 2

int pokemonsVivos = qntPokemon;

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
    int vivo; // 0 = morto e 1 = vivo
} pokemon;

typedef struct {
    char nome[maxCaracter];
    pokemon pokemonsEscolhidos[qntPokemon];
    int jaEscolhido[qntPokemon];
    pokemon pokemonEmCampo;
    pokemon pokmonsMortos[qntPokemon];
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


// Definições dos tipos como strings
char* nomesTipos[totalTipos] = {
    "Normal", "Fogo", "Agua", "Planta", "Eletrico",
    "Gelo", "Lutador", "Venenoso", "Terra", "Voador",
    "Psiquico", "Inseto", "Rocha", "Fantasma", "Dragao",
    "Sombrio", "Fada"
};

// Tabela de efetividade dos tipos
int tabelaEfetividade[totalTipos][totalTipos] = {
    { 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Normal
    { 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Fogo
    { 2, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Água
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Planta
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Elétrico
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Gelo
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Lutador
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Venenoso
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Terra
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Voador
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Psíquico
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Inseto
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Rocha
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Fantasma
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Dragão
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }, // Sombrio
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }  // Fada
};


// Função que retorna o índice do tipo ou -1 se não encontrado
int retornaIndiceTipo(char* tipo) {
    // Itera sobre a lista de nomes para verificar se o tipo existe
    for (int i = 0; i < totalTipos; i++) {
        if (strcmp(nomesTipos[i], tipo) == 0) {
            return i; // Retorna o índice quando o tipo é encontrado
        }
    }

    return -1; // Retorna -1 se o tipo não for encontrado
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
    pokemons[0].vivo = 1;  // O Pokémon começa vivo
    inicializarHabilidade(&pokemons[0].habilidades[0], "Habilidade 1", "Fogo", 40);
    inicializarHabilidade(&pokemons[0].habilidades[1], "Habilidade 2", "Agua", 30);
    inicializarHabilidade(&pokemons[0].habilidades[2], "Habilidade 3", "Terra", 20);

    // Inicializando o segundo Pokémon
    strcpy(pokemons[1].nome, "Nome2");
    strcpy(pokemons[1].tipo, "Agua");
    pokemons[1].vida = 100;
    pokemons[1].vivo = 1;  // O Pokémon começa vivo
    inicializarHabilidade(&pokemons[1].habilidades[0], "Habilidade 1", "Vento", 35);
    inicializarHabilidade(&pokemons[1].habilidades[1], "Habilidade 2", "Eletrico", 25);
    inicializarHabilidade(&pokemons[1].habilidades[2], "Habilidade 3", "Gelo", 15);

    // Inicializando o terceiro Pokémon
    strcpy(pokemons[2].nome, "Nome3");
    strcpy(pokemons[2].tipo, "Terra");
    pokemons[2].vida = 100;
    pokemons[2].vivo = 1;  // O Pokémon começa vivo
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

void derrotarPokemon(pokemon *pokemon) {
    if (pokemon->vida <= 0) {
        pokemon->vivo = 0;  // Marca como morto
    }
}

void imprimirPokemonsVivos(pokemon pokemons[], int quantidade) {
    int contador = 1;  // Usado para numerar os Pokémons vivos corretamente
    for (int i = 0; i < quantidade; i++) {
        if (pokemons[i].vivo == 1) {  // Verifica se o Pokémon está vivo
            printf("Pokemon %d: \nNome: %s - Tipo: %s - Vida: %d \nHabilidades: ", 
                    contador, pokemons[i].nome, pokemons[i].tipo, pokemons[i].vida);
            for (int j = 0; j < qntSkills; j++) {
                printf("%s (Dano: %d)", pokemons[i].habilidades[j].nome, pokemons[i].habilidades[j].dano);
                if (j < qntSkills - 1) {
                    printf(", ");  // Adiciona uma vírgula entre as habilidades, mas não após a última
                }
            }
            printf("\n\n");
            contador++;  // Incrementa o número para o próximo Pokémon vivo
        }
    }

    if (contador == 1) {
        printf("Nenhum Pokémon vivo.\n");  // Se nenhum Pokémon estiver vivo
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
    int num = 0;

    // Contar quantos pokémons estão vivos
    for (int i = 0; i < qntPokemon; i++) {
        if (player->pokemonsEscolhidos[i].vida > 0) {
            num++;
        }
    }

    // Verificar se há pokémons vivos
    if (num == 0) {
        printf("Todos os pokémons de %s estão desmaiados.\n", player->nome);
        return;
    }

    // Imprimir pokémons vivos
    imprimirPokemonsVivos(player->pokemonsEscolhidos, qntPokemon);

    // Repetir até que o jogador faça uma escolha válida
    do {
        printf("Jogador %s, escolha o pokémon em campo (1 a %d): ", player->nome, num);
        scanf("%d", &escolha);

        if (escolha >= 1 && escolha <= num) {
            player->pokemonEmCampo = player->pokemonsEscolhidos[escolha - 1];
            printf("O jogador %s escolheu o pokémon %s\n", player->nome, player->pokemonEmCampo.nome);
        } else {
            printf("Escolha inválida. Tente novamente.\n");
        }

    } while (escolha < 1 || escolha > num);
}




void pausar() {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');  // Limpa qualquer caractere residual no buffer
    getchar();  // Aguarda o Enter do usuário
}


void exibirHabilidades(jogador* player) {
    printf("Escolha qual ataque fazer:\n");
    for (int i = 0; i < qntSkills; i++) {
        printf("%d: %s (Dano: %d)\n", i + 1, player->pokemonEmCampo.habilidades[i].nome, player->pokemonEmCampo.habilidades[i].dano);
    }
}

int escolherAtaque() {
    int escolhaAtaque;
    scanf("%d", &escolhaAtaque);
    return escolhaAtaque;
}

void aplicarDano(jogador* atacante, jogador* defensor, int ataqueIndex) {
        // Obtenha o índice do tipo atacante
    int tipoAtacante = retornaIndiceTipo(atacante->pokemonEmCampo.habilidades[ataqueIndex].tipo);
    // Obtenha o índice do tipo defensor
    int tipoDefensor = retornaIndiceTipo(defensor->pokemonEmCampo.tipo);
    int multiplicador = tabelaEfetividade[tipoAtacante][tipoDefensor];
    int danoCalculado = atacante->pokemonEmCampo.habilidades[ataqueIndex].dano * multiplicador;
    defensor->pokemonEmCampo.vida -= danoCalculado;

    printf("O Pokémon %s sofreu %d de dano!\n", defensor->pokemonEmCampo.nome, danoCalculado);
    printf("Vida do pokemon em campo de %s: %d\n", defensor->nome, defensor->pokemonEmCampo.vida);

}

void removerPokemonEscolhido(jogador* player, pokemon pokemonMorto) {
    for (int i = 0; i < qntPokemon; i++) {
        if (strcmp(player->pokemonsEscolhidos[i].nome, pokemonMorto.nome) == 0) {
            // Remover o Pokémon e reorganizar o array
            for (int j = i; j < qntPokemon - 1; j++) {
                player->pokemonsEscolhidos[j] = player->pokemonsEscolhidos[j + 1];
            }
            // Zera o último Pokémon da lista
            memset(&player->pokemonsEscolhidos[qntPokemon - 1], 0, sizeof(pokemon));
            break;
        }
    }
}

void verificarPokemonMorto(jogador* player) {
    if (player->pokemonEmCampo.vida <= 0) {
        pokemonsVivos--;  // Diminui a contagem de pokémons vivos
        int num = 0;

         // Contar quantos pokémons estão vivos
        for (int i = 0; i < qntPokemon; i++) {
            if (player->pokemonsEscolhidos[i].vida > 0) {
                num++;
            }
        }

        if (pokemonsVivos <= 0) {
            system("clear");
            printf("O jogador %s perdeu\n\n", player->nome); 
            exit(0); // Finaliza o jogo se o jogador não tiver mais pokémons vivos
        }

        printf("O Pokémon %s do jogador %s morreu! Será preciso trocar de Pokémon agora.\n", player->pokemonEmCampo.nome, player->nome);

        // Adiciona o Pokémon morto à lista de pokemonsMortos
        for (int i = 0; i < qntPokemon; i++) {
            if (strlen(player->pokmonsMortos[i].nome) == 0) {
                player->pokmonsMortos[i] = player->pokemonEmCampo;
                printf("Pokémon Morto: %s\n\n", player->pokmonsMortos[i].nome);
                removerPokemonEscolhido(player, player->pokemonEmCampo); // Remove o Pokémon morto da lista de escolhidos
                derrotarPokemon(&player->pokemonEmCampo); // Função que "zera" o Pokémon derrotado
                break; // Saímos do loop após encontrar um espaço vazio
            }
        }

        // Solicitar ao jogador que troque o Pokémon em campo
        printf("Jogador %s, escolha um novo Pokémon para o campo.\n", player->nome);
        pokemonEmCampo(player); // Função para escolher um novo Pokémon em campo
    }
}



void combate(jogador* player1, jogador* player2) {
    int escolhaAtaque;
    int verificador = 1;
    srand(time(NULL));
    int escolhaComputador = rand() % 3;
    
    while (verificador == 1)
    {
    printf("--------------------------------------------------------\n                  FASE DE COMBATE\n--------------------------------------------------------\n\n");
    
    printf("Jogador %s ataca com %s\n", player1->nome, player1->pokemonEmCampo.nome);
    exibirHabilidades(player1);
    escolhaAtaque = escolherAtaque();
    if (escolhaAtaque < 1 || escolhaAtaque > qntSkills) {
        printf("Escolha de ataque inválida.\n");
        return;
    } 
    aplicarDano(player1, player2, escolhaAtaque - 1);  // Subtraímos 1 para ajustar ao índice do vetor
    verificarPokemonMorto(player2); 

    pausar();
    printf("--------------------------------------------------------\n                  FASE DE COMBATE\n--------------------------------------------------------\n\n");
    printf("Jogador %s ataca com %s\n", player2->nome, player1->pokemonEmCampo.nome);
    aplicarDano(player2, player1, escolhaComputador);  // Subtraímos 1 para ajustar ao índice do vetor
    printf("O computador usou o ataque: %s", player2->pokemonEmCampo.habilidades[escolhaComputador].nome);
    verificarPokemonMorto(player1);
    pausar();   
    }
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
