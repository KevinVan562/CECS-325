// Name: Kevin Van
// Class: CECS 325-02
// Program 1 - One Card War
// Due Date: 09/19/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program

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

