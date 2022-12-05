/*
 * Course: EEL2880 U02 1228
 * Term: Fall 2022
 * Assignment: Final Project
 * Author: Christopher Millan
 * Date: 11/20/22
 */

#include <stdlib.h>
#include "Die.h"

struct Die{
    int numSides;
    int currentValue;
};

//Constructor (no allocation)
void initDie(struct Die* self, int numSides){
    self->numSides = numSides;
    roll(self);
}

//Allocation + initialization
struct Die* createDie(int numSides){
    struct Die* result = (struct Die*) malloc(sizeof(struct Die));
    if((numSides >= MIN_SIDES) && (numSides <= MAX_SIDES)){
        initDie(result, numSides);
    }
    else{
        initDie(result, DEFAULT_SIDES);
    }
    return result;
}

//Destructor (no deallocation)
void resetDie(struct Die* self){}

//Destructor + deallocation
void destroyDie(struct Die* die){
    if(die){
        resetDie(die);
        free(die);
    }
}

//method to get the number of sides
int getNumSides(struct Die* self){return self->numSides;}

//method to get the current value
int getCurrentValue(struct Die* self){return self->currentValue;}

//method to roll die and get random value between 1 & numSides
void roll(struct Die* self){
    self->currentValue = (rand() % (self->numSides)) + 1;
}
