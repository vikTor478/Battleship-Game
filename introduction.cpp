#include <iostream>
#include <string>
#include <limits>
#include <vector>

using namespace std;

// Function to clear the input buffer in case of invalid input
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayWelcomeMessage() {
    cout << "=========================================\n";
    cout << "        Welcome to Battleship Game!      \n";
    cout << "=========================================\n\n";

    cout << "Here are the rules:\n";
    cout << "The game is played on a 10x10 grid.\n";
    cout << "You and the computer will each have your own grid.\n";
    cout << "Ships are placed randomly on the grid.\n";
    cout << "Take turns inputting coordinates to strike.\n";
    cout << "The Grid Symbols:\n";
    cout << "    '~' - Water (empty cell)\n";
    cout << "    'S' - Player's ship location\n";
    cout << "    'X' - Hit (a successful strike on a ship)\n";
    cout << "    '0' - Miss (a strike on water)\n";
    cout << "The first to sink all enemy ships wins!\n";
    cout << "Good Luck!\n\n";
}

void getShipConfiguration(int& shipCount, vector<int>& shipSizes) {
    while (true) {
        cout << "Enter the number of ships you want to place (1-5): ";
        if (cin >> shipCount && shipCount >= 1 && shipCount <= 5)
            break;
        else {
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
            clearInput();
        }
    }

    shipSizes.resize(shipCount);

    for (int i = 0; i < shipCount; ++i) {
        while (true) {
            cout << "Enter the size (number of cells) for ship #" << (i + 1) << " (1-4): ";
            if (cin >> shipSizes[i] && shipSizes[i] >= 1 && shipSizes[i] <= 4)
                break;
            else {
                cout << "Invalid input. Please enter a number between 1 and 4.\n";
                clearInput();
            }
        }
    }

    cout << "\nYou chose to place " << shipCount << " ship(s) with the following sizes: ";
    for (int size : shipSizes) {
        cout << size << " ";
    }
    cout << "\nLet's set up your battlefield!\n\n";
}

int main() {
    int numberOfShips;
    vector<int> shipSizes;

    displayWelcomeMessage();
    getShipConfiguration(numberOfShips, shipSizes);

    return 0;
}
