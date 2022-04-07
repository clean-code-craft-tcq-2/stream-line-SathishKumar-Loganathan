#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_READINGS 50
#define MAXIMUM_BATTERYTEMPERATURE 40.55f
#define MAXIMUM_DISCHARGE_VOLTAGE 32.25f 
#define MAXIMUM_SOH 90

float* arrayToStoreFloatValues;
int *arrayToStoreIntegerValues;

struct BatteryHealthParameters {
    float* batteryTemperatureInCelsius;
    float* dischargingVoltage;
    int* stateOfHealth;
};
