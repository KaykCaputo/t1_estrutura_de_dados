#ifndef T1_ESTRUTURA_DE_DADOS_CARDS_H
#define T1_ESTRUTURA_DE_DADOS_CARDS_H
enum CardType {
    NORMAL,
    BONUS,
    PENALTY
};

enum CardState {
    HIDDEN,
    REVEALED,
    MATCHED
};

struct Card {
    int id;
    char symbol;
    CardState state;
    CardType type;
    int pairId;
};

#endif //T1_ESTRUTURA_DE_DADOS_CARDS_H