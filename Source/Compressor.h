/*
  ==============================================================================

    Compressor.h
    Created: 14 Jun 2020 5:15:12pm
    Author:  Jonas Persson

  ==============================================================================
*/
#include "CircularBuffer.h"
#pragma once

class Compressor
{
    
public:
    
    //constructor function
    Compressor();
    //function
    float compressSample (float mData, float mThresh, float mRatio, float mAttack, float mRelease, float mKnee);
    //function for interpolating samples for a soft knee
    float interpolatePoints(float* xPoints, float* yPoints, float detectedValue);
    
private:
    //create a variable for circular buffer
    CircularBuffer mBuffer;
    //mTav is averaging time used when calculating mRms (Root Mean Square)
    float mTav, mRms, mGain;
    
};
