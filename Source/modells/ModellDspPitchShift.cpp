/*
  ==============================================================================

    ModellDSPPitchShift.cpp
    Created: 14 Oct 2023 5:35:34pm
    Author:  Michael

  ==============================================================================
*/

#include "ModellDspPitchShift.h"

void ModellDSPPitchShift::prepareToPlay(juce::dsp::ProcessSpec spec)
{
    stretch.presetDefault(spec.numChannels, spec.sampleRate);
}

void ModellDSPPitchShift::renderNextBlock(juce::AudioBuffer<float>& outputBuffer)
{
    auto numChannels = outputBuffer.getNumChannels();
    auto numSamples = outputBuffer.getNumSamples();

    juce::AudioBuffer<float> tempBuffer;
    tempBuffer.makeCopyOf(outputBuffer);

    float* inData[2] = { tempBuffer.getWritePointer(0), tempBuffer.getWritePointer(1) };
    float* outData[2] = { outputBuffer.getWritePointer(0), outputBuffer.getWritePointer(1) };

    stretch.process(inData, numSamples, outData, numSamples);
}

void ModellDSPPitchShift::updateParameters(float semitones)
{
    stretch.setTransposeSemitones(semitones);
}