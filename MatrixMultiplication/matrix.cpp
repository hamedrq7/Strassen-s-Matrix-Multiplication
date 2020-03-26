//
// Created by hamed on 3/24/2020.
//

#include "matrix.h"
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int matrix::getCols() {return this->cols;}
int matrix::getRows() {return this->rows;}

void matrix::setCols(int inputCols) {this->cols = inputCols;}
void matrix::setRows(int inputRows) {this->rows = inputRows;}


void matrix::show() {
    //cout << "Matrix: \n";
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->cols; j++)
        {
            cout << this->numbers[i][j] << " ";
        }
        cout << "\n";
    }
}
void matrix::setMatrix() {
    for(int i = 0; i < this->rows; i++)
    {
        vector <int> v;
        this->numbers.push_back(v);
        for(int j = 0; j < this->cols; j++)
        {
            int temp;
            cin >> temp;
            numbers[i].push_back(temp);
        }
    }
}

matrix::matrix(int row, int col, bool set) {
    this -> rows = row;
    this -> cols = col;
    if(set) {
        setMatrix();
    }
}

matrix::matrix() = default;

matrix::matrix(matrix a, matrix b) {
    if(a.getCols() != b.getRows()) {
        cout << "Invalid! (rows!=cols)\n";
        this->~matrix();
    }
    else {
        this->rows = a.getRows();
        this->cols = b.getCols();

        for(int i = 0; i < a.getRows(); i++) {
            vector <int> v;
            this->numbers.push_back(v);
            for(int j = 0; j < b.getCols(); j++) {
                int sum = 0;
                for(int k = 0; k < a.getCols(); k++) {
                    sum += a.numbers[i][k] * b.numbers[k][j];
                }
                this->numbers[i].push_back(sum);
            }
        }
    }
}

void matrix::setRecursiveMatrix(matrix source, int indexI, int indexJ) {
    this->setRows(source.getRows()/2);
    this->setCols(source.getCols()/2);
    this->pushBackByRowCol();
    //cout << "+ ";
    for(int i = 0; i < source.getRows()/2; i++) {
        vector <int> v;
        for(int j = 0; j < source.getCols()/2; j++) {
            this->setSpecificElement(source.getSpecificElement(i + indexI*source.getRows()/2 , j + indexJ*source.getCols()/2), i, j);
        }
    }
}

void matrix::setMatrixByVector(vector<vector<int> > sourceNums) {
    this->numbers = sourceNums;
}

vector<vector<int> > matrix::getNumbers() {
    return this->numbers;
}

int matrix::getSpecificElement(int rowIndex, int colIndex) {
    return this->numbers[rowIndex][colIndex];
}

void matrix::setSpecificElement(int numberToPut, int rowDestination, int colDestination) {
    this->numbers[rowDestination][colDestination] = numberToPut;
}

void matrix::pushBackByRowCol() {
    for(int i = 0; i < this->getRows(); i++) {
        vector <int> v(this->getCols());
        this->numbers.push_back(v);
    }
}

void matrix::set4MatricesToOne(matrix matrix, int indexI, int indexJ) {
    //ghable in havaset bashe pushback karde baashi

    //optimal kon baadaan:
    //(if haro bardar generic kon):
    if(indexI == 0 && indexJ == 0) {
        for(int i = 0; i < this->getRows()/2; i++) {
            for(int j = 0; j < this->getCols()/2; j++) {
                this->setSpecificElement(matrix.getSpecificElement(i, j), i, j);
            }
        }
    }
    else if(indexI == 0 && indexJ == 1) {
        for(int i = 0; i < this->getRows()/2; i++) {
            for(int j = 0; j < this->getCols()/2; j++) {
                this->setSpecificElement(matrix.getSpecificElement(i, j), i, j+this->getCols()/2);
            }
        }
    }
    else if(indexI == 1 && indexJ == 0) {
        for(int i = 0; i < this->getRows()/2; i++) {
            for(int j = 0; j < this->getCols()/2; j++) {
                this->setSpecificElement(matrix.getSpecificElement(i, j), i+this->getRows()/2, j);
            }
        }
    }
    else if(indexI == 1 && indexJ == 1) {
        for(int i = 0; i < this->getRows()/2; i++) {
            for(int j = 0; j < this->getCols()/2; j++) {
                this->setSpecificElement(matrix.getSpecificElement(i, j), i+this->getRows()/2, j+this->getCols()/2);
            }
        }
    }
}


matrix::~matrix() = default;


