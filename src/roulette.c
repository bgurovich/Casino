#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int RouletteSpin();
char* FindColor(int number);
void PlayRoulette(int betAmount, char* betType, int betNumber);

int tokens; // Global variable to track the total tokens

int main() {
    int betAmount;
    char betType[15];
    char userChoice;
    int betNumber = -1;

    srand(time(NULL));

    printf("\n\n\n\n\n\n\n\nWelcome to the Roulette Table!\n\n\n\n");

    // Initial tokens input
    printf("Enter the amount of tokens you want to start with: ");
    scanf("%d", &tokens);

    do {
        // Ensure player has tokens to bet
        if (tokens <= 0) {
            printf("You have run out of tokens!\n");
            break;
        }

        printf("You have %d tokens.\n", tokens);
        printf("Enter your bet amount: ");
        scanf("%d", &betAmount);

        printf("Enter your bet type (number, odd, even, red, black, zero): ");
        scanf("%s", betType);

        if (strcmp(betType, "number") == 0) {
            printf("Enter the number you are betting on (0-36): ");
            scanf("%d", &betNumber);
            printf("\n\n");
        }

        PlayRoulette(betAmount, betType, betNumber);

        printf("Do you want to continue playing? (y/n): ");
        scanf(" %c", &userChoice);
        printf("\n\n\n\n\n\n");
    
    } while (userChoice == 'Y' || userChoice == 'y');

    printf("Thanks for playing Roulette with us!\n\n\n\n");

    return 0;
}

int RouletteSpin() {
    return rand() % 37;
}

char* FindColor(int number) {
    if (number == 0) {
        return "green";
    }

    int redNumbers[] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
    int blackNumbers[] = {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35};
    
    for (int i = 0; i < 18; ++i) {
        if (number == redNumbers[i]) {
            return "red";
        }
        if (number == blackNumbers[i]) {
            return "black";
        }
    }
    return "error";
}

void PlayRoulette(int betAmount, char* betType, int betNumber) {
    if (betAmount > tokens) {
        printf("You cannot bet more tokens than you have!\n\n");
        return;
    }

    tokens -= betAmount; // Deduct bet amount from tokens

    int resultNumber = RouletteSpin();
    char* color = FindColor(resultNumber);
    int payOut = 0;

    printf("The Roulette Wheel landed on %d (%s)\n\n\n", resultNumber, color);

    if (strcmp(betType, "number") == 0) {
        if (betNumber == resultNumber) {
            if (betNumber == 0) {
                payOut = betAmount * 50;
                printf("YOU HIT JACKPOT!\nYou made %d\n\n\n\n", payOut);
            } else {
                payOut = betAmount * 35;
                printf("Nice, your number hit!\nYou made %d\n\n\n\n", payOut);
            }
            tokens += payOut; // Add the payout to tokens
        } else {
            printf("Oops, looks like you lost!\n\n\n\n");
        }
    } else if (strcmp(betType, "odd") == 0) {
        if (resultNumber != 0 && resultNumber % 2 != 0) {
            payOut = betAmount * 2;
            printf("Your bet landed!\nYou made %d\n\n\n\n", payOut);
            tokens += payOut; // Add the payout to tokens
        } else {
            printf("You lost!\nThe house took your tokens\n\n\n\n");
        }
    } else if (strcmp(betType, "even") == 0) {
        if (resultNumber != 0 && resultNumber % 2 == 0) {
            payOut = betAmount * 2;
            printf("Yippy, your bet hit!\nYou made %d\n\n\n\n", payOut);
            tokens += payOut; // Add the payout to tokens
        } else {
            printf("Better luck next time!\nYou lost!\n\n\n\n");
        }
    } else if (strcmp(betType, "red") == 0) {
        if (strcmp(color, "red") == 0) {
            payOut = betAmount * 2;
            printf("Good job, your bet hit!\nYou made %d\n\n\n\n", payOut);
            tokens += payOut; // Add the payout to tokens
        } else {
            printf("Oh no, your bet didn't land!\nYou lost!\n\n\n\n");
        }
    } else if (strcmp(betType, "black") == 0) {
        if (strcmp(color, "black") == 0) {
            payOut = betAmount * 2;
            printf("You're a pro, you should gamble more!\nYou made %d\n\n\n\n", payOut);
            tokens += payOut; // Add the payout to tokens
        } else {
            printf("Wow, that was a lousy bet!\nYou lost!\n\n\n\n");
        }
    } else if (strcmp(betType, "zero") == 0) {
        if (resultNumber == 0) {
            payOut = betAmount * 50;
            printf("CONGRATULATIONS, YOU HIT JACKPOT!\nYou made %d\n\n\n\n", payOut);
            tokens += payOut; // Add the payout to tokens
        } else {
            printf("What the Sigma!\nYou lost!\n\n\n\n");
        }
    } else {
        printf("Invalid bet type.\n\n\n\n");
    }

    printf("You now have %d tokens.\n\n\n\n", tokens);
}

