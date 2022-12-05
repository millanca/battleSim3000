/*
 * Course: EEL2880 U02 1228
 * Term: Fall 2022
 * Assignment: Final Project
 * Author: Christopher Millan
 * Date: 11/20/22
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "Die.h"
#include "Mugwump.h"
#include "Warrior.h"

void intro();

char* battle(struct Warrior* warrior, struct Mugwump* mugwump);

void report(struct Warrior* warrior, struct Mugwump* mugwump);

int attackChoice();

int initiative(struct Warrior* warrior, struct Mugwump* mugwump);

void victory(char* winner);

bool playAgain();

bool playCheck();

void thanks();

int main(){
    srand( time( NULL ) ); // seed random-number generator NOLINT(cert-msc51-cpp)
    intro();
    bool play = playCheck();
    if(play == 1){
        while (play == 1){
            struct Warrior* warrior = createWarrior();
            struct Mugwump* mugwump = createMugwump();
            victory(battle(warrior, mugwump));
            play = playAgain();
            destroyWarrior(warrior);
            destroyMugwump(mugwump);
        }
        thanks();
    }
    return 0;
}

void intro(){
    printf("Welcome to Battle Simulator 3000! The world's most low tech battle simulator!\n"
           "You are a Valiant Warrior defending your humble village from an evil Mugwump! Fight bravely, \n"
           "or the citizens of your town will be the Mugwump's dinner!\n\n"
           "You have your Trusty Sword, which deals decent damage, but can be tough to hit with sometimes. \n"
           "You also have your Shield of Light, which is not as strong as your sword, but is easier to deal \n"
           "damage with.\n\n"
           "Would you like to play? (Enter 'y', 'Y', 'yes', or 'Yes' to begin)\n");
}

/**
 * This method handles the battle logic for the game.
 * @param warrior The Warrior of Light!
 * @param mugwump The Evil Mugwump!
 * @return The name of the victor, or "none", if the battle is still raging on
 */
char* battle(struct Warrior* warrior, struct Mugwump* mugwump){
    while(1){
        report(warrior, mugwump);
        int init = initiative(warrior, mugwump);
        if (init == 1){
            //Warrior Initiative
            switch (attackChoice()) {
                case 1:
                    //SWORD
                    takeDamageM(mugwump, attackW(warrior, 1));
                    break;
                case 2:
                    //SHIELD
                    takeDamageM(mugwump, attackW(warrior, 2));
                    break;
            }
            //Check if Mugwump is defeated
            if(getHitPointsM(mugwump) <= 0){
                return "warrior";
            }
            else{
                //Mugwump response
                takeDamageW(warrior, attackM(mugwump,ai(mugwump)));
            }
            //Check if Warrior is defeated
            if(getHitPointsW(warrior) <= 0){
                return "mugwump";
            }
        }
        else {
            //Mugwump Initiative
            takeDamageW(warrior, attackM(mugwump, ai(mugwump)));
            //Check if Warrior is defeated
            if (getHitPointsW(warrior) <= 0) {
                return "mugwump";
            } else {
                //Warrior response
                switch (attackChoice()) {
                    case 1:
                        //SWORD
                        takeDamageM(mugwump, attackW(warrior, 1));
                        break;
                    case 2:
                        //SHIELD
                        takeDamageM(mugwump, attackW(warrior, 2));
                        break;
                }
                //Check if Mugwump is defeated
                if (getHitPointsM(mugwump) <= 0) {
                    return "warrior";
                }
            }
        }
    }
}

/**
 * This method reports the status of the combatants before each new round
 * @param warrior The Warrior of Light!
 * @param mugwump The Evil Mugwump!
 */
void report(struct Warrior* warrior, struct Mugwump* mugwump){
    printf("\nWarrior HP: %d\n", getHitPointsW(warrior));
    printf("Mugwump HP: %d\n\n", getHitPointsM(mugwump));
}

/**
 * This method asks the user what attack type they want to use and returns the result
 * @return 1 for sword, 2 for shield
 */
int attackChoice(){
    int choice = 0;
    while(1){
        printf("\nHow would you like to attack?\n"
               "1. Your Trusty Sword\n"
               "2. Your Shield of Light\n"
               "Enter choice:");
        scanf("%d", &choice); // NOLINT(cert-err34-c)
        if((choice == 1) || (choice == 2)){
            return choice;
        }
    }
}

/**
 * Determines which combatant attacks first, displays and returns the result.
 * Re-rolls if its a tie.
 * @return 1 if the warrior goes first, 2 if the mugwump goes first
 */
int initiative(struct Warrior* warrior, struct Mugwump* mugwump){
    int result = 0;
    while (result == 0){
        roll(warrior->d10);
        roll(mugwump->d10);
        if((getCurrentValue(warrior->d10)) > (getCurrentValue(mugwump->d10))){
            result = 1;
            printf("The Warrior attacks first!\n");
        }
        else if((getCurrentValue(warrior->d10)) < (getCurrentValue(mugwump->d10))){
            result = 2;
            printf("The Mugwump attacks first!\n");
        }
    }
    return result;
}

/**
 * This method declares the winner of the epic battle
 * @param winner the name of the winner of the epic battle
 */
void victory(char* winner){
    if(!strcmp(winner, "warrior")){
        printf("\nThe citizens cheer and invite you back to town for a feast as thanks for saving their lives (again)!\n\n");
    }
    else if(!strcmp(winner, "mugwump")){
        printf("\nThe dastardly Mugwump slayed the weakened warrior. All hope is lost for the townsfolk.\n\n");
    }
    else{
        printf("\nYou shouldn't be seeing this, its an error when displaying the victor.\n\n");
    }
}

bool playAgain(){
    printf("Would you like to play again? (yes/no)\n");
    return playCheck();
}

bool playCheck(){
    char response[4];
    scanf("%s", response);
    if(!strcmp(response, "y") || !strcmp(response, "Y")
       || !strcmp(response, "yes") || !strcmp(response, "Yes")){
        printf("Let the epic battle begin!\n\n");
        return 1;
    }
    else {
        return 0;
    }
}

void thanks(){
    printf("\nThank you for playing Battle Simulator 3000!\n");
}
