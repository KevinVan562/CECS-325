// Name: Kevin Van
// Class: CECS 325-02
// Program 1 - One Card War
// Due Date: 09/19/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program

#include "Card.h"
#include <iostream>

using namespace std;

// Default Constructor
Card::Card() : rank(' '), suit(' ') {};

// Constructor to initialize rank and suit
Card::Card(char r, char s) : rank(r), suit(s) {}

// Print cards (display the cards)
void Card::print() {
    if (rank == 'T') {
        cout << "10" << suit;
    } else {
        cout << rank << suit;
    }
}

// Compare two cards by looking at the rank order
int Card::compare(Card other) {
    const string rankOrder = "A23456789TJQK";
    int thisRankIndex = rankOrder.find(rank);
    int otherRankIndex = rankOrder.find(other.rank);

    if (thisRankIndex < otherRankIndex) {
        return -1;  // Card is Lower
    } else if (thisRankIndex > otherRankIndex) {
        return 1;   // Card is Higher
    } else {
        return 0;   //  Cards equal
    }
}
