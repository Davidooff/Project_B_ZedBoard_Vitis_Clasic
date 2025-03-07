//#include <algorithm> // For std::copy

#include "TemperatureData.h"
using namespace std;


// A simple circular queue class for SampleEntry

	TemperatureData::TemperatureData() : data(), count(0) {}

    // Function to get uptime in seconds


    void TemperatureData::addTemperatureData(int new_temp) {
    	TemperatureSample new_sample;
    	new_sample.temperature = new_temp;
    	new_sample.timestamp = 0;
		xil_printf("Adding sample:");
		xil_printf("Temperature is - %d\r\n", new_sample.temperature);
		xil_printf("Time is        - %d\r\n", new_sample.timestamp);
    	if (count == QUEUE_SIZE) {
    		shiftLeftAndAdd(QUEUE_SIZE, new_sample);
    	} else if(count < QUEUE_SIZE) {
    		addWithoutShifting(new_sample);
    	}
    }

    void TemperatureData::showAllData() {
    	for (int i = 0; i < count; i++) {
    		xil_printf("Data sample:");
    		xil_printf("Temperature is - %d\r\n", data[i].temperature);
    		xil_printf("Time is        - %d\r\n", data[i].timestamp);
    	}
    }

    void TemperatureData::clearData() {count = 0;}

//    uint32_t TemperatureData::getUptimeSeconds(void) const {
//        TickType_t ticks = xTaskGetTickCount();
//        return (uint32_t)(ticks * portTICK_PERIOD_MS / 1000);
//    }

    void TemperatureData::shiftLeftAndAdd(int size, const TemperatureSample& new_data) {
        if (size <= 1) return;

        memmove( data, data +1, sizeof( data ) -sizeof( data[ 0 ] ) );
    }

    void TemperatureData::addWithoutShifting(const TemperatureSample& new_sample) {
    	data[count] = new_sample;
    	count++;
    }
