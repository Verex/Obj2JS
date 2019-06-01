#include "Model.h"
using namespace Obj2JS;

Index::Index(int vert, int tex, int normal)
{
    // Assign index values.
    Vertex = vert;
    Texture = tex;
    Normal = normal;
}

std::map<string, CMDType> ModelData::CommandValues = {{"#", COMMENT},
                                                      {"v", VERTEX},
                                                      {"vt", TCOORD},
                                                      {"vn", NORMAL},
                                                      {"f", FACE}};