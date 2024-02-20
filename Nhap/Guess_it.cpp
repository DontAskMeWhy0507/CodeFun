#include <iostream>
using namespace std;

int generateSecretNumber ();
int getPlayerGuess();
void printAnswer(int doan);

int main (int argc, char* argv[])
{
    int SecretNumber = generateSecretNumber();
    int guess;
    do {
     guess = getPlayerGuess();
    printAnswer(guess);
    } while ( guess != SecretNumber);
    cout<<"Done!";
    return 0;
}

int generateSecretNumber()
{
    return 10;
}

int getPlayerGuess()
{
    int guess;
    cout<<"Enter your guess: ";
    cin>>guess;
    return guess;
}

void printAnswer(int doan)
{
    cout<<"You guessed: "<<doan<<endl;
}