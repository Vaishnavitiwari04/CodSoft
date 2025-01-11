#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(std::time(0)));

    // Generate a random number between 1 and 100
    int random_number = std::rand() % 100 + 1;

    int guess;
    int attempts = 0;

    cout << "Welcome to the Number Guessing Game" << std::endl;
    cout << "I have selected a random number between 1 and 100. Try to guess it!" << std::endl;

    // Loop until the user guesses the correct number
    do {
        cout << "Enter your guess: ";
        cin >> guess;
        attempts++;


        // Check if the guess is too high, too low, or correct
        if (guess > random_number) {
            cout << "Too high! Try again." << std::endl;
        } else if (guess < random_number) {
            cout << "Too low! Try again." << std::endl;
        } else {
            cout << "Congratulations! You guessed the correct number " << random_number << " in " << attempts << " attempts." << std::endl;
        }
    } while (guess != random_number);

    return 0;
}