/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.
 
    This code implement parts of Alex Rycroft's code (audioordeal.com)

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
                                    std::make_unique<AudioParameterFloat>("inputGain", //ID
                                                                          "Input Gain", //Name
                                                NormalisableRange<float> (0.f, //Minimum
                                                                          10.f, //Maximum
                                                                          0.01f), //change in incraments
                                                                          1.f), //default value
                                    std::make_unique<AudioParameterFloat>("threshold",
                                                                          "Threshold",
                                                NormalisableRange<float> (-60.f,
                                                                           20.f,
                                                                          0.01f),
                                                                          10.0f),
                                    std::make_unique<AudioParameterFloat>("knee",
                                                                          "Knee",
                                                NormalisableRange<float> (0.0f,
                                                                          24.0f,
                                                                          0.01f),
                                                                          12.0f),
                                    std::make_unique<AudioParameterFloat>("ratio",
                                                                          "Ratio",
                                                NormalisableRange<float> (1.0f,
                                                                          20.0f,
                                                                          0.01f),
                                                                          2.0f),
                                    std::make_unique<AudioParameterFloat>("attack",
                                                                          "Attack",
                                                NormalisableRange<float> (0.01f,
                                                                          500.f,
                                                                          0.01f),
                                                                          100.0f),
                                    std::make_unique<AudioParameterFloat>("release",
                                                                          "Relase",
                                                 NormalisableRange<float> (0.01f,
                                                                          2000.f,
                                                                          0.01f),
                                                                          500.0f),
                                    std::make_unique<AudioParameterFloat>("saturation",
                                                                          "Saturation",
                                                NormalisableRange<float> (0.0f,
                                                                          1.0f,
                                                                          0.01f),
                                                                          0.0f),
                                    std::make_unique<AudioParameterFloat>("mix",
                                                                          "Mix",
                                                NormalisableRange<float>  (0.0f,
                                                                          1.0f,
                                                                          0.01f),
                                                                          1.0f),
                                    std::make_unique<AudioParameterFloat>("outputGain",
                                                                          "Output Gain",
                                                NormalisableRange<float> (0.0f,
                                                                          10.0f,
                                                                          0.01f),
                                                                          1.0f),
                                    std::make_unique<AudioParameterBool>("prePostSat", //ID
                                                                         "Pre Post Saturation", //Name
                                                                         false), //Default
                                    std::make_unique<AudioParameterBool>("bypass",
                                                                         "Bypass",
                                                                         false),
                                    std::make_unique<AudioParameterBool>( "dToggle",   //parameter ID
                                                                          "Toggle",    // parameter name
                                                                           false),
                                                        
                                 
                                   
                               })
                                    
#endif
{
           waveShaper1.functionToUse = [] (float x) {
                   return jlimit((float)-0.1, (float) 0.1, x); // lambda function creating the distortion
           };
           waveShaper2.functionToUse = [] (float z) {
                   return std::tanh (z); // second lambda function for second distortion
             };// [4]
    
    mInputGainParameter = parameters.getRawParameterValue("inputGain");
    mThresholdParameter = parameters.getRawParameterValue("threshold");
    mKneeParameter = parameters.getRawParameterValue("knee");
    mRatioParameter = parameters.getRawParameterValue("ratio");
    mAttackParameter = parameters.getRawParameterValue("attack");
    mReleaseParameter = parameters.getRawParameterValue("release");
    mSatParameter = parameters.getRawParameterValue("saturation");
    mMixParameter = parameters.getRawParameterValue("mix");
    mOutputGainParameter = parameters.getRawParameterValue("outputGain");
    
    dToggleParameter = parameters.getRawParameterValue("dToggle");
    
  //  preGain.setGainDecibels(*dGainParameter); // pre gain float attached to gain parameter

    
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

    
    //create an array of compressors
       for (int channel = 0; channel < getTotalNumOutputChannels(); channel++)
       {
           mAllCompressors.add(Compressor());
       }
    
    //setting both buttons to false
    *mBypassParameter = false;
    *mPrePostParameter = false;

    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getMainBusNumOutputChannels();
    

    
  //  preGain.prepare(spec); // prepare DSP
    waveShaper1.prepare(spec);
    waveShaper2.prepare(spec);

  //  preGain.reset(); // reset DSP
   
    
 //   preGain.setGainDecibels(*dGainParameter); //re reference the gain decibel from gain parameter
    
}

void _2020sw2compAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    waveShaper1.reset();
       waveShaper2.reset();
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

    //maths on the attack and release times to convert from seconds to milliseconds and from a linear to time scale.
    float mAttackTime = 1 - std::pow(MathConstants<float>::euler, ((1 / getSampleRate()) * -2.2f) / (*mAttackParameter / 1000.0f));
    float mReleaseTime = 1 - std::pow(MathConstants<float>::euler, ((1 / getSampleRate()) * -2.2f) / (*mReleaseParameter / 1000.0f));
    
    //Loop through samples and channels
    
for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
      {
          for (int channel = 0; channel < totalNumInputChannels; ++channel)
           {
              
               
 
        

       
            //create an in- and outbuffer
        
            
                auto* mInBuffer = buffer.getReadPointer(channel); //maybe not necessary?
                auto* mOutBuffer = buffer.getWritePointer(channel);
            
              //  preGain.setGainDecibels(*dGainParameter); // re reference the gain decibel from gain parameter
                auto   dryMix = preGain.processSample(mInBuffer[sample]); // drymix is equal to pregains relation to the dry signal
                float  wetMix;
                float outputLevel = *mSatParameter; // get outputLevel from mixparameters position
                float inputLevel = 1.0 - outputLevel; // input level is equal to 1 - output level
                
            //  wetMix = waveShaper1.processSample(mInBuffer[sample]);
               
               
            if (*dToggleParameter == true) // if button is true complete code:
                            {
                                  wetMix = waveShaper1.processSample(mInBuffer[sample]);
                                DBG('here');
                            } else // or else run the second waveshaper function
                            {
                                  wetMix = waveShaper2.processSample(mInBuffer[sample]);
                            }

            //get a reference from Compressor class for the current channel
            Compressor* mComp = &mAllCompressors.getReference(channel);
            
            if (*mBypassParameter) //if bypass is enabled (true)
            {
             
             // do nothing to the signal
                
            }
        
            else //if bypass is disabled (false)
            {
                
                  if (*mPrePostParameter) //if prepost it true, in this loop the saturation/distortion is before compression
                  {
                                
                    //Calculate the compressed samples with some initial values passed into the compressSample function
                      mOutBuffer[sample] = *mInputGainParameter * *mMixParameter * mComp->compressSample(mOutBuffer[sample], *mThresholdParameter, *mRatioParameter, mAttackTime, mReleaseTime, *mKneeParameter) + dryMix * inputLevel + wetMix * outputLevel * *mOutputGainParameter  + mOutBuffer[sample] * (1 - *mMixParameter);
                                  
                    }
                              
                        else //in this loop the saturation/distortion is after the compression
                        {

                            mOutBuffer[sample] = *mInputGainParameter * *mMixParameter * mComp->compressSample(mOutBuffer[sample], *mThresholdParameter, *mRatioParameter, mAttackTime, mReleaseTime, *mKneeParameter) + dryMix * inputLevel + wetMix * outputLevel * *mOutputGainParameter + mOutBuffer[sample] * (1 - *mMixParameter);
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
//testy
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new _2020sw2compAudioProcessor();
}
