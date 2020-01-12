/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSEGTIOSystemParams.h
 * Author: demensdeum
 *
 * Created on March 8, 2017, 1:29 PM
 */

#ifndef IOSYSTEMPARAMS_H
#define IOSYSTEMPARAMS_H

#include <memory>

using namespace std;

class IOSystemParams {
public:
    IOSystemParams();
    IOSystemParams(const IOSystemParams& orig);
    virtual ~IOSystemParams();

    shared_ptr<string> title;

    int width = 0;
    int height = 0;
    bool windowed = false;

private:

};

#endif

