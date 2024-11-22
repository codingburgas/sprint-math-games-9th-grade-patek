#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>


using namespace std;


const int WORD_LENGTH = 5;
const int NOT_MATCH = 0;
const int PARTIAL_MATCH = 1;
const int MATCH = 2;


void printWelcomeBanner()
{
    cout << "======================== WORDLE =========================\n";
    cout << "|        Welcome to the Wordle Game Challenge!         |\n";
    cout << "| Guess the hidden 5-letter word within 6 attempts!    |\n";
    cout << "| Match colors indicate:                               |\n";
    cout << "| - Green: Correct letter in the correct position.     |\n";
    cout << "| - Yellow: Correct letter in the wrong position.      |\n";
    cout << "| - No color: No match for the letter.                 |\n";
    cout << "========================================================\n\n";
}

string getRandomWord()

{
    return "ready","chery","plays","sweet", "zesty", "stone", "pearl", "fruit", "piano", "lucky",
    "taste", "beach", "night", "happy", "liver", "dream", "flame", "grape", "shine","apple", "grape", "peach", "lemon", "cherry", "melon", "mango", "berry",
    "candy", "juice" "blast";
}

void toUpperCase(string &input)

{
    transform(input.begin(), input.end(), input.begin(), [](unsigned char c)
    { return toupper(c); });
}

bool isValid(string word)

{
    return word.length() == WORD_LENGTH && word.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos;
}

void markMatch(vector<vector<int>> &matches, int tryIndex, string target, string guess)
{
    for (int i = 0; i < guess.length(); i++)

    {
        matches[tryIndex][i] = NOT_MATCH;

    }
    for (int j = 0; j < guess.length(); j++)

    {
        for (int i = 0; i < target.length(); i++)

        {
            if (guess[j] == target[i])

            {
                if (i == j)

                {
                    matches[tryIndex][j] = MATCH;

                    break;
                }

                {
                    matches[tryIndex][j] = PARTIAL_MATCH;

                }
            }
        }
    }
}

bool isAllMatch(string target, string guess)

{
    for (int i = 0; i < guess.length(); i++)

    {
        if (guess[i] != target[i])

            return false;
    }

}

void printWordle(vector<string> tries, vector<vector<int>> matches, int currentTry)
{
    system("cls");
    cout << "=================================================================" << endl;
    cout << "|                                                               |" << endl;
    cout << "|   $$\\      $$\\                           $$\\ $$\\   |" << endl;
    cout << "|   $$ | $\\  $$ |                          $$ |$$ |             |" << endl;
    cout << "|   $$ |$$$\\ $$ | $$$$$$\\   $$$$$$\\   $$$$$$$ |$$ | $$$$$$\\     |" << endl;
    cout << "|   $$ $$ $$\\$$ |$$  __$$\\ $$  __$$\\ $$  __$$ |$$ |$$  __$$\\    |" << endl;
    cout << "|   $$$$  _$$$$ |$$ /  $$ |$$ |  \\__|$$ /  $$ |$$ |$$$$$$$$ |   |" << endl;
    cout << "|   $$$  / \\$$$ |$$ |  $$ |$$ |      $$ |  $$ |$$ |$$   ____|   |" << endl;
    cout << "|   $$  /   \\$$ |\\$$$$$$  |$$ |      \\$$$$$$$ |$$ |\\$$$$$$$\\    |" << endl;
    cout << "|   \\__/     \\__| \\______/ \\__|       \\_______|\\__| \\_______|   |" << endl;
    cout << "|                                                               |" << endl;
    cout << "=================================================================" << endl;
    for (int i = 0; i <= currentTry && i < tries.size(); i++)
    {
        string separator = "-";
        string padding = "|";
        string text = "|";
        for (int j = 0; j < tries[i].length(); j++)
        {
            separator += "------";
            padding += "     |";
            char value = toupper(tries[i][j]);
            text += "  ";
            if (matches[i][j] == PARTIAL_MATCH)
            {
                text += "\033[33m";
            }
            else if (matches[i][j] == MATCH)
            {
                text += "\033[32m";
            }
            text += value;
            if (matches[i][j] == PARTIAL_MATCH || matches[i][j] == MATCH)
            {
                text += "\033[0m";
            }
            text += "  |";
        }
        if (i == 0)
        {
            cout << separator << endl;
        }
        cout << padding << endl;
        cout << text << endl;
        cout << padding << endl;
        cout << separator << endl;
    }
}
void printWinMessage(const string &target, int triesUsed) {
    cout << "\n========================================================\n";
    cout << "🎉 Congratulations! You guessed the word: " << target << " 🎉\n";
    cout << "Attempts used: " << triesUsed << " out of "  << ".\n";
    cout << "========================================================\n";
}

// Печата съобщение за загуба
void printLoseMessage(const string &target) {
    cout << "\n========================================================\n";
    cout << "❌ Sorry! You've used all your attempts. ❌\n";
    cout << "The correct word was: " << target << ".\n";
    cout << "Better luck next time!\n";
    cout << "========================================================\n";
}

int main()
{
    int numberOfTries = 6;
    vector<string> tries(numberOfTries);
    vector<vector<int>> matches(numberOfTries, vector<int>(WORD_LENGTH));
    string targetWord = getRandomWord();
    toUpperCase(targetWord);
    string input;
    int currentTry = 0;
    while (currentTry < numberOfTries)
    {
        do
        {
            cout << "Please enter your guess (word length must be " + to_string(WORD_LENGTH) + ") or type Q to quit: ";
            getline(cin, input);
            toUpperCase(input);
        } while (input != "Q" && !isValid(input));
        if (input == "Q")
        {
            cout << "Quit game" << endl;
            break;
        }
        tries[currentTry] = input;
        markMatch(matches, currentTry, targetWord, input);
        printWordle(tries, matches, currentTry);
        if (isAllMatch(targetWord, input))
        {

        }
        if (currentTry == numberOfTries - 1)
        {
            cout << "You didn't find the word" << endl;
        }
    }

}