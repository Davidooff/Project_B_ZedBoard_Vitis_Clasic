#include "xuartps.h"
#include "UartImp.h"
#include "TemperatureData.h"
#include "xil_printf.h"
#include "sleep.h"
#include <stdexcept>

UartImp::UartImp(u8 uart_id, u32 baud_rate){
    int Status;

	Config = XUartPs_LookupConfig(uart_id);
	if(Config == NULL) {
		xil_printf("UART config is null \r\n");
        throw std::runtime_error("Uart config is null!");
	}

	Status = XUartPs_CfgInitialize(&Uart_PS, Config, Config->BaseAddress);
	XUartPs_SetBaudRate(&Uart_PS, baud_rate);
	if(Status == XST_SUCCESS){
		xil_printf("UART seted up \r\n");
	} else {
		xil_printf("!Error while setting up UART! \r\n");
        throw std::runtime_error("!Error while setting up UART!");
	}
}

void UartImp::u32_to_u8_4( u32 value, u8 array[4] )
{
  array[0] = value >> 24;
  array[1] = value >> 16;
  array[2] = value >>  8;
  array[3] = value >>  0;
}


int UartImp::send(TemperatureSample *TemperatureSample, int size){

//	xil_printf("Starting transfering\r\n");
	static u8 start_of_data[4] = {255,255,255,255};
	static u8 u32_in_u8[4];
	xil_printf("Size %d\r\n", size);
	for(int i = 0; i < size; i++){
		xil_printf("Starting package sending %d\r\n", TemperatureSample[i].temperature);
		u32_to_u8_4(TemperatureSample[i].timestamp, u32_in_u8);

		xil_printf("Starting part 1 \r\n");
		XUartPs_Send(&Uart_PS, start_of_data, 4);
		UartImp::whileUntilSend();
		usleep(50);

		u8 temp = (u8) TemperatureSample[i].temperature;

		XUartPs_Send(&Uart_PS, &temp, 1);
		UartImp::whileUntilSend();
		usleep(50);

		xil_printf("Starting part 3 %d\r\n");
		XUartPs_Send(&Uart_PS, u32_in_u8, sizeof (u32_in_u8));
		UartImp::whileUntilSend();
		usleep(100);
	}
}

void UartImp::whileUntilSend() {
	while (XUartPs_IsSending(&Uart_PS)){}
}

u8 UartImp::check_for_connection() {
	u8 start_of_data[4] = {255,255,255,255};

	XUartPs_Send(&Uart_PS, start_of_data, 4);
	whileUntilSend();

	u8 answer_buffer[1] = {200};
	bloking_recive(answer_buffer, sizeof(answer_buffer) /4, 1000);

	return answer_buffer[0];
}

void UartImp::bloking_recive(u8 *buffer, u32 size, int time_to_wait_ms) {
	u32 ReceivedCount = 0;
	ReceivedCount +=
				XUartPs_Recv(&Uart_PS, &buffer[ReceivedCount], (size - ReceivedCount));
	while (ReceivedCount < size && ReceivedCount) {
		ReceivedCount +=
			XUartPs_Recv(&Uart_PS, &buffer[ReceivedCount], (size - ReceivedCount));
	}
}

//u8 UartImp::read_bite

