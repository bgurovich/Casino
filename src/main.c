#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//global variables
int tokens;
int bet;

//Function to print ouf the dice face based on the random number generated
void printDiceFace(int num) {
    switch(num) {
        case 1:
            printf(" ___________\n|           |\n|           |\n|     *     |\n|           |\n|___________|\n");
            break;
        case 2:
            printf(" ___________\n|           |\n|  *        |\n|           |\n|        *  |\n|___________|\n");
            break;
        case 3:
            printf(" ___________\n|           |\n|  *        |\n|     *     |\n|        *  |\n|___________|\n");
            break;
        case 4:
            printf(" ___________\n|           |\n|  *     *  |\n|           |\n|  *     *  |\n|___________|\n");
            break;
        case 5:
            printf(" ___________\n|           |\n|  *     *  |\n|     *     |\n|  *     *  |\n|___________|\n");
            break;
        case 6:
            printf(" ___________\n|           |\n|  *     *  |\n|  *     *  |\n|  *     *  |\n|___________|\n");
            break;
        default:
            printf("Invalid dice number\n");
            break;
    }
}

void craps(int max,int min)
{
//declaring the random generator and initializing time for the generator
    int getRandomGenerator(int max, int min);
        srand(time(0));

    max=6; min=1;
    int dsum;
    int dsum2;
    int dice1 = getRandomGenerator(max,min);
    int dice2 = getRandomGenerator(max,min);
    int dice3 = getRandomGenerator(max,min);
    int dice4 = getRandomGenerator(max,min);

// denoting the sum for the rolls
    dsum=dice1+dice2;
    dsum2=dice3+dice4;

//ask user for bet
    printf("\n");
    printf("\nAvailable Tokens: %d\n", tokens);
    printf("\nPlace your bet PLEASE:\n");
    scanf("%d", &bet);
    printf("\n");
   
//loop to prevent a negative balance
    while (bet>tokens)
    {
        printf("\n");
        printf("\nPlease place a bet less than or equal to %d, enter new bet:", tokens);
        scanf("%d",&bet);
    }
    
    printf("\n\n");

    printDiceFace(dice1); printf("\t\t\n");
    printDiceFace(dice2);
    printf("\nRoll is %d\n",dsum);
    if(dsum==7||dsum==11)
    {
        tokens=tokens+bet+(bet*2);
        printf("What a stroke of luck, you have WON!!\n");
        printf("Tokens: %d", tokens);
    }
    else
    {
        if(dsum==2||dsum==3||dsum==12)
        {
            tokens=tokens-bet;
            printf("You have lost\n");
            printf("Tokens: %d\n", tokens);
        }
        else 
        {
            printf("Pointer is %d\n", dsum);
            printf("Let's roll again.\n");

            printDiceFace(dice3); printf("\t\t\n");
            printDiceFace(dice4);

            printf("\nRoll is %d \n",dsum2);
            if(dsum==dsum2)
            {
                tokens=tokens+bet+(bet*2);
                printf("Winner winner\n");
                printf("Tokens: %d\n", tokens);
            }
            else
            {
                tokens=tokens-bet;
                printf("Unfortunely your luck runs out here\n");
                printf("Tokens: %d\n", tokens);

            }
        }
    }
}

//Define constants for the number of suits, ranks, cards in a deck, and total cards for two decks
const int NUM_SUITS = 4;
const int NUM_RANKS = 13;
const int NUM_CARDS = 52;
const int TOTAL_CARDS = 104;

// Define a structure for a card, which includes its suit, rank, and value
typedef struct {
    char *suit;
    char *rank;
    int value;
} Card;

// Function to initialize the deck of cards with two decks
void cardDeck(Card *deck){

    char *suits[] = {"<3", "<>", "&&", "##"}; // Represent suits: Hearts, Diamonds, Clubs, Spades
    char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K"}; // Card ranks
    int values[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10}; //Blackjack Values

    // Loop through two decks
    for(int deckNum = 0; deckNum < 2; deckNum++){
        for(int i = 0; i < NUM_SUITS; i++){
            for(int j = 0; j < NUM_RANKS; j++){
                int index = deckNum * NUM_CARDS + i * NUM_RANKS + j;
                deck[index].suit = suits[i];
                deck[index].rank = ranks[j];
                deck[index].value = values[j];
            }
        }
    }
}

// Function to shuffle the deck
void shuffleDeck(Card *deck){
    Card temp;
    for(int i = 0; i < TOTAL_CARDS; i++){
        int j = i + rand() % (TOTAL_CARDS - i);
        temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

// Function to draw a card from the deck
int drawCard(Card *deck, int *cardDrawn, int *currentIndex){
    if(*currentIndex < TOTAL_CARDS){
        int index = *currentIndex;
        cardDrawn[index] = 1;
        (*currentIndex)++;
        return index;
    }
    return -1; //No more cards to draw
}

// Funciton to calculate the total value of a hand
int calculateHandValue(Card *deck, int *hand, int numCards){
    int totalValue = 0, numAces = 0;
    for(int i = 0; i < numCards; i++){
        int cardValue = deck[hand[i]].value;
        totalValue += cardValue;
        if(cardValue == 11){
            numAces++;
        }
    }
    // Adjust value of Aces from 11 to 1 if the total value exceeds 21
    while(totalValue > 21 && numAces > 0){
        totalValue -= 10;
        numAces--;
    }
    return totalValue;
}

// Function to print a player's or dealer's hand in a card-like format
void printHand(Card *deck, int *hand, int numCards){
    for (int i = 0; i < numCards; i++){
        printf("\n/-----/\n");
        printf("|%s   |\n", deck[hand[i]].suit);
        printf("|  %s  |\n", deck[hand[i]].rank);
        printf("|   %s|\n", deck[hand[i]].suit);
        printf("/-----/\n");
    }
}

// Function to simulate the game of Blackjack
void playBlackjack(Card *deck){
    int cardDrawn[TOTAL_CARDS];
    for(int i = 0; i < TOTAL_CARDS; i++){
        cardDrawn[i] = 0;
    }
    int currentIndex = 0;
    int playerHand[10], dealerHand[10];
    int playerCardCount = 0, dealerCardCount = 0;
    int bet;

    //Get the player's bet
    printf("\nYou have %d tokens. Enter your bet: ", tokens);
    scanf("%d", &bet);

    if(bet > tokens){
        printf("You don't have enough tokens to make that bet.\n");
        return;
    }

    // Starting Hands
    playerHand[playerCardCount++] = drawCard(deck, cardDrawn, &currentIndex);
    playerHand[playerCardCount++] = drawCard(deck, cardDrawn, &currentIndex);
    dealerHand[dealerCardCount++] = drawCard(deck, cardDrawn, &currentIndex);

    printf("\nYour hand:\n");
    printHand(deck, playerHand, playerCardCount);

    printf("\nDealer's visible card:\n");
    printHand(deck, dealerHand, 1);

    // Player's turn
    int playerValue = calculateHandValue(deck, playerHand, playerCardCount);
    char choice;
    while (playerValue < 21){
        printf("\nYour total: %d. Hit (h) or Stand (s)? ", playerValue);
        scanf(" %c", &choice);
        if(choice == 's'){
            break;
        }
        else if(choice == 'h'){
            playerHand[playerCardCount++] = drawCard(deck, cardDrawn, &currentIndex);
            printf("\nYour hand:\n");
            printHand(deck, playerHand, playerCardCount);
            playerValue = calculateHandValue(deck, playerHand, playerCardCount);
        }
    }
    if (playerValue > 21){
        printf("\nYou busted! Dealer wins.\n");
        tokens -= bet;
        return;
    }

    //Dealer's turn
    printf("\nDealer's turn:\n");
    while(calculateHandValue(deck, dealerHand, dealerCardCount) < 17){
        dealerHand[dealerCardCount++] = drawCard(deck, cardDrawn, &currentIndex);
    }
    printf("\nDealer's hand:\n");
    printHand(deck, dealerHand, dealerCardCount);

    int dealerValue = calculateHandValue(deck, dealerHand, dealerCardCount);
    printf("\nYour total: %d, Dealer's total: %d\n", playerValue, dealerValue);

    // Determine winner and update tokens
    if (dealerValue > 21 || playerValue > dealerValue){
        if(playerValue == 21 && playerCardCount == 2){
            printf("Blackjack! You win 3 to 2!\n");
            tokens += bet * 1.5;
        }
        else{
            printf("You win! You win 1 to 1!\n");
            tokens += bet;
        }
    }
    else if(playerValue < dealerValue){
        printf("Dealer wins! You lost your bet.\n");
        tokens -= bet;
    }
    else {
        printf("It's a tie! You get your bet back.\n");
    }
    printf("You now have %d tokens.\n", tokens);
}

// Main funtion to connect all previous Blackjack functions
void blackjack()
{
    Card deck[TOTAL_CARDS];
    while(tokens > 0){
        srand(time(NULL));
        cardDeck(deck);
        shuffleDeck(deck);

        playBlackjack(deck);
        char choice;
        do{
        printf("Play again? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y'){
            break;
        }
        else if (choice == 'n'){
            break;
        }
        else 
        {
            printf("Invalid input. Please enter 'y' or 'n'.\n");
        }
    }while(choice != 'y' || choice != 'n');
    if(choice != 'y'){
        break;
    }
    }

    printf("Game over! You ended with %d tokens.\n", tokens);

}
// Declaring functions used for roulette wheel
int RouletteSpin();
char* FindColor(int number);
void PlayRoulette(int betAmount, char* betType, int betNumber);



void roulette()
{
    int betAmount;
    char betType[15];
    char userChoice;
    int betNumber = -1;

    srand(time(NULL)); //seed the random number generator in time so maximize the random chance

    printf("\n\n\n\n\n\n\n\nWelcome to the Roulette Table!\n\n\n\n");

    do { //prompting user for bet amount, bet type, and if they want to continue playing
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

}

int RouletteSpin() {  //Function for random number generator used for roulette wheel.
    return rand() % 37;
}

char* FindColor(int number) {  //function used to find the color of a specific random number, routing the color and number values together
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

void PlayRoulette(int betAmount, char* betType, int betNumber) { //function used for playing roulette
    int payOut;
    if (betAmount > tokens || tokens <= 0) { //prompt user they can only bet the amount of tokens they have available
        printf("\n\nYou cannot bet more tokens than what you have!\n\n\n");
        return;
    }
    int resultNumber = RouletteSpin();  //initializing functions equal to variables to make coding easier
    char* color = FindColor(resultNumber);

    printf ("\nThe Roulette Wheel landed on %d (%s).\n\n\n", resultNumber, color); //result of roulette spin in number and color


    if (strcmp(betType, "number") == 0) { //outcomes for number type bet
        if (betNumber == resultNumber) {
            if (betNumber == resultNumber && resultNumber == 0) {
                payOut = betAmount * 50;
                tokens += betAmount * 50;
                printf("YOU HIT JACK POT!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
            } 
            else {
                payOut = betAmount * 35;
                tokens +=  betAmount * 35;
                printf("Nice, your number hit!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
            }
        }
        else {
            tokens -= betAmount;
            printf("Oops looks like you lost %d tokens!\n\nYou now have %d tokens!\n\n\n\n", betAmount, tokens);
        }
    }
    else if (strcmp(betType, "odd") == 0) { //outcomes for odd type bet
        if (resultNumber != 0 && resultNumber % 2 != 0) {
            payOut = betAmount * 2;
            tokens += betAmount * 2;
            printf("Your bet landed!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
        }
        else {
            tokens -= betAmount;
            printf("You lost!\n\nThe house took %d tokens from you!\n\nYou now have %d tokens!\n\n\n\n", betAmount, tokens);
        }
    }
    else if (strcmp(betType, "even") == 0) { //outcomes for even type bet
        if (resultNumber != 0 && resultNumber % 2 == 0) {
            payOut = betAmount * 2;
            tokens += betAmount * 2;
            printf("Yippy your bet hit!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
        }
        else {
            tokens -= betAmount;
            printf("Better luck next time!\n\nYou lost %d tokens!\n\nYou now have %d tokens!\n\n\n\n", betAmount, tokens);
        }
    }
    else if (strcmp(betType, "red") == 0) { //outcomes for red type bet
        if (strcmp(color, "red") == 0) {
            payOut = betAmount * 2;
            tokens += betAmount * 2;
            printf("Good job, your bet hit!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
        }
        else {
            tokens -= betAmount;
            printf("Oh no your bet didn't land!\n\nYou lost %d tokens!\n\nYou now have %d tokens!\n\n\n\n", betAmount, tokens);
        }
    }
    else if (strcmp(betType, "black") == 0) { //outcomes for black type bet
        if (strcmp(color, "black") == 0) {
            payOut = betAmount * 2;
            tokens += betAmount * 2;
            printf("You're a pro, you should gamble more!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
        }
        else {
            tokens -= betAmount;
            printf("Wow, that was a lousy bet!\n\nYou lost %d tokens!\n\nYou now have %d tokens!\n\n\n\n", betAmount, tokens);
        }
    }
    else if (strcmp(betType, "zero") == 0) { //outcomes for zero type bet (jackpot)
        if (resultNumber == 0) {
            payOut = betAmount * 50;
            tokens += betAmount * 50;
            printf("CONGRATULATIONS YOU HIT JACKPOT!\n\nYou made %d tokens!\n\nYou now have %d tokens!\n\n\n\n", payOut, tokens);
        }
        else {
            tokens -= betAmount;
            printf("What the Sigma!\n\nYou lost %d tokens!\n\nYou now have %d tokens!\n\n\n\n", betAmount, tokens);
        }
    }
    else { //inavlid type bet outcome 
        printf("Invalid bet type\n\n\n\n");
    }
}

void cashout(int cash)
{
    printf("cash");
}


//function for random number generator for the reels as well as the dice
int getRandomGenerator(int max, int min){
    return (rand() % (max - min + 1)) + min; 
}
void GameOne(int max, int min)
{
//initialize the time for the generator
    srand(time(0));

//name each integer/variable
    int jckptodds;
    int scndodds;  
    int pout;     
    int jckptout;
    int wout;

    
    int reel1 = getRandomGenerator(max,min);
    int reel2 = getRandomGenerator(max,min);
    int reel3 = getRandomGenerator(max,min);
    
//odds calculator that will calculate payout
pout=max*max*max;
jckptout=max;
wout=3*max*(max-1);
jckptodds=pout/jckptout;
scndodds=pout/wout;

//ask user for bet
    printf("\n");
    printf("\nAvailable Tokens: %d\n", tokens);
    printf("\nPlace your bet PLEASE:\n");
    scanf("%d", &bet);
    printf("\n");
    
//loop to prevent negative balance
    while (bet>tokens)
    {
        printf("\n");
        printf("\nPlease place a bet less than or equal to %d, enter new bet:", tokens);
        scanf("%d",&bet);
    }
    
    printf("\n\n");
    printf("%d  %d  %d",reel1,reel2,reel3);
    printf("\n");
    
    // Nested if else that reads the outcomes to output winnings or loss
    if(reel1==reel2 && reel2==reel3)   
    { 
        tokens=tokens+bet+(bet*jckptodds);
        printf("Winner winner chicken dinner\n");
        printf("Tokens: %d\n", tokens); 
    }
    else 
    {
        if((reel1==reel2 && reel3!=reel2)||(reel2==reel3 && reel1!=reel3)||(reel1==reel3 && reel2!=reel3))
        {
            tokens=tokens+bet+(bet*scndodds);
            printf("Better luck next time but you're not going home with nothing\n");
            printf("Tokens: %d\n", tokens);
        }
        else
        {
            tokens=tokens-bet;
            printf("Yeah just put the frys in the bag bro\n");
            printf("Tokens: %d\n", tokens);
        }
    }
}
void GameTwo(int max,int min, int lck)
{

    int jckptodds; int pairout;
    int scndodds;  int pairodds;
    int pout;     
    int jckptout;
    int wout;
    int specificjckpt;

//Generating the random reels
    int reel1 = getRandomGenerator(max,min);
    int reel2 = getRandomGenerator(max,min);
    int reel3 = getRandomGenerator(max,min);
   
   //Calculator for the payout
    pout=max*max*max;
    wout=3*max*(max-1);
    scndodds=pout/wout;
    specificjckpt=pout/1;

//ask user for bet
    printf("\n");
    printf("\nAvailable Tokens: %d\n", tokens);
    printf("\nPlace your bet PLEASE:\n");
    scanf("%d", &bet);
    printf("\n");
    
// loop to prevent negative balance
    while (bet>tokens)
    {
        printf("\n");
        printf("\nPlease place a bet less than or equal to %d, enter new bet:", tokens);
        scanf("%d",&bet);
    }
   

    printf("\n\n");
    printf("%d  %d  %d",reel1,reel2,reel3);
    printf("\n");
    
    // Nested if else that reads the outcomes to output winnings or loss
    if(reel1==lck && reel2==lck && reel3==lck)   
    { 
        tokens=tokens+bet+(bet*specificjckpt);
        printf("Winner winner chicken dinner\n");
        printf("Tokens: %d\n", tokens); 
    }
    else 
    {
        if((reel1==reel2 && reel3!=reel2)||(reel2==reel3 && reel1!=reel3)||(reel1==reel3 && reel2!=reel3))
        {
            tokens=tokens+bet+(bet*scndodds);
            printf("Better luck next time but you're not going home with nothing\n");
            printf("Tokens: %d\n", tokens);
        }
        else
        {
            tokens=tokens-bet;
            printf("Yeah just put the frys in the bag bro\n");
            printf("Tokens: %d\n", tokens);
        }
    }
}
void GameThree(int max,int min, int lck2)
{
    
    int jckptodds; int pairout;
    int scndodds;  int pairodds;
    int pout;     
    int jckptout;
    int wout;

//Generating the random reels
    int reel1 = getRandomGenerator(max,min);
    int reel2 = getRandomGenerator(max,min);
    int reel3 = getRandomGenerator(max,min);

//Calculator for the payouts
    wout=3*max*(max-1);
    pout=max*max*max;
    jckptout=max;
    pairout=max*(max-1);
    pairodds=pout/pairout;
    jckptodds=pout/jckptout;
    scndodds=pout/wout;

//ask user for bet
    printf("\n");
    printf("\nAvailable Tokens: %d\n", tokens);
    printf("\nPlace your bet PLEASE:\n");
    scanf("%d", &bet);
    printf("\n");
    
//loop to prevent negative balance
    while (bet>tokens)
    {
        printf("\n");
        printf("\nPlease place a bet less than or equal to %d, enter new bet:", tokens);
        scanf("%d",&bet);
    }
    

    printf("\n\n");
    printf("%d  %d  %d",reel1,reel2,reel3);
    printf("\n");
    
   // Nested if else that reads the outcomes to output winnings or loss
    if(reel1==reel2 && reel2==reel3)   
    { 
        tokens=tokens+bet+(bet*jckptodds);
        printf("Winner winner chicken dinner\n");
        printf("Tokens: %d\n", tokens); 
    }
    else 
    {
        if((reel1==reel2 && reel3!=reel2 && reel1==lck2)||(reel2==reel3 && reel1!=reel3 && reel2==lck2)||(reel1==reel3 && reel2!=reel3 && reel1==lck2))
        {
            tokens=tokens+bet+(bet*pairodds);
            printf("Seems like those lucky numbers did have some magic after all\n");
            printf("Tokens: %d\n", tokens);
        }
        else
        {
                if((reel1==reel2 && reel3!=reel2)||(reel2==reel3 && reel1!=reel3)||(reel1==reel3 && reel2!=reel3))
                {
                    tokens=tokens+bet+(bet*scndodds);
                    printf("Better luck next time but you're not going home with nothing\n");
                    printf("Tokens: %d\n", tokens);
                }
                        else 
                        {
                            tokens= tokens-bet;
                            printf("Yeah just put the frys in the bag bro\n");
                            printf("Tokens: %d\n", tokens);
                            printf("\n\n");
                        }
        }
    }
}
void slots(int lck,int lck2,int max,int min, int choice)
{
    //This is the menu for the slots games
    min=1;
while(1)
{
    printf("\n\n");
    printf("******************************************\n");
    printf("*                                        *\n");
    printf("*   777   Choose a game any game   777   *\n");
    printf("*                                        *\n");
    printf("******************************************\n");
    printf("*                                        *\n");
    printf("*         1. Traditional Jackpot         *\n");
    printf("*         2. Super Jackpot               *\n");
    printf("*         3. Paris Parade                *\n");
    printf("*         4. Main Menu                   *\n");
    printf("*                                        *\n");
    printf("******************************************\n");
    scanf("%d", &choice);
//Switch cases so the user can choose a game
switch(choice)
{
    case 1:
            printf("Welcome to Traditional Jackpot, rules are simple, there is a standard payout with 3 different payout possibilites \n 100 to 1 payout for 10 symbols \n 400 to 1 payout for 20 symbols \n 900 to 1 payout for 30 symbols\n");
            printf("Choose your odds, 10, 20 or 30: \n");
            scanf("%d", &max);
            GameOne( max, min);
    break;

    case 2:
            printf("Welcome to Super Jackpot, rules are simple pick a specific Jackpot number for 20 times the payout, rest of payouts are standard\n");
            printf("Choose your lucky number(1-20): \n");
            scanf("%d", &lck);
            max=20;
            GameTwo( max, min, lck);
    break;

    case 3:
            printf("Welcome to Pairs Parade, rules are simple pick a specific pair for 3 times the payouts on pairs, rest of payouts are standard\n");
            printf("Choose your lucky pair(1-20): \n");
            scanf("%d", &lck2);
            max=20;
            GameThree( max, min, lck2);
    break;

    case 4:
            return;
            exit(0);
    
     default:
                printf("Invalid Choice. Feel free to try again. \n");
}
}

}

void gameinfo(int choice)
{
    while(1)
    {
        printf("******************************************\n");
        printf("*                                        *\n");
        printf("*        1. Information on Slots         *\n");
        printf("*        2. Information on Blackjack     *\n");
        printf("*        3. Information on Roulette      *\n");
        printf("*        4. Information on Craps         *\n");
        printf("*        5. Back to Main Menu            *\n");
        printf("*                                        *\n");
        printf("******************************************\n");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
                printf("\nOdds\n");
                printf("First off odds are based on the ratio of symbols to probability for the specific win.\n");
                printf("The ratio states that if odds are 10:1 the payout is 10 tokens won for every 1 token bet.\n");
                printf("Therefore the odds will change and to know payout as will be described below the first number in the ratio is the the winning for token bet.\n");
                printf("\nGame #1\n");
                printf("In Traditional Jackpot there are 3 different options for odds.\n");
                printf("The first odds are with 10 symbols, meaning it'll only generate numbers 1-10 giving 100:1 odds for a jackpot win.\n");
                printf("The secondd odds are with 20 symbols, giving a 400:1 payout for a jackpot win.\n");
                printf("The third odds are with 30 symbols, giving 900:1 payout for a jackpot win.\n");
                printf("A jackpot win in this game means all 3 reels match up with the same number for jackpot win.\n");
                printf("In this game you will also receive a payout for matching pairs, this can be any pair.\n");
                printf("The payouts for the pairs will be less than the jackpot winning but still a win.\n");
                printf("For a 10 symbol game the payout for pairs is 4:1\n For a 20 symbol game the payout for pairs is 7:1\nFor a 30 symbol game the payout for pairs is 10:1.\n ");
                printf("Therefore to sum up the least symbols means higher probability of win therefore lower payout and more is lower probability meaning higher payout.\n");
                printf("For a jackpot all 3 symbols must match, and for a pairs payout only 2 must match, these payouts will be the standard payout in the other 2 games as well.\n");
                printf("\nGame#2\n");
                printf("In Super Jackpot the symbols are fixed down to only 20 symbols meaning the game has a standard payout for 20 symbols that was described in Game#1.\n");
                printf("This game lets you pick a lucky number for a jackpot winning.\n");
                printf("What this entails is that if you draw a jackpot with the lucky number your payout is 8000:1.\n");
                printf("Now if you draw a jackpot but the lucky number is not drawn, the payout is the standard jackpot payout for 20 symbols.\n");
                printf("The payout for pairs in this game is also the standard payout for pairs in a 20 symbol game. \n");
                printf("\nGame#3\n");
                printf("Pairs Parade is a fixed game of 20 symbols meaning standard payouts are drawn from the traditional game at 20 symbols.\n");
                printf("This game lets you pick a lucky number for a pairs winning only\n");
                printf("What this means is that if you draw pairs with your lucky number you get a 21:1 payout.\n");
                printf("The rest of the payouts for jackpot and pairs are standard.\n");

        break;

        case 2:
            printf("\nCard Values\n");
            printf("1: Number Cards (2-10) are worth their face value.\n");
            printf("2: Face cards (Jack, Queen, King) are worth 10 points each.\n");
            printf("3: Aces can be worth 1 or 11, depending on whcih value benefits the hand most.\n\n");
            printf("\nGameplay\n");
            printf("1: Player is dealt two cards face-up.\n");
            printf("2: The dealer is dealt one card face-up and one face down (the 'hole card').\n");
            printf("3: Player decides to hit or stand\n");
            printf("\t3.1: Hit- to take another card. Player can hit as many times as they want until hand totals 21 or player 'busts.'\n");
            printf("\t3.2: Stand- to keep the current total and end the turn.\n");
            printf("4: The dealer reveals their 'hole card' once the player finishes their turn.\n");
            printf("\t4.1: The dealer must 'hit' until their hand totals at least 17.\n\n");
            printf("\nWinning and Losing\n");
            printf("1: Blackjack- A hand totaling 21 with an Ace and a 10-point card on the first two cards.\n");
            printf("\t1.1: The payout is 3 to 2\n");
            printf("2: Win- Player hand total is closer to 21 than the dealers without exceeding 21.\n");
            printf("3: Bust- If the player's hand total exceeds 21, player lose automatically, even if the dealer also busts.\n");
            printf("4: Push- If the player and the dealer have the same hand total, its a tie, and the bet is returned.\n");
            printf("5: Dealer Bust- If the dealer exceeds 21, all remaining players win.\n");
        break;

        case 3:
            printf("\nBet Types: \n");
            printf("1: Black or Red are the colors (excluding 0 because it is green) of the slots 1-36 that you can bet on.\n");
            printf("2: Numbers bet is a bet where you can choose what number (0-36) that you think the wheel will land on.\n");
            printf("3: Odd or Even bet is a bet where you choose if you think the wheel will land on an odd or even number.\n");
            printf("4: Zero bet is where you bet on the number 0 which is the only Green slot on the wheel.\n");
            printf("\t4.1: Because zero is the only green slot on the wheel we decided to make it our Jackpot slot.\n");
            printf("\t4.2: You can choose to bet on 0 by typing 'zero' or typing 'number' and entering the number 0 after asked for bet type.\n");
            printf("\nPay Outs:\n");
            printf("Black, Red, Odd, and Even type bets all have a 1 to 1 pay out, meaning you double your tokens if your bet lands.\n");
            printf("Number type bets (except 0) have a times 35 pay out, meaning your pay out will be your bet amount times 35 if your number lands.\n");
            printf("Zero bet (including betting 'number' then typing number '0') is the jackpot with a bet amount times 50 pay out if 0 lands.\n");
            printf("In all bet types if your bet does not land you will lose the amount of tokens you bet on for your type of bet, so play recklessly!\n");
            printf("\nNow let your addiction to gambling begin, have fun, stay committed, and remember 100%% of gamblers quit before making millions!\n\n\n");
        break;

        case 4:
            printf("\nThis game operates under only one bet type and a 1:1 odds for payouts.\n");
            printf("This game is played with two dice, and the roll is the sum of both dice.\n");
            printf("The first roll can determine a win or loss.\n");
            printf("If you roll a 7 or 11 on the first roll you automatically win.\n");
            printf("A roll of 2,3, or 12 though is an automatic loss.\n");
            printf("Now if you roll none of these values the number you rolled becomes your pointer.\n");
            printf("This means that your pointer is the number that must be rolled again in order to win.\n");
            printf("If the pointer does not match the second roll you have lost.\n\n");
        break;

        case 5:
        return;
        exit(0);

        default:
                        printf("Invalid Choice. Feel free to try again. ");
        }
    }
}

int main()
{

    int yeah,yee,cash,max,min,lck,lck2,choice;
     printf("\n\nWelcome to Ohms Casino how many tokens would you like to buy: \n");
     scanf("%d", &tokens);

    while(1)
    {
        printf("\n\n");
        printf("******************************************\n");
        printf("*                                        *\n");
        printf("*           $$ OHM'S CASINO $$           *\n");
        printf("*                                        *\n");
        printf("******************************************\n");
        printf("*                                        *\n");
        printf("*           1. Play Slots                *\n");
        printf("*           2. Play Blackjack            *\n");
        printf("*           3. Play Roulette             *\n");
        printf("*           4. Play Craps                *\n");
        printf("*           5. View Tokens               *\n");
        printf("*           6. Game Information          *\n");
        printf("*           7. Exit                      *\n");
        printf("*                                        *\n");
        printf("******************************************\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                    slots(lck,lck2,max,min,choice);
            break;

            case 2:
                    blackjack();
            break;
            
            case 3:
                    roulette();
            break;

            case 4:
                    min=1;
                    max=6;
                    craps(max,min);
            break;

            case 5:
                    printf("You have %d tokens!", tokens);
            break;

            case 6:
                    gameinfo(choice);
            break;

            case 7:
                    printf("Thank you for playing. \n");
                    exit(0);

                default:
                        printf("Invalid Choice. Feel free to try again. ");
        }
    }
}
