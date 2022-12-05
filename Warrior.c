/*
 * Course: EEL2880 U02 1228
 * Term: Fall 2022
 * Assignment: Final Project
 * Author: Christopher Millan
 * Date: 11/20/22
 */

#include <stdio.h>
#include <stdlib.h>
#include "Warrior.h"
#include "Die.h"

//Constructor (no allocation)
void initWarrior(struct Warrior* self){
    self->d20 = createDie(20);
    self->d10 = createDie(10);
    self->d8 = createDie(8);
    self->d4 = createDie(4);
    self->hitPoints = 0;
    self->hitPoints = rollHitPointsW(self);
}

//Allocation + initialization
struct Warrior* createWarrior(){
    struct Warrior* result = (struct Warrior*) malloc(sizeof(struct Warrior));
    initWarrior(result);
    return result;
}

//Destructor (no deallocation)
void resetWarrior(struct Warrior* self){
    destroyDie(self->d20);
    destroyDie(self->d10);
    destroyDie(self->d8);
    destroyDie(self->d4);
}

//Destructor + deallocation
void destroyWarrior(struct Warrior* warrior){
    if(warrior){
        resetWarrior(warrior);
        free(warrior);
    }
}

//method to get the number of hitpoints
int getHitPointsW(struct Warrior* self){return self->hitPoints;}

void takeDamageW(struct Warrior* self, int hp){
    int health = self->hitPoints-hp;
    if(health > 0){
        self->hitPoints = health;
    }
    else{
        self->hitPoints = 0;
    }
}

int attackW(struct Warrior* self, int type){
    int damage = 0;
    roll(self->d20);
    if(type == SWORD){
        if(getCurrentValue(self->d20) >= 12){
            for(int i = 0; i < 3; i++){
                roll(self->d8);
                damage += getCurrentValue(self->d8);
            }
            printf("\nYou slash the Mugwump with your sword and deal %d damage!\n", damage);
        }
        else{
            printf("\nYou swing your sword and miss the foul creature!\n");
        }
    }
    else if(type == SHIELD){
        if(getCurrentValue(self->d20) >= 8){
            roll(self->d4);
            damage += getCurrentValue(self->d4);
            printf("\nYou hit the Mugwump with your Shield of Light for %d points of damage!\n", damage);
        }
        else{
            printf("\nYou charge at the Mugwump and miss!\n");
        }
    }
    else{
        printf("\nError in Warrior Attack Type.\n");
    }
    return damage;
}

static int rollHitPointsW(struct Warrior* self){
    for(int i=0; i < 6; i++){
        roll(self->d10);
        self->hitPoints += getCurrentValue(self->d10);
    }
    return self->hitPoints;
}