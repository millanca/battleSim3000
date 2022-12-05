#ifndef WARRIOR_H_INCLUDED
#define WARRIOR_H_INCLUDED

#define SWORD 1
#define SHIELD 2

struct Warrior{
    int hitPoints;
    struct Die* d20;
    struct Die* d10;
    struct Die* d8;
    struct Die* d4;
};

//Constructor (no allocation)
void initWarrior(struct Warrior* self);

//Allocation + initialization
struct Warrior* createWarrior();

//Destructor (no deallocation)
void resetWarrior(struct Warrior* self);

//Destructor + deallocation
void destroyWarrior(struct Warrior* warrior);

//method to get the number of hitpoints
int getHitPointsW(struct Warrior* self);

void takeDamageW(struct Warrior* self, int hp);

int attackW(struct Warrior* self, int type);

static int rollHitPointsW(struct Warrior* self);

#endif // WARRIOR_H_INCLUDED
