// Name: Kevin Van
// Class: CECS 325-02
// Program 1 - One Card War
// Due Date: 09/19/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program

#include <iostream>
#include <string>
#include "Deck.h"
using namespace std;

int main() {
    
    int p1Wins = 0;
    int p2Wins = 0;
    int ties = 0;
    string p1Name;
    string p2Name;

    Deck deck;

    cout << "Enter the name of the first player: ";
    cin >> p1Name;
    cout << "Enter the name of the second player: ";
    cin >> p2Name;
    
    cout << "Original Deck \n";
    deck.print();
    cout << "\n";
    cout << "Shuffled Deck \n";
    deck.shuffle();
    deck.print();

    for (int totalGames = 1; totalGames < 27; totalGames++) {
        Card p1Card = deck.deal();
        Card p2Card = deck.deal();
        cout << endl;
        cout << "Game " << totalGames << endl;
        cout << "--------" << endl;
        cout << "\t" << p1Name << " => ";
        p1Card.print();
        cout << endl;
        cout << "\t" << p2Name << " => ";
        p2Card.print();
        cout << endl;

        int winner = p1Card.compare(p2Card);

        if (winner == 1) {
            cout << p1Name << " => Winner" << endl;
            p1Wins++;
        } else if (winner == 0) {
            cout << "Tie game" << endl;
            ties++;
        } else if (winner == -1) {
            cout << p2Name << " => Winner" << endl;
            p2Wins++;
        }
    }

    cout << "----- Final Stats -----" << endl;
    cout << "\t" << p1Name << " vs. " << p2Name << endl;
    cout << "Wins\t" << p1Wins << "\t\t" << p2Wins << endl;
    cout << "Losses\t" << p2Wins << "\t\t" << p1Wins << endl;
    cout << "Ties\t" << ties << "\t\t" << ties << endl;

    return 0;
}
