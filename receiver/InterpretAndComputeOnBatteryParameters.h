#define MOVING_AVERAGE_SAMPLE_COUNT 5

struct parameterStatisticalData{
	char parameter[20];
	float minValue;
	float maxValue;
	float movingAverage;
};

char *splitString(char* string, const char delimiter[5]);
float stringToFloat(char* string);
void parseBatteryParameters(char formattedBatteryParameters[][30], size_t numberOfSamples,
		float* batteryTemperature, float* batteryVoltage, float* stateOfHealth);
float computeMinOfGivenFloatValues(float batteryParameters[], size_t numberOfSamples);
float computeMaxOfGivenFloatValues(float batteryParameters[], size_t numberOfSamples);
float computeMovingAvgOfGivenFloatValues(float batteryParameters[],  size_t numberOfSamples, size_t countOfSamplesForAvg);
void computeStatistics(float batteryParameters[], size_t numberOfSamples,
	parameterStatisticalData *ParameterStatisticalData, const char parameter[20]);
void printStatistics(struct parameterStatisticalData *ParameterStatisticalData);
void computeStatisticsAndPrint(float* parameterValues, size_t numberOfSamples,
	parameterStatisticalData *ParameterStatisticalData, const char parmeter[20]);
void interpretBatteryParametersAndComputeStatistics(char formattedBatteryParameters[][30],
	size_t numberOfSamples, parameterStatisticalData batteryStatisticalData[]);
