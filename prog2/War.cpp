// Name: Kevin Van
// Class: CECS 325-02
// Program 1 - One Card War
// Due Date: 09/19/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class Card {
    private:
        char rank;
        char suit;

    public:
        Card(char r, char s) : rank(r), suit(s) {}

        void print() {
            if (rank == 'T') {
                cout << "10" << suit;
            } else {
                cout << rank << suit;
            }
        }

        int compare(Card other) {
            const string rankOrder = "A23456789TJQK";
            int thisRankIndex = rankOrder.find(rank);
            int otherRankIndex = rankOrder.find(other.rank);

            if (thisRankIndex < otherRankIndex) {
                return -1;
            } else if (thisRankIndex > otherRankIndex) {
                return 1;
            } else {
                return 0;
            }
        }
};

class Deck {
    private:
        vector<Card> deck;
        int topCard;

    public:
        Deck() {
            char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
            char suits[] = {'C', 'S', 'D', 'H'};
            topCard = 0;

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 13; j++) {
                    deck.push_back(Card(ranks[j], suits[i]));
                }
            }
        }

        Card deal() {
            if (topCard < deck.size()) {
                return deck[topCard++];
            } else {
                throw out_of_range("Error - Deck is empty");
            }
        }

        void print() {
	    for (int i = 0; i < deck.size(); i++) {
    	    deck[i].print();
    	    if (i == 12 || i == 25 || i == 38 || i == 51) {
        	    cout << endl;
    	    } else if (i != 51) {
        	    cout << ", ";
    	    }
	    }
	        cout << endl;
        }

        void shuffle() {
            srand(time(0));
            for (int n = 0; n < deck.size(); n ++) {
                int m = rand() % deck.size();
                Card temp = deck[n];
                deck[n] = deck [m];
                deck[m] = temp;
            }
        }

        bool isEmpty() {
            if (topCard >= deck.size()) {
                return true;
            }
            return false;
        }
};


int main() {
    
    int p1Wins = 0;
    int p2Wins = 0;
    int ties = 0;
    int totalGames;
    string p1Name;
    string p2Name;

    Deck deck;

    cout << "Enter the name of the first player: ";
    cin >> p1Name;
    cout << "Enter the name of the second player: ";
    cin >> p2Name;
    cout << "How many games will they play? ";
    cin >> totalGames;

    cout << "Original Deck \n";
    deck.print();
    cout << "\n";
    cout << "Shuffled Deck \n";
    deck.shuffle();
    deck.print();

    for (int games = 1; games <= totalGames; games++) {
        try {
            Card p1Card = deck.deal();
            Card p2Card = deck.deal();
            cout << endl;
            cout << "Game " << games << endl;
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
        } catch (const out_of_range r) {
            cout << r.what() << endl;
            break;
        }
    }

    cout << "----- Final Stats -----" << endl;
    cout << "\t" << p1Name << " vs. " << p2Name << endl;
    cout << "Wins\t" << p1Wins << "\t\t" << p2Wins << endl;
    cout << "Losses\t" << p2Wins << "\t\t" << p1Wins << endl;
    cout << "Ties\t" << ties << "\t\t" << ties << endl;

    return 0;
}
