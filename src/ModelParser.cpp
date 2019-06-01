#include "ModelParser.h"
using namespace std;
using namespace Obj2JS;

vector<string> ModelParser::splitLine(string line, char d)
{
    vector<string> lineWords;
    string segment;
    istringstream tokenStream(line);

    while (getline(tokenStream, segment, d))
    {
        lineWords.push_back(segment);
    }

    return lineWords;
}

/*
    Attempts to parse three elements from line.
*/
void ModelParser::parseVector3(vector<string> *line, vector<float> *out)
{
    // Ensure input line is correct size.
    if ((*line).size() == 4)
    {
        // Start parsing vector line after CMD.
        for (int i = 1; i < 4; i++)
        {
            // Parse float value from line.
            float value = stof((*line)[i]);

            // Push float value.
            (*out).push_back(value);
        }
    }
    else
    {
        throw "Vector size malformed.";
    }
}

void ModelParser::parseLine(vector<string> line)
{
    // Get first cmd.
    string cmd = line[0];

    // Check if command is a valid command.
    if (ModelData::CommandValues.count(cmd))
    {
        CMDType type = ModelData::CommandValues[cmd];

        // Ignore comment and other.
        if (type == COMMENT || type == NONE)
            return;

        // Handle parsing of each.
        switch (type)
        {
        case VERTEX:
            // Parse vertex.
            parseVector3(&line, &data.vertices);

            break;
        case NORMAL:
            // Parse normal.
            parseVector3(&line, &data.normals);

            break;
        case FACE:
            for (vector<string>::iterator i = ++line.begin(); i != line.end(); i++)
            {
                // Split line.
                vector<string> fVals = splitLine(*i, '/');

                // Ensure correct value count.
                if (fVals.size() == 3)
                {
                    int vertex = -1, texture = -1, normal = -1;

                    if (fVals[0] != "")
                    {
                        vertex = stoi(fVals[0]) - 1;
                    }

                    if (fVals[1] != "")
                    {
                        texture = stoi(fVals[1]) - 1;
                    }

                    if (fVals[2] != "")
                    {
                        normal = stoi(fVals[2]) - 1;
                    }

                    // Push new index entry.
                    data.indices.push_back(Index(vertex, texture, normal));
                }
            }
            break;
        default:
            break;
        }
    }
}

ModelParser::ModelParser()
{
    // Initialize model data.
    data = ModelData();
}

bool ModelParser::LoadModel(string filePath)
{
    // Open input file.
    ifstream inputFile(filePath);

    try
    {
        // Read each line of model.
        string line;
        while (getline(inputFile, line))
        {
            parseLine(splitLine(line, ' '));
        }
    }
    catch (exception e)
    {
        // Failure.
        return 0;
    }

    // Close input file.
    inputFile.close();

    return 1;
}

ModelData ModelParser::GetData(bool flat)
{
    ModelData outputData;

    // Handle flat-shader OpenGL 1.0 Workaround.
    if (flat)
    {
        int indexCount = 0;

        // Loop through each index (assuming each face has 3 points)
        for (int i = 0; i < data.indices.size(); i++)
        {
            // Push new incremented index entry.
            outputData.indices.push_back(Index(indexCount++, 0, 0));

            // Get vertex starting index.
            int vStart = data.indices[i].Vertex * 3;

            // Push X, Y, and Z verts.
            outputData.vertices.push_back(data.vertices[vStart]);
            outputData.vertices.push_back(data.vertices[vStart + 1]);
            outputData.vertices.push_back(data.vertices[vStart + 2]);

            // Get starting index for normals.
            int nStart = data.indices[i].Normal * 3;

            // Push X, Y, and Z norms.
            outputData.normals.push_back(data.normals[nStart]);
            outputData.normals.push_back(data.normals[nStart + 1]);
            outputData.normals.push_back(data.normals[nStart + 2]);
        }
    }
    else
    {
        outputData = data;
    }

    return outputData;
}