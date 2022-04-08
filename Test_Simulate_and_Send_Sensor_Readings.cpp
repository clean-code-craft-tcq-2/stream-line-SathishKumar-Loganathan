#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Simulate_and_Send_Sensor_Readings.h"
#include "catch.hpp"

TEST_CASE("Tests to check if float values are Simulated correctly") {
    int NumberOfReadings = 10;
    float maximumValue = 50.25;
    float *BatteryParameterValues;
    BatteryParameterValues = simulateBatteryParameterFloatValues(NumberOfReadings,maximumValue);
    
    for(int i=0; i<NumberOfReadings; i++) {
        REQUIRE(BatteryParameterValues[i] <= maximumValue);
    }
}
