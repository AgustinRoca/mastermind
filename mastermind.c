#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

#define MAX_LENGTH 50
#define EASY_TRIES 30
#define MEDIUM_TRIES 20
#define HARD_TRIES 10
#define DIGITS 4

typedef enum {EASY, MEDIUM, HARD} difficulty;

int pickRandomNumber();
char * getIntAsStringByStdin(char ans[DIGITS + 1]);
char * numToString(int num, char numAsString[DIGITS + 1]);
difficulty chooseDifficulty();
difficulty askDifficulty();
int getMaximumTries(difficulty difficulty);


int main(){
    int num = pickRandomNumber();
    char numAsString[DIGITS + 1];
    numToString(num, numAsString);
    difficulty difficulty = chooseDifficulty();
    int maxTries = getMaximumTries(difficulty);
    for(int tries; tries < maxTries; tries++){
        char guess[DIGITS + 1];
        getIntAsStringByStdin(guess);
        int wellPlaced = 0;
        int wrongPlaced = 0;
        int wrongNumber = 0;
        for(int guessingDigit = 0; guessingDigit < DIGITS; guessingDigit++){
            if(guess[guessingDigit] == numAsString[guessingDigit]){
                wellPlaced++;
            } else {
                int found = 0;
                for(int digit = 0; digit < DIGITS && !found; digit++){
                    if(guess[guessingDigit] == numAsString[digit]){
                        found = 1;
                    }
                }
                if(found){
                    wrongPlaced++;
                } else {
                    wrongNumber++;
                }
            }
        }
        if(wellPlaced == DIGITS){
            printf("You won!\n");
            return 0;
        } else {
            printf("%d well placed numbers\n%d correct numbers in wrong positions\n%d wrong numbers\n", wellPlaced, wrongPlaced, wrongNumber);
            printf("You have %d tries left\n", maxTries - tries - 1);
            printf("\n");
        }
    }
    printf("You lost! The number was %d\n", num);
    return 0;
}

int pickRandomNumber(){
    srand(time(NULL));
    char digits[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int num = 0;
    for(int digit = 0; digit < DIGITS; digit++){
        int random = rand() % (10 - digit);
        int randDigit = digits[random];
        for(int digitPos = random + 1; digitPos < 10 - digit; digitPos++){
            digits[digitPos - 1] = digits[digitPos];
        }
        num += randDigit * pow(10, digit);
    }
    return num;
}

char * getIntAsStringByStdin(char ans[DIGITS + 1]){
    int done = 0;
    char inputString[MAX_LENGTH];
    do {
        printf("Enter a 4-digit number: ");
        if(fgets(inputString, MAX_LENGTH, stdin) != NULL){
            if(strlen(inputString) == DIGITS + 1 && inputString[DIGITS] == '\n'){
                done = 1;
                for (int digit = 0; digit < DIGITS && done; digit++)
                {
                    if(!isdigit(inputString[digit])){
                        printf("You must enter a 4-digit NUMBER\n");
                        done = 0;
                    }
                }        
            } else {
                printf("You must enter FOUR-digit number\n");
            }
        } else {
            printf("Please enter a 4-digit number\n");
        }
    } while(!done);
    inputString[DIGITS] = 0;
    strncpy(ans, inputString, DIGITS);
    return ans;
}

char * numToString(int num, char numAsString[DIGITS + 1]){
    for(int digitPosition = 0; digitPosition < DIGITS; digitPosition++){
        char digitToChar = num % 10 + '0';
        numAsString[DIGITS - digitPosition - 1] = digitToChar;
        num /= 10;
    }
    numAsString[DIGITS] = 0;
    return numAsString;
}

difficulty chooseDifficulty(){
    printf("Choose dificulty:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    return askDifficulty();

}

difficulty askDifficulty(){
    int done = 0;
    do {
        char inputString[MAX_LENGTH];
        if(fgets(inputString, MAX_LENGTH, stdin) != NULL){
            if(strlen(inputString) == 2 && inputString[1] == '\n'){
                done = 1;
                switch (inputString[0])
                {
                    case '1': 
                        printf("Easy mode selected, you have %d tries. Good luck!\n\n", EASY_TRIES);
                        return EASY;
                    case '2':
                        printf("Medium mode selected, you have %d tries. Good luck!\n\n", MEDIUM_TRIES);
                        return MEDIUM;    
                    case '3':
                        printf("Hard mode selected, you have %d tries. Good luck!\n\n", HARD_TRIES);
                        return HARD;
                    default:
                        done = 0;
                        printf("You must enter 1 (easy), 2 (medium) or 3 (hard)\n\n");
                }
            }
        } else {
            printf("Please select an option\n");
        }
    } while(!done);
    return -1;
}

int getMaximumTries(difficulty difficulty){
    switch (difficulty)
    {
        case EASY: return EASY_TRIES;
        case MEDIUM: return MEDIUM_TRIES;
        case HARD: return HARD_TRIES;
        default: return -1;
    }
}