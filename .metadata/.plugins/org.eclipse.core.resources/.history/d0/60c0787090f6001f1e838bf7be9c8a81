/*
    Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
    Copyright (c) 2012 - 2022 Xilinx, Inc. All Rights Reserved.
	SPDX-License-Identifier: MIT


    http://www.FreeRTOS.org
    http://aws.amazon.com/freertos


    1 tab == 4 spaces!
*/

/* FreeRTOS includes. */
//#include "FreeRTOS.h"
//#include "task.h"
//#include "queue.h"
#include "xiltimer.h"
/* Xilinx includes. */
#include "xil_printf.h"
#include "xparameters.h"

// #include "xuartps.h"

#include "TemperatureData.h"
#include "UartImp.h"
#include "SDCard.h"

//#include "platform.h"

#define DELAY_100_MS    	100UL
#define DELAY_10_SECONDS	10000UL
#define DELAY_1_SECOND		1000UL




void saveSD(TemperatureSample *samples ) {
	static SDCard SD(QUEUE_SIZE);
	xil_printf("Starting save data by sd... \r\n");
	int complit = SD.write((char* )"asd.txt", samples);
	xil_printf("Data written code: %d \r\n", complit);
}

void xAddNewTemp(TemperatureData* temperatureData) {
		static int temp_count = 0;

		temperatureData->addTemperatureData(temp_count); // Invoke member function
		temp_count++;

		if(temperatureData->count == QUEUE_SIZE){
			saveSD(temperatureData->data);
			temperatureData->clearData();

		}
}

void xWaitForUart(TemperatureData* temperatureData) {
//	xil_printf("UART FUB IN");
	static UartImp UartClass(0, 1200);

//		xil_printf("UART FUB WORKS \r\n");
		u8 buffer[1] = {0};
		UartClass.bloking_recive(buffer, 1, 1000);
		if (buffer[0] != 0){
			xil_printf("Buffer: %d \r\n", buffer[0]);
		}
		if(buffer[0] == 123){


			UartClass.send(temperatureData->data, temperatureData->count);
			temperatureData->clearData();

		}
}


int main() {
//	init_platform();
	TemperatureData temperatureData;
	xil_printf("START 1\r\n");
	XTime tStart, tEnd;
	for(;;) {
		xAddNewTemp(&temperatureData);
		XTime_GetTime(&tStart);
		xil_printf("Start uart");
		for (int i = 0; i < 10000000; i++){
//			xil_printf("WHILe...");
			xWaitForUart(&temperatureData);
			XTime_GetTime(&tEnd);
		}
		xil_printf("End uart %d \r\n", tEnd - tStart);

	}
//	cleanup_platform();
}
