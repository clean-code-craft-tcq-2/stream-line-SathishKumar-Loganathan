#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Simulate_and_Send_Sensor_Readings.h"
#include "../catch.hpp"

TEST_CASE("Tests to check if float values are Simulated correctly") {
    int NumberOfReadings = 10;
    float maximumValue = 50.25;
    float *BatteryParameterValues = simulateBatteryParameterFloatValues(NumberOfReadings,maximumValue);
    for(int i=0; i<NumberOfReadings; i++) {
        REQUIRE(BatteryParameterValues[i] <= maximumValue);
    }
}

TEST_CASE("Tests to check if integer values are Simulated correctly") {
    int NumberOfReadings = 15;
    int maximumValue = 30;
    int *BatteryParameterValues = simulateBatteryParameterIntegerValues(NumberOfReadings,maximumValue);
    for(int i=0; i<NumberOfReadings; i++) {
        REQUIRE(BatteryParameterValues[i] <= maximumValue);
    }
}

TEST_CASE("Print Sender values when executed") {
    struct BatteryHealthParameters myBattery;
    Simulate_and_Send_Sensor_Readings_for_BMS(&myBattery);
}
