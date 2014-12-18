#include "matrix.h"

template<typename Type>
LinAlg::Matrix<Type>::Matrix ()
{
    this->lines = 0;
    this->columns = 0;

    this->mat = NULL;
};

template<typename Type>
LinAlg::Matrix<Type>::Matrix (unsigned lin, unsigned col)
{
    this->Init(lin, col);
};

template<typename Type>
LinAlg::Matrix<Type>::Matrix (std::string Mat)
{
    this->Init(Mat);
};

template<typename Type>
LinAlg::Matrix(const LinAlg::Matrix<Type>& otherMatrix)
{
    this->Init(otherMatrix.lines, otherMatrix.columns);

    for(unsigned i = 0; i < otherMatrix.lines; i++)
        for(unsigned j = 0; j < otherMatrix.columns; j++)
            this->mat[i][j] = otherMatrix.mat[i][j];
};

template<typename Type>
LinAlg::Matrix<Type>::~Matrix ()
{
    for(unsigned i = 0; i < this->lines; i++)
        delete this->mat[i];
    delete [] this->mat;

    this->lines = 0;
    this->columns = 0;

    this->mat = NULL;
};

template<typename Type>
void LinAlg::Matrix<Type>::Init (std::string Mat)
{
    int posComma, posSemiComma, col = 1, lin = 1;
    std::string temp;

    while (!value.empty())
    {
        posSemiComma = value.find(";");
        if (posSemiComma != -1)
            temp = value.substr(0,posSemiComma);
        else
        {
            temp = value;
            posSemiComma = value.length();
        }
        while (!temp.empty())
        {
            posComma = temp.find(",");
            if( posComma == -1)
                posComma = temp.length();

            string temp2 = temp.substr(0, posComma);
            UsedType num = (UsedType)atof(temp2.c_str());
            this->Add(lin, col, num);
            temp.erase(0, posComma+1);
            col++;
        }
        value.erase(0,posSemiComma+1);
        col = 1;
        lin++;
    }
};

template<typename Type>
void LinAlg::Matrix<Type>::Init (unsigned lin, unsigned col)
{
    this->lines = lin;
    this->columns = col;

    this->mat = new Type*[col];
    for(unsigned i = 0; i < lin; i++)
        this->mat[i] = new Type[lin];
};

template<typename Type>
void LinAlg::Matrix<Type>::Add (unsigned lin, unsigned col)
{
    LinAlg::Matrix<UsedType> Temp;

    if (this->lines < lin || this->columns < col)
    {
        if(this->lines == 0 || this->columns == 0)
            this->init(1,1);

        if (this->lines < lin && lin > 0)
           Temp.init(lin, this->columns);
        else
           Temp.init(this->lines, col);

        if((this->lines != 0) && (this->columns != 0))
        {
            for(int i = 0; i < this->lines; i++)
                for (int j = 0; j < this->columns; j++)
                    Temp.Mat[i][j] = this->Mat[i][j];
        }
        Temp.Mat[lin-1][col-1] = number;
        this->init(Temp.lines, Temp.columns);

        for(int i = 0; i < this->lines; i++)
            for (int j = 0; j < this->columns; j++)
                this->Mat[i][j] = Temp.Mat[i][j];
    }
    else
        this->Mat[lin-1][col-1] = number;
};

template<typename Type>
unsigned LinAlg::Matrix<Type>::getNumberOfLines ()
{
    return this->lines;
};

template<typename Type>
unsigned LinAlg::Matrix<Type>::getNumberOfColumns ()
{
    return this->columns;
};

template<typename Type>
Type LinAlg::Matrix<Type>::operator() (unsigned line, unsigned column)
{
    return this->mat[line][column];
};

template<typename Type>
void LinAlg::Matrix<Type>::operator() (unsigned line, unsigned column, Type number)
{
    this->Add(line, column, number);
};

template<typename Type>
void LinAlg::Matrix<Type>::operator= (std::string Mat)
{
    this->Init(Mat);
};

template<typename Type>
void LinAlg::Matrix<Type>::operator= (LinAlg::Matrix<Type>& Mat)
{
    this->Init(Mat.lines, Mat.columns);

    for(unsigned i = 0; i < Mat.lines; i++)
        for(unsigned j = 0; j < Mat.columns; j++)
            this->mat[i][j] = Mat.mat[i][j];
};

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator+= (LinAlg::Matrix<Type>& Mat)
{

}

template<typename Type>
void LinAlg::Zeros(Matrix<Type>& Mat)
{
    for(unsigned i = 0; i < Mat.getNumberOfLines(); i++)
        for(unsigned j = 0; j < Mat.getNumberOfColumns(); j++)
            Mat(i, j, 0);
};

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Zeros (unsigned lines, unsigned columns)
{
    LinAlg::Matrix<Type> Ret(lines, columns);

    for(unsigned i = 0; i < Mat.getNumberOfLines(); i++)
        for(unsigned j = 0; j < Mat.getNumberOfColumns(); j++)
            Mat(i, j, 0);

    return Ret;
};

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Eye(unsigned dimension)
{
    LinAlg::Matrix<Type> Ret(dimension, dimension);

    for(unsigned i = 0; i < dimension; i++)
        for(unsigned j = 0; j < dimension; j++)
            {
                if( i == j)
                    Ret(i, j, 1);
                else
                    Ret(i, j, 0);
            }

    return Ret;
};

template<typename Type>
void LinAlg::Print(Matrix<Type>& Mat)
{
  std::cout << '\n';

  for(unsigned i = 0; i < Mat.getNumberOfLines(); i++)
  {
    for(unsigned j = 0; j < Mat.getNumberOfColumns(); j++)
        std::cout << std::setw(10) << Mat(i, j) << ' ';

    std::cout << std::endl;
  };
};


template class LinAlg::Matrix<int>;
template class LinAlg::Matrix<float>;
template class LinAlg::Matrix<double>;

template void LinAlg::Zeros<int> (LinAlg::Matrix<int>&);
template void LinAlg::Zeros<float> (LinAlg::Matrix<float>&);
template void LinAlg::Zeros<double> (LinAlg::Matrix<double>&);

template void LinAlg::Zeros<int> (unsigned lines, unsigned columns);
template void LinAlg::Zeros<float> (unsigned lines, unsigned columns);
template void LinAlg::Zeros<double> (unsigned lines, unsigned columns);

template void LinAlg::Print<int> (LinAlg::Matrix<int>&);
template void LinAlg::Print<float> (LinAlg::Matrix<float>&);
template void LinAlg::Print<double> (LinAlg::Matrix<double>&);
