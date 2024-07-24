/*
  ==============================================================================

    ModellLPFilter.h
    Created: 13 Oct 2023 4:41:42pm
    Author:  Michael

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ModellLPFilter
{
public:
    ModellLPFilter();

    void prepare(juce::dsp::ProcessSpec spec);
    void process(juce::dsp::AudioBlock<float> dspAudioBlock);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer);
    void updateParameters(const float frequency);
    void reset();

private:
    std::array<juce::dsp::StateVariableTPTFilter<float>, 3> filters =
    {
        juce::dsp::StateVariableTPTFilter<float>(), // filterLP1
        juce::dsp::StateVariableTPTFilter<float>(), // filterLP2
        juce::dsp::StateVariableTPTFilter<float>()  // filterLP3
    };
};