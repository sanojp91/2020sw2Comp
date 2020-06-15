/*
  ==============================================================================

    Compressor.cpp
    Created: 14 Jun 2020 5:15:12pm
    Author:  Jonas Persson

  ==============================================================================
*/

#include "Compressor.h"

//initialise compressor constructor function
Compressor::Compressor()
{
    //set variables to a default value
    mBuffer = CircularBuffer(150, 20); //sets the buffer to circular buffer
    mTav = 0.01; // mTav is the averaging time when calculating mRms
    mRms = 0;
    mGain = 1;
}

float Compressor::compressSample(float mData, float mThresh, float mRatio, float mAttack, float mRelease, float mKnee)
{
    //Gain detection
    //adjust the rms value depending on the incoming signal, std::pow computes the value of base raised to the power exp or iexp (mData = base, 2.0f = exp)
    mRms = (1 - mTav) * mRms +mTav * std::pow(mData, 2.0f);
    
     //converts this value to the decibel scale, std::log10 computes the common (base-10) logarithm of the argument (mRms)
    float mDbRMS = 10 * std::log10(mRms);
    
    //Gain reduction
    /*Convert the ratio to a slope, which is a decimal value:
    (Ratio) 1:4 -> (Slope) 0.7
    (Ratio) 1:2 -> (Slope) 0.5*/
    //Calculate slope from ratio
    float mSlope = 1 - (1 / mRatio);
    
    //interpolate
    if (mKnee > 0 && mDbRMS > (mThresh - mKnee / 2.0) && mDbRMS < (mThresh + mKnee / 2.0))
    {
        float mKneeBottom = mThresh - mKnee /    2.0, mKneeTop = mThresh + mKnee / 2.0;
        float xPoints[2], yPoints[2];
        xPoints[0] = mKneeBottom;
        xPoints[1] = mKneeTop;
        xPoints[1] = std::fmin(0.0f, mKneeTop);
        yPoints[0] = 0.0f;
        yPoints[1] = mSlope;
        mSlope = interpolatePoints(&xPoints[0], &yPoints[0], mThresh);
        mThresh = mKneeBottom;
    }
    
    //find the gain to be applied in dB, and make sure it is less than 0.0f which means the signal is never boosted if the rms value is above the threshold
    float mDbGain = std::min(0.0f, (mSlope * (mThresh - mDbRMS)));
    
    //calculate the new gain in a linear scale
    float mNewGain = std::pow(10, mDbGain / 20);
    
    //Smooth transition
    //declare mCoeff variable (coefficient)
    float mCoeff;
    
    //if mNewGain is less than current mGain set to mAttack variable
    if (mNewGain < mGain) mCoeff = mAttack;
    
    //otherwise set to mRelease
    else mCoeff = mRelease;
    
    //adjust mGain based in mNewGain and mCoeff
    mGain = (1 - mCoeff) * mGain + mCoeff * mNewGain;
    
    //set and get values from CircularBuffer
    float mCompressedSample = mGain * mBuffer.getData();
    //set the data from mBuffer to mData
    mBuffer.setData(mData);
    mBuffer.nextSample();
    return mCompressedSample;
    
    return 0.0f;
    
    
}
/*takes an array of two x points, two y points and approximates a value between them.
This value will replace the slope value*/

float Compressor::interpolatePoints(float* xPoints, float* yPoints, float detectedValue)
{
   float result = 0.0f;
   int n = 2;

   for (int i = 0; i < n; i++){
      float term = 1.0f;
      for (int j = 0; j < n; j++)
      {
         if (j != i)
         {
         term *= (detectedValue - xPoints[j]) / (xPoints[i] - xPoints[j]);
         }
      }
   result += term * yPoints[i];
   }
return result;
}
