#include "SDCard.h"
#include "ff.h"
#include <stdexcept>

SDCard::SDCard(int amount_of_samples_to_write)  {
	amount_of_samples = amount_of_samples_to_write;
	FRESULT Res;
	TCHAR *Path = "0:/";

	Res = f_mount(&fatfs, Path, 0);
	if (Res != FR_OK){
		xil_printf("Step 0 faild %d", Res);
		throw std::runtime_error("Unable to mount");
	}

//	Res = f_mkfs("0:/", FM_FAT32, 0, work, sizeof work);
//	if (Res != FR_OK) {
//		xil_printf("Step 0.5 faild %d", Res);
//		throw std::runtime_error("Unable to mount");
//
//	}
};

int SDCard::write(char* file_name,TemperatureSample* data){
	FRESULT Res;
	FIL fil;
	char buff[sample_size_in_bytes * amount_of_samples];
	UINT NumBytesWritten;

	Res = f_open(&fil, "test.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
	if (Res) {
		xil_printf("Step 1 faild");
		return Res;
	}

	Res = f_lseek(&fil, 0);
	if (Res) {
		xil_printf("Step 2 faild");
		return Res;
	}

	fill_buffer_with_data((char* )buff, (TemperatureSample* )data);

	Res = f_write(&fil, (const void*)buff, amount_of_samples * sample_size_in_bytes, &NumBytesWritten);
	if (Res) {
		xil_printf("Step 3 faild");
		return Res;
	}

	Res = f_close(&fil);
	if (Res) {
		xil_printf("Step 4 faild");
		return Res;
	}

	return XST_SUCCESS;
}

void SDCard::fill_buffer_with_data(char* buff, TemperatureSample* data){
	for (int i = 0; i < amount_of_samples; i++){
        buff[i * sample_size_in_bytes + 0] = (data[i].timestamp >> 24); // Ensure byte is taken
        buff[i * sample_size_in_bytes + 1] = (data[i].timestamp >> 16);
        buff[i * sample_size_in_bytes + 2] = (data[i].timestamp >>  8);
        buff[i * sample_size_in_bytes + 3] = (data[i].timestamp >>  0);
        buff[i * sample_size_in_bytes + 4] = ' ';
        buff[i * sample_size_in_bytes + 5] = data[i].temperature;
        buff[i * sample_size_in_bytes + 6] = '\n';
	}
}


