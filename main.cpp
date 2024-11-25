#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>


using namespace std;


const int WORD_LENGTH = 5;
const int NUMBER_LENGTH = 5;
const int NOT_MATCH = 0;
const int PARTIAL_MATCH = 1;
const int MATCH = 2;



//ЧАСТ 1: WORDLE С ДУМИ

string getRandomWord() {
    string words[] = {"READY", "CHERY", "PLAYS", "SWEET", "ZESTY"};
    srand(time(0));
    return words[rand() % 5];
}

bool isValidWord(const string &word) {
    return word.length() == WORD_LENGTH && word.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos;
}

//ЧАСТ 2: WORDLE С ЧИСЛА

string getRandomNumber() {
    string number;
    srand(time(0));
    for (int i = 0; i < NUMBER_LENGTH; i++) {
        number += to_string(rand() % 10);
    }
    return number;
}

bool isValidNumber(const string &number) {
    return number.length() == NUMBER_LENGTH && number.find_first_not_of("0123456789") == string::npos;
}

// ОБЩА ЛОГИКА ЗА СЪВПАДЕНИЯ

void markMatch(vector<vector<int>> &matches, int tryIndex, string target, string guess) {
    for (int i = 0; i < guess.length(); i++) {
        matches[tryIndex][i] = NOT_MATCH;
    }
    for (int j = 0; j < guess.length(); j++) {
        for (int i = 0; i < target.length(); i++) {
            if (guess[j] == target[i]) {
                if (i == j) {
                    matches[tryIndex][j] = MATCH;
                    break;
                } else {
                    matches[tryIndex][j] = PARTIAL_MATCH;
                }
            }
        }
    }
}

bool isAllMatch(const string &target, const string &guess) {
    return target == guess;
}

//ПЕЧАТ НА СЪСТОЯНИЕТО НА ИГРАТА

void printWordle(vector<string> tries, vector<vector<int>> matches, int currentTry, bool isNumberGame) {
    system("cls");
    cout << (isNumberGame ? "===================== NUMBER GUESS =====================\n"
                          : "===================== WORDLE GAME =====================\n");
    for (int i = 0; i <= currentTry && i < tries.size(); i++) {
        string separator = "|";
        string text = "|";
        for (int j = 0; j < tries[i].length(); j++) {
            separator += "=====";
            char value = tries[i][j];
            text += "  ";
            if (matches[i][j] == PARTIAL_MATCH) {
                text += "\033[33m";
            } else if (matches[i][j] == MATCH) {
                text += "\033[32m";
            }
            text += value;
            text += "\033[0m";
            text += "  |";
        }
        if (i == 0) {
            cout << separator << endl;
        }
        cout << text << endl;
        cout << separator << endl;
    }
}



void playWordle(bool isNumberGame) {
    const int maxTries = 6;
    vector<string> tries(maxTries);
    vector<vector<int>> matches(maxTries, vector<int>(isNumberGame ? NUMBER_LENGTH : WORD_LENGTH));
    string target = isNumberGame ? getRandomNumber() : getRandomWord();
    string input;
    int currentTry = 0;
    while (currentTry < maxTries) {
        do {
            cout << "Enter your " << (isNumberGame ? "number" : "word")
                 << " (" << (isNumberGame ? NUMBER_LENGTH : WORD_LENGTH) << "-length) or Q to quit: ";
            getline(cin, input);

        } while (input != "Q" && !(isNumberGame ? isValidNumber(input) : isValidWord(input)));

        if (input == "Q") {
            cout << "Game quit. The correct answer was: " << target << endl;
            break;
        }

        tries[currentTry] = input;
        markMatch(matches, currentTry, target, input);
        printWordle(tries, matches, currentTry, isNumberGame);

        if (isAllMatch(target, input)) {
            cout << "Congratulations! You guessed the " << (isNumberGame ? "number: " : "word: ") << target << endl;
            break;
        }

        currentTry++;
        if (currentTry == maxTries) {
            cout << "Sorry, you didn't guess the " << (isNumberGame ? "number." : "word.") << endl;
            cout << "The correct answer was: " << target << endl;
        }
    }
}



int main() {

    {
        system("cls");
        cout << "| ==================================================================================|" << endl;
        cout << "|  %%%%%%%%                         %%%%%%%%%%%%%%                     %%      %%   |" << endl;
        cout << "|  %%       %%           %%%%             %%         %%%%%%%%%%        %%     %%    | " << endl;
        cout << "|  %%         %%      %%      %%          %%         %%                %%   %%      |" << endl;
        cout << "|  %%        %%      %%        %%         %%         %%                %%  %%       |" << endl;
        cout << "|  %% %%%%%%%       %%%%%%%%%%%%%         %%         %%%%%%%%%%        %% %%        |" << endl;
        cout << "|  %%              %%           %%        %%         %%                %%    %%     |" << endl;
        cout << "|  %%             %%             %%       %%         %%                %%      %%   |" << endl;
        cout << "|  %%            %%               %%      %%         %%%%%%%%%%        %%       %%  |" << endl;
        cout << "| ==================================================================================|" << endl;

        cout << "|==========================================================================|" << endl;
        cout << "|   %%       %%                                %%                          |" << endl;
        cout << "|   %% | %%  %%                                %%                          |" << endl;
        cout << "|   %% |%%%  %%    %%%%%    %%%%%%  %%%%%%%    %%    %%%%%%                |" << endl;
        cout << "|   %% %% %% %%  %%     %%  %%      %%     %%  %%   %%     %%              |" << endl;
        cout << "|   %%%%   %%%%  %%     %%  %%      %%     %%  %%   %%%%%%%%               |" << endl;
        cout << "|   %%%     %%%  %%     %%  %%      %%     %%  %%   %%                     |" << endl;
        cout << "|   %%      %%%    %%%%%    %%      %%%%%%%    %%    %%%%%%%               |" << endl;
        cout << "|==========================================================================|" << endl;


        {
            while (true) {
                system("cls");
                cout << "===================== WORDLE MENU =====================" <<endl;
                cout << "1. Play Wordle with words" << endl;
                cout << "2. Play Wordle with numbers" << endl;
                cout << "3. Quit" << endl;
                cout << "======================================================" << endl;
                cout << "Choose an option (1/2/3): " << endl;

                int choice;
                cin >> choice;
                cin.ignore();

                if (choice == 1) {
                    playWordle(false); // Игра с думи
                } else if (choice == 2) {
                    playWordle(true); // Игра с числа
                } else if (choice == 3) {
                    cout << "Thank you for playing! Goodbye!" << endl;
                    break;
                } else {
                    cout << "Invalid option. Try again.\n";
                }
            }
        }
    }
}


