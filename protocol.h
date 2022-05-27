#ifndef PROTOCOL
#define PROTOCOL
//first arduments
#define LED_ADR 10 // arg1, 1-10
#define MOT_ADR 11 // 5 arg for all motors
#define STABLE_ADR 12 // arg 1, enable/diable stabilisation 
#define RGB_ADR 13 // arg 1, modes for rgb lane, arg - wait, do, error

//side actions
#define SIDE_ACT_ADR 14 //side action can return data


//mes with return
/*
fitst is do only, but that will return smth
like:
pi: send me depth data
ard: here 1.5767 meters
*/
#define SEND_DEPTH 20
#define SEND_ANGLE1 21
#define SEND_ANGLE2 22
#define SEND_TEMPER 23

#endif
