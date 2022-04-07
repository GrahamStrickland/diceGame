// Dice throwing game where 2 is a loss, 7 and 11 are wins.
#include <iostream>
#include <cstdlib>

void startGame(char& ans);
// Precondition: ans has been declared to indicate start.
// Postcondition: Game is in start state and loops.

unsigned int throwDice();
// Postcondition: Returned the sum of two random numbers
//  between 1 and 6.

void displayDie(int die);
// Precondition: die has been determined by call to throwDice().
// Postcondition: Value of die has been printed to console.

bool userTurn(char& ans);
// Precondition: An order of turns has been determined
//  by throwing the dice.
// Postcondition: The user has either won and function
//  returns true; or the user lost and function returns
//  false.

bool compTurn();
// Precondition: An order of turns has been determined
//  by throwing the dice.
// Postcondition: The computer has either won and function
//  returns true; or the computer lost and function returns
//  false.

void printScore(unsigned int user, unsigned int comp);
// Postcondition: Prints the current score.

int main()
{
    using namespace std;
    
    // Seed random number generator.
    srand(time(0));

    // Decide who goes first; user or computer.
    char ans;
    cout << "Welcome to the game of dice.\nThrow the dice "
         << "using \'t\' for throw and \'x\' for exit.\n";
    cin >> ans;
    while (ans != 't' && ans != 'T' && ans != 'x' && ans != 'X')
    {
        cout << "Please enter \'t\' to throw or \'x\' to exit!\n";
        cin >> ans;
    }
   
    // If user decides to play, enter game state.  if (ans == 't' || ans == 'T')
    startGame(ans);

    // Display thank you message on exit.
    cout << "Thanks for playing!\n";

    return 0;
}

// Uses iostream.
void startGame(char& ans)
{
    using namespace std;

    // Declare variables
    unsigned int userThrow = 0, compThrow = 0, userScore = 0,
                 compScore = 0, rounds = 1;
    bool win, next = true;
    
    // Loop through game states and update functions accordingly.
    while (next) {
        userThrow = throwDice();
        cout << endl;
        compThrow = throwDice();
        cout << "You threw " << userThrow << " and the computer threw "
             << compThrow << ".\n";
        
        // User turn.
        if (userThrow > compThrow) {
            cout << "Your throw was higher, your turn.\n";
            while (next) {
                cout << "Round " << rounds << ", your turn!\n";
                win = userTurn(ans);
                rounds++;
                if (win) userScore++;
                printScore(userScore, compScore);
                if (ans != 'x' && ans != 'X') {
                    cout << "Round " << rounds << ", computer\'s turn.\n";
                    win = compTurn();
                    rounds++;
                    if (win) compScore++;
                    printScore(userScore, compScore);
                }
                else next = false;
            }
        }
        // Computer turn.
        else if (userThrow < compThrow){
            cout << "The computer threw higher, their turn.\n";
            while (next) {
                cout << "Round " << rounds << ", computer\'s turn.\n";
                win = compTurn();
                rounds++;
                if (win) compScore++;
                printScore(userScore, compScore);
                cout << "Round " << rounds << ", your turn!\n";
                win = userTurn(ans);
                if (ans == 'x' || ans == 'X') next = false;
                else {
                    rounds++;
                    if (win) userScore++;
                    printScore(userScore, compScore);
                }
            }
        }
        else {
            cout << "Throw again!\n";
            cin >> ans;
            while (ans != 't' && ans != 'T' && ans != 'x' && ans != 'X')
            {
                cout << "Please enter \'t\' to throw or \'x\' to exit.\n";
                cin >> ans;
            }
            if (ans == 'x' || ans == 'X') break;
        }
    }
}

// Uses iostream.
unsigned int throwDice()
{
    using namespace std;

    unsigned int die1, die2, total;
    
    // Simulate dice being thrown.
    die1 = (rand() % 6) + 1;
    displayDie(die1);
    die2 = (rand() % 6) + 1;
    displayDie(die2);
    total = die1 + die2;
    cout << endl;

    return total;
}

// Uses iostream.
void displayDie(int die)
{
    using namespace std;

    switch(die) {
        case 1:
            cout << ".";
            break;
        case 2:
            cout << ":";
            break;
        case 3:
            cout << ":.";
            break;
        case 4:
            cout << "::";
            break;
        case 5:
            cout << "::.";
            break;
        case 6:
            cout << ":::";
            break;
    }
    cout << '\t';
}

// Uses iostream.
bool userTurn(char& ans)
{
    using namespace std;

    unsigned int userThrow = 0;
    bool next = true, win = false;

    while (next) {
        cout << "Throw dice? (t/x): ";
        cin >> ans;
        if (ans == 't' || ans == 'T')
        {
            userThrow = throwDice();
            if (userThrow == 7 || userThrow == 11) {
                cout << "You win this round!\n";
                next = false;
                win = true;
            }
            else if (userThrow == 2) {
                cout << "Snake eyes! You lose this round!\n";
                next = false;
            }
        } 
        else if (ans == 'x' || ans == 'X') {
            cout << "Goodbye!\n";
            next = false;
        }
        else cout << "Please enter \'t\' to throw or \'x\' to exit!\n";
    }

    return win;
}

// Uses iostream.
bool compTurn()
{
    using namespace std;

    unsigned int compThrow = 0;
    bool next = true, win = false;

    while (next) {
        compThrow = throwDice();
        if (compThrow == 7 || compThrow == 11) {
            cout << "The computer won!\n";
            next = false;
            win = true;
        }
        else if (compThrow == 2) {
            cout << "Snake eyes! The computer lost this round.\n";
            next = false;
        }
    }

    return win;
}

// Uses iostream.
void printScore(unsigned int user, unsigned int comp)
{
    using namespace std;

    cout << "User: " << user << " | Computer: " << comp << endl;
}
