#include "SetUp.h"

using namespace std;

bool Soduko::StartGuessing(list<Matrix>& listOfMatrices)
{
    list<Matrix>::iterator itr;
    list<Matrix>::iterator start = listOfMatrices.begin();

    Matrix temp, try1;
    int x=0;
    bool done = false, real = true;

    for(int row=0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            x = ReturnCurrentX(row, col);
            if(listOfValues[x].realValue == 0)
            {
                for(itr = start; itr != listOfMatrices.end(); itr++)
                {
                    CopyMatrix(temp, *itr);
                    UpDate(temp);
                    //FindEasyStates(temp);
                    //UpDate(temp);
                    for(int counter =0; counter < listOfValues[x].values.size(); counter++)
                    {
                        listOfValues[x].realValue = listOfValues[x].values[counter];
                        temp.setSpecific(row, col, listOfValues[x].realValue);
                        real = CheckIfReal(temp, x);
                        done = CheckIfEnd(temp);
                        if(real == true)
                        {
                            listOfMatrices.push_back(temp);
                            start = itr;

                            if(done == true)
                                return true;
                        }
                    }
                }
                //flag = false;
            }
            if(x == 80)
                return true;
            //same = false;
        }
    }

    //closeList.clear();

    return false;
}

bool Soduko::NaiveControl(list<Matrix>& listOfMatrices)
{
    bool done = true;
    ofstream outFile;
    outFile.open("NaiveSolution.txt");

    outFile << "Original Puzzle" << endl;
    outFile << "------------------------" << endl;
    listOfMatrices.front().getMatrix(outFile);
    outFile << endl;
    for(list<Matrix>::iterator itr = listOfMatrices.begin(); itr != listOfMatrices.end(); itr++)
    {
        UpDate(*itr);
        FindEasyStates(*itr);
        done = CheckIfEnd(*itr);
        UpDate(*itr);
    }
    StartGuessing(listOfMatrices);

    list<Matrix>::iterator itr = listOfMatrices.end();
    itr--;
    done = CheckIfEnd(*itr);

    if(done == true)
    {
        outFile << "\nSolved Puzzle" << endl;
        outFile << "------------------------" << endl;
        itr->getMatrix(outFile);
        outFile.close();
        listOfMatrices.clear();
        cout << "The Naive Solver has found a solution. Please look in the NaiveSolution.txt file" << endl;
        return true;
    }
    return false;
}
