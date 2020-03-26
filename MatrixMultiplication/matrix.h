//
// Created by hamed on 3/24/2020.
//

#ifndef MATRIXMULTIPLICATION_MATRIX_H
#define MATRIXMULTIPLICATION_MATRIX_H

#include <vector>
using namespace std;

class matrix {
private:
    int rows{};
    int cols{};
    vector <vector<int> > numbers;

public:
    void setRows(int rows);
    void setCols(int cols);
    int getRows();
    int getCols();
    void setMatrix();
    matrix(int row, int col, bool set);
    matrix(matrix a, matrix b);
    matrix();
    //for recursive:
    void setRecursiveMatrix(matrix source, int indexI, int indexJ);
    ~matrix();
    void show();
    void setMatrixByVector(vector <vector <int> > sourceNums);
    vector<vector <int> > getNumbers();
    int getSpecificElement(int rowIndex, int colIndex);
    void setSpecificElement(int numberToPut, int rowDestination, int colDestination);
    void pushBackByRowCol();
    void set4MatricesToOne(matrix matrix, int i, int j);
};


#endif //MATRIXMULTIPLICATION_MATRIX_H
