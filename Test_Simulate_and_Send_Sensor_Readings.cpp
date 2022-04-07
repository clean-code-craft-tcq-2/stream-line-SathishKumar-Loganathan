#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Simulate_and_Send_Sensor_Readings.h"
#include "catch.hpp"

TEST_CASE("Tests to check if data is Simulated and printed correctly") {
    struct BatteryHealthParameters myBattery;
    Simulate_and_Send_Sensor_Readings_for_BMS(&myBattery);
}
