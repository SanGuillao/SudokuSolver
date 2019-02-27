#include "SetUp.h"

using namespace std;

bool Soduko::SortArray()
{
    blockValues temp;

    for(int x=0; x<81; x++)
    {
        for(int y=0; y<81; y++)
        {
            if(x!=y)
            {
                if(listOfValues[x].values.size() > listOfValues[y].values.size())
                {
                    CopyBlockValues(temp, listOfValues[x]);
                    CopyBlockValues(listOfValues[x], listOfValues[y]);
                    CopyBlockValues(listOfValues[y], temp);
                }
            }
        }
    }

    return true;
}

bool Soduko::SmartGuessing(list<Matrix>& listOfMatrices)
{
    list<Matrix>::iterator itr;
    list<Matrix>::iterator start = listOfMatrices.begin();

    Matrix temp, try1;
    int x=0;
    bool done = false, real = true;

    while(x<81)
    {
        //x = ReturnCurrentX(row, col);
        if(listOfValues[x].realValue == 0)
        {
            for(itr = start; itr != listOfMatrices.end(); itr++)
            {
                CopyMatrix(temp, *itr);
                UpDate(temp);
                //SortArray();
                //FindEasyStates(temp);
                //UpDate(temp);
                for(int counter =0; counter < listOfValues[x].values.size(); counter++)
                {
                    listOfValues[x].realValue = listOfValues[x].values[counter];
                    temp.setSpecific(listOfValues[x].idx, listOfValues[x].idy, listOfValues[x].realValue);
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
        x++;
    }

    //closeList.clear();

    return false;
}

bool Soduko::SmartControl(list<Matrix>& listOfMatrices)
{
    bool done = false;

    ofstream outFile;
    outFile.open("SmartSolution.txt");

    outFile << "Original Puzzle" << endl;
    outFile << "------------------------" << endl;
    listOfMatrices.front().getMatrix(outFile);
    outFile << endl;

    UpDate(listOfMatrices.front());
    FindEasyStates(listOfMatrices.front());
    SortArray();

    SmartGuessing(listOfMatrices);

    list<Matrix>::iterator itr = listOfMatrices.end();
    itr--;
    //itr->getMatrix();

    done = CheckIfEnd(*itr);

    if(done == true)
    {
        outFile << "\nSolved Puzzle" << endl;
        outFile << "------------------------" << endl;
        itr->getMatrix(outFile);
        outFile.close();
        listOfMatrices.clear();
        cout << "The Smart Solver has found a solution. Please look in the SmartSolution.txt file" << endl;
        return true;
    }

    //getBlock();
    return false;
}
