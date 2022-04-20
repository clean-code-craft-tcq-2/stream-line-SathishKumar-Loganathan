#include "Simulate_and_Send_Sensor_Readings.h"

float* arrayToStoreFloatValues;
int *arrayToStoreIntegerValues;

float* simulateBatteryParameterFloatValues(int NumberOfReadings, float maximumValue) {
    int loopCounter = 0;
    arrayToStoreFloatValues = (float*) calloc(NumberOfReadings, sizeof(maximumValue));

    for(loopCounter = 0; loopCounter < NumberOfReadings; loopCounter++) {
        arrayToStoreFloatValues[loopCounter] = ((float) rand()/ RAND_MAX) * maximumValue;
    }
    return arrayToStoreFloatValues;
}

int* simulateBatteryParameterIntegerValues(int NumberOfReadings, int maximumValue) {
    int loopCounter = 0;
    arrayToStoreIntegerValues = (int*) calloc(NumberOfReadings, sizeof(maximumValue));

    for(loopCounter = 0; loopCounter < NumberOfReadings; loopCounter++) {
        arrayToStoreIntegerValues[loopCounter] = ((float) rand()/ RAND_MAX) * maximumValue;
    }
    return arrayToStoreIntegerValues;
}

void simulateSensorReadings(struct BatteryHealthParameters *myBattery) {
    srand(time(NULL));
    myBattery->batteryTemperatureInCelsius = simulateBatteryParameterFloatValues((int)NUMBER_OF_READINGS,(float)MAXIMUM_BATTERYTEMPERATURE);
    myBattery->dischargingVoltage = simulateBatteryParameterFloatValues((int)NUMBER_OF_READINGS,(float)MAXIMUM_DISCHARGE_VOLTAGE);
    myBattery->stateOfHealth = simulateBatteryParameterIntegerValues((int)NUMBER_OF_READINGS,(float)MAXIMUM_SOH);
}

void formatAndPrintToConsole(struct BatteryHealthParameters *batteryHealth) {
    int loopCounter = 0;
    for(loopCounter=0;loopCounter<50;loopCounter++)
        printf("%.2f,%.2f,%d\n",batteryHealth->batteryTemperatureInCelsius[loopCounter],batteryHealth->dischargingVoltage[loopCounter],batteryHealth->stateOfHealth[loopCounter]);
}

void Simulate_and_Send_Sensor_Readings_for_BMS(struct BatteryHealthParameters *myBattery) {
    (void) simulateSensorReadings(myBattery);
    (void) formatAndPrintToConsole(myBattery);
    free(myBattery->batteryTemperatureInCelsius);
    free(myBattery->dischargingVoltage);
    free(myBattery->stateOfHealth);
}
