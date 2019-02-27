#include "SetUp.h"

using namespace std;

Soduko::Matrix::Matrix()
{
    for(int row =0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            matrix[row][col] = 0;
        }
    }
}

Soduko::Soduko()
{
    //listOfMatrices.push_back(Matrix());
}

Soduko::blockValues::blockValues()
{
    idx = 0;
    idy = 0;
    realValue = 0;
}

Soduko::usedValues::usedValues()
{
    rowValues.push_back(0);
    colValues.push_back(0);
}

bool Soduko::Matrix::getMatrix()
{
    for(int row =0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            cout << matrix[row][col];
        }
        cout << endl;
    }
    return true;
}

bool Soduko::Matrix::getMatrix(ofstream& outFile)
{
    for(int row =0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
             outFile << matrix[row][col];
        }
        outFile << endl;
    }
    return true;
}

string Soduko::Matrix::getMatrixString()
{
    string temp = "";
    char hold = ' ';
    for(int row =0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            hold = matrix[row][col] + '0';
            temp += hold;
        }
    }
    return temp;
}

int Soduko::Matrix::getTotalValue()
{
    int total = 0;
    for(int row =0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            total += matrix[row][col];
        }
    }
    return total;
}

bool Soduko::Matrix::setMatrix(int row, int col, int value)
{
    matrix[row][col] = value;
    return true;
}

int Soduko::Matrix::getSpecific(int row, int col)
{
    return matrix[row][col];
}

bool Soduko::Matrix::setSpecific(int row, int col, int value)
{
    matrix[row][col] = value;
    return true;
}

bool Soduko::InputMatrix(Matrix& currentMatrix)
{
    ifstream inFile;
    char temp = ' ';
    int a = 0;
    inFile.open("inputFile.txt", std::ifstream::in);
    if(!inFile)
    {
        cout << "Error Input file not found" << endl;
        return false;
    }

    for(int row=0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            temp = inFile.get();
            if(temp != '\n')
            {
            a = temp - '0';
            if(a>=0)
                currentMatrix.setMatrix(row, col, a);
            }
            else if(temp == '\n')
                col--;
        }
    }

    inFile.close();
    return true;
}

bool Soduko::getPossiblities()
{
    for(int x=0; x<9; x++)
    {
        cout << "\nX: " << x << endl;
        for(int y=0; y<listOfPossbilities[x].rowValues.size(); y++)
        {
            cout << "Row: " <<listOfPossbilities[x].rowValues[y] << endl;
        }
        for(int y=0; y<listOfPossbilities[x].colValues.size(); y++)
        {
            cout << "Col: " <<listOfPossbilities[x].colValues[y] << endl;
        }
    }
    return true;
}

bool Soduko::getBlock()
{
    for(int x=0; x<81; x++)
    {
        cout << "X: " << listOfValues[x].idx << " Y: " << listOfValues[x].idy << " Real Value: " << listOfValues[x].realValue << endl;
        for(int counter=0; counter<listOfValues[x].values.size(); counter++)
        {
            cout << "Possible Values in " << x << " are " << listOfValues[x].values[counter] << endl;
        }
    }
    return true;
}

bool Soduko::UpDate(Matrix& currentMatrix)
{
    int x =0;
    while(x<9)
    {
        listOfPossbilities[x].rowValues.clear();
        listOfPossbilities[x].colValues.clear();
        x++;
    }
    x=0;
    while(x<81)
    {
        listOfValues[x].values.clear();
        x++;
    }
    InitPossibilities(currentMatrix);
    generateBlock(currentMatrix);
    return true;
}

bool Soduko::FindEasyStates(Matrix& currentMatrix)
{
    //UpDate(currentMatrix);
    int x =0;
    while(x<81)
    {
        if(listOfValues[x].values.size() == 1 && listOfValues[x].realValue == 0)
        {
            currentMatrix.setSpecific(listOfValues[x].idx, listOfValues[x].idy, listOfValues[x].values[0]);
            listOfValues[x].realValue = listOfValues[x].values[0];
        }
        x++;
    }
    UpDate(currentMatrix);
    return true;
}

bool Soduko::InitPossibilities(Matrix& currentMatrix)
{
    int x=0;
    while(x<9)
    {
        for(int row=0; row<9; row++)
        {
            for(int col=0; col<9; col++)
            {
                if(currentMatrix.getSpecific(row, col) != 0)
                {
                    listOfPossbilities[x].rowValues.push_back(currentMatrix.getSpecific(row, col));
                }
            }
            x++;
        }
    }
    x=0;
    while(x<9)
    {
        for(int col=0; col<9; col++)
        {
            for(int row=0; row<9; row++)
            {
                if(currentMatrix.getSpecific(row, col) != 0)
                {
                    listOfPossbilities[x].colValues.push_back(currentMatrix.getSpecific(row, col));
                }
            }
            x++;
        }
    }
    return true;
}

bool Soduko::generateBlock(Matrix& currentMatrix)
{
    int x=0;
    bool colflag = false, rowflag = false, repeatflag = false, groupflag = false;
    while(x<81)
    {
        for(int row=0; row<9; row++)
        {
            for(int col=0; col<9; col++)
            {
                listOfValues[x].idx = row;
                listOfValues[x].idy = col;
                listOfValues[x].realValue = currentMatrix.getSpecific(row, col);
                x++;
            }
        }
    }
    x=0;
    while(x<81)
    {
        if(listOfValues[x].realValue == 0)
        {
                for(int z=1; z<10; z++)
                {
                    for(int counter =0; counter < listOfPossbilities[listOfValues[x].idx].rowValues.size(); counter++)
                    {
                        if(z == listOfPossbilities[listOfValues[x].idx].rowValues[counter])
                            rowflag = true;
                    }
                    for(int counter =0; counter < listOfPossbilities[listOfValues[x].idy].colValues.size(); counter++)
                    {
                        if(z == listOfPossbilities[listOfValues[x].idy].colValues[counter])
                            colflag = true;
                    }
                    if(listOfValues[x].idx < 3)
                    {
                    for(int row =0; row<3; row++) // check all 3 groups of the top of the puzzle
                    {
                        if(listOfValues[x].idy < 3)
                        {
                            for(int col=0; col<3; col++)
                            {
                                if(z == currentMatrix.getSpecific(row, col))
                                    groupflag = true;
                            }
                        }
                        else if(listOfValues[x].idy > 2 && listOfValues[x].idy < 6)
                        {
                            for(int col=3; col<6; col++)
                            {
                                if(z == currentMatrix.getSpecific(row, col))
                                    groupflag = true;
                            }
                        }
                        else if(listOfValues[x].idy > 5 && listOfValues[x].idy < 9)
                        {
                            for(int col=6; col<9; col++)
                            {
                                if(z == currentMatrix.getSpecific(row, col))
                                    groupflag = true;
                            }
                        }
                    }
                    }

                    if(listOfValues[x].idx > 2 && listOfValues[x].idx < 6)
                    {
                    for(int row =3; row<6; row++) // check all 3 groups of the mid of the puzzle
                    {
                        if(listOfValues[x].idy < 3)
                        {
                            for(int col=0; col<3; col++)
                            {
                                if(z == currentMatrix.getSpecific(row, col))
                                    groupflag = true;
                            }
                        }
                        else if(listOfValues[x].idy > 2 && listOfValues[x].idy < 6)
                        {
                            for(int col=3; col<6; col++)
                            {
                                if(z == currentMatrix.getSpecific(row, col))
                                    groupflag = true;
                            }
                        }
                        else if(listOfValues[x].idy > 5 && listOfValues[x].idy < 9)
                        {
                            for(int col=6; col<9; col++)
                            {
                                if(z == currentMatrix.getSpecific(row, col))
                                    groupflag = true;
                            }
                        }
                    }
                    }

                    if(listOfValues[x].idx > 5 && listOfValues[x].idx < 9)
                    {
                    for(int row =6; row<9; row++) // check all 3 groups of the bot of the puzzle
                    {
                        if(listOfValues[x].idy < 3)
                        {
                            for(int col=0; col<3; col++)
                            {
                                if(z == currentMatrix.getSpecific(row, col))
                                    groupflag = true;
                            }
                        }
                        else if(listOfValues[x].idy > 2 && listOfValues[x].idy < 6)
                        {
                            for(int col=3; col<6; col++)
                            {
                                if(z == currentMatrix.getSpecific(row, col))
                                    groupflag = true;
                            }
                        }
                        else if(listOfValues[x].idy > 5 && listOfValues[x].idy < 9)
                        {
                            for(int col=6; col<9; col++)
                            {
                                if(z == currentMatrix.getSpecific(row, col))
                                    groupflag = true;
                            }
                        }
                    }
                    }


                    for(int counter =0; counter < listOfValues[x].values.size(); counter++)
                    {
                        if(z == listOfValues[x].values[counter])
                            repeatflag = true;
                    }
                    if(rowflag == false && colflag == false && repeatflag == false && groupflag == false)
                    {
                        listOfValues[x].values.push_back(z);
                    }
                    rowflag = false;
                    colflag = false;
                    repeatflag = false;
                    groupflag = false;
                }
        }
        x++;
    }
    return true;
}

int Soduko::ReturnCurrentX(int row, int col)
{
    int x=0;
    while(x<81)
    {
        if(listOfValues[x].idx == row && listOfValues[x].idy == col)
            return x;
        else
            x++;
    }
    return -1;
}

bool Soduko::CheckIfEnd(Matrix currentMatrix)
{
    int x = 1;
    bool flag = true;
    for(int row=0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            x = currentMatrix.getSpecific(row, col);
            if(x==0)
                flag = false;
        }
    }
    if(flag == true)
        return true;
    return false;
}

bool Soduko::CheckIfReal(Matrix currentMatrix, int currentX)
{
    for(int row=0; row<=listOfValues[currentX].idx; row++)
    {
        for(int col=0; col<=listOfValues[currentX].idy; col++)
        {
            if(currentMatrix.getSpecific(row,col) == 0)
            {
                //cerr << "Returning false" << endl;
                return false;
            }
        }
    }
    return true;
}

bool Soduko::CheckIfZero(Matrix currentMatrix)
{
    for(int row=0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            if(currentMatrix.getSpecific(row,col) == 0)
            {
                //cerr << "Returning false" << endl;
                return false;
            }
        }
    }
    return true;
}

bool Soduko::CopyMatrix(Matrix& lhs, Matrix rhs)
{
    for(int row =0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            lhs.setMatrix(row, col, rhs.getSpecific(row, col));
        }
    }
    return true;
}

bool Soduko::CopyBlockValues(blockValues& lhs, blockValues rhs)
{
    lhs.values.clear();
    for(int counter =0; counter < rhs.values.size(); counter++)
    {
        lhs.values.push_back(rhs.values[counter]);
    }
    lhs.idx = rhs.idx;
    lhs.idy = rhs.idy;
    lhs.realValue = rhs.realValue;

    return true;
}

bool Soduko::CompareMatrix(Matrix lhs, Matrix rhs)
{
    if(lhs.getMatrixString() == rhs.getMatrixString())
        return true;
    return false;
}


int Soduko::Control()
{
    bool check = true, done = false;
    std::list<Matrix> NaiveListOfMatrices;
    std::list<Matrix> SmartListOfMatrices;
    NaiveListOfMatrices.push_back(Matrix());
    SmartListOfMatrices.push_back(Matrix());
    check = InputMatrix(NaiveListOfMatrices.front());
    check = InputMatrix(SmartListOfMatrices.front());

    if(check)
    {
        done = NaiveControl(NaiveListOfMatrices);
        done = SmartControl(SmartListOfMatrices);
        if(done == true)
            return 0;
    }
    cout << "The Solver did not find a solution. " << endl;
    return 1;
}
