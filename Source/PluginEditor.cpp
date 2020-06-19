/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
_2020sw2compAudioProcessorEditor::_2020sw2compAudioProcessorEditor (_2020sw2compAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    //set look and feel for the mix & knee slider and buttons
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::skyblue);
    getLookAndFeel().setColour(Slider::rotarySliderFillColourId, Colours::lightcyan);
    getLookAndFeel().setColour(ToggleButton::textColourId, Colours::whitesmoke);
    getLookAndFeel().setColour(ToggleButton::tickColourId, Colours::skyblue);
   
    //set up look and feel for the rest of the sliders
    mInputSlider.setLookAndFeel(&otherLookAndFeel);
    mThresholdSlider.setLookAndFeel(&otherLookAndFeel);
    mKneeSlider.setLookAndFeel(&otherLookAndFeel);
    mAttackSlider.setLookAndFeel(&otherLookAndFeel);
    mReleaseSlider.setLookAndFeel(&otherLookAndFeel);
    mRatioSlider.setLookAndFeel(&otherLookAndFeel);
    mOutPutSlider.setLookAndFeel(&otherLookAndFeel);
    mSatSlider.setLookAndFeel(&otherLookAndFeel);
   
    
    //Input Gain Slider
    mInputSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mInputSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(mInputSlider);
    //ValueTreeState
    mInputAttachment.reset( new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "inputGain", mInputSlider));
    //Label
    mInputLabel.setText("Input", dontSendNotification);
    mInputLabel.setJustificationType(Justification::centredTop);
    mInputLabel.attachToComponent(&mInputSlider, false);
    addAndMakeVisible(mInputLabel);
    
    //Threshold Slider
     mThresholdSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
     mThresholdSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 30);
     mThresholdSlider.setTextValueSuffix("dB");
     addAndMakeVisible(mThresholdSlider);
     //ValueTreeState
     mThresholdAttachment.reset( new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "threshold", mThresholdSlider));
     //Label
     mThresholdLabel.setText("Threshold", dontSendNotification);
     mThresholdLabel.setJustificationType(Justification::centredTop);
     mThresholdLabel.attachToComponent(&mThresholdSlider, false);
     addAndMakeVisible(mThresholdLabel);
    
    //Knee Slider
    mKneeSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mKneeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(mKneeSlider);
    //ValueTreeState
    mKneeAttachment.reset( new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "knee", mKneeSlider));
    //Label
    mKneeLabel.setText("Hard<-Knee->Soft", dontSendNotification);
    mKneeLabel.setJustificationType(Justification::centredTop);
    mKneeLabel.attachToComponent(&mKneeSlider, false);
    addAndMakeVisible(mKneeLabel);
    
    //Attack Time Slider
     mAttackSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
     mAttackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 30);
     mAttackSlider.setTextValueSuffix("MS");
     addAndMakeVisible(mAttackSlider);
     //ValueTreeState
     mAttackAttachment.reset( new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "attack", mAttackSlider));
     //Label
     mAttackLabel.setText("Attack", dontSendNotification);
     mAttackLabel.setJustificationType(Justification::centredTop);
     mAttackLabel.attachToComponent(&mAttackSlider, false);
     addAndMakeVisible(mAttackLabel);
    
    //Release Time Slider
     mReleaseSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
     mReleaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 30);
     mReleaseSlider.setTextValueSuffix("MS");
     addAndMakeVisible(mReleaseSlider);
     //ValueTreeState
     mReleaseAttachment.reset( new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "release", mReleaseSlider));
     //Label
     mReleaseLabel.setText("Release", dontSendNotification);
     mReleaseLabel.setJustificationType(Justification::centredTop);
     mReleaseLabel.attachToComponent(&mReleaseSlider, false);
     addAndMakeVisible(mReleaseLabel);
    
    //Ratio Slider
    mRatioSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mRatioSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 30);
    mRatioSlider.setSkewFactorFromMidPoint(5.0f);
    addAndMakeVisible(mRatioSlider);
    //ValuteTreeState
    mRatioAttachment.reset( new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "ratio", mRatioSlider));
    //Label
    mRatioLabel.setText("Ratio", dontSendNotification);
    mRatioLabel.setJustificationType(Justification::centredTop);
    mRatioLabel.attachToComponent(&mRatioSlider, false);
    addAndMakeVisible(mRatioLabel);
    
    //Output Gain Slider
     mOutPutSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
     mOutPutSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
     addAndMakeVisible(mOutPutSlider);
     //ValueTreeState
     mOutputAttachment.reset( new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "outputGain", mOutPutSlider));
     //Label
     mOutputLabel.setText("Makeup", dontSendNotification);
     mOutputLabel.setJustificationType(Justification::centredTop);
     mOutputLabel.attachToComponent(&mOutPutSlider, false);
     addAndMakeVisible(mOutputLabel);
    
    //Mix Slider
     mMixSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
     mMixSlider.setTextBoxStyle(Slider::TextBoxRight, true, 50, 15);
     mMixSlider.setTextValueSuffix("%");
     addAndMakeVisible(mMixSlider);
     //ValueTreeState
     mMixAttachment.reset( new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mix", mMixSlider));
     //Label
     mMixLabel.setText("Mix", dontSendNotification);
     mMixLabel.setJustificationType(Justification::centredRight);
     mMixLabel.attachToComponent(&mMixSlider, true);
     addAndMakeVisible(mMixLabel);
    
    //Saturation Slider
     mSatSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
     mSatSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 30);
     mSatSlider.setTextValueSuffix("%");
     addAndMakeVisible(mSatSlider);
     //ValueTreeState
     mSatAttachment.reset( new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "saturation", mSatSlider));
     //Label
     mSatLabel.setText("Saturation", dontSendNotification);
     mSatLabel.setJustificationType(Justification::centredTop);
     mSatLabel.attachToComponent(&mSatSlider, false);
     addAndMakeVisible(mSatLabel);
    
    //PrePost button
    mPrePostSatButton.setClickingTogglesState(true);
    mPrePostSatButton.setButtonText("Saturation Pre/Post");
    mPrePostSatButton.setState(Button::ButtonState::buttonNormal);
    //valueTreeState
    mPrePostAttachment.reset( new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "prePostSat", mPrePostSatButton));
    addAndMakeVisible(mPrePostSatButton);

    //bypass button
    mBypassButton.setClickingTogglesState(true);
    mBypassButton.setButtonText("Bypass");
    mBypassButton.setState(Button::ButtonState::buttonNormal);
    //valueTreeState
    mBypassAttachment.reset( new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "bypass", mBypassButton));
    addAndMakeVisible(mBypassButton);
    
     dToggleButton.setClickingTogglesState(true);
     dToggleButton.setButtonText("Distortion A");
    // toggleButton.addListener(this);
     dToggleButton.setState(Button::ButtonState::buttonNormal);
     addAndMakeVisible(dToggleButton);
     dToggleAttachment.reset(new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "toggle", dToggleButton));

    
    
    //size of the window
    setSize (600, 200);
}

_2020sw2compAudioProcessorEditor::~_2020sw2compAudioProcessorEditor()
{
    //deconstructor for custom lookAndFeel class to avoid error when shutting down the plugin
    mInputSlider.setLookAndFeel(nullptr);
    mThresholdSlider.setLookAndFeel(nullptr);
    mAttackSlider.setLookAndFeel(nullptr);
    mReleaseSlider.setLookAndFeel(nullptr);
    mRatioSlider.setLookAndFeel(nullptr);
    mOutPutSlider.setLookAndFeel(nullptr);
    mMixSlider.setLookAndFeel(nullptr);
    mSatSlider.setLookAndFeel(nullptr);
    
}

void _2020sw2compAudioProcessorEditor::buttonClicked(Button* button)
{
}

//==============================================================================
void _2020sw2compAudioProcessorEditor::paint (Graphics& g)
{
    // solid black background colour
    g.fillAll (Colours::darkblue);
    //set colour and background for compressor controls
    g.setColour (Colours::steelblue);
    g.fillRoundedRectangle(85, 60, 340, 140, 5.0);
    g.fillRoundedRectangle(getWidth() / 2 - 50, 0, 100, 85, 5.0);
    //set colour and background for saturation control
    g.setColour(Colours::midnightblue);
    g.fillRoundedRectangle(425, 60, 85, 140, 5.0);
    //set colour and background for input/output control
    g.setColour(Colours::blueviolet);
    g.fillRoundedRectangle(510, 60, 85, 140, 5.0);
    g.fillRoundedRectangle(0, 60, 85, 140, 5.0);

}

void _2020sw2compAudioProcessorEditor::resized()
{
    //get local bounds for the window
    auto area = getLocalBounds();
    
    
    //positioning for the sliders
    auto sliderHeight = 85;
    auto sliderWidth = 85;
    mInputSlider.setBounds (area.removeFromTop(sliderHeight));
    mInputSlider.setBounds (area. removeFromLeft(sliderWidth));
    mThresholdSlider.setBounds (area.removeFromLeft(sliderWidth));
    mAttackSlider.setBounds (area.removeFromLeft(sliderHeight));
    mReleaseSlider.setBounds (area.removeFromLeft(sliderHeight));
    mRatioSlider.setBounds (area.removeFromLeft(sliderHeight));
    mSatSlider.setBounds (area.removeFromLeft(sliderHeight));
    mOutPutSlider.setBounds (area.removeFromLeft(sliderHeight));
    
    //positioning for the mix slider, needs to be tweaked
    mMixSlider.setBounds(getWidth() - 100, getHeight() - 220, 100, 100);
    mKneeSlider.setBounds(getWidth() / 2 - 50, getHeight() - 180, 100, 50);
    
    //positioning for the buttons, also needs to be tweaked
    mBypassButton.setBounds(getWidth() - 590, getHeight() - 195, 80, 50);
    mPrePostSatButton.setBounds(getWidth() - 500, getHeight() - 195, 80, 50);
    dToggleButton.setBounds(getWidth() - 420, getHeight() - 195, 80, 50);

    
}
