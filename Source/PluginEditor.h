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

class OtherLookAndFeel : public LookAndFeel_V4 //custom look and feel class for the sliders
{
    
public:
/*   OtherLookAndFeel()
    {
       setColour (Slider::thumbColourId, Colours::darkkhaki);
    }*/

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
    _2020sw2compAudioProcessorEditor (_2020sw2compAudioProcessor&, AudioProcessorValueTreeState&);
    ~_2020sw2compAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void buttonClicked (Button* button);
    void sliderValueChanged (Slider *slider);



private:
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    _2020sw2compAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;
    
    //declaring otherlookand feel for the rotary sliders
    OtherLookAndFeel otherLookAndFeel;
    
    //declaring togglebuttons and labels for them
    ToggleButton mBypassButton;
    ToggleButton mPrePostSatButton;
   
    ToggleButton dToggleButton;
    
    Label mBypassLabel;
    Label mPrePostLabel;
    
    //declaring sliders and labels for them
    Slider mInputSlider;
    Slider mThresholdSlider;
    Slider mKneeSlider;
    Slider mAttackSlider;
    Slider mReleaseSlider;
    Slider mRatioSlider;
    Slider mOutPutSlider;
    Slider mMixSlider;
    Slider mSatSlider;
    
    Slider dGainSlider;
  
    
    Label mInputLabel;
    Label mThresholdLabel;
    Label mKneeLabel;
    Label mAttackLabel;
    Label mReleaseLabel;
    Label mRatioLabel;
    Label mOutputLabel;
    Label mMixLabel;
    Label mSatLabel;
    
    //slider and button attachments
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mInputAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mThresholdAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mKneeAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mAttackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mReleaseAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mRatioAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mOutputAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mMixAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mSatAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> mPrePostAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> mBypassAttachment;
    
    
    //distortion attachments
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> dGainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> dToggleAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_2020sw2compAudioProcessorEditor)
};
