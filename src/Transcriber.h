#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Model.h"
using namespace std;
using namespace Obj2JS;

namespace Obj2JS
{

class Transcriber
{
    string meshName;
    ofstream output;

    void WriteVectorList(vector<float> *);
    void WriteVertices(vector<float> *);
    void WriteNormals(vector<float> *);
    void WriteIndices(vector<Index> *);
    void WriteColors(int);

public:
    Transcriber(string);
    
    int WriteFile(string, ModelData);
};

} // namespace Obj2JS