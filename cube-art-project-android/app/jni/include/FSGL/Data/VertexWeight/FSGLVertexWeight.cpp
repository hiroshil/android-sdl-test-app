#include "FSGLVertexWeight.h"
#include <sstream>

FSGLVertexWeight::FSGLVertexWeight(int vertexID, float weight)
{

    this->vertexID = vertexID;
    this->weight = weight;

}

shared_ptr<string> FSGLVertexWeight::serializeIntoString(int identation)
{

    stringstream serializedData;

    for (auto i = 0; i < identation; i++)
    {
        serializedData << "\t";
    }

    serializedData << vertexID;
    serializedData << ",";
    serializedData << weight;

    auto stringContainer = make_shared<string>(serializedData.str());
    return stringContainer;
}