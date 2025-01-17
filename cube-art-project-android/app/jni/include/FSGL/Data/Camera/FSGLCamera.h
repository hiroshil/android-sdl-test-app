/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLCamera.h
 * Author: demensdeum
 *
 * Created on July 8, 2017, 10:46 AM
 */

#ifndef FSGLCAMERA_H
#define FSGLCAMERA_H

#include "../../Data/Object/FSGLObject.h"

class FSGLCamera: public FSGLObject
{
public:
    FSGLCamera();
    virtual ~FSGLCamera();

    virtual glm::mat4 matrix();

private:
	float cameraX = -90.0f;
	float cameraY = 0;

};

#endif /* FSGLCAMERA_H */

