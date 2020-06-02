/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
_2020sw2compAudioProcessor::_2020sw2compAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, Identifier("Compressor"),
                                     {
                                    std::make_unique<AudioParameterFloat>("inputGain",
                                                                          "Input Gain",
                                                                          0.f,
                                                                          2.f,
                                                                          1.f),
                                    std::make_unique<AudioParameterFloat>("threhold",
                                                                          "Threshold",
                                                                          -20.f,
                                                                          20.f,
                                                                          -20.f),
                                    std::make_unique<AudioParameterFloat>("ratio",
                                                                           "Ratio",
                                                                           2.f,
                                                                           10.f,
                                                                           4.f),
                                    std::make_unique<AudioParameterFloat>("attack",
                                                                          "Attack",
                                                                          1.f,
                                                                          30.f,
                                                                          1.f),
                                    std::make_unique<AudioParameterFloat>("release",
                                                                          "Relase",
                                                                          3.f,
                                                                          500.f,
                                                                          100.f),
                                    std::make_unique<AudioParameterFloat>("saturation",
                                                                          "Saturation",
                                                                          0.f,
                                                                          100.f,
                                                                          50.f),
                                    std::make_unique<AudioParameterFloat>("mix",
                                                                          "Mix",
                                                                          0.f,
                                                                          100.f,
                                                                          100.f),
                                    std::make_unique<AudioParameterFloat>("outputGain",
                                                                          "Output Gain",
                                                                          0.f,
                                                                          2.f,
                                                                          1.f),
                                    std::make_unique<AudioParameterBool>("prePostSat",
                                                                         "Pre Post Saturation",
                                                                         false),
                                    std::make_unique<AudioParameterBool>("bypass",
                                                                         "Bypass",
                                                                         false),
                                    })
#endif
{
    mInputGainParameter = parameters.getRawParameterValue("inputGain");
    mThresholdParameter = parameters.getRawParameterValue("threshold");
    mRatioParameter = parameters.getRawParameterValue("ratio");
    mAttackParameter = parameters.getRawParameterValue("attack");
    mReleaseParameter = parameters.getRawParameterValue("release");
    mSatParameter = parameters.getRawParameterValue("saturation");
    mMixParameter = parameters.getRawParameterValue("mix");
    mOutputGainParameter = parameters.getRawParameterValue("outputGain");
    
    mPrePostParameter = parameters.getRawParameterValue("prePostSat");
    mBypassParameter = parameters.getRawParameterValue("bypass");
    
}

_2020sw2compAudioProcessor::~_2020sw2compAudioProcessor()
{
}

//==============================================================================
const String _2020sw2compAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool _2020sw2compAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool _2020sw2compAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool _2020sw2compAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double _2020sw2compAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int _2020sw2compAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int _2020sw2compAudioProcessor::getCurrentProgram()
{
    return 0;
}

void _2020sw2compAudioProcessor::setCurrentProgram (int index)
{
}

const String _2020sw2compAudioProcessor::getProgramName (int index)
{
    return {};
}

void _2020sw2compAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void _2020sw2compAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    //setting both buttons to false
    *mBypassParameter = false;
    *mPrePostParameter = false;

    
}

void _2020sw2compAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool _2020sw2compAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void _2020sw2compAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //create an in- and outbuffer
        auto* mInBuffer = buffer.getReadPointer(channel);
        auto* mOutBuffer = buffer.getWritePointer(channel);
        
        for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            if (*mBypassParameter) //if bypass is enabled (true)
            {
             
             // do nothing to the signal
                
            }
        
            else //if bypass is disabled (false)
            {
                
                  if (*mPrePostParameter) //if prepost it true, in this loop the saturation/distortion is before compression
                              {
                                  
                                  mOutBuffer[sample] = *mInputGainParameter * mInBuffer[sample] * *mOutputGainParameter;
                                  
                              }
                              
                              else //in this loop the saturation/distortion is after the compression
                              {
                                  
                                  mOutBuffer[sample] = *mInputGainParameter * mInBuffer[sample] * *mOutputGainParameter;
                                  
                              }
                             
                
            }
       

        }
    }
}

//==============================================================================
bool _2020sw2compAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* _2020sw2compAudioProcessor::createEditor()
{
    return new _2020sw2compAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void _2020sw2compAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml()); //store the parameters state
    copyXmlToBinary(*xml, destData); //saves the pointer xml to have it saved when the plugin is closed
}

void _2020sw2compAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes)); //get the xml data from the memory
    if (xmlState.get() != nullptr)
    {
        
        if (xmlState -> hasTagName(parameters.state.getType()))
        {
            
            parameters.replaceState(ValueTree::fromXml(*xmlState)); //replace all of the data in the parameters with the saved data
            
        }
        
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new _2020sw2compAudioProcessor();
}
