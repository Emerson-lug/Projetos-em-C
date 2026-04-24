/*
========================================
        VERSÕES DE DESENVOLVIMENTO

Versão: 1.0 - data versão: 13/04/2026
Nota: Criado as principais funções.
Como as struct, player e mostros para teste.
------------------------------------------

=========================================
            DADOS CRIAÇÃO

Criador: Emerson Carlos Marins da Silva
Criado em: 13/04/2026
Data concluido: ??/??/2026

=======================================

Criado um sistema de RPG no terminal.

======================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
    // Se o código rodar no seu computador (Windows), ele usa a biblioteca original
    #include <conio.h> 
#else
    // Se rodar no Replit (Linux), nós construímos a função na mão!
    #include <termios.h>
    #include <unistd.h>

    // Criando a função _getch() para o Linux
    int _getch(void) {
        struct termios oldattr, newattr;
        int ch;
        
        // Pega as configurações atuais do terminal
        tcgetattr(STDIN_FILENO, &oldattr); 
        newattr = oldattr;
        
        // Desliga a necessidade de apertar Enter (ICANON) e esconde a letra digitada (ECHO)
        newattr.c_lflag &= ~(ICANON | ECHO); 
        
        // Aplica as novas configurações imediatamente
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr); 
        
        // Lê a tecla
        ch = getchar(); 
        
        // Restaura o terminal ao normal para não quebrar outros programas
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); 
        
        return ch;
    }
#endif

//========================================
//Structs geral que sera usado no sistema
//========================================

typedef struct{
    int id;
    char nome[60];
    char tipo[30];
    int quantidade;
    int poder;
}Item;

typedef struct {
    char nomeMissao[70];
    char tipoMissao[50];
    Item recompensa;
    float xpMissao;
}Missao;

typedef struct{
    char nome[50];
    Item dropItem;
    int hp;
    int ataque;
    int level;
    float xpDrop;
    float moedaDrop;
}Mostro;

typedef struct{
    char nome[50];
    int hp;
    int hpMax;
    int level;
    float xp;
    float coins;
    int posX;
    int posY;
    Item inventario[20];
    Item armaduraEquipada[4];
    Item itemDeDanoEquipado[1];
}Player;

typedef struct{
    char nome[50];
    char tipoNpc[50];
    Missao missaoNpc;
}NPC;

typedef struct{
    char nomeLoja[50];
    char tipoLoja[50];
    Item vendaItem;
}Loja;

typedef struct{
    char nomeRaid[60];
    Mostro quantidade;
    Item recompensaRaid;
    float xpRaid;
    int coinsRaid;
}Raid;

//================================
//Player chamado heroi para o RPG.
Player heroi;

void abrirMenuHeroi() {
    int menuHeroi = 1;
    int mochilaVazia = 1;

    while(menuHeroi == 1){
        int retorno, opcHeroi;

        printf("\n====================\n");
        printf("     MENU DO HEROI   ");
        printf("\n====================\n\n");

        printf("=== OPCOES DO MENU ===\n\n");
        printf("1. Mochila.\n");
        printf("2. Equipamentos.\n");
        printf("3. Status Heroi.\n");
        printf("0. Sair.\n\n");

        printf("Qual opcao deseja: ");
        retorno = scanf("%d", &opcHeroi);
        printf("\n");

        if(retorno == 0){
            printf("ERRO: Voce digitou letra!\n");
            while(getchar() != '\n');
            continue;
        }else if(opcHeroi == 0){
            menuHeroi = 0; // sai do mine-loop
        }else if(opcHeroi == 1){
            for(int i = 0; i < 20; i++){
                if(heroi.inventario[i].quantidade > 0){
                    mochilaVazia = 0;

                    printf("ID: %d | NOME: %s (%s)| PODER: %d | Qtd: %d\n",
                        heroi.inventario[i].id,
                        heroi.inventario[i].nome,
                        heroi.inventario[i].tipo,
                        heroi.inventario[i].poder,
                        heroi.inventario[i].quantidade
                    );
                }
            }
            if(mochilaVazia == 1){
                printf("Sua mochila esta completamente vazia!\n");

            }
            printf("\n[Precione QUALQUER tecla para fechar mochila..]\n");
            _getch();

        }else if(opcHeroi == 2){
            int opEquipar = 1, retorno;
            do{
                printf("\n*** EQUIPAMENTOS ***\n\n");
                printf("1. Ver equipamento.\n");
                printf("2. Equipar Itens.\n");
                printf("0. Voltar ao Mapa.\n\n");
                
                printf("Escolha: ");
                retorno = scanf("%d", &opEquipar);

                if(retorno == 0){
                    printf("ERRO: Voce digitou letra!!\n");
                    while(getchar() != '\n');
                    continue;
                }else if(opEquipar == 1){
                    printf("\n--- EQUIPAMENTO ATUAL ---\n\n");

                    printf("\n       ** ARMA **\n");
                    if(heroi.itemDeDanoEquipado[0].quantidade > 0){
                        printf("Arma: %s (+%d Dano)\n\n", heroi.itemDeDanoEquipado[0].nome, heroi.itemDeDanoEquipado[0].poder);
                    }else{
                        printf("Arma: Nenhuma (soco)\n\n");
                    }

                    printf("** ARMADURA **\n\n");

                    //Parte da cabeca: ELMO
                    if(heroi.armaduraEquipada[0].quantidade > 0){
                        printf("Elmo: %s (+%d HP)\n", heroi.armaduraEquipada[0].nome,heroi.armaduraEquipada[0].poder);
                    }else{
                        printf("Elmo: Nenhuma\n");
                    }

                    //Parte do peito: PEITORAL
                    if(heroi.armaduraEquipada[1].quantidade > 0){
                        printf("Peitoral: %s (+%d HP)\n", heroi.armaduraEquipada[1].nome, heroi.armaduraEquipada[1].poder);
                    }else{
                        printf("Peitoral: Nenhuma\n");
                    }

                    //Parte da calca: CALCA
                    if(heroi.armaduraEquipada[2].quantidade > 0){
                        printf("Calca: %s (+%d HP)\n", heroi.armaduraEquipada[1].nome,heroi.armaduraEquipada[1].poder);
                    }else{
                        printf("Calca: Nenhuma\n");
                    }

                    // Parte do pé: BOTA
                    if(heroi.armaduraEquipada[3].quantidade > 0){
                        printf("Bota: %s (+%d HP)\n\n", heroi.armaduraEquipada[3].nome,heroi.armaduraEquipada[3].poder);
                    }else{
                        printf("Bota: Nenhuma\n\n");
                    }

                    printf("[Precione QUALQUER tecla para continuar]\n");
                    _getch();

                }else if(opEquipar == 2){
                    printf("\n--- EQUIPAR ITEM ---\n\n");

                    printf("\nDigite o ID do item que deseja equipar: ");
                    int idParaEquipar;
                    scanf("%d", &idParaEquipar);
                    while(getchar() != '\n');

                    int achouEquipar = 0; // Bandeira de busca

                    for(int i = 0; i < 20; i++){
                        if(heroi.inventario[i].id == idParaEquipar && heroi.inventario[i].quantidade > 0){
                            achouEquipar = 1;

                            //Se for arma.
                            if(strcmp(heroi.inventario[i].tipo, "Espada") == 0){
                                heroi.itemDeDanoEquipado[0] = heroi.inventario[i];
                                heroi.inventario[i].quantidade -= 1;
                                printf("\n-> Voce Equipou: %s!\n", heroi.itemDeDanoEquipado[0].nome);
                            }

                            //Se for tipo armadura: ELMO
                            else if(strcmp(heroi.inventario[i].tipo, "Elmo") == 0){
                                heroi.armaduraEquipada[0] = heroi.inventario[i];
                                heroi.inventario[i].quantidade -= 1;
                                heroi.hp += heroi.armaduraEquipada[0].poder;
                                printf("\n-> Voce Equipou: %s!\n", heroi.armaduraEquipada[0].nome);
                            }
                            
                            //Se for tipo armadura: PEITORAL
                            else if(strcmp(heroi.inventario[i].tipo, "Peitoral") == 0){
                                heroi.armaduraEquipada[1] = heroi.inventario[i];
                                heroi.inventario[i].quantidade -= 1;
                                heroi.hp += heroi.armaduraEquipada[1].poder;
                                printf("\n-> Voce Equipou: %s!\n", heroi.armaduraEquipada[1].nome);
                            }

                            //Se for tipo armadura: CALCA
                            else if(strcmp(heroi.inventario[i].tipo, "Calca") == 2){
                                heroi.armaduraEquipada[2] = heroi.inventario[i];
                                heroi.inventario[i].quantidade -= 1;
                                heroi.hp += heroi.armaduraEquipada[2].poder;
                                printf("\n-> Voce Equipou: %s!\n", heroi.armaduraEquipada[0].nome);
                            }

                            //Se for tipo armadura: BOTA
                            else if(strcmp(heroi.inventario[i].tipo, "Bota") == 3){
                                heroi.armaduraEquipada[3] = heroi.inventario[i];
                                heroi.inventario[i].quantidade -= 1;
                                heroi.hp += heroi.armaduraEquipada[3].poder;
                                printf("\n-> Voce Equipou: %s!\n", heroi.armaduraEquipada[0].nome);
                            }
                            else{
                                printf("\n-> Esse item nao tem no inventario!!\n");
                            }
                            break;
                        }
                    }

                    if(achouEquipar == 0){
                        printf("ERRO: Item com ID %d nao encontrado na mochila!\n", idParaEquipar);
                    }
                    printf("[Precione QUALQUER tecla para continuar]\n");
                    _getch();

                }else if(opEquipar == 0){
                    opEquipar = 0;
                }

            }while(retorno == 0);
                                        
        }else if(opcHeroi == 3){
            // Soma com arma ou sem.
            int danoTotal = 5; //Dano por soco se não tiver equipado nada
            if(heroi.itemDeDanoEquipado[0].quantidade > 0){
                danoTotal += heroi.itemDeDanoEquipado[0].poder;
            }

            // Somando vida com armadura ou sem.
            int hpMaxComArmadura = heroi.hpMax;
            for(int i = 0; i < 4; i++){
                if(heroi.armaduraEquipada[i].quantidade > 0){
                    hpMaxComArmadura += heroi.armaduraEquipada[i].poder;
                }
            }

            //Mostrando informções na tela.
            printf("\n*** STATUS DO HEROI\n\n");
            printf("NOME: %s\n", heroi.nome);
            printf("LEVEL: %d (XP: %.0f/20)\n", heroi.level, heroi.xp);
            printf("HP: %d/%d\n", heroi.hp, hpMaxComArmadura);
            printf("ATAQUE TOTAL: %d\n", danoTotal);
            printf("MOEDAS: %.0f\n\n", heroi.coins);

            printf("[Precione QUALQUER tecla para continuar...]\n");
            _getch();

        }else{
            printf("Opcao Invalida!!\n");
        }
    }
}

void iniciarCombate(Mostro inimigo){
    int emCombate = 1;

    printf("\n=========================\n");
    printf("     BATALHA INICIADA    ");
    printf("\n=========================\n");
    printf("\nUm %s Nivel %d apareceu!\n", inimigo.nome, inimigo.level);

    while(emCombate == 1){
        //Calculando o dano do heroi e dando bonus por level
        int danoHeroi = 5 + (heroi.level * 2);

        if(heroi.itemDeDanoEquipado[0].quantidade > 0){
            danoHeroi += heroi.itemDeDanoEquipado[0].poder;
        }

        //Calculando HP do heroi
        int hpMaxAtual = heroi.hpMax;

        for (int i = 0; i < 4; i++){
            if(heroi.armaduraEquipada[i].quantidade > 0) hpMaxAtual += heroi.armaduraEquipada[i].poder;
        }

        //Infotmações que sera mostrado na tela
        printf("\n-----------------------------------------------\n\n");
        printf("[HEROI] %s | HP: %d/%d | Dano: %d\n", heroi.nome, heroi.hp, hpMaxAtual, danoHeroi);
        printf("[INIMIGO] %s | HP: %d\n", inimigo.nome, inimigo.hp);
        printf("-------------------------------------------------\n\n");
        printf("1. Atacar.\n");
        printf("2. Usar Pocao.\n");
        printf("3. Tentar Fugir.\n");
        printf("Sua acao: ");

        char acao = _getch();

        if(acao == '1'){
            //Turno do jogador
            printf("\n\n-> Voce ataca %s e cause %d de dano!\n", inimigo.nome, danoHeroi);
            inimigo.hp -= danoHeroi;

            //Verificão se o inimigo esta vivo
            if(inimigo.hp <= 0){
                printf("\n*** VOCE DERROTOU O %s! ***\n", inimigo.nome);
                printf("-> Ganhou %.0f de XP!\n", inimigo.xpDrop);
                printf("-> Ganhou %.0f de moedas!\n", inimigo.moedaDrop);

                heroi.xp += inimigo.xpDrop;
                heroi.coins += inimigo.moedaDrop;

                if(inimigo.dropItem.quantidade > 0){
                    for(int i = 0; i < 20; i++){
                        if(heroi.inventario[i].quantidade > 0){
                            heroi.inventario[i] = inimigo.dropItem;
                            printf("-> O inimigo deixou cair: 1x %s!\n", inimigo.nome);
                            break;
                        }
                    }
                }
                printf("\n[Precione QUALQUER tecla para voltar ao mapa...]\n");
                _getch();
                emCombate = 0;
                break;
            }

            //Turno do inimigo
            printf("-> O %s ataca de volta e causa %d de dano!\n", inimigo.nome, inimigo.ataque);
            heroi.hp -= inimigo.ataque;

            if(heroi.hp <= 0){
                printf("\n*** SUA VISTA ESCURESE ***\n");
                printf("[Precione QUALQUER tecla...]\n");
                _getch();
                emCombate = 0;
            }
            printf("\n[Precione QUALQUER tecla para o proximo turno...]\n");
            _getch();
        }
        else if(acao == '2'){
            printf("\n ** SUAS POCOES **\n\n");
            int temPocao = 0;

            //Buscando por itens consumiveis
            for(int i = 0; i < 20; i++){
                if(heroi.inventario[i].quantidade > 0 && strncmp(heroi.inventario[i].tipo, "Consumivel", 10) == 0){
                    printf("ID: %d | NOME: %s | CURA: %d HP | QTD: %d\n", 
                        heroi.inventario[i].id, heroi.inventario[i].nome,
                        heroi.inventario[i].poder, heroi.inventario[i].quantidade);
                    temPocao = 1;    
                }
            }
            if(temPocao == 0){
                printf("-> Voce não tem pocoes!\n\n");
                printf("[Precione QUALQUER tecla...]\n");
                _getch();
            }else{
                //Se tiver poção entra nesse else e faz a digitação do ID da poçao
                printf("\nDigite o ID da pocao (ou 0 para cancelar): ");
                int idPocao;
                scanf("%d", &idPocao);
                while(getchar() != '\n');

                if(idPocao != 0){
                    int achouPocaoUsar = 0;

                    for(int i = 0; i < 20; i++){
                        if(heroi.inventario[i].id == idPocao && heroi.inventario[i].quantidade > 0){
                            achouPocaoUsar = 1;
                            
                            //LOGICA DA CURA
                            heroi.hp += heroi.inventario[i].poder;
                            heroi.inventario[i].quantidade -= 1;

                            if(heroi.hp > hpMaxAtual){
                                heroi.hp = hpMaxAtual;
                            }

                            printf("-> Voce bebeu %s e recuperou %d de HP.\n", heroi.inventario[i].nome, heroi.inventario[i].poder);

                            //Muda para o turno do inimigo, perdendo um turno de ataque.
                            printf("-> O %s aproveita e te ataca causando %d de dano!\n", inimigo.nome, inimigo.ataque);
                            heroi.hp -= inimigo.ataque;

                            if(heroi.hp <= 0){
                                printf("\n*** SUA VISTA ESCURECE ***\n\n");
                                emCombate = 0;
                            }
                            break;
                        }
                    }
                    if(achouPocaoUsar == 0){
                        printf("-> ID da pocao invalida!\n");
                    }
                }
                printf("[Precione QUALQUER tecla para o proximo turno...]\n");
                _getch();
            }

        }
        
        else if(acao == '3'){
            //Sorte de Fuga = 50% de chance
            int sorte = rand() % 100;
            if(sorte > 50){
                printf("\n\n> Voce conseguio fugir da batalha!\n");
                printf("\n[Precione QUALQUER tecla para voltar ao mapa...]\n");
                _getch();
                emCombate = 0;
            }else{
                printf("\n-> Voce tropesou e nao conseguio fugir!\n");
                printf("-> O %s aproveita a brecha e te ataca causando %d de dano!\n", inimigo.nome, inimigo.ataque);
                heroi.hp -= inimigo.ataque;

                if (heroi.hp <= 0) emCombate = 0;

                printf("\n[Precione QUALQUER tecla para continuar...]\n");
                _getch();
            }
        }
    }

} 


int main() {
    srand(time(NULL));

    int estadoJogo = 0;
    // 0 = Criação de personagem.
    // 1 = Zona inicial (7x7 - meio 3 e 3) 
    // 2 = Mapa 1 (15x15, com pequenos monstros iniciais)
    // 3 = combate
    // 4 = Vila (mercado e lojas)
    // 5 = Mapa 2 (25x25, com outros tipos de mostros e loots melhores)

    //======================
    //MAPAS GLOBAL DO RPG

    //MAPA SPAWN MUNDO
    int mapaCaverna[7][7] = {
        //0 = chão, 1 = água, 2 = Parede, 3 = arvore, 4 = bau.
        {2, 2, 2, 2, 2, 2, 2},
        {2, 2, 1, 1, 1, 2, 2},
        {2, 1, 1, 0, 1, 1, 2},
        {2, 1, 0, 0, 0, 1, 2},
        {2, 0, 4, 0, 3, 1, 2},
        {2, 2, 0, 0, 0, 2, 2},
        {2, 2, 2, 9, 2, 2, 2}
    };

    //MUNDO EXTERIOR (MAPA 1)
    int mapa1[15][15] = {
        //0 = chão, 1 = água, 2 = parede, 3 = arvore, 4 = bau, 6 = grama alta
        //5 = entrada/saida esquerda, 9 = entrada/saida cima, 8 = entrada/saida baixo
        {2, 2, 2, 2, 2, 2, 2, 9, 2, 2, 2, 2, 2, 2, 2},
        {2, 2, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
        {2, 2, 6, 6, 0, 0, 0, 0, 0, 0, 3, 0, 0, 2, 2},
        {2, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 6, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 2},
        {2, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {5, 0, 0, 3, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 2},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 6, 0, 0, 0, 0, 0, 3, 0, 6, 6, 6, 0, 2},
        {2, 0, 6, 6, 6, 0, 3, 0, 3, 0, 6, 6, 6, 0, 2},
        {2, 4, 6, 6, 6, 6, 0, 0, 0, 6, 6, 6, 0, 2, 2},
        {2, 2, 0, 6, 6, 6, 0, 0, 0, 6, 6, 0, 2, 2, 2},
        {2, 2, 2, 0, 6, 6, 0, 0, 0, 0, 0, 2, 2, 2, 2},
        {2, 2, 2, 2, 8, 8, 8, 8, 8, 8, 2, 2, 2, 2, 2},
    };

    while (estadoJogo != -1){

        //=============================
        //      CRIAÇÃO DO PERSONAGEM
        //-----------------------------

        if(estadoJogo == 0){
            //Criação do personagem e os status basicos.
            //sendo feito com printf e scanf, e mostrar status iniciais.
            //e no final manda para o estadoJogo == 1, iniciando a zona inicial.
            printf("\n===============================\n");
            printf("          INICIO DE JOGO     \n");
            printf("===============================\n\n");

            printf("-> Digite um nome para personagem: ");
            scanf("%s", heroi.nome);
            while(getchar() != '\n');

            //=========================================
            //preenchendo dados iniciais do personagem
            //-----------------------------------------
            heroi.hpMax = 100;
            heroi.hp = heroi.hpMax;
            heroi.level = 1;
            heroi.xp = 0.0;
            heroi.coins = 100;
            //-----------------------------------------

            //Iniciando personagem no meio da zona inicial (6x6)
            heroi.posX = 3;
            heroi.posY = 3;
            
            //==================
            //Esvaziando vetores

            //Mochila
            for(int i = 0; i < 20; i++){
                heroi.inventario[i].quantidade = 0;
            }

            //Deixando slot de armaduras vazio
            for (int i = 0; i < 4; i++){
                heroi.armaduraEquipada[i].quantidade = 0;
            }

            //Deixando slot de espada vazio
            heroi.itemDeDanoEquipado[0].quantidade = 0;

            //=====================================================
            //Imprimindo informações basicas do personagem na tela.
            //-----------------------------------------------------

            printf("\n================================\n");
            printf("    INFORMACAES PERSONAGEM  ");
            printf("\n================================\n\n");

            printf("NOME: %s\nHP: %d\nLEVEL: %d\nXP: %.2f\nMOEDAS: %.2f\n", heroi.nome, heroi.hp, heroi.level, heroi.xp, heroi.coins);
            printf("\n[Precione QUALQUER tecla para entrar no mundo...]");
            _getch(); //Pause de jogo, continuar quando apertado ENTER.

            //Mudando de estadoJogo para a zona inicial, primeiro mapa.
            estadoJogo = 1;
        }

        //================================
        //       ZONA DE SPAWN (CAVERNA)
        //--------------------------------

        else if(estadoJogo == 1) {
            //Primeira matriz da parte de spawn.
            //Fazendo as colisão com parede e agua caso o player tente, matriz 10x10.
            //se o usuario ir para o lado certo, vai para o estadoJogo == 2.

            char movimento;
            int continuarNoMapa = 1;

            do{
                printf("\n=============== ===========\n");
                printf("  SPAWN DO MUNDO (CAVERNA)  ");
                printf("\n===========================\n\n");

                for (int i = 0; i < 7; i++){
                    for (int j = 0; j < 7; j++){

                        //Olhando as cordenadas do heroi e mostrando ' O ' representado seu numero
                        if(i == heroi.posX && j == heroi.posY){
                            printf(" O ");
                        }

                        //Verificando posições no mapa, e mostrando algun caracter para representar no mapa.
                        else if(mapaCaverna[i][j] == 0){
                            printf(" . "); // chão
                        }
                        else if(mapaCaverna[i][j] == 1){
                            printf(" ~ "); //agua
                        }
                        else if(mapaCaverna[i][j] == 2){
                            printf("[#]"); //parede
                        }
                        else if(mapaCaverna[i][j] == 3){
                            printf(" T "); //arvore
                        }
                        else if(mapaCaverna[i][j] == 4){
                            printf(" X "); //bau
                        }
                        else if(mapaCaverna[i][j] == 9){
                            printf("[ ]"); //saida da caverna
                        }
                    }
                    printf("\n");
                }

                //===========================
                //Menu com opções de interação .

                printf("\n===================\n");
                printf("        COMANDOS  ");
                printf("\n====================\n\n");

                printf("W: Cima.\n");
                printf("S: Baixo.\n");
                printf("A: Esq.\n");
                printf("D: Dir.\n");
                printf("I: Inventario.\n");
                printf("Q: Sair.\n\n");


                movimento = _getch();

                //==================
                //Logica de colisão

                int proximoX = heroi.posX;
                int proximoY = heroi.posY;

                //LENDO AS OPÇÕES ESCOLHIDAS NO MENU
                if(movimento == 'W' || movimento == 'w') proximoX -= 1;
                else if(movimento == 'S' || movimento == 's') proximoX += 1;
                else if(movimento == 'D' || movimento == 'd') proximoY += 1;
                else if(movimento == 'A' || movimento == 'a') proximoY -= 1;
                else if(movimento == 'Q' || movimento == 'q'){
                    continuarNoMapa = 0;
                    estadoJogo = -1;
                }
                else if(movimento == 'I' || movimento == 'i'){
                    abrirMenuHeroi();
                }
                
                //================================
                //TESTE DE TERRENO ANTES DE ANDAR.

                //Testando terreno para ir.
                if(mapaCaverna[proximoX][proximoY] == 0 || mapaCaverna[proximoX][proximoY] == 6){
                    heroi.posX = proximoX;
                    heroi.posY = proximoY;
                }

                //======================
                //Sistema de abrir bau.

                else if (mapaCaverna[proximoX][proximoY] == 4){
                    heroi.posX = proximoX;
                    heroi.posY = proximoY;

                    printf("\n*** VOCE ENCONTROU UM BAU ***\n\n");

                    int itemEncontrado = 0; // Bandeira para procurar item igual no inventario.


                    //=========================
                    //ENTREGANDO POCAO DE CURA

                    //Verificando se ja tem o item.
                    for (int i = 0; i < 20; i++){
                        if(heroi.inventario[i].id == 1 && heroi.inventario[i].quantidade > 0){
                            heroi.inventario[i].quantidade += 2;
                            itemEncontrado = 1;

                            printf("-> Voce pegou: +2 pocao de cura (25 HP). total: %d\n", heroi.inventario[i].quantidade);
                            break;
                        }
                    }

                    //Um for para percorrer inventario com slot vazio e inserir poção.
                    if(itemEncontrado == 0){
                        for(int i = 0; i < 20; i++){
                            if(heroi.inventario[i].quantidade == 0){
                                heroi.inventario[i].id = 1;
                                strcpy(heroi.inventario[i].nome, "Pocao de cura");
                                strcpy(heroi.inventario[i].tipo, "Consumivel de Cura");
                                heroi.inventario[i].poder = 25; // cura 25 de HP
                                heroi.inventario[i].quantidade = 2; // Da duas Poções

                                printf("-> Voce pegou: 2x Pocoes de cura (25 HP).\n");
                                break;
                            }
                        }
                    }

                    //=============================
                    //ENTREGANDO ESPADA DE MADEIRA

                    //Verificando se ja tem o item.
                    for (int i = 0; i < 20; i++){
                        if(heroi.inventario[i].id == 2 && heroi.inventario[i].quantidade > 0){
                            heroi.inventario[i].quantidade += 1;
                            itemEncontrado = 1;

                            printf("-> Voce pegou: +1 espada de madeira (7 de Dano). total: %d\n", heroi.inventario[i].quantidade);
                            break;
                        }
                    }

                    //Segundo for para procurar slot vazio e dar a espada.
                    for(int i = 0; i < 20; i++){
                        if(heroi.inventario[i].quantidade == 0){
                            heroi.inventario[i].id = 2;
                            strcpy(heroi.inventario[i].nome, "Espada de Madeira");
                            strcpy(heroi.inventario[i].tipo, "Espada");
                            heroi.inventario[i].poder = 7; // Da 7 de dano
                            heroi.inventario[i].quantidade = 1; //Uma espada para o heroi

                            printf("-> Voce pegou: 1x Espada de Madeira (7 de Dano).\n");
                            break;
                        }
                    }

                    //Tirando o bau do mapa.
                    mapaCaverna[proximoX][proximoY] = 0;

                    printf("\n[Precione QUALQUER tecla para fechar o bau...]\n");
                    _getch();
                }

                //Indo para o mundo exterior, fora da caverna.
                else if(mapaCaverna[proximoX][proximoY] == 9){
                    printf("\n*** SAINDO DA CAVERNA ***\n\n");
                    printf("[Precione ENTER para continuar...]\n");
                    getchar();

                    estadoJogo = 2;
                    continuarNoMapa = 0;

                    heroi.posX = 1;
                    heroi.posY = 7;
                    
                }

                //COLISÃO COM A AGUA e PAREDE
                else if(mapaCaverna[proximoX][proximoY] == 1){
                    printf("\n-> A agua esta muito funda. Voce recua!\n");
                }
                else if(mapaCaverna[proximoX][proximoY] == 2 || mapaCaverna[proximoX][proximoY] == 3){
                    printf("\n->CAMINHO BLOQUEADO!!\n");
                }

            }while(continuarNoMapa == 1);

        }

        //================================
        //    PRIMEIRO MAPA (PLANISE)
        //--------------------------------

        else if(estadoJogo == 2) {
            //Matriz 15x15, primeiro mapa de zona de combate.
            //frente, cima e baixo, tres lados com vilas depois da matriz.
            //se entrar em combate entra no estadoJogo == 3

            int movimento;
            int continuarNoMapa2 = 1;
            
            do{
                printf("\n======================================\n");
                printf("    Mundo exterior (Mapa 1 - PLANISE) ");
                printf("\n=====================================\n\n");

                for (int i = 0; i < 15; i++){
                    for (int j = 0; j < 15; j++){

                        //Inserindo oque é o player no mapa.
                        if(i == heroi.posX && j == heroi.posY){
                            printf(" O ");
                        }

                        //Mostrando os objetos no mapa
                        else if(mapa1[i][j] == 0){
                            printf(" . "); // chao
                        }
                        else if(mapa1[i][j] == 1){
                            printf(" ~ "); // agua
                        }
                        else if(mapa1[i][j] == 2){
                            printf("[#]"); // parede
                        }
                        else if(mapa1[i][j] == 3){
                            printf(" T "); //Arvore
                        }
                        else if(mapa1[i][j] == 4){
                            printf(" X "); //bau
                        }
                        else if(mapa1[i][j] == 6){
                            printf(" ; "); // grama alta
                        }
                        else if(mapa1[i][j] == 5){
                            printf("[ ]");// entrada ou saida esquerda
                        }
                        else if(mapa1[i][j] == 8){
                            printf("[ ]");// entrada ou saida de baixo
                        }
                        else if(mapa1[i][j] == 9){
                            printf("[ ]");// entrada ou saida de cima
                        }
                    }
                    printf("\n");
                }

                //===========================
                //Menu com opções de interação .

                printf("\n===================\n");
                printf("        COMANDOS  ");
                printf("\n====================\n\n");

                printf("W: Cima.\n");
                printf("S: Baixo.\n");
                printf("A: Esq.\n");
                printf("D: Dir.\n");
                printf("I: Menu de Heroi.\n");
                printf("Q: Sair.\n\n");


                movimento = _getch();

                //==================
                //Logica de colisão

                int proximoX = heroi.posX;
                int proximoY = heroi.posY;

                //LENDO AS OPÇÕES ESCOLHIDAS NO MENU
                if(movimento == 'W' || movimento == 'w') proximoX -= 1;
                else if(movimento == 'S' || movimento == 's') proximoX += 1;
                else if(movimento == 'D' || movimento == 'd') proximoY += 1;
                else if(movimento == 'A' || movimento == 'a') proximoY -= 1;
                else if(movimento == 'Q' || movimento == 'q'){
                    continuarNoMapa2 = 0;
                    estadoJogo = -1;
                }
                else if(movimento == 'I' || movimento == 'i'){
                    abrirMenuHeroi();
                }
                
                //=================
                //TESTE DE TERRENO 

                if(mapa1[proximoX][proximoY] == 0 || mapa1[proximoX][proximoY] == 6){
                    heroi.posX = proximoX;
                    heroi.posY = proximoY;

                    if(mapa1[proximoX][proximoY] == 6){
                        int chanceDeCombate = rand() % 100;

                        if(chanceDeCombate < 20){
                            Mostro goblin;
                            strcpy(goblin.nome, "Goblin Selvagem");
                            goblin.hp = 20;
                            goblin.ataque = 4;
                            goblin.level = 1;
                            goblin.xpDrop = 7.5;
                            goblin.moedaDrop = 10.5;
                            goblin.dropItem.quantidade = 0;

                            iniciarCombate(goblin);
                        }
                        if(chanceDeCombate < 35){
                            Mostro lobo;
                            strcpy(lobo.nome, "Lobo Selvagem");
                            lobo.hp = 40;
                            lobo.ataque = 9;
                            lobo.level = 3;
                            lobo.xpDrop = 12.8;
                            lobo.moedaDrop = 14.0;
                            lobo.dropItem.quantidade = 0;

                            iniciarCombate(lobo);
                        }
                    }
                }

                //======================
                //SISTEMA DE ABIR BAU (planice)

                else if(mapa1[proximoX][proximoY] == 4){
                    heroi.posX = proximoX;
                    heroi.posY = proximoY;

                    printf("\n*** VOCE ENCONTROU UM BAU ***\n\n");

                    int itemEncontrado = 0;

                    //======================
                    //    ENTREGANDO ITENS

                
                    // POCAO DE CURA

                    //VERIFICANDO ITEM, SE TIVER APENAS SOMA.
                    for (int i = 0; i < 20; i++){
                        if(heroi.inventario[i].id == 1 && heroi.inventario[i].quantidade > 0){
                            heroi.inventario[i].quantidade += 2;
                            itemEncontrado = 1;

                            printf("-> Voce pegou: +2 pocao de cura (25 HP). total: %d\n", heroi.inventario[i].quantidade);
                            break;
                        }
                    }

                    //CASO NÃO TENHA ITEM VEM PARA O SEGUNDO FOR QUE PROCURA SLOT VAZIO.
                    if(itemEncontrado == 0){
                        for(int i = 0; i < 20; i++){
                            if(heroi.inventario[i].quantidade == 0){
                                heroi.inventario[i].id = 1;
                                strcpy(heroi.inventario[i].nome, "Pocao de cura");
                                strcpy(heroi.inventario[i].tipo, "Consumivel");
                                heroi.inventario[i].poder = 25; // cura 25 de HP
                                heroi.inventario[i].quantidade = 2; // Da duas Poções

                                printf("-> Voce pegou: 2x Pocoes de cura (25 HP).\n");
                                break;
                            }
                        }
                    }

                    //====================
                    // ITENS DE ARMARURA
                    //--------------------
                    

                    //Verificando se tem o item
                    for(int i = 0; i < 20; i++){
                        if(heroi.inventario[i].id == 3 && heroi.inventario[i].quantidade > 0){
                            heroi.inventario[i].quantidade += 1;
                            itemEncontrado = 1;

                            printf("-> Voce pegou: +1 Peitoral de coura (5 HP). total: %d\n", heroi.inventario[i].quantidade);
                            break;
                        }
                    }

                    itemEncontrado = 0;

                    //Caso não tenha entra no segundo for adicionando o item.
                    if(itemEncontrado == 0){
                        for(int i = 0; i < 20; i++){
                            if(heroi.inventario[i].quantidade == 0){
                                heroi.inventario[i].id = 3;
                                strcpy(heroi.inventario[i].nome, "Peitoral de Couro");
                                strcpy(heroi.inventario[i].tipo, "Peitoral");
                                heroi.inventario[i].poder = 5; //Dá +5 de HP para o player
                                heroi.inventario[i].quantidade = 1; //Dá uma peca de armadura

                                printf("-> Voce Pegou: 1x Peitoral de Couro (5 HP)\n");
                                break;
                            }
                        }
                    }
        
                    //TIRANDO BAU DO MAPA
                    mapa1[proximoX][proximoY] = 0;

                    printf("\n[Precione QUAQUER tecla para continuar...]\n");
                    _getch();
                    
                }

                //================
                //  TROCA DE MAPA

                //Mapa da zona de spawn 
                else if(mapa1[proximoX][proximoY] == 9){
                    printf("\n*** ENTRANDO NA CAVERNA ***\n\n");
                    printf("[Precione QUALQUER tecla para continuar...]\n");
                    _getch();

                    estadoJogo = 1;
                    continuarNoMapa2 = 0;

                    heroi.posX = 6;
                    heroi.posY = 3;
                }

                //===========================
                //COLISAO COM A AGUA E PAREDE
                else if( mapa1[proximoX][proximoY] == 1){
                    printf("\n-> A agua esta muito funda. Voce recua!\n");
                }
                else if(mapa1[proximoX][proximoY] == 2){
                    printf("\n->CAMINHO BLOQUEADO!!\n");
                }


            }while(continuarNoMapa2 == 1);
            
        }
        
        else if(estadoJogo == 3) {
            //Player entrou em combate, tendo o sistema de combate.
            //dependendo da pos volta pro estadoJogo == 2 ou avança pro estadoJogo == 4.
        }

        else if(estadoJogo == 4) {
            //Saindo do mapa, entra na vila, dependendo do lado que entrou
            //muda as opcao da vila.
            //se sair da vila por outro lado da entrada entra no estadoJogo == 4, mapa 2
        }
         //=================================
        //  REGRAS DE STATUS DE PERSONAGEM
        //=================================

        //Regra do XP
        if(heroi.xp >= 20.0){
            heroi.level += 1;
            heroi.hpMax += 20;
            heroi.hp = heroi.hpMax;
            heroi.xp -= 20.0;
            printf("\n*** LEVEL UP! Voce alcancou o Nivel %d! ***\n", heroi.level);
        }

        //Regra de morte
        if(heroi.hp <= 0) {
            printf("\n*** VOCE MORREU! ***");
            heroi.hp = heroi.hpMax;
            heroi.coins -= 50;
            estadoJogo = 2;

        }

        //Regra da moeda negativa
        if (heroi.coins < 0){
            heroi.coins = 0;
        }
    }
    return 0;
}