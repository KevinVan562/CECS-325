#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck {
    private:
        Card deck[52]; // Array to store the cards
        int topCard; // Index of the top card

    public:
        Deck();        // Constructor to initialize the deck
        Card deal();   // Deal a card
        void print(); // Display all cards in the deck
        void shuffle(); // Shuffle the deck
};

#endif

