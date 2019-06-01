#include <vector>
#include "Transcriber.h"
using namespace std;
using namespace Obj2JS;

void Transcriber::WriteVectorList(vector<float> *vec)
{
    if (!output.is_open())
        return;

    for (vector<float>::iterator i = (*vec).begin(); i != (*vec).end(); i++)
    {
        output << *i << (i != --(*vec).end() ? "," : "");
    }
}

void Transcriber::WriteVertices(vector<float> *vertices)
{
    if (!output.is_open())
        return;

    output << "var vertices = [";

    // Output standard list from vector.
    WriteVectorList(vertices);

    output << "]; ";
}

void Transcriber::WriteNormals(vector<float> *normals)
{
    if (!output.is_open())
        return;

    output << "var normals = [";

    // Output standard list from vector.
    WriteVectorList(normals);

    output << "]; ";
}

void Transcriber::WriteIndices(vector<Index> *indices)
{
    if (!output.is_open())
        return;
    output << "var indices = [";

    // Output vertex indices.
    for (vector<Index>::iterator i = (*indices).begin(); i != (*indices).end(); i++)
    {
        output << (*i).Vertex << (i != --(*indices).end() ? "," : "");
    }

    output << "]; ";
}

void Transcriber::WriteColors(int indexSize)
{
    if (!output.is_open())
        return;

    output << "var colors = [";

    for (int i = 0; i < indexSize; i++)
    {
        output << "1.0, 1.0, 1.0, 1.0" << (i != (indexSize - 1) ? ", " : "");
    }

    output << "]; ";
}

Transcriber::Transcriber(string meshName)
{
    this->meshName = meshName;
}

int Transcriber::WriteFile(string filePath, ModelData data)
{
    // Open output file.
    output = ofstream(filePath);

    if (!output.is_open())
    {
        return 1;
    }

    output << "let " << meshName << " = () => {";

    // Output model data to file.
    WriteVertices(&data.vertices);
    WriteNormals(&data.normals);
    WriteIndices(&data.indices);
    WriteColors(data.normals.size());

    // Output remaining model function.
    output << "return {"
                  "indices: () => { return indices; },"
                  "vertices: () => { return vertices; },"
                  "normals: () => { return normals; },"
                  "color: () => {return colors;}};";

    // Close the file.
    output << "};";

    // Close the files.
    output.close();
}