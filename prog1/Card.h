// Name: Kevin Van
// Class: CECS 325-02
// Program 1 - One Card War
// Due Date: 09/19/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program

#ifndef CARD_H
#define CARD_H

class Card {
    private:
        char rank;
        char suit;
    public:
        // Default Constructor
        Card();

        // Card Constructor
        Card(char, char);

        // Print function
        void print();

        // Compare function
        int compare(Card);
};

#endif

