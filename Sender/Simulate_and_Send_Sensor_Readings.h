#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_READINGS 50
#define MAXIMUM_BATTERYTEMPERATURE 40.55f
#define MAXIMUM_DISCHARGE_VOLTAGE 32.25f 
#define MAXIMUM_SOH 90

struct BatteryHealthParameters {
    float* batteryTemperatureInCelsius;
    float* dischargingVoltage;
    int* stateOfHealth;
};

void Simulate_and_Send_Sensor_Readings_for_BMS(struct BatteryHealthParameters*);
float* simulateBatteryParameterFloatValues(int, float);
int* simulateBatteryParameterIntegerValues(int, int);
void formatAndPrintToConsole(struct BatteryHealthParameters*);
void simulateSensorReadings(struct BatteryHealthParameters*);
