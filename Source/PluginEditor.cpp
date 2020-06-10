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
    //set look and feel for the mix slider and buttons
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::skyblue);
    getLookAndFeel().setColour(Slider::rotarySliderFillColourId, Colours::lightcyan);
    getLookAndFeel().setColour(ToggleButton::textColourId, Colours::whitesmoke);
    getLookAndFeel().setColour(ToggleButton::tickColourId, Colours::skyblue);
    
    //set up look and feel for the rest of the sliders
    mInputSlider.setLookAndFeel(&otherLookAndFeel);
    mThresholdSlider.setLookAndFeel(&otherLookAndFeel);
    mAttackSlider.setLookAndFeel(&otherLookAndFeel);
    mReleaseSlider.setLookAndFeel(&otherLookAndFeel);
    mRatioSlider.setLookAndFeel(&otherLookAndFeel);
    mOutPutSlider.setLookAndFeel(&otherLookAndFeel);
    mSatSlider.setLookAndFeel(&otherLookAndFeel);
    
    //Input Gain Slider
    mInputSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mInputSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 30);
    mInputSlider.setRange(-15.0f, 15.0f, 1.0f);
    mInputSlider.setValue(0.0f);
    mInputSlider.setTextValueSuffix("dB");
    mInputSlider.setSkewFactorFromMidPoint(0.0f);
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
     mThresholdSlider.setRange(0.0f, 100.0f, 0.1f);
     mThresholdSlider.setValue(50.0f);
     mThresholdSlider.setTextValueSuffix("%");
     mThresholdSlider.setSkewFactorFromMidPoint(50.0f);
     addAndMakeVisible(mThresholdSlider);
     //ValueTreeState
     mThresholdAttachment.reset( new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "threshold", mThresholdSlider));
     //Label
     mThresholdLabel.setText("Threshold", dontSendNotification);
     mThresholdLabel.setJustificationType(Justification::centredTop);
     mThresholdLabel.attachToComponent(&mThresholdSlider, false);
     addAndMakeVisible(mThresholdLabel);
    
    //Attack Time Slider
     mAttackSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
     mAttackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 30);
     mAttackSlider.setRange(3.0f, 30.0f, 1.0f);
     mAttackSlider.setValue(10.0f);
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
     mReleaseSlider.setRange(30.0f, 500.0f, 1.0f);
     mReleaseSlider.setValue(30.0f);
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
    mRatioSlider.setRange(0.0f, 100.f, 1.f);
    mRatioSlider.setValue(50.f);
    mRatioSlider.setTextValueSuffix("%");
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
     mOutPutSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 80, 30);
     mOutPutSlider.setRange(-10.0f, 20.0f, 1.0f);
     mOutPutSlider.setValue(0.0f);
     mOutPutSlider.setTextValueSuffix("dB");
     mOutPutSlider.setSkewFactorFromMidPoint(0.0f);
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
     mMixSlider.setRange(0.0f, 100.0f, 1.f);
     mMixSlider.setValue(0.0f);
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
     mSatSlider.setRange(0.0f, 100.0f, 0.01f);
     mSatSlider.setValue(0.0f);
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

//==============================================================================
void _2020sw2compAudioProcessorEditor::paint (Graphics& g)
{
    // solid black background colour
    g.fillAll (Colours::black);

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
    
    //positioning for the buttons, also needs to be tweaked
    mBypassButton.setBounds(getWidth() - 590, getHeight() - 195, 80, 50);
    mPrePostSatButton.setBounds(getWidth() - 500, getHeight() - 195, 80, 50);

    //some attempts and positioning the mix slider and buttons more cleanly, but it fucks with me
     //auto mixHeight = 10;
    // auto mixWidth = 100;
    // mMixSlider.setBounds (area.removeFromTop(mixHeight));
    // mMixSlider.setBounds (area.removeFromBottom(mixWidth));
  // auto buttonHeight = 5;
   //auto buttonWidth = 10;
   // mPrePostSatButton.setBounds (area.removeFromTop(buttonHeight));
   // mPrePostSatButton.setBounds (area.removeFromLeft(buttonWidth));
  //  mBypassButton.setBounds (area.removeFromLeft(buttonWidth));

    
}
