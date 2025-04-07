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
		void SetData(float in_data[][3]);
		void Calc();
		void GetData(float out_data[3]);

	private:

		uint8_t num_taps;
		uint8_t block_size;
		float (*data)[3];
		float (*tmp_data)[3];
		float (*status)[3];
		float* Coefficient;
};

#endif /* INC_FIR_FILTER_HPP_ */
