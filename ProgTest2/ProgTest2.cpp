// ProgTest2.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "formula.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;



int main()
{	


	//質点ファイルの読み込み
	//質量m 初期座標x y z 初期速度x y z の項目
	ifstream ifile ("C:/IN.csv");
	//存在しなければ終了
	if(!ifile) return 1;

	//入力ファイルを一時受け取るvector
	vector <string>tempVector;

	/*入力ファイルを一行ずつに分解したvector
	*質量m 初期座標x y z 初期速度x y z の7項目
	*/ 
	vector <double> dataVector;

	//上記をまとめた質点の集合vector
	vector<vector<double>> materialVector;

	//計算結果を詰める、質点の集合vector
	vector<vector<double>> resultVector;
	//計算結果を一時的に詰める、質点の集合vector
	vector<vector<double>> tempResultVector;

	//ifstreamをstringに変換
	stringstream istream;
	istream<<ifile.rdbuf ();
	ifile.close ();

	string istring (istream.str ());

	//入力データを行でvectorに詰める
	tempVector = makeVector (istring, '\n');

	//質点データをdoubleにしてvectorに詰める
	for(int j = 0; j < tempVector.size () ; j++) {

		for(int k = 0; k < 7; k++) {
			dataVector.push_back (stof (makeVector (tempVector[j], ',')[k]));
			if(dataVector[0] < 0) {
				cout << "質点 " << j + 1 << " の質量が負です。ご確認下さい。" << endl;
				return 0;
			}
		}
		materialVector.push_back (dataVector);
		//dataVectorをリセット
		dataVector.clear ();
		dataVector.shrink_to_fit ();
	}
	//結果用vectorを設定
	copy (materialVector.begin (), materialVector.end (), back_inserter (resultVector));
	//計算結果一時保存用vectorを設定
	copy (materialVector.begin (), materialVector.end (), back_inserter (tempResultVector));

	double time=0;
	while( time <= 5000 ) {
		for(int i = 0; i < materialVector.size (); i++) {
			for(int j = 0; j < materialVector.size (); j++){
				//同じ質点同士は計算しない
				if(i == j) continue;

				allCalcPointMethod (tempResultVector[i], materialVector[i], resultVector[i], resultVector[j], time);
			}
		}
		//resultVectorをリセット
		resultVector.clear ();
		resultVector.shrink_to_fit ();
		copy (tempResultVector.begin (), tempResultVector.end (), back_inserter (resultVector));
		for(int i = 0; i < resultVector.size(); i++){
			//結果を出力用に整形
			string result = "時間 : ";
			result.append (to_string(time))
				.append ("  質点").append (to_string(i+1))
				.append (" : 座標 (").append(to_string(resultVector[i][1])).append(",").append(to_string(resultVector[i][2])).append (",").append (to_string (resultVector[i][3]))
				.append(")  : 速度(").append(to_string(resultVector[i][4])).append (",").append (to_string (resultVector[i][5])).append (",").append (to_string (resultVector[i][6])).append(")\n")
				;
			
			//結果をコンソールに出力
			cout << result << endl;
			
			//出力用ファイルオープン(追記モード)
			ofstream outputfile ("C:/OUT.txt", ios::app);			
			outputfile << result.append ("\n");
			outputfile.close ();
			
		}
		//時を進める
		time++;
	}
	
		return 0;

}
