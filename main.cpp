#include <iostream>
#include <typeinfo>
#include "include/matrix.h"

using namespace std;

int main()
{
    LinAlg::Matrix<double> A, B;
    LinAlg::Matrix<int> C, D;

    A = "1,2,3;4,5,6";
    B = "7,8;9,10;11,12";

    C = 2 - A;

    LinAlg::Print(C);

    return 0;
}
