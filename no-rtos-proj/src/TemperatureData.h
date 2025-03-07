// TemperatureData.h

#ifndef TEMPERATUREDATA_H
#define TEMPERATUREDATA_H

//#include <algorithm>      // For std::copy
//#include "FreeRTOS.h"     // For TickType_t
//#include "task.h"         // For xTaskGetTickCount
#include "xil_printf.h"   // For xil_printf

// Delay definitions in milliseconds
#define DELAY_100_MS      100UL
#define DELAY_1_SECOND    1000UL
#define DELAY_10_SECONDS 10000UL

// Define the size of the temperature queue
#define QUEUE_SIZE 10UL

// Structure to hold temperature data and a timestamp
struct TemperatureSample {
    int8_t temperature;          // The temperature reading
    unsigned int timestamp;   // Timestamp in seconds
};

// A simple circular queue class for TemperatureSample entries
class TemperatureData {
public:
    TemperatureSample data[QUEUE_SIZE]; // Array to store temperature samples
	int count;
    // Constructor
    TemperatureData();

    /**
     * @brief Adds a new temperature sample to the queue.
     *
     * @param new_temp The new temperature reading to add.
     */
    void addTemperatureData(int new_temp);

    /**
     * @brief Displays all temperature samples in the queue.
     */
    void showAllData();

    void clearData();

private:
                              // Current number of samples in the queue

    /**
     * @brief Retrieves the system uptime in seconds.
     *
     * @return uint32_t Uptime in seconds.
     */
//    uint32_t getUptimeSeconds() const;

    /**
     * @brief Shifts all elements in the queue to the left and adds a new sample at the end.
     *
     * @param size The size of the queue.
     * @param new_data The new temperature sample to add.
     */
    void shiftLeftAndAdd(int size, const TemperatureSample& new_data);

    /**
     * @brief Adds a new temperature sample to the queue without shifting.
     *
     * @param new_sample The new temperature sample to add.
     */
    void addWithoutShifting(const TemperatureSample& new_sample);
};

#endif // TEMPERATUREDATA_H
