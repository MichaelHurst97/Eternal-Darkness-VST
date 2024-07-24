/*
  ==============================================================================

    ModellReverb.h
    Created: 13 Oct 2023 7:44:35pm
    Author:  Michael

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModellLPFilter.h"

class ModellReverb
{
public:
    ModellReverb();

    void prepareToPlay(juce::dsp::ProcessSpec spec);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer);

    void updateParameters(float wetLevel, float dryLevel, float roomSize, float damping, float width, 
        bool freezeMode, float lpf);

private:
    juce::dsp::Reverb::Parameters parameters;
    juce::dsp::Reverb reverb;

    ModellLPFilter filter;

    juce::dsp::DryWetMixer<float> mixer;
    float dryWet;
};