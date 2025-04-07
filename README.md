# STM32_FIRFILTER
STM32でFIRフィルターを使うためのコードです

製作中なので必要ファイル等はアップロードしていません
（完成したら、readmeの記述と必要ファイルをアップロードします）

## メモ


### pose_estimation
```cpp
FIR_FILTER fir(8,32);

void Init_PoseEstimation(){

	float Coefficient[8]= {
		0.02069113757759074,
		0.06555078083899221,
		0.16641303731126522,
		0.24734504427215181,
		0.24734504427215181,
		0.16641303731126522,
		0.06555078083899221,
		0.02069113757759074
	};

	fir.SetCoefficient(Coefficient);
}

uint8_t PoseEstimation(float AccelData[3],float GyroData[3],float MagData[3],float theta[3],float speed[3],float position[3]){

	static uint8_t index = 0;

	static float accel_tmp[3] = {};
	static float gyro_tmp[3][8] = {};
	static float filter_gyro[3] = {};

	if(index < 8){

		for(uint8_t i=0; i<3; i++){

			accel_tmp[i] += AccelData[i];
			gyro_tmp[i][index] = GyroData[i];
		}

		index++;

		return 1; //データを取得中
	}
	else{

		index = 0;

		//加速度の平均値を取得
		for(uint8_t i=0; i<3; i++){

			accel_tmp[i] = accel_tmp[i] / 8;
		}

		fir.SetData(gyro_tmp);
		fir.Calc();
		fir.GetData(filter_gyro);

		//printf("%3.4lf_%3.4lf_%3.4lf\n", filter_gyro[0], filter_gyro[1], filter_gyro[2]);


		float rotation[3][3];
		kalman_theta(accel_tmp,filter_gyro,theta,0.001,rotation);//カルマンフィルタ

		return 0; //計算処理終了
	}

}
```
