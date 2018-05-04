#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//万有引力定数(運動方程式に指数を吸収させている)
const double G = 66.73;
//質点vector 座標の項
const int POSITION = 1;
//質点vector 速度の項
const int VELOCITY = 4;
//次元数
const int DIMENSION = 3;


/*
* 注目質点の求めたい次元の加速度算出
* @param vector<double> me: 注目質点のvector
* @param vector<double> you: 相手質点のvector
* @param int d: 求めたい次元のid x座標:0 y座標:1 z座標:2
* @return 求めたい次元の加速度
*/
double calcAccel (vector<double> me, vector<double> you, const int d) {
	if(you[0] == 0||me[d + POSITION] - you[d + POSITION] == 0) {
		return 0; 
	}else{		
		return me[d + POSITION] - you[d + POSITION] > 0 ?
			-( G * you[0] / pow (floor (me[d + POSITION] * ( 1e+6 )) - floor (you[d + POSITION] * ( 1e+6 )), 2) ) :
			G * you[0] / pow (floor (me[d + POSITION] * ( 1e+6 )) - floor (you[d + POSITION] * ( 1e+6 )), 2);
		
	}
}

/*
* 各次元ごとに分解した速度算出
* @param double 各次元ごとに分解した初速度
* @param double 各次元ごとに分解した加速度
* @param double 時間
* @return double 各次元ごとに分解した速度
*/
double calcVelocity (const double v0, const double a, const double time) {
	return v0 + a * time;
}




/*
* 各次元ごとに分解した移動距離算出
* @param double 各次元ごとに分解した初速度
* @param double 各次元ごとに分解した加速度
* @param double 時間
* @return double 各次元ごとに分解した速度
*/
double calcMoveDistance (const double v0, const double a, const double time) {
	return v0*time + a * pow (time, 2) * 3 / 2;
}


/*
* 質点2点について各計算処理を実行し、質点の速度と座標を算出する
* @param vector<vector<double>> materialVector 質点のセット*1.5

* @param double time 経過時間
* @return vector<vector<double>> 各質点の速度と座標
*/
void allCalcPointMethod (vector<double> &result,const vector<double> firstMe, const vector<double> me, const vector<double> you, const double time) {
	//各次元について処理
	//i = 0 :x座標 1:y座標 2:z座標
	for(int i=0; i < DIMENSION; i++) {
		//加速度を算出
		double a = calcAccel (me, you, i) ;
		//速度を算出,代入
		double vt = calcVelocity (firstMe[i + VELOCITY], a, time);
		result[i + VELOCITY] = result[i + VELOCITY] + vt;
		//移動距離を算出
		double l = calcMoveDistance (firstMe[i + VELOCITY], a, time);
		//移動後の座標を算出
		result[i + POSITION] = result[i + POSITION] + l;
	}
}



/*
*区切り文字で区切り、配列に詰める
*@param string 入力ファイル
*@return string[]
*/
vector<string> makeVector (string &line, char sep) {
	//戻り値を宣言
	vector<string> v;

	stringstream ifile (line);
	string buffer;
	while(getline (ifile, buffer, sep)) {
		v.push_back (buffer);
	}
	return v;
}

