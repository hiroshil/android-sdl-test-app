/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLCamera.cpp
 * Author: demensdeum
 *
 * Created on July 8, 2017, 10:46 AM
 */

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "FSGLCamera.h"

using namespace std;

FSGLCamera::FSGLCamera()
{
}

glm::mat4 FSGLCamera::matrix()
{
	auto cameraMatrix = FSGLObject::matrix();
	auto cameraPositionVector = cameraMatrix * glm::vec4(0.f, 0.f, 0.f, 1.f);

	auto yaw = glm::radians(cameraX - rotationVector->x);
	auto pitch = glm::radians(cameraY - rotationVector->y);

	glm::vec3 front;
	front.x = cos(pitch) * cos(yaw);
	front.y = sin(pitch);
	front.z = cos(pitch) * sin(yaw);

	auto cameraFront = glm::normalize(front);
	auto targetPosition = glm::vec3(cameraPositionVector) + glm::vec3(cameraFront);

	auto upVector = glm::normalize(glm::vec4(0.0f,1.0f,0.0f,0.0f));
	cameraMatrix = glm::lookAt(glm::vec3(cameraPositionVector), targetPosition, glm::vec3(upVector));

	return cameraMatrix;
}

FSGLCamera::~FSGLCamera()
{
}