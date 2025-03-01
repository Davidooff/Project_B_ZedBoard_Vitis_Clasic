#Data Handling and UART Communication

##Data Storage and Processing< br / >
When data[QUEUE_SIZE] < QUEUE_SIZE, new temperature samples are added:< br / >
struct TemperatureSamples {< br / >
  ulong timestamp;< br / >
  short temperature;< br / >
};< br / >
When data[QUEUE_SIZE] == QUEUE_SIZE, data is saved to the SD card.< br / >
< br / >
##UART Communication< br / >
Upon receiving 123 (1 byte) via UART, all samples stored in data are sent inside the TemperatureData class. After transmission, the data is cleared.< br / >
Data package format:< br / >
Package = [255, 255, 255, timestamp[1st byte], timestamp[2nd byte], timestamp[3rd byte], timestamp[4th byte], temperature[1st byte], temperature[2nd byte]]< br / >
< br / >
##Issues Encountered< br / >
SDK and Vitis Problems< br / >
SDK 2015, 2019 – xilfs error with SD card (error code 3). The issue occurred on both Debian and Windows 11, even with the official repository code.< br / >
Vitis 2023.2 (FreeRTOS) – Unable to set cin and cout to ps7_coresight_comp_0.< br / >
Vitis 2023.2 (Bare-metal) – uartps library not working (Windows 11).< br / >
Vitis 2024.2 – Software stuck on the startup page.< br / >
More problems with Vitis 2024.2: Vitis 2024 Known Issues.< br / >
< br / >
Vitis Classic 2024.2 – Does not exist.< br / >
Vitis Classic 2023.2 – Previously worked well, but the timer broke during the last task. Rolling back to a previous version didn’t help. (Possibly clearing and rebuilding the project might resolve the issue.)< br / >
< br / >
##Recommended Tools< br / >
I recommend using Vivado 2023.2 and Vitis Classic 2023.2 because:< br / >
-They do not require high-performance PCs (Vitis Classic is Eclipse-based).< br / >
-This is the most stable version.< br / >
-It allows setting up cin and cout in FreeRTOS.< br / >
-Free for ZedBoard: List of FPGA boards that don’t require a license.< br / >
