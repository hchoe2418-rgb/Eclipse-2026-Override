#include "main.h"

int liftPosition();
void liftStop();
bool liftToPosition(int target, int timeoutMs = 2500);

bool moveToLow();
bool moveToMid();
bool moveToHigh();