#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

struct Matrix {
    string Name;
    uint32_t Rows = 0, Columns = 0;
    vector <vector<int32_t>> matrice;
};

struct Data {
    char* data;
    int length=0;
};


Data& readBin(string);
Matrix* format(Data&);
void writeTxt(Matrix[]);


int main()
{
    Data d = readBin("matrices.bin");
    Matrix *m = format(d);
    cout << (m)->Columns;
    writeTxt(m);

}


Data& readBin(string Path) {
    ifstream file(Path, ios::binary | ios::in);
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);
    char* buffer = new char[length + 1];
    file.read(buffer, length);
    file.close();

    Data ret;
    ret.data = buffer;
    ret.length = length;
    return ret;
}


Matrix* format(Data& D) {
    Matrix matrices[4];
    size_t currentMatrix = 0;

    bool nameRead = false;
    for (size_t i = 1; i < D.length; i++) // acknowledge bit passed
    {
        if (!nameRead) {
            while (D.data[i] != 0x00) {
                matrices[currentMatrix].Name += D.data[i];
                i++;
            }
            nameRead = true;
            i += 16; // null terminator and 16 bytes passed to read row and column
        }
        else {
            matrices[currentMatrix].Rows = ( D.data[i] << 24 + D.data[i+1] << 16 + D.data[i+2] << 8 + D.data[i+3]);
            i += 4;
            matrices[currentMatrix].Columns = ( D.data[i] << 24 + D.data[i+1] << 16 + D.data[i+2] << 8 + D.data[i+3]);
            i += 4;
            // read row and column sizes

            for (uint32_t j = 0; j < matrices[currentMatrix].Rows; j++)
            {
                vector<int32_t> vec;
                for (uint32_t k = 0; k < matrices[currentMatrix].Columns; k++)
                {
                     vec.push_back(D.data[i] << 24 + D.data[i + 1] << 16 + D.data[i + 2] << 8 + D.data[i + 3]);
                     i += 4;
                }
                matrices[currentMatrix].matrice.push_back(vec);
            }

        }
    }

    return matrices;
}


void writeTxt(Matrix M[]) {
    
}