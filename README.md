# Data Handling and UART Communication

## Data Storage and Processing
### When data[QUEUE_SIZE] < QUEUE_SIZE, new temperature samples are added:   
```c
struct TemperatureSamples  
  ulong timestamp;  
  short temperature;  
};
```
### When data[QUEUE_SIZE] == QUEUE_SIZE, data is saved to the SD card.  
  
## UART Communication  
Upon receiving 123 (1 byte) via UART, all samples stored in data are sent inside the TemperatureData class. After transmission, the data is cleared.  
Data package format:  
Package = [255, 255, 255, timestamp[1st byte], timestamp[2nd byte], timestamp[3rd byte], timestamp[4th byte], temperature[1st byte], temperature[2nd byte]]  
  
## Issues Encountered  
SDK and Vitis Problems  
SDK 2015, 2019 – xilfs error with SD card (error code 3). The issue occurred on both Debian and Windows 11, even with the official repository code.  
Vitis 2023.2 (FreeRTOS) – Unable to set cin and cout to ps7_coresight_comp_0.  
Vitis 2023.2 (Bare-metal) – uartps library not working (Windows 11).  
Vitis 2024.2 – Software stuck on the startup page.  
More problems with Vitis 2024.2: Vitis 2024 Known Issues.  
  
Vitis Classic 2024.2 – Does not exist.  
Vitis Classic 2023.2 – Previously worked well, but the timer broke during the last task. Rolling back to a previous version didn’t help. (Possibly clearing and rebuilding the project might resolve the issue.)  
  
## Recommended Tools  
I recommend using Vivado 2023.2 and Vitis Classic 2023.2 because:  
-They do not require high-performance PCs (Vitis Classic is Eclipse-based).  
-This is the most stable version.  
-It allows setting up cin and cout in FreeRTOS.  
-Free for ZedBoard: List of FPGA boards that don’t require a license.  
