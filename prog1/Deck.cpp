// Name: Kevin Van
// Class: CECS 325-02
// Program 1 - One Card War
// Due Date: 09/19/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program

#include "Deck.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Deck::Deck() : topCard(0) {
    // Define ranks and suits using array
	char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9','T', 'J', 'Q', 'K'};
	char suits[] = {'C', 'S', 'D', 'H'};

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

