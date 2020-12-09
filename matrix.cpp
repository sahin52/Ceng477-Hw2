#include "matrix.h"
#include <iostream>
using namespace std;

matrix4x4::matrix4x4(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			mat[i][j]=0;
		}
	}
}

matrix4x4::matrix4x4(float mat2[4][4]){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			mat[i][j]=mat2[i][j];
		}
	}
}

matrix4x4::matrix4x4(matrix4x4 &mat2){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			mat[i][j]=mat2.mat[i][j];
		}
	}
}