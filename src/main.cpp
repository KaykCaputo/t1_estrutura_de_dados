#include <iostream>
#include "game_logic.h"

using namespace std;

int main() {
    GameState game;
    
    cout << "=== BEM-VINDO AO JOGO DA MEMORIA COM DESAFIOS ===\n";
    cout << "Inicializando o tabuleiro...\n";
    
    startGame(game);

    // Loop principal do Jogo
    while (!isGameOver(game)) {
        playTurn(game);
        
        // Pausa para o usuário poder ler as mensagens
        cout << "\nPressione ENTER para continuar...";
        cin.ignore();
        cin.get();
        
        // Limpa o console para o próximo turno
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    // Tela Final
    cout << "\n================ FIM DE JOGO ================\n";
    cout << game.player1.name << " - Pontuacao: " << game.player1.score << "\n";
    cout << game.player2.name << " - Pontuacao: " << game.player2.score << "\n";
    
    if (game.player1.score > game.player2.score) {
        cout << "\nVENCEDOR: " << game.player1.name << "!\n";
    } else if (game.player2.score > game.player1.score) {
        cout << "\nVENCEDOR: " << game.player2.name << "!\n";
    } else {
        cout << "\nEMPATE!\n";
    }
    
    // Libera a memória das Listas Duplamente Encadeadas
    destroy(game.board);
    destroy(game.player1.inventory);
    destroy(game.player2.inventory);

    return 0;
}