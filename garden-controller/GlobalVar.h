#ifndef __GLOBAL_VAR__
#define __GLOBAL_VAR__

#include "string.h"

#define PINLED1 13
#define PINLED2 12
#define PINLED3 11
#define PINLED4 6
#define PINMOTOR 5
#define PIN_BT_RX 3
#define PIN_BT_TX 2

enum GlobalState{
    AUTO,
    MANUAL,
    ALARM
};

extern GlobalState globalState;
extern bool l1;
extern bool l2;
extern int l3;
extern int l4;
extern bool irrigation;


#endif
