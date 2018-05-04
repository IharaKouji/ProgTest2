#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//���L���͒萔(�^���������Ɏw�����z�������Ă���)
const double G = 66.73;
//���_vector ���W�̍�
const int POSITION = 1;
//���_vector ���x�̍�
const int VELOCITY = 4;
//������
const int DIMENSION = 3;


/*
* ���ڎ��_�̋��߂��������̉����x�Z�o
* @param vector<double> me: ���ڎ��_��vector
* @param vector<double> you: ���莿�_��vector
* @param int d: ���߂���������id x���W:0 y���W:1 z���W:2
* @return ���߂��������̉����x
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
* �e�������Ƃɕ����������x�Z�o
* @param double �e�������Ƃɕ������������x
* @param double �e�������Ƃɕ������������x
* @param double ����
* @return double �e�������Ƃɕ����������x
*/
double calcVelocity (const double v0, const double a, const double time) {
	return v0 + a * time;
}




/*
* �e�������Ƃɕ��������ړ������Z�o
* @param double �e�������Ƃɕ������������x
* @param double �e�������Ƃɕ������������x
* @param double ����
* @return double �e�������Ƃɕ����������x
*/
double calcMoveDistance (const double v0, const double a, const double time) {
	return v0*time + a * pow (time, 2) * 3 / 2;
}


/*
* ���_2�_�ɂ��Ċe�v�Z���������s���A���_�̑��x�ƍ��W���Z�o����
* @param vector<vector<double>> materialVector ���_�̃Z�b�g*1.5

* @param double time �o�ߎ���
* @return vector<vector<double>> �e���_�̑��x�ƍ��W
*/
void allCalcPointMethod (vector<double> &result,const vector<double> firstMe, const vector<double> me, const vector<double> you, const double time) {
	//�e�����ɂ��ď���
	//i = 0 :x���W 1:y���W 2:z���W
	for(int i=0; i < DIMENSION; i++) {
		//�����x���Z�o
		double a = calcAccel (me, you, i) ;
		//���x���Z�o,���
		double vt = calcVelocity (firstMe[i + VELOCITY], a, time);
		result[i + VELOCITY] = result[i + VELOCITY] + vt;
		//�ړ��������Z�o
		double l = calcMoveDistance (firstMe[i + VELOCITY], a, time);
		//�ړ���̍��W���Z�o
		result[i + POSITION] = result[i + POSITION] + l;
	}
}



/*
*��؂蕶���ŋ�؂�A�z��ɋl�߂�
*@param string ���̓t�@�C��
*@return string[]
*/
vector<string> makeVector (string &line, char sep) {
	//�߂�l��錾
	vector<string> v;

	stringstream ifile (line);
	string buffer;
	while(getline (ifile, buffer, sep)) {
		v.push_back (buffer);
	}
	return v;
}

