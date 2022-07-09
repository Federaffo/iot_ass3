#ifndef __GLOBAL_VAR__
#define __GLOBAL_VAR__

#include "string.h"

#define PINLED1 2
#define PINLED2 3
#define PINLED3 "A1"
#define PINLED4 "A2"
#define PINMOTOR 6
#define PIN_BT_RX 4
#define PIN_BT_TX 5

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
extern int irrSpeed;

#endif