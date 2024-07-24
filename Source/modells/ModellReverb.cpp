/*
  ==============================================================================

    ModellReverb.cpp
    Created: 13 Oct 2023 7:44:35pm
    Author:  Michael

  ==============================================================================
*/

#include "ModellReverb.h"

ModellReverb::ModellReverb()
{
    dryWet = 0.5f;
    mixer.setMixingRule(juce::dsp::DryWetMixingRule::balanced);
}

void ModellReverb::prepareToPlay(juce::dsp::ProcessSpec spec)
{
    reverb.reset();
    mixer.reset();

    filter.prepare(spec);
    reverb.prepare(spec);
    mixer.prepare(spec);
}

void ModellReverb::renderNextBlock(juce::AudioBuffer<float>& outputBuffer)
{
    juce::dsp::AudioBlock<float> dspAudioBlock{ outputBuffer };
    
    mixer.setWetMixProportion(dryWet);
    mixer.pushDrySamples(dspAudioBlock);

    reverb.process(juce::dsp::ProcessContextReplacing<float>(dspAudioBlock));
    filter.process(dspAudioBlock);

    mixer.mixWetSamples(dspAudioBlock);
}

void ModellReverb::updateParameters(float dryWetIn, float dryLevel, float roomSize, float damping,
                                       float width, bool freezeMode, float lpf)
{
    dryWet = dryWetIn;

    parameters.wetLevel = 1.0f;
    parameters.dryLevel = 0.0f;
    parameters.roomSize = roomSize;
    parameters.damping = damping;
    parameters.width = width;
    parameters.freezeMode = freezeMode;

    reverb.setParameters(parameters);

    filter.updateParameters(lpf);
}