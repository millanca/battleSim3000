#ifndef MUGWUMP_H_INCLUDED
#define MUGWUMP_H_INCLUDED

#define CLAWS 1
#define FANGS 2
#define LICK 3

struct Mugwump{
    int hitPoints;
    int maxHitPoints;
    struct Die* d100;
    struct Die* d20;
    struct Die* d10;
    struct Die* d6;
};

//Constructor (no allocation)
void initMugwump(struct Mugwump* self);

//Allocation + initialization
struct Mugwump* createMugwump();

//Destructor (no deallocation)
void resetMugwump(struct Mugwump* self);

//Destructor + deallocation
void destroyMugwump(struct Mugwump* mugwump);

//method to get the number of hitpoints
int getHitPointsM(struct Mugwump* self);

void takeDamageM(struct Mugwump* self, int hp);

int attackM(struct Mugwump* self, int type);

static int rollHitPointsM(struct Mugwump* self);

int ai(struct Mugwump* self);

#endif // MUGWUMP_H_INCLUDED
