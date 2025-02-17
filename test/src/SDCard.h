/*
 * SDCard.h
 *
 *  Created on: 7 ????. 2025 ?.
 *      Author: david
 */
#include "ff.h"
#include "xparameters.h"
#include "xsdps.h"
#include "xplatform_info.h"
#include "TemperatureData.h"

#include "xparameters.h"	/* SDK generated parameters */
#include "xsdps.h"		/* SD device driver */
#include "xil_printf.h"
#include "ff.h"
#include "xil_cache.h"
#include "xplatform_info.h"


#ifndef SRC_SDCARD_H_
#define SRC_SDCARD_H_

static const int sample_size_in_bytes = 7;

class SDCard {
	private:
//		MKFS_PARM mkfs_parm;
		FATFS fatfs;
		char SD_File[32];
	public:
		int amount_of_samples;
		SDCard(int amount_of_samples_to_write);
		int write(char* file_name,TemperatureSample* data);
		void fill_buffer_with_data(char* buff, TemperatureSample* data);
};


#endif /* SRC_SDCARD_H_ */
