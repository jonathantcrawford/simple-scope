/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SmallScopeAudioProcessor::SmallScopeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
:   AudioProcessor (BusesProperties().withInput ("Input",  AudioChannelSet::stereo(), true)
                                     .withOutput ("Output", AudioChannelSet::stereo(), true)), oscilloscopeWaveform (), parameters (*this, nullptr)

#endif
{
    //PARAMETER LIST
    //All parameters are created here
    parameters.createAndAddParameter ("hue",
                                      "Hue",
                                      String(),
                                      NormalisableRange<float> (0.22f, 1.22f),
                                      0.22f,
                                      nullptr,
                                      nullptr);
    
    parameters.createAndAddParameter ("fill",
                                      "Fill",
                                      String(),
                                      NormalisableRange<float> (0.0f, 0.3f),
                                      0.0f,
                                      nullptr,
                                      nullptr);
    
    parameters.createAndAddParameter ("decay",
                                      "Decay",
                                      String(),
                                      NormalisableRange<float> (1.0f, 128.0f),
                                      1.0f,
                                      nullptr,
                                      nullptr);
    
    parameters.createAndAddParameter ("xzoom",
                                      "xZoom",
                                      String(),
                                      NormalisableRange<float> (2.0f, 256.0f),
                                      2.0f,
                                      nullptr,
                                      nullptr);
    
    parameters.createAndAddParameter ("yzoom",
                                      "yZoom",
                                      String(),
                                      NormalisableRange<float> (1.0f, 3.0f), 1.0f,
                                      nullptr, nullptr);
    
    parameters.createAndAddParameter ("triggermode",
                                      "TriggerMode",
                                      String(),
                                      NormalisableRange<float> (0.1f, 1.0f), 0.15f,
                                      [](float value)
                                      {
                                          if (value >= 0.1f && value < 0.333f)
                                              return "Off";
                                          else if (value >= 0.333f && value < 0.666f)
                                              return "Up";
                                          else
                                              return "Down";
                                      },
                                      [](const String& text)
                                      {
                                          if (text == "Off")    return 0.15f;
                                          else if (text == "Up")  return 0.45f;
                                          else return 0.75f;
                                      });

    //Overall parameter list
    parameters.state = ValueTree (Identifier ("SmallScope"));
}

//==============================================================================
SmallScopeAudioProcessor::~SmallScopeAudioProcessor()
{
}

//==============================================================================
const String SmallScopeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

//==============================================================================
bool SmallScopeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

//==============================================================================
bool SmallScopeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

//==============================================================================
double SmallScopeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

//==============================================================================
int SmallScopeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

//==============================================================================
int SmallScopeAudioProcessor::getCurrentProgram()
{
    return 0;
}

//==============================================================================
void SmallScopeAudioProcessor::setCurrentProgram (int index)
{
}

//==============================================================================
const String SmallScopeAudioProcessor::getProgramName (int index)
{
    return String();
}

//==============================================================================
void SmallScopeAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SmallScopeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //RESET PARAMETERS
    //Initialise oscilloscope
    oscilloscopeWaveform.setTraceHue (*parameters.getRawParameterValue ("hue"));
    oscilloscopeWaveform.setPhosphorDecayFactor (*parameters.getRawParameterValue ("decay"));
    oscilloscopeWaveform.setWaveformFillFactor (*parameters.getRawParameterValue ("fill"));
    oscilloscopeWaveform.setNumSamplesPerPixel (*parameters.getRawParameterValue ("xzoom"));
    oscilloscopeWaveform.setVerticalZoomFactor (*parameters.getRawParameterValue ("yzoom"));
    oscilloscopeWaveform.setTriggerMode (*parameters.getRawParameterValue ("triggermode"));
}

//==============================================================================
void SmallScopeAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
//==============================================================================
bool SmallScopeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    /*
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
     */

    return true;
}
#endif

//==============================================================================
void SmallScopeAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (int i = totalNumInputChannels; i < (totalNumOutputChannels-1); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    //Channel data for 1st or left channel only
    const float* channelData = buffer.getWritePointer (0);
    oscilloscopeWaveform.addSamples (channelData, buffer.getNumSamples());
}

//==============================================================================
bool SmallScopeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

//==============================================================================
AudioProcessorEditor* SmallScopeAudioProcessor::createEditor()
{
    return new SmallScopeAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void SmallScopeAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    //Restore plugins proper state
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary (*xml, destData);
}

//==============================================================================
void SmallScopeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //Save plugin state through host
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState != nullptr){
        if (xmlState->hasTagName (parameters.state.getType())){
            parameters.state = ValueTree::fromXml (*xmlState);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SmallScopeAudioProcessor();
}

