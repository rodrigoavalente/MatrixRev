#include <iostream>

#include "include/matrix.h"

using namespace std;

int main()
{
    LinAlg::Matrix<double> A, B, C;

    A = "1,2,3;4,5,6";
    B = "7,8;10,11;13,14,15;16";

    C = LinAlg::Zeros<double>(2, 2);

    LinAlg::Print(C);

    return 0;
}
