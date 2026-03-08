#ifndef T1_ESTRUTURA_DE_DADOS_GAME_LOGIC_H
#define T1_ESTRUTURA_DE_DADOS_GAME_LOGIC_H


#include "doubly_linked_list.h"
#include "cards.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct GameState;

void shuffleCards(Card cards[], int size);
void displayBoard(const GameState &game);

struct Effect {
    string description;
    int duration;
};

struct Player {
    int id;
    int score;
    string name;
    DoublyLinkedList<Effect> inventory; 
};

struct GameState {
    DoublyLinkedList<Card> board;
    Player player1;
    Player player2;
    int curPlayer;
    int totalPairs;
    int pairsFound;
    int totalMoves;
};

void startGame(GameState &game) {
    create(game.board);
    create(game.player1.inventory);
    create(game.player2.inventory);

    game.player1.id = 1; game.player1.score = 0; game.player1.name = "Jogador 1";
    game.player2.id = 2; game.player2.score = 0; game.player2.name = "Jogador 2";

    game.curPlayer = 1;
    game.totalPairs = 10;
    game.pairsFound = 0;
    game.totalMoves = 0;

    char symbols[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', '*', 'X'};
    Card cards[20];

    for (int i = 0; i < 10; i++) {
        cards[i * 2].id = i * 2 + 1;
        cards[i * 2].symbol = symbols[i];
        cards[i * 2].state = HIDDEN;
        cards[i * 2].pairId = i * 2 + 2;

        cards[i * 2 + 1].id = i * 2 + 2;
        cards[i * 2 + 1].symbol = symbols[i];
        cards[i * 2 + 1].state = HIDDEN;
        cards[i * 2 + 1].pairId = i * 2 + 1;

        if (symbols[i] == '*') {
            cards[i * 2].type = BONUS;
            cards[i * 2 + 1].type = BONUS;
        } else if (symbols[i] == 'X') {
            cards[i * 2].type = PENALTY;
            cards[i * 2 + 1].type = PENALTY;
        } else {
            cards[i * 2].type = NORMAL;
            cards[i * 2 + 1].type = NORMAL;
        }
    }

    shuffleCards(cards, 20);

    for (int i = 0; i < 20; i++) {
        insert(game.board, cards[i], i + 1);
    }
}

void shuffleCards(Card cards[], int size) {
    srand(time(0));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

void displayBoard(const GameState &game) {
    cout << "\n-------------- Board ---------------\n";

    Node<Card> *cur = game.board.start;
    int pos = 1;

    while (cur != NULL) {
        if (pos < 10) cout << "[0" << pos << "] ";
        else cout << "[" << pos << "] ";

        char display = '?';
        if (cur->elem.state == REVEALED)
            display = cur->elem.symbol;

        cout << left << setw(6) << display;
        
        if (pos % 5 == 0) cout << "\n"; //quebra de linha tabuleiro
        
        cur = cur->next;
        pos++;
    }
    
    if ((pos - 1) % 5 != 0 && (pos - 1) > 0) 
        cout << "\n";
    
    cout << "=================================================\n";
    cout << game.player1.name << " Pontos: " << game.player1.score 
         << " | Inventario: " << game.player1.inventory.amount << " item(s)\n";
    cout << game.player2.name << " Pontos: " << game.player2.score 
         << " | Inventario: " << game.player2.inventory.amount << " item(s)\n";
    cout << "-------------------------------------------------\n";
}

Node<Card>* getCardAt(DoublyLinkedList<Card>& list, int pos) {
    if (pos < 1 || pos > list.amount) return NULL;
    Node<Card>* cur = list.start;
    for (int i = 1; i < pos; i++) 
        cur = cur->next;
    return cur;
}

// Lógica de uma rodada
void playTurn(GameState &game) {
    Player& currentPlayer = (game.curPlayer == 1) ? game.player1 : game.player2;

    if (!isEmpty(currentPlayer.inventory)) {
        cout << "\n[" << currentPlayer.name << "] tem uma penalidade ativa no inventario! Perdeu a vez.\n";
        remove(currentPlayer.inventory, 1); 
        game.curPlayer = (game.curPlayer == 1) ? 2 : 1;
        return;
    }

    cout << "\n>>> VEZ DO " << currentPlayer.name << " <<<\n";
    displayBoard(game);

    int pos1, pos2;
    
    // Escolha da Primeira Carta
    cout << "\nEscolha a posicao da PRIMEIRA carta (1 a " << game.board.amount << "): ";
    cin >> pos1;
    Node<Card>* node1 = getCardAt(game.board, pos1);
    
    if (node1 == NULL || node1->elem.state != HIDDEN) {
        cout << "Posicao invalida ou carta ja virada! Perdeu a vez.\n";
        game.curPlayer = (game.curPlayer == 1) ? 2 : 1;
        return;
    }
    node1->elem.state = REVEALED;
    displayBoard(game);

    // Escolha da Segunda Carta
    cout << "\nEscolha a posicao da SEGUNDA carta (1 a " << game.board.amount << "): ";
    cin >> pos2;
    
    if (pos1 == pos2) {
        cout << "Voce nao pode escolher a mesma carta! Perdeu a vez.\n";
        node1->elem.state = HIDDEN;
        game.curPlayer = (game.curPlayer == 1) ? 2 : 1;
        return;
    }

    Node<Card>* node2 = getCardAt(game.board, pos2);
    if (node2 == NULL || node2->elem.state != HIDDEN) {
        cout << "Posicao invalida ou carta ja virada! Perdeu a vez.\n";
        node1->elem.state = HIDDEN;
        game.curPlayer = (game.curPlayer == 1) ? 2 : 1;
        return;
    }
    node2->elem.state = REVEALED;
    displayBoard(game);

    game.totalMoves++;

    if (node1->elem.symbol == node2->elem.symbol) {
        cout << "\n*** PARABENS! Voce encontrou um par (" << node1->elem.symbol << ")! ***\n";
        currentPlayer.score++;
        game.pairsFound++;

        int removeFirst = (pos1 > pos2) ? pos1 : pos2;
        int removeSecond = (pos1 > pos2) ? pos2 : pos1;
        
        remove(game.board, removeFirst);
        remove(game.board, removeSecond);

        cout << currentPlayer.name << " joga novamente!\n";

    } else {
        cout << "\nAs cartas sao diferentes...\n";
        
        if (node1->elem.type == BONUS || node2->elem.type == BONUS) {
            cout << "UAU! Voce virou um BONUS (*). Ganhou uma jogada extra!\n";
            node1->elem.state = HIDDEN;
            node2->elem.state = HIDDEN;
            return;
        }
        else if (node1->elem.type == PENALTY || node2->elem.type == PENALTY) {
            cout << "CUIDADO! Voce virou uma PENALIDADE (X). Adicionando ao seu inventario...\n";
            Effect pen = {"Perda de Jogada", 1};
            insert(currentPlayer.inventory, pen, currentPlayer.inventory.amount + 1);
        }

        node1->elem.state = HIDDEN;
        node2->elem.state = HIDDEN;
        game.curPlayer = (game.curPlayer == 1) ? 2 : 1;
    }
}

bool isGameOver(const GameState &game) {
    return isEmpty(game.board) || game.pairsFound == game.totalPairs;
}

#endif //T1_ESTRUTURA_DE_DADOS_GAME_LOGIC_H