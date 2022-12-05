#ifndef DIE_H_INCLUDED
#define DIE_H_INCLUDED

#define MIN_SIDES 2
#define MAX_SIDES 100
#define DEFAULT_SIDES 6

struct Die;

//Constructor (no allocation)
void initDie(struct Die* self, int numSides);

//Allocation + initialization
struct Die* createDie(int numSides);

//Destructor (no deallocation)
void resetDie(struct Die* self);

//Destructor + deallocation
void destroyDie(struct Die* die);

//method to get the number of sides
int getNumSides(struct Die* self);

//method to get the current value
int getCurrentValue(struct Die* self);

//method to roll die and get random value between 1 & numSides
void roll(struct Die* self);

#endif // DIE_H_INCLUDED
