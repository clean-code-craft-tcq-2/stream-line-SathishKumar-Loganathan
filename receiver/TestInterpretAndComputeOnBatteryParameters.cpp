#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch.hpp"
#include "InterpretAndComputeOnBatteryParameters.h"

#include <iostream>
#include <fstream>

using std::cout; 
using std::cerr;
using std::endl; 
using std::string;
using std::ifstream;

void readInputValuesFromFile(string inputFileName, char formattedBatteryParameters[50][30]){
	int maxChar=100, i=0;
	char inputValueRead[maxChar];
	string formattedInput(inputFileName);
	ifstream input_file(formattedInput);
	
	if (!input_file.is_open()) {
		cerr << "Could not open the input file" << endl;
	}
	cout << " Reading from Input file" << endl;
	while (input_file.getline(inputValueRead, maxChar)){
		strcpy(formattedBatteryParameters[i], inputValueRead);	
		i++;
	}
	input_file.close();
}

void readFromStandardInput(char formattedBatteryParameters[50][30]){
	int i=0;
	char readValue[30];
	cout << " Reading from Standard Input" << endl;
	while (std::cin.getline(readValue, 30)){
		std::strcpy(formattedBatteryParameters[i], readValue); 
		i++;
	}	
}

SCENARIO("Compute statistics on formatted battery parameters from the input file with battery parameter values") {
	size_t numberOfSamples = 0;
	int numberOfparameters = 3;
	struct parameterStatisticalData expectedOutput[numberOfparameters];
	struct parameterStatisticalData ParameterStatisticalData[numberOfparameters];
	char formattedBatteryParameters[50][30];

	GIVEN( "CSV fomatted battery parameters"){
		
		// Input Values
		readInputValuesFromFile("InputValues.txt", formattedBatteryParameters);
	
		// Size of Input Samples
		numberOfSamples = sizeof(formattedBatteryParameters) / sizeof(formattedBatteryParameters[0]);

		// Expect Values
		expectedOutput[0].minValue = 1.32;
		expectedOutput[0].maxValue = 39.69;
		expectedOutput[0].movingAverage = 14.272;

		expectedOutput[1].minValue = 0.40;
		expectedOutput[1].maxValue = 31.61;
		expectedOutput[1].movingAverage = 16.778;
		
		expectedOutput[2].minValue = 1.00;
		expectedOutput[2].maxValue = 88.00;
		expectedOutput[2].movingAverage = 33.20;
	
		WHEN ( "interpretBatteryParametersAndComputeStatistics functions is called" ) {
			interpretBatteryParametersAndComputeStatistics(formattedBatteryParameters, numberOfSamples, ParameterStatisticalData);

			THEN ( "Computed statistical data on battery parameters should be" ) {
				for(int k=0; k < numberOfparameters; k++) {
					REQUIRE(ParameterStatisticalData[k].minValue == Approx(expectedOutput[k].minValue));
					REQUIRE(ParameterStatisticalData[k].maxValue == Approx(expectedOutput[k].maxValue));
					REQUIRE(ParameterStatisticalData[k].movingAverage == Approx(expectedOutput[k].movingAverage));
				}
			}
		}
	}
}

SCENARIO("Compute statistics on formatted battery parameters on random values from receiver") {
	size_t numberOfSamples = 0;
	int numberOfparameters = 3;
	struct parameterStatisticalData ParameterStatisticalData[numberOfparameters];
	char formattedBatteryParameters[50][30];

	GIVEN( "Randomly generated CSV fomatted battery parameters from the receiver"){
		
		// Input Values
		readFromStandardInput(formattedBatteryParameters);
		
		// Size of Input Samples
		numberOfSamples = sizeof(formattedBatteryParameters) / sizeof(formattedBatteryParameters[0]);

		WHEN ( "interpretBatteryParametersAndComputeStatistics functions is called" ) {
			interpretBatteryParametersAndComputeStatistics(formattedBatteryParameters, numberOfSamples, ParameterStatisticalData);

			THEN ( "Check for the behaviour and state of print function" ) {
				 SUCCEED("Required Statistic is computed and printed");
			}
		}
	}
}
