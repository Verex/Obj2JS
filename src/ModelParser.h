#pragma once
#include <map>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "Model.h"
using namespace std;

namespace Obj2JS
{
class ModelParser
{
    ModelData data;

    vector<string> splitLine(string, char);
    void parseVector3(vector<string> *, vector<float> *);
    void parseLine(vector<string>);

public:
    ModelParser();
    bool LoadModel(string);

    ModelData GetData(bool);
};

} // namespace Obj2JS