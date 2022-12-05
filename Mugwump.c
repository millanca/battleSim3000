/*
 * Course: EEL2880 U02 1228
 * Term: Fall 2022
 * Assignment: Final Project
 * Author: Christopher Millan
 * Date: 11/20/22
 */

#include <stdio.h>
#include <stdlib.h>
#include "Mugwump.h"
#include "Die.h"

//Constructor (no allocation)
void initMugwump(struct Mugwump* self){
    self->d100 = createDie(100);
    self->d20 = createDie(20);
    self->d10 = createDie(10);
    self->d6 = createDie(6);
    self->hitPoints = 0;
    self->hitPoints = rollHitPointsM(self);
    self->maxHitPoints = self->hitPoints;
}

//Allocation + initialization
struct Mugwump* createMugwump(){
    struct Mugwump* result = (struct Mugwump*) malloc(sizeof(struct Mugwump));
    initMugwump(result);
    return result;
}

//Destructor (no deallocation)
void resetMugwump(struct Mugwump* self){
    destroyDie(self->d100);
    destroyDie(self->d20);
    destroyDie(self->d10);
    destroyDie(self->d6);
}

//Destructor + deallocation
void destroyMugwump(struct Mugwump* mugwump){
    if(mugwump){
        resetMugwump(mugwump);
        free(mugwump);
    }
}

//method to get the number of hitpoints
int getHitPointsM(struct Mugwump* self){return self->hitPoints;}

void takeDamageM(struct Mugwump* self, int hp){
    int health = self->hitPoints-hp;
    if(health > 0){
        self->hitPoints = health;
    }
    else{
        self->hitPoints = 0;
    }
}

/**
 * This method handles the attack logic
 * @return the amount of damage an attack has caused, 0 if the attack misses or the Mugwump heals
 */
int attackM(struct Mugwump* self, int type){
    int damage = 0;
    roll(self->d20);
    if(type == CLAWS){
        if(getCurrentValue(self->d20) >= 12){
            for(int i = 0; i < 2; i++){
                roll(self->d6);
                damage += getCurrentValue(self->d6);
            }
            printf("\nThe Mugwump slices you and deals %d damage!\n", damage);
        }
        else{
            printf("\nThe Mugwump swings their claws at you and misses!\n");
        }
    }
    else if(type == FANGS){
        if(getCurrentValue(self->d20) >= 16){
            for(int i = 0; i < 3; i++){
                roll(self->d6);
                damage += getCurrentValue(self->d6);
            }
            printf("\nThe Mugwump bites you and deals %d damage!\n", damage);
        }
        else{
            printf("\nThe Mugwump snaps at you and misses!\n");
        }
    }
    else if(type == LICK){
        roll(self->d6);
        self->hitPoints += getCurrentValue(self->d6);
        if(self->hitPoints < self->maxHitPoints){
            printf("\nThe Mugwump licks their wounds and heals for %d health!\n", getCurrentValue(self->d6));
        }
        else{
            self->hitPoints = self->maxHitPoints;
            printf("\nThe Mugwump licks their wounds and regains their full health!\n");
        }
    }
    else{
        printf("\nError in Mugwump Attack Type.\n");
    }
    return damage;
}

static int rollHitPointsM(struct Mugwump* self){
    for(int i=0; i < 10; i++){
        roll(self->d10);
        self->hitPoints += getCurrentValue(self->d10);
    }
    return self->hitPoints;
}

/**
 * This method determines what action the Mugwump performs
 * @return 1 for a Claw attack, 2 for a Bite, and 3 if the Mugwump licks its wounds, instead
 */
int ai(struct Mugwump* self){
    roll(self->d100);
    if(getCurrentValue(self->d100) <= 75){
        return CLAWS;
    }
    if((getCurrentValue(self->d100) > 75) && (getCurrentValue(self->d100) <= 90)){
        return FANGS;
    }
    else{
        return LICK;
    }
}