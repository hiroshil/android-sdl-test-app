#ifndef FSGLMODELFSGLVERTEXWEIGHT_H_
#define FSGLMODELFSGLVERTEXWEIGHT_H_

#include <memory>
using namespace std;

class FSGLVertexWeight
{

public:
    FSGLVertexWeight(int vertexID, float weight);
    int vertexID;
    float weight;

    shared_ptr<string> serializeIntoString(int identation);
};

#endif