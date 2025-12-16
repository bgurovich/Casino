#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


int RouletteSpin();
char* FindColor(int number);
void PlayRoulette(int betAmount, char* betType, int betNumber);



int main() {
    int betAmount;
    char betType[15];
    char userChoice;
    int betNumber = -1;

    srand(time(NULL));

    printf("\n\n\n\n\n\n\n\nWelcome to the Roulette Table!\n\n\n\n");

    do {
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
    
    } 
    while (userChoice == 'Y' || userChoice == 'y');

    printf("Thanks for playing Roulette with us!\n\n\n\n");


    return 0;
}

int RouletteSpin() {
    return rand() % 37;
}

char* FindColor(int number) {
    if (number == 0){
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
    int resultNumber = RouletteSpin();
    char* color = FindColor(resultNumber);
    int payOut = 0;

    printf ("The Roulette Wheel landed on %d (%s)\n\n\n", resultNumber, color);


    if (strcmp(betType, "number") == 0) {
        if (betNumber == resultNumber) {
            if (betNumber == resultNumber && resultNumber == 0) {
                payOut = betAmount * 50;
                printf("YOU HIT JACK POT!\nYou made %d\n\n\n\n", payOut);
            } 
            else {
                payOut =  betAmount * 35;
                printf("Nice, your number hit!\nYou made %d\n\n\n\n", payOut);
            }
        }
        else {
            
            printf("Oops looks like you lost %d!\n\n\n\n", betAmount);
        }
    }
    else if (strcmp(betType, "odd") == 0) {
        if (resultNumber != 0 && resultNumber % 2 != 0) {
            payOut = betAmount * 2;
            printf("Your bet landed!\nYou made %d\n\n\n\n", payOut);
        }
        else {

            printf("You lost!\nThe house took %d from you\n\n\n\n", betAmount);
        }
    }
    else if (strcmp(betType, "even") == 0) {
        if (resultNumber != 0 && resultNumber % 2 == 0) {
            payOut = betAmount * 2;
            printf("Yippy your bet hit!\nYou made %d\n\n\n\n", payOut );
        }
        else {

            printf("Better luck next time!\nYou lost %d\n\n\n\n", betAmount);
        }
    }
    else if (strcmp(betType, "red") == 0) {
        if (strcmp(color, "red") == 0) {
            payOut = betAmount * 2;
            printf("Good job, your bet hit!\nYou made %d\n\n\n\n", payOut);
        }
        else {

            printf("Oh no your bet didn't land!\nYou lost %d\n\n\n\n", betAmount);
        }
    }
    else if (strcmp(betType, "black") == 0) {
        if (strcmp(color, "black") == 0) {
            payOut = betAmount * 2;
            printf("You're a pro, you should gamble more!\nYou made %d\n\n\n\n", payOut);
        }
        else {

            printf("Wow, that was a lousy bet!\nYou lost %d\n\n\n\n", betAmount);
        }
    }
    else if (strcmp(betType, "zero") == 0) {
        if (resultNumber == 0) {
            payOut = betAmount * 50;
            printf("CONGRATULATIONS YOU HIT JACKPOT!\nYou made %d\n\n\n\n", payOut);
        }
        else {

            printf("What the Sigma!\nYou lost %d\n\n\n\n", betAmount);
        }
    }
    else {
        printf("Invalid bet type\n\n\n\n");
    }
} 