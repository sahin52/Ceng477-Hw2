#include <iostream>
using namespace std;

class matrix4x4
{
public:
    float mat[4][4];

    matrix4x4();
    matrix4x4(float mat[4][4]);
    matrix4x4(matrix4x4 &matrix);

};