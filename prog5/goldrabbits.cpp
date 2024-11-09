

#include <iostream>
#include <time.h>
#include <iomanip>
#include <map>
#include <climits> // for INT_MAX
using namespace std;

// Prototype or signature
int goldRabbits(int);
// Global count for goldRabbits
int fiboCount = 0;

int goldRabbits(int n) {
    static map<int, int> store;
    // if n = -1, print contents of map by using iterator
    if (n == -1) {
        cout << "Fibo Map\n--------\n";
        for (map<int, int>::iterator it = store.begin(); it != store.end(); ++it) {
            cout << it->first << ": " << it->second << endl;
        }
        return 0;
    }
    
    fiboCount++;

    if (n == 0 || n == 1) {
        store[n] = 1;
        return 1;
    }
    
    // Checks if already calculated
    if(store.find(n) != store.end()) {
        return store[n];
    }

    // Calculate previous two values
    int prev1 = goldRabbits(n - 1);
    int prev2 = goldRabbits(n - 2);

    // Check for overflow using INT_MAX
    if (prev1 > 0 && prev2 > 0 && prev1 > INT_MAX - prev2) {
        throw overflow_error("\nOverflow at(" + to_string(n) + ")");
    }
    
    // Store the result in map and return results
    int result = prev1 + prev2;
    store[n] = result;
    return result;
}

int main() {
    int const months = 12 * 10;
    int start = time(0);
    for (int i = 0; i < months; i++) {
        try {
            int current = time(0);
            cout << setw(5) << current - start << ":";
            cout << " GoldRabbits(" << setw(2) << i << ") = ";
            cout << setw(11) << goldRabbits(i) << "  fiboCount:" << setw(11) << fiboCount << endl;
        } catch (const overflow_error& e) {
            cout << e.what() << endl;
            break;
        }       
    }

    // Prints content of map if -1 is passed
    goldRabbits(-1);

    return 0;
};
