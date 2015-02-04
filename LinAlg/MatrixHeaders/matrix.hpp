#include "../matrix.h"

template<typename Type>
LinAlg::Matrix<Type>::Matrix (std::string Mat)
{
    this->Init(Mat);
}

template<typename Type>
LinAlg::Matrix<Type>::Matrix (unsigned row, unsigned column)
{
    this->Init(row, column);
}

template<typename Type>
LinAlg::Matrix<Type>::Matrix (const LinAlg::Matrix<Type>& otherMatrix)
{
    this->Init(otherMatrix.rows, otherMatrix.columns);

    for(unsigned i = 0; i < otherMatrix.rows; i++)
        for(unsigned j = 0; j < otherMatrix.columns; j++)
            this->mat[i][j] = otherMatrix.mat[i][j];
}

template<typename Type>
LinAlg::Matrix<Type>::~Matrix ()
{
    for(unsigned i = 0; i < this->rows; i++)
        delete this->mat[i];
    delete [] this->mat;

    this->rows = 0;
    this->columns = 0;

    this->mat = NULL;
}

template<typename Type>
void LinAlg::Matrix<Type>::Init (std::string Mat)
{
    unsigned commas = 1, semiColons = 1, row, column, lin = 0, col = 0;
    int posComma = 0, posSemiColon = 0;
    std::string temp;

    for(unsigned i = 0; i < Mat.length(); i++)
    {
        if(Mat[i] == ';')
            semiColons += 1;
        else if (Mat[i] == ',')
            commas += 1;
    }

    row = semiColons;
    column = (commas + semiColons - 1)/semiColons;

    this->Init(row, column);

    while(!(Mat.empty()))
    {
        posSemiColon = Mat.find(";");
        if(posSemiColon != -1)
            temp = Mat.substr(0, posSemiColon);
        else
        {
            temp = Mat;
            posSemiColon = Mat.length();
        }

        while(!(temp.empty()))
        {
            posComma = temp.find(",");
            if (posComma == -1)
                posComma = temp.length();

            std::string temp2 = temp.substr(0, posComma);
            Type number;

            if(temp2 == "")
                number = 0;
            else
                number = (Type)atof(temp2.c_str());

            this->mat[lin][col] =  number;
            temp.erase(0, posComma + 1);
            col++;
        }

        Mat.erase(0, posSemiColon + 1);
        col = 0;
        lin++;
    }
}

template<typename Type>
void LinAlg::Matrix<Type>::Init (unsigned row, unsigned column)
{
    if(row == 0)
        row = 1;
    if(column == 0)
        column = 1;

    this->rows = row;
    this->columns = column;

    this->mat = new Type*[row];
    for(unsigned i = 0; i < row; i++)
        this->mat[i] = new Type[column];

    LinAlg::Zeros(*this);
};

template<typename Type>
void LinAlg::Matrix<Type>::ReInit (unsigned row, unsigned column)
{
    LinAlg::Matrix<Type> temp(row, column);

    for(unsigned i = 0; i < this->rows; i++)
        for(unsigned j = 0; j < this->columns; j++)
            temp.mat[i][j] = this->mat[i][j];

    *this = temp;
}

template<typename Type>
void LinAlg::Matrix<Type>::Add (unsigned& row, unsigned& column, Type& number)
{
    unsigned greaterRow, greaterColumn;

    if(((row + 1) > this->rows) || ((column + 1) > this->columns))
    {
        if((row + 1) > this->rows)
            greaterRow = row + 1;
        else
            greaterRow = this->rows;

        if((column + 1) > this->columns)
            greaterColumn = column + 1;
        else
            greaterColumn = this->columns;

        this->ReInit(greaterRow, greaterColumn);
    }

    this->mat[row][column] = number;
}

template<typename Type> template<typename OtherMatrixType>
bool LinAlg::Matrix<Type>::CheckDimensions (const LinAlg::Matrix<OtherMatrixType>& rhs, unsigned operation)
{
    bool checked;

    switch(operation)
    {
    case 0:
        try
        {
            if((this->rows == rhs.getNumberOfRows()) && (this->columns == rhs.getNumberOfColumns()))
                checked = true;
            else
            {
                throw "As dimensoes nao batem. Impossivel realizar operacao";
                checked = false;
            }
        }
        catch(const char* msg)
        {
            std::cerr << msg;
        }
        break;
    case 1:
        try
        {
            if(this->columns == rhs.getNumberOfRows())
                checked = true;
            else
            {
                throw "As dimensoes nao batem. Impossivel realizar operacao";
                checked = false;
            }
        }
        catch(const char* msg)
        {
            std::cerr << msg;
        }
        break;
    }

    return checked;
}

template<typename Type> template<typename OtherMatrixType>
void LinAlg::Matrix<Type>::swap (const LinAlg::Matrix<OtherMatrixType>& otherMatrix)
{
    using std::swap;

    LinAlg::Matrix<Type> temp(otherMatrix.getNumberOfRows(), otherMatrix.getNumberOfColumns());

    for(unsigned i = 0; i < temp.rows; i++)
        for(unsigned j = 0; j < temp.columns; j++)
            temp.mat[i][j] = otherMatrix(i + 1, j + 1);

    swap (rows, temp.rows);
    swap (columns, temp.columns);

    swap (mat, temp.mat);
}

template<typename Type>
unsigned LinAlg::Matrix<Type>::getNumberOfRows () const
{
    return this->rows;
}

template<typename Type>
unsigned LinAlg::Matrix<Type>::getNumberOfColumns () const
{
    return this->columns;
}

template<typename Type>
Type& LinAlg::Matrix<Type>::operator() (unsigned row, unsigned column)
{
    return this->mat[row - 1][column - 1];
}

template<typename Type>
Type LinAlg::Matrix<Type>::operator() (unsigned row, unsigned column) const
{
    return this->mat[row - 1][column - 1];
}

template<typename Type>
void LinAlg::Matrix<Type>::operator() (unsigned row, unsigned column, Type number)
{
    this->Add(row, column, number);
}

template<typename Type>
void LinAlg::Matrix<Type>::operator= (std::string Mat)
{
    this->Init(Mat);
}

template<typename Type> template<typename OtherMatrixType>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator= (const LinAlg::Matrix<OtherMatrixType>& rhs)
{
    swap(rhs);

    return *this;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Matrix<Type>::operator- () const
{
    LinAlg::Matrix<Type> temp(*this);

    for(unsigned i = 0; i < temp.rows; i++)
        for(unsigned j = 0; j < temp.columns; j++)
            temp.mat[i][j] *= -1;

    return temp;
}

template<typename Type>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator+= (const Type& rhs /*scalar*/)
{
    for(unsigned i = 0; i < this->rows; i++)
        for(unsigned j = 0; j < this-> columns; j++)
            this->mat[i][j] += rhs;

    return *this;
}

template<typename Type> template<typename RightType>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator+= (const LinAlg::Matrix<RightType>& rhs)
{
    if(CheckDimensions(rhs, 0))
    {
        for(unsigned i = 0; i < this->rows; i++)
            for(unsigned j = 0; j < this->columns; j++)
                this->mat[i][j] += rhs(i + 1, j + 1);
    }

    return *this;
}

template<typename Type>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator-= (const Type& rhs /*scalar*/)
{
    return *this += -rhs;
}


template<typename Type> template<typename RightType>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator-= (const LinAlg::Matrix<RightType>& rhs)
{
    return *this += -rhs;
}

template<typename Type>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator*= (const Type& rhs /*scalar*/)
{
    for(unsigned i = 0; i < this->rows; i++)
        for(unsigned j = 0; j < this->columns; j++)
            this->mat[i][j] *= rhs;

    return *this;
}

template<typename Type> template<typename RightType>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator*= (const LinAlg::Matrix<RightType>& rhs)
{
    if(CheckDimensions(rhs, 1))
    {
        Type temp;
        LinAlg::Matrix<Type> tempMat(*this);
        this->Init(this->rows, rhs.columns);

        for(unsigned i = 0; i < tempMat.rows; i++)
            for(unsigned col = 0; col < rhs.getNumberOfColumns(); col++)
            {
                temp = 0;
                for(unsigned j = 0; j < tempMat.columns; j++)
                    temp += tempMat.mat[i][j] * rhs(j + 1, col + 1);
                this->mat[i][col] = temp;
            }
    }

    return *this;
}

template<typename Type>
LinAlg::Matrix<Type>& LinAlg::Matrix<Type>::operator/= (const Type& rhs)
{
    return *this *= 1/rhs;
}

template<typename Type>
void LinAlg::Zeros(Matrix<Type>& Mat)
{
    for(unsigned i = 1; i <= Mat.getNumberOfRows(); i++)
        for(unsigned j = 1; j <= Mat.getNumberOfColumns(); j++)
            Mat(i, j) = 0;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Zeros (unsigned rows, unsigned columns)
{
    LinAlg::Matrix<Type> Ret(rows, columns);

    return Ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Eye (unsigned dimension)
{
    LinAlg::Matrix<Type> Ret(dimension, dimension);

    for(unsigned i = 1; i <= dimension; i++)
        for(unsigned j = 1; j <= dimension; j++)
            {
                if( i == j)
                    Ret(i, j) = 1;
                else
                    Ret(i, j) = 0;
            }

    return Ret;
}

template<typename Type>
void LinAlg::Print(const Matrix<Type>& Mat)
{
  std::cout << std::endl;

  for(unsigned i = 1; i <= Mat.getNumberOfRows(); i++)
  {
    for(unsigned j = 1; j <= Mat.getNumberOfColumns(); j++)
        std::cout << std::setw(10) << Mat(i, j) << ' ';

    std::cout << std::endl;
  }
}
