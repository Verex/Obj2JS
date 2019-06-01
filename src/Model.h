#pragma once
#include <vector>
#include <map>
using namespace std;

namespace Obj2JS
{

enum CMDType
{
    NONE,
    COMMENT,
    VERTEX,
    TCOORD,
    NORMAL,
    FACE,
    OTHER
};

class Index
{
public:
    int Vertex, Texture, Normal;

    Index(int vert, int tex, int normal);
};

class ModelData
{
public:
    vector<float> vertices, normals;
    vector<Index> indices;

    static std::map<std::string, CMDType> CommandValues;
};

} // namespace Obj2JS