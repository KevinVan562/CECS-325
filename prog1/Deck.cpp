#include "Deck.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
using namespace std;

Deck::Deck() : topCard(0) {
    // Define ranks and suits using array
	array<char, 13> ranks = {'A', '2', '3', '4', '5', '6', '7', '8', '9','T', 'J', 'Q', 'K'};
	array<char, 4> suits = {'C', 'S', 'D', 'H'};

	int index = 0;
    // Initialize deck array with 52 cards
	for (int suit = 0; suit < 4; suit++) {
    	for (int rank = 0; rank < 13; rank++) {
            //  Card object to add to deck
        	deck[index] = Card(ranks[rank], suits[suit]);
        	index++;
    	}
	}
}

Card Deck::deal() {
    //  Check if there are cards available
	if (topCard < 52) {
        // Return top card and increment topCard Index
    	return deck[topCard++];
	} else {
        // Exception if no cards left
    	throw out_of_range("No more cards!");
	}
}

void Deck::print() {
    //  Print all cards in the deck
	for (int i = 0; i < 52; i++) {
    	deck[i].print();
        //  Format output for cards after printing
    	if (i == 12 || i == 25 || i == 38 || i == 51) {
        	cout << endl;
    	} else if (i != 51) {
            // Comma between cards
        	cout << ", ";
    	}
	}
	cout << endl;
}

void Deck::shuffle() {
    srand(time(0));
    Card temp;  //  Temp variable to swap cards
    for (int n = 0; n < 52; n++) {
        int m = rand() % 52;    // Random Index
        temp = deck[n];
        deck[n] = deck [m];
        deck[m] = temp;
    }
}

