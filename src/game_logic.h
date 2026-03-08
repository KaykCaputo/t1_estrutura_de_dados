#ifndef T1_ESTRUTURA_DE_DADOS_GAME_LOGIC_H
#define T1_ESTRUTURA_DE_DADOS_GAME_LOGIC_H


#include "doubly_linked_list.h"
#include "cards.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

struct Player {
    int id;
    int score;
    string name;
};

struct GameState {
    DoublyLinkedList <Card> board;
    Player player1;
    Player player2;
    int curPlayer;
    int totalPairs;
    int pairsFound;
    int totalMoves;
};

void startGame(GameState &game) {
    create(game.board);

    game.player1.id = 1;
    game.player1.score = 0;
    game.player1.name = "Jogador 1";

    game.player2.id = 2;
    game.player2.score = 0;
    game.player2.name = "Jogador 2";

    game.currentPlayer = 1;
    game.totalPairs = 10;
    game.pairsFound = 0;
    game.totalMoves = 0;

    char symbols[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    Card cards[20];

    for (int i = 0; i < 10; i++) {
        cards[i * 2].id = i * 2 + 1;
        cards[i * 2].symbol = symbols[i];
        cards[i * 2].state = STATE_HIDDEN;
        cards[i * 2].type = CARD_NORMAL;
        cards[i * 2].pairId = i * 2 + 2;

        cards[i * 2 + 1].id = i * 2 + 2;
        cards[i * 2 + 1].symbol = symbols[i];
        cards[i * 2 + 1].state = STATE_HIDDEN;
        cards[i * 2 + 1].type = CARD_NORMAL;
        cards[i * 2 + 1].pairId = i * 2 + 1;
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
    cout << "\n--------------- Board ---------------" << endl;

    Node<Card> * cur = game.board.start;
    int pos = 1;

    while (cur != NULL) {
        cout << "[" << pos << "] ";

        if (cur-elem.state == HIDDEN) {
            cout << "?";
        }else if (cur->elem.state == REVEALED) {
            cout << cur->elem.symbol;
        }else { // Quando são iguais || MATCH
            cout << " "
        }

        cout << " ";

        if (pos % 5 == 0) cout << "\n"; //quebra de linha tabuleiro
    }

    cout << "\n---------------------------------------";
}

// O resto ai ja n sei kk tentei


#endif //T1_ESTRUTURA_DE_DADOS_GAME_LOGIC_H