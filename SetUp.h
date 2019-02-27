#ifndef SETUP_H_INCLUDED
#define SETUP_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

class Soduko
{
    private:
        struct usedValues
        {
            std::vector<int> rowValues;
            std::vector<int> colValues;
                usedValues();
        };
        struct blockValues
        {
            std::vector<int> values;
            int idx;
            int idy;
            int realValue;
                blockValues();
        };
        struct Matrix
        {
            int matrix[9][9] = {};
                Matrix();
            bool getMatrix();
            bool getMatrix(std::ofstream& outFile);
            int getSpecific(int, int);
            int getTotalValue();
            bool setMatrix(int, int, int);
            bool setSpecific(int, int, int);
            std::string getMatrixString();
        };

        usedValues listOfPossbilities[9];
        blockValues listOfValues[81];

        //int Matrix[9][9] = {};
    public:
             Soduko();
        //bool getMatrix();
        bool getPossiblities();
        bool generateBlock(Matrix& currentMatrix);
        bool getBlock();
        bool InputMatrix(Matrix& currentMatrix);
        bool CopyMatrix(Matrix& lhs, Matrix rhs);
        bool CopyBlockValues(blockValues& lhs, blockValues rhs);
        bool CompareMatrix(Matrix lhs, Matrix rhs);
        bool FindEasyStates(Matrix& currentMatrix);
        bool StartGuessing(std::list<Matrix>& listOfMatrices);
        bool SmartGuessing(std::list<Matrix>& listOfMatrices);

        bool InitPossibilities(Matrix& currentMatrix);
        bool UpDate(Matrix& currentMatrix);
        bool CheckIfEnd(Matrix currentMatrix);
        bool CheckIfZero(Matrix currentMatrix);
        bool CheckIfReal(Matrix currentMatrix, int);
        int  ReturnCurrentX(int, int);
        bool NaiveControl(std::list<Matrix>& listOfMatrices);
        bool SmartControl(std::list<Matrix>& listOfMatrices);
        bool SortArray();
        int  Control();

};

#endif // SETUP_H_INCLUDED
