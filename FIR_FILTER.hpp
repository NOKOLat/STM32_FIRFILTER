/*
 * FIR_FILTER.hpp
 *
 *  Created on: Apr 5, 2025
 *      Author: Sezakiaoi
 */

#ifndef INC_FIR_FILTER_HPP_
#define INC_FIR_FILTER_HPP_

#include <cstdint>
#include "dsp/filtering_functions.h"

class FIR_FILTER {


	public:

		FIR_FILTER(uint8_t num_taps, uint8_t block_size);

		void SetCoefficient(float* Coefficient);
		void SetData(float (*in_data)[8]);
		void Calc();
		void GetData(float buffer[3]);

	private:

		uint8_t num_taps;
		uint8_t block_size;
		float in_data[32][3];
		float out_data[32][3];
		float status[32][3];
		float Coefficient[8];
};

#endif /* INC_FIR_FILTER_HPP_ */
