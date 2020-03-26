#include <iostream>
#include <vector>
#include "matrix.h"
using namespace std;
matrix combineMatrices(matrix a, matrix b);
matrix unCombineMatrices(matrix a, matrix b);

void recursiveMultiplication(matrix x, matrix y, matrix& xy)
{
    int n = x.getRows();
    if(n > 1) {

        matrix xs[2][2];
        matrix ys[2][2];
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                xs[i][j].setRecursiveMatrix(x, i, j);
                ys[i][j].setRecursiveMatrix(y, i, j);
                //cout << "Xs[" << i << "][" << j << "]: " << "\n";
                xs[i][j].show();
                //cout << "Ys[" << i << "][" << j << "]: " << "\n";
                ys[i][j].show();
            }
        }



        matrix ABCD[4];
        //prep of ABCD:
        ABCD[0].setRows(xs[0]->getRows());
        ABCD[0].setCols(xs[0]->getCols());
        //ABCD[0] = ///                  xs[0][0]*ys[0][0] + xs[0][1]*ys[1][0]

        //creating AE an BG:
        matrix AE, BG;
        recursiveMultiplication(xs[0][0], ys[0][0], AE);
        recursiveMultiplication(xs[0][1], ys[1][0], BG);
        ABCD[0] = combineMatrices(AE, BG);

        matrix AF, BH;
        recursiveMultiplication(xs[0][0], ys[0][1], AF);
        recursiveMultiplication(xs[0][1], ys[1][1], BH);
        ABCD[1] = combineMatrices(AF, BH);

        matrix CE, DG;
        recursiveMultiplication(xs[1][0], ys[0][0], CE);
        recursiveMultiplication(xs[1][1], ys[1][0], DG);
        ABCD[2] = combineMatrices(CE, DG);

        matrix CF, DH;
        recursiveMultiplication(xs[1][0], ys[0][1], CF);
        recursiveMultiplication(xs[1][1], ys[1][1], DH);
        ABCD[3] = combineMatrices(CF, DH);

        //aval set row and col
        xy.setRows(ABCD[0].getRows()*2);
        xy.setCols(ABCD[0].getCols()*2);

        //dovom pushback
        xy.pushBackByRowCol();

        //sevvom meghdar dehi
        xy.set4MatricesToOne(ABCD[0], 0, 0);
        xy.set4MatricesToOne(ABCD[1], 0, 1);
        xy.set4MatricesToOne(ABCD[2], 1, 0);
        xy.set4MatricesToOne(ABCD[3], 1, 1);

    }
    else
    {
        xy.setRows(1);
        xy.setCols(1);
        xy.pushBackByRowCol();
        xy.setSpecificElement(x.getSpecificElement(0, 0) * y.getSpecificElement(0, 0), 0, 0);
    }
}

void strassenMultiplication(matrix x, matrix y, matrix& xy)
{
    int n = x.getRows();
    if(n > 1) {
        matrix xs[2][2];
        matrix ys[2][2];
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                xs[i][j].setRecursiveMatrix(x, i, j);
                ys[i][j].setRecursiveMatrix(y, i, j);
                //cout << "Xs[" << i << "][" << j << "]: " << "\n";
                xs[i][j].show();
                //cout << "Ys[" << i << "][" << j << "]: " << "\n";
                ys[i][j].show();
            }
        }

        matrix ABCD[4];
        //prep of ABCD:
        ABCD[0].setRows(xs[0]->getRows());
        ABCD[0].setCols(xs[0]->getCols());
        //ABCD[0] = ///                  xs[0][0]*ys[0][0] + xs[0][1]*ys[1][0]

        //p1 = A(F-H)
        matrix p1;
        strassenMultiplication(xs[0][0], unCombineMatrices(ys[0][1], ys[1][1]), p1);

        //p2 = (A+B)H
        matrix p2;
        strassenMultiplication(combineMatrices(xs[0][0], xs[0][1]), ys[1][1], p2);

        //p3 = (C+D)E
        matrix p3;
        strassenMultiplication(combineMatrices(xs[1][0], xs[1][1]), ys[0][0], p3);

        //p4 = D(G-E)
        matrix p4;
        strassenMultiplication(xs[1][1], unCombineMatrices(ys[1][0], ys[0][0]), p4);

        //p5 = (A+D)(E+H)
        matrix p5;
        strassenMultiplication(combineMatrices(xs[0][0], xs[1][1]), combineMatrices(ys[0][0], ys[1][1]), p5);


        //p6 = (B-D)(G+H)
        matrix p6;
        strassenMultiplication(unCombineMatrices(xs[0][1], xs[1][1]), combineMatrices(ys[1][0], ys[1][1]), p6);

        //p7 = (A-C)(E+F)
        matrix p7;
        strassenMultiplication(unCombineMatrices(xs[0][0], xs[1][0]), combineMatrices(ys[0][0], ys[0][1]), p7);

        //set ABCD:
        ABCD[0] = unCombineMatrices(combineMatrices(combineMatrices(p4, p5), p6), p2);
        ABCD[1] = combineMatrices(p1, p2);
        ABCD[2] = combineMatrices(p3, p4);
        ABCD[3] = unCombineMatrices(unCombineMatrices(combineMatrices(p1, p5), p3), p7);

        //aval set row and col
        xy.setRows(ABCD[0].getRows()*2);
        xy.setCols(ABCD[0].getCols()*2);

        //dovom pushback
        xy.pushBackByRowCol();

        //sevvom meghdar dehi
        xy.set4MatricesToOne(ABCD[0], 0, 0);
        xy.set4MatricesToOne(ABCD[1], 0, 1);
        xy.set4MatricesToOne(ABCD[2], 1, 0);
        xy.set4MatricesToOne(ABCD[3], 1, 1);

    }
    else
    {
        xy.setRows(1);
        xy.setCols(1);
        xy.pushBackByRowCol();
        xy.setSpecificElement(x.getSpecificElement(0, 0) * y.getSpecificElement(0, 0), 0, 0);
    }
}

matrix unCombineMatrices(matrix a, matrix b)
{
    matrix c;
    if(a.getRows() != b.getRows() || a.getCols() != b.getCols())
    {
        cout << "Invalid input in combineMatrices Function\n";
    }
    else {
        c.setRows(a.getRows());
        c.setCols(a.getCols());
        c.pushBackByRowCol();
        for(int i = 0; i < c.getRows(); i++) {
            for(int j = 0; j < c.getCols(); j++) {
                c.setSpecificElement(a.getSpecificElement(i, j) - b.getSpecificElement(i, j), i, j);
            }
        }
    }
    return c;
}

matrix combineMatrices(matrix a, matrix b)
{
    matrix c;
    if(a.getRows() != b.getRows() || a.getCols() != b.getCols())
    {
        cout << "Invalid input in combineMatrices Function\n";
    }
    else {
        c.setRows(a.getRows());
        c.setCols(a.getCols());
        c.pushBackByRowCol();
        for(int i = 0; i < c.getRows(); i++) {
            for(int j = 0; j < c.getCols(); j++) {
                c.setSpecificElement(a.getSpecificElement(i, j) + b.getSpecificElement(i, j), i, j);
            }
        }
    }
    return c;
}

int main()
{
    int N = 1;
    cout << "HELLO\n";
    matrix a(N, N, true);
    matrix b(N, N, true);
    matrix threeFor(a, b);
    matrix simpleRecursion;
    recursiveMultiplication(a, b, simpleRecursion);

    matrix strassen;
    strassenMultiplication(a, b, strassen);

    cout << "Result of simple 3x for multiplication: \n";
    threeFor.show();
    cout << "\n";

    cout << "Result of not Optimal recursion multiplication: \n";
    simpleRecursion.show();
    cout << "\n";

    cout << "Result with Strassen's matrix multiplication: \n";
    strassen.show();
    cout << "\n";

}
