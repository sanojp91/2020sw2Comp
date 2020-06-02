/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/

class OtherLookAndFeel : public LookAndFeel_V4
{
    
public:
    OtherLookAndFeel()
    {
        setColour (Slider::thumbColourId, Colours::darkkhaki);
    }

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        
        auto radius = jmin (width / 2, height / 2) - 4.0f;
        auto centreX = x + width * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        //fill
        g.setColour (Colours::antiquewhite);
        g.fillEllipse (rx, ry, rw, rw);
        
        //outline
        g.setColour (Colours::black);
        g.drawEllipse(rx, ry, rw, rw, 4.0f);
        
        Path p;
        auto pointerLength = radius * 0.66f;
        auto pointerThickness = 2.0f;
        p.addRectangle (-pointerThickness * 0.5f, - radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        
        //pointer
        g.setColour (Colours::black);
        g.fillPath (p);
        
    }
    

    
};


class _2020sw2compAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    _2020sw2compAudioProcessorEditor (_2020sw2compAudioProcessor&);
    ~_2020sw2compAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    OtherLookAndFeel otherLookAndFeel;
    
    ToggleButton mBypassButton;
    ToggleButton mPrePostSatButton;
    
    Label mBypassLabel;
    Label mPrePostLabel;
    
    Slider mInputSlider;
    Slider mThresholdSlider;
    Slider mAttackSlider;
    Slider mReleaseSlider;
    Slider mOutPutSlider;
    Slider mMixSlider;
    Slider mSatSlider;
    
    Label mInputLabel;
    Label mThresholdLabel;
    Label mAttackLabel;
    Label mReleaseLabel;
    Label mOutputLabel;
    Label mMixLabel;
    Label mSatLabel;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    _2020sw2compAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_2020sw2compAudioProcessorEditor)
};
