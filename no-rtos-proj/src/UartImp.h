/*
 * Uart.h
 *
 *  Created on: 14 ???. 2025 ?.
 *      Author: david
 */

#ifndef SRC_UART_H_
#define SRC_UART_H_

#include "xuartps.h"
#include "UartImp.h"
#include "TemperatureData.h"
#include "xil_printf.h"
#include "sleep.h"


class UartImp {
public:
    // Constructor
    UartImp(u8 uart_id, u32 baud_rate);
    int send(TemperatureSample *TemperatureSample, int size);
    void bloking_recive(u8 *buffer, u32 size, int time_to_wait_ms);
private:
    void u32_to_u8_4( u32 value, u8 array[4] );
    void whileUntilSend();
    u8 check_for_connection();
    XUartPs Uart_PS;
    XUartPs_Config *Config;
};



#endif /* SRC_UART_H_ */
