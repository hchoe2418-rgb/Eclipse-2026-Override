#include "main.h"
#include "helpers.hpp"

static constexpr double LIFT_KP = 0.15;
static constexpr double LIFT_KD = 0.01;

static constexpr int LIFT_HOLD_POWER = 8;
static constexpr int LIFT_MAX_POWER = 80;
static constexpr int LIFT_MIN_POWER = 8;

int LIFT_LOW = 0;
int LIFT_MID = 12000;
int LIFT_HIGH = 25000;

int liftPosition() {
    return lift_sensor.get_position();
}

void liftStop() {
    lift.move(0);
}

bool liftToPosition(int target, int timeoutMs) {
    int startTime = pros::millis();
    int lastError = target - liftPosition();
    int settledCount = 0;

    while (pros::millis() - startTime < timeoutMs) {
        int currentPosition = liftPosition();
        int error = target - currentPosition;
        double derivative = (error - lastError) / 0.02;

        double power = LIFT_KP * error + LIFT_KD * derivative;

        if (std::abs(error) > 300) {
            if (error > 0) {
                power += LIFT_HOLD_POWER;
            }
            else {
                power += -LIFT_HOLD_POWER;
            }
        }

        if (power > LIFT_MAX_POWER) {
            power = LIFT_MAX_POWER;
        }
        
        if (power < -LIFT_MAX_POWER) {
            power = -LIFT_MAX_POWER;
        }

        if (std::abs(error) > 300 && std::abs(power) < LIFT_MIN_POWER) {
            if (power >= 0) {
                power = LIFT_MIN_POWER;
            }
            else
            {
                power = -LIFT_MIN_POWER;
            }
        }
        lift.move(static_cast<int>(power));

        if (std::abs(error) < 300) {
            if (++settledCount >= 5) {
                // Stop active movement; holding must be handled safely.
                lift.move(0);
                return true;
            }
        } 
        else {
            settledCount = 0;
        }

        pros::delay(20);
        }

        liftStop();
        return false;
    }

bool moveToLow() {
    return liftToPosition(LIFT_LOW);
}

bool moveToMid() {
    return liftToPosition(LIFT_MID);
}

bool moveToHigh() {
    return liftToPosition(LIFT_HIGH);
}
