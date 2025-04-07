/*
 * FIR_FILTER.cpp
 *
 *  Created on: Apr 5, 2025
 *      Author: Sezakiaoi
 */

#include <FIR_FILTER.hpp>
#include <stdio.h>

/*　@brief コンストラクタ
 *
 * @param[in] num_taps フィルターのタップ数
 * @param[in] block_size (mod4 == 0)全体のデータ数
 *
 * データの4分の1が実行ごとに更新する数になります
 * block_sizeは必ず4の倍数にしてください
 *
 * @return None
 */
FIR_FILTER::FIR_FILTER(uint8_t num_taps, uint8_t block_size) {

	//データの確認
	if(block_size % 4 == 0){

	//配列の確保
	data = new float[block_size][3];
	tmp_data = new float[block_size][3];
	status = new float[block_size + num_taps - 1][3];
	Coefficient = new float[num_taps];

	//引数の保存
	this->num_taps = num_taps;
	this->block_size = block_size;

	}

	printf("%3.3lf \n",Coefficient[0]);
}

/*　@brief FIRフィルタ係数（タップ係数）の設定
 *
 * @param[in] Coefficient FIRフィルタの係数
 *
 * コンストラクタで定義したタップ数に合わせた配列のポインタを渡してください
 *
 * @return None
 */
void FIR_FILTER::SetCoefficient(float* Coefficient){

	for(uint8_t i=0; i<block_size/4; i++){

		this->Coefficient[i] = Coefficient[i];
	}

}

/*　@brief データの入力
 *
 * @param[in] in_data
 *
 * 3軸のデータを入力できます
 * [blocksize/4][3]の配列のポインタを渡してください
 *
 * @return None
 */
void FIR_FILTER::SetData(float in_data[][3]){

	//保存されているデータを後ろにずらす
	for(uint8_t i=0; i<block_size-(block_size/4); i++){

		for(uint8_t j=0; j<3; j++){

			data[i][j] = data[i+1][j];
		}
	}

	//空いた配列にデータを入力
	for(uint8_t i=0; i<(block_size/4); i++){

		for(uint8_t j=0; j<3; j++){

			data[i][j] = in_data[i][j];
		}
	}

}

/*　@brief FIRフィルタの計算
 *
 * @return None
 */
void FIR_FILTER::Calc(){

	for (uint8_t i=0;i<3;i++){

		arm_fir_instance_f32 fir_instance = {num_taps, status[i], Coefficient};
		arm_fir_f32 (&fir_instance, data[i], tmp_data[i], block_size);
	}
}

/*　@brief データの出力
 *
 * @param[out] out_data 出力データのポインタ
 *
 * 3軸のデータが出力されます
 * 入力と同じ順番で要素が格納されています
 *
 * @return None
 */
void FIR_FILTER::GetData(float out_data[3]){

	for(uint8_t i=0; i<3; i++){

		out_data[i] = tmp_data[i][block_size - 1];
	}
}
