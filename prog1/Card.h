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

