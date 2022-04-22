#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "InterpretAndComputeOnBatteryParameters.h"

char *splitString(char* string, const char delimiter[5]){
	char *splittedString;
	splittedString = strtok(string, delimiter);
	return splittedString;
}

float stringToFloat(char* string){
	float parameterValue;
	parameterValue = strtof(string, NULL);
	return parameterValue;
};

void parseBatteryParameters(char formattedBatteryParameters[][30], size_t numberOfSamples,
							float* batteryTemperature, float* batteryVoltage, float* stateOfHealth){
	char *parsedString;
	for(size_t i=0; i < numberOfSamples; i++) {
		parsedString = splitString(formattedBatteryParameters[i], ",");
		batteryTemperature[i] = stringToFloat(parsedString);
		parsedString = splitString(NULL, ",");
		batteryVoltage[i] = stringToFloat(parsedString);
		parsedString = splitString(NULL, ",");
		stateOfHealth[i] = stringToFloat(parsedString);
	}
}

float computeMinOfGivenFloatValues(float batteryParameters[], size_t numberOfSamples){
	size_t i=0;
	float minValue = batteryParameters[i];
	for(i=0; i<numberOfSamples; i++){
		if(batteryParameters[i] < minValue){
			minValue = batteryParameters[i];
		}
	}
	return minValue;
}
		
float computeMaxOfGivenFloatValues(float batteryParameters[], size_t numberOfSamples){
	size_t i=0;
	float maxValue = batteryParameters[i];
	for(i=0; i<numberOfSamples; i++){
		if(batteryParameters[i] > maxValue){
			maxValue = batteryParameters[i];
		}
	}
	return maxValue;
}

float computeMovingAvgOfGivenFloatValues(float batteryParameters[],  size_t numberOfSamples, size_t countOfSamplesForAvg){
	float sum=0.0, movingAvg;
	size_t startingIndex = numberOfSamples - countOfSamplesForAvg;
	for(size_t i=startingIndex; i<numberOfSamples; i++){
		sum = sum+batteryParameters[i];
	}
	movingAvg = float(sum)/float(countOfSamplesForAvg);
	return movingAvg;
}

void computeStatistics(float batteryParameters[], size_t numberOfSamples, parameterStatisticalData *ParameterStatisticalData, const char parameter[20]) {
	size_t countOfSamplesForAvg = MOVING_AVERAGE_SAMPLE_COUNT;
	strcpy(ParameterStatisticalData->parameter, parameter);
	ParameterStatisticalData->minValue = computeMinOfGivenFloatValues(batteryParameters, numberOfSamples);
	ParameterStatisticalData->maxValue = computeMaxOfGivenFloatValues(batteryParameters, numberOfSamples);
	ParameterStatisticalData->movingAverage = computeMovingAvgOfGivenFloatValues(batteryParameters, numberOfSamples, countOfSamplesForAvg);
}

void printStatistics(struct parameterStatisticalData *ParameterStatisticalData){
	printf(" *** Battery Parmeter:%s ***\n Min: %.2f\n Max: %.2f\n Moving Avg: %.2f \n", ParameterStatisticalData->parameter, ParameterStatisticalData->minValue,
			ParameterStatisticalData->maxValue, ParameterStatisticalData->movingAverage);
}

void computeStatisticsAndPrint(float* parameterValues, size_t numberOfSamples, parameterStatisticalData *ParameterStatisticalData, const char parmeter[20]) {
	computeStatistics(parameterValues, numberOfSamples, ParameterStatisticalData, parmeter);
	printStatistics(ParameterStatisticalData);
	free(parameterValues);
}

void interpretBatteryParametersAndComputeStatistics(char formattedBatteryParameters[][30], size_t numberOfSamples, parameterStatisticalData batteryStatisticalData[]) {
	float *batteryTemperature = (float *)malloc(sizeof(float) * numberOfSamples);
	float *batteryVoltage = (float *)malloc(sizeof(float) * numberOfSamples);
	float *stateOfHealth = (float *)malloc(sizeof(float) * numberOfSamples);
	
	parseBatteryParameters(formattedBatteryParameters, numberOfSamples, batteryTemperature, batteryVoltage, stateOfHealth);
	computeStatisticsAndPrint(batteryTemperature, numberOfSamples, &batteryStatisticalData[0], "Temperature");
	computeStatisticsAndPrint(batteryVoltage, numberOfSamples, &batteryStatisticalData[1], "Voltage");
	computeStatisticsAndPrint(stateOfHealth, numberOfSamples, &batteryStatisticalData[2], "State of Health");
};
