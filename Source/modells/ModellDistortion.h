/*
  ==============================================================================

    ModellDistortion.h
    Created: 13 Oct 2023 4:42:22pm
    Author:  Michael

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ModellDistortion : public juce::dsp::WaveShaper<float>
{
public:
    ModellDistortion();

    void prepareToPlay(juce::dsp::ProcessSpec spec);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer);
    void updateParameters(float drive, float dryWetIn);

private:
    juce::dsp::Gain<float> preGain;

    juce::dsp::DryWetMixer<float> mixer;
    float dryWet;
};