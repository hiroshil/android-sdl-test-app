/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FSGLAnimation.h
 * Author: demensdeum
 *
 * Created on October 22, 2017, 8:14 PM
 */

#ifndef FSGLANIMATION_H
#define FSGLANIMATION_H

#include <chrono>
#include <string>
#include <memory>

#include <FSGL/Data/NodeAnimation/FSGLNodeAnimation.h>

using namespace std;
using namespace std::chrono;

class FSGLAnimation
{
public:
    FSGLAnimation();
    FSGLAnimation(const FSGLAnimation& orig);
    virtual ~FSGLAnimation();

    shared_ptr<string> name;

    double duration = 0;
    double ticksPerSecond = 0;

    double currentOffset;

    vector< shared_ptr<FSGLNodeAnimation> >  nodeAnimations;

    void setCurrentOffset(double offset);
    shared_ptr<string> serializeIntoString(int identation = 0);

    void postRenderUpdate();

    void restartAnimationCounters();

    int ticks();
    bool isEnded();

private:

    shared_ptr<time_point<system_clock> > startDate;
    shared_ptr<time_point<system_clock> > endDate;

};

#endif /* FSGLANIMATION_H */

