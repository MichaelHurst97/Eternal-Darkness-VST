/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EternalDarknessAudioProcessor::EternalDarknessAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    apvts(*this, nullptr, juce::Identifier("apvts"), createParameterLayout())
#endif
{
}

EternalDarknessAudioProcessor::~EternalDarknessAudioProcessor()
{
}

//==============================================================================
const juce::String EternalDarknessAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EternalDarknessAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EternalDarknessAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EternalDarknessAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EternalDarknessAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EternalDarknessAudioProcessor::getNumPrograms()
{
    return 1;
               
}

int EternalDarknessAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EternalDarknessAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EternalDarknessAudioProcessor::getProgramName (int index)
{
    return {};
}

void EternalDarknessAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EternalDarknessAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::String message;
    message << "Preparing to play audio...\n";
    message << " samplesPerBlock = " << samplesPerBlock << "\n";
    message << " sampleRate = " << sampleRate << "\n";
    message << "in channels = " << getNumInputChannels();
    juce::Logger::getCurrentLogger()->writeToLog(message);

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32> (samplesPerBlock);
    spec.numChannels = static_cast<juce::uint32> (getTotalNumOutputChannels());

    dspRack.prepareToPlay(spec);
}

void EternalDarknessAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EternalDarknessAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannelSet() == juce::AudioChannelSet::disabled()
        || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::disabled())
        return false;

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}
#endif

void EternalDarknessAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    auto& r1wetLevel = *apvts.getRawParameterValue("r1wetLevel");
    auto& r1roomSize = *apvts.getRawParameterValue("r1roomSize");
    auto& pSemitones = *apvts.getRawParameterValue("p1semitones");
    auto& r2wetLevel = *apvts.getRawParameterValue("r2wetLevel");
    auto& r2roomSize = *apvts.getRawParameterValue("r2roomSize");
    auto& dDrive = *apvts.getRawParameterValue("d1drive");
    auto& dDryWet = *apvts.getRawParameterValue("d1dryWet");
    auto& lpfCutoff = *apvts.getRawParameterValue("f1cutoff");
    auto& r3wetLevel = *apvts.getRawParameterValue("r3wetLevel");
    auto& r3roomSize = *apvts.getRawParameterValue("r3roomSize");

    dspRack.updateParameters(r1wetLevel, r1roomSize, pSemitones, r2wetLevel, r2roomSize,
        dDrive, dDryWet, lpfCutoff, r3wetLevel, r3roomSize);
    dspRack.renderNextBlock(buffer);

    auto numSamples = buffer.getNumSamples();
    auto numChannels = buffer.getNumChannels();
}

void EternalDarknessAudioProcessor::processBlockBypassed(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    // Free up audio buffer
    buffer.clear();
}

//==============================================================================
bool EternalDarknessAudioProcessor::hasEditor() const
{
    return true; 
}

juce::AudioProcessorEditor* EternalDarknessAudioProcessor::createEditor()
{
    return new EternalDarknessAudioProcessorEditor (*this);
}

//==============================================================================
void EternalDarknessAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void EternalDarknessAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessorValueTreeState::ParameterLayout EternalDarknessAudioProcessor::createParameterLayout()
{
    // Vector of Pointers of all Parameters in the plugin
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    // Reverb 1
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("r1wetLevel", "Reverb 1 Wet Level",
        juce::NormalisableRange<float>(0.0f, 0.5f, 0.01f), 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("r1roomSize", "Reverb 1 Room Size",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f));

    // Pitch Shifter
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("p1semitones", "Pitch Semitones",
        juce::NormalisableRange<float>(-12.0f, 12.0f, 1.0f), -12.0f));

    // Reverb 2
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("r2wetLevel", "Reverb 2 Wet Level",
        juce::NormalisableRange<float>(0.0f, 0.5f, 0.01f), 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("r2roomSize", "Reverb 2 Room Size",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f));

    // Distortion
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("d1drive", "Distortion Drive",
        juce::NormalisableRange<float>(0.0f, 10.0f, 0.001f), 1.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("d1dryWet", "Distortion Dry / Wet",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f), 0.5f));

    // Filter
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("f1cutoff", "LP Filter Cutoff",
        juce::NormalisableRange<float>(20.0f, 22000.0f, 1.0f, 0.3f), 2000.0f));

    // Reverb 3
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("r3wetLevel", "Reverb 3 Wet Level",
        juce::NormalisableRange<float>(0.0f, 0.5f, 0.01f), 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("r3roomSize", "Reverb 3 Room Size",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f));

    return { parameters.begin(), parameters.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EternalDarknessAudioProcessor();
}
