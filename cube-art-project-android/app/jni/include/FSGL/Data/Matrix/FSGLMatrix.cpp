/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLMatrix.cpp
 * Author: demensdeum
 *
 * Created on November 12, 2017, 12:51 PM
 */

#define GLM_ENABLE_EXPERIMENTAL

#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include <string>

#include <sstream>
#include "FSGLMatrix.h"
#include <iostream>
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <stdexcept>


using namespace std;

FSGLMatrix::FSGLMatrix()
{

    matrix = glm::mat4(1.0);

}

FSGLMatrix::FSGLMatrix(const FSGLMatrix& )
{
}

FSGLMatrix::~FSGLMatrix()
{
}

void FSGLMatrix::deserializeFromString(shared_ptr<string> rawString)
{

    return; // bugs

    stringstream rawStringStream(rawString->substr(rawString->find("Matrix 4 - ") + strlen("Matrix 4 - ")));
    string token;

    int i = -1;

    while(getline(rawStringStream, token, ',') && i < 16)
    {
        //cout << "token" << token << endl;
        float number = stof(token);

        int index = i - 1;
        int x = index % 4;
        int y = index / 4;

        if (index >= 0)
        {

            cout << x << ";" << y << endl;

            matrix[x][y] = number;
        }

        //cout << token <<";"<<"x:" << x  << ";y:" << y << endl;
        i += 1;
    }

};

shared_ptr<string> FSGLMatrix::serializeIntoString(int identation)
{
    stringstream serializedData;

    for (auto i = 0; i < identation; i++)
    {
        serializedData << "\t";
    }

    serializedData << "Matrix 4 - " << matrix[0][0] << ", " << matrix[1][0] << ", " << matrix[2][0] << ", " << matrix[3][0] << ", "<< matrix[0][1] << ", " << matrix[1][1] << ", " << matrix[2][1] << ", " << matrix[3][1] << ", " << matrix[0][2] << ", " << matrix[1][2] << ", " << matrix[2][2] << ", " << matrix[3][2] << ", " << matrix[0][3] << ", " << matrix[1][3] << ", " << matrix[2][3] << ", " << matrix[3][3] << endl;

    auto stringContainer = make_shared<string>(serializedData.str());
    return stringContainer;
}

void FSGLMatrix::debugPrintout()
{
    cout << "FSGLMatrix debugPrintout" << endl;

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;

    glm::decompose(matrix, scale, rotation, translation, skew, perspective);

    rotation = rotation=glm::conjugate(rotation);

    cout << "Translation x: " << translation.x << "  " << endl;
    cout << "Translation y: " << translation.y << "  " << endl;
    cout << "Translation z: " << translation.z << "  " << endl;

    cout << "Scale x: " << scale.x << "  " << endl;
    cout << "Scale y: " << scale.y << "  " << endl;
    cout << "Scale z: " << scale.z << "  " << endl;

    cout << "Rotation w: " << rotation.w << "  " << endl;
    cout << "Rotation x: " << rotation.x << "  " << endl;
    cout << "Rotation y: " << rotation.y << "  " << endl;
    cout << "Rotation z: " << rotation.z << "  " << endl;

}