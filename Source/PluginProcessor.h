/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Compressor.h" //include the compressor class

//==============================================================================
/**
*/
class _2020sw2compAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    _2020sw2compAudioProcessor();
    ~_2020sw2compAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float previousMix;

private:
    
    //DSP declerations
    juce::dsp::Gain<float> preGain; // [1]
    dsp::WaveShaper<float> waveShaper1;
    dsp::WaveShaper<float> waveShaper2;
    
    //declare a new array of compressors
    Array<Compressor> mAllCompressors;
    
    //declaring parameters for sliders
    std::atomic<float>* mInputGainParameter = nullptr;
    std::atomic<float>* mThresholdParameter = nullptr;
    std::atomic<float>* mKneeParameter = nullptr;
    std::atomic<float>* mRatioParameter = nullptr;
    std::atomic<float>* mAttackParameter = nullptr;
    std::atomic<float>* mReleaseParameter = nullptr;
    std::atomic<float>* mSatParameter = nullptr;
    std::atomic<float>* mMixParameter = nullptr;
    std::atomic<float>* mOutputGainParameter = nullptr;
    
    
    
    //declaring parameters for buttons
    std::atomic<float>* mBypassParameter = nullptr;
    std::atomic<float>* mPrePostParameter = nullptr;
    
    //waveshaper declerations button and sliders
    std::atomic<float>* dToggleParameter = nullptr;
    
    

    AudioProcessorValueTreeState parameters;

    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_2020sw2compAudioProcessor)
};
