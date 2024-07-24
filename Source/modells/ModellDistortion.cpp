/*
  ==============================================================================

    ModellDistortion.cpp
    Created: 13 Oct 2023 4:42:22pm
    Author:  Michael

  ==============================================================================
*/

#include "ModellDistortion.h"

ModellDistortion::ModellDistortion()
{
    functionToUse = [](float x)
    {
        //return juce::jlimit(float(-0.1), float(0.1), x);

        //return std::tanh(2*x);

        //return (2.0f / juce::MathConstants<float>::pi) * std::atan(x);

        //return ((x * (std::abs(x) + 0.9f)) * 1.5f / (x * x + (0.3f) * (0.1f / std::abs(x)) + 1.0f)) * 0.75f;
        
        //return (x / (std::abs(x) + 1)) * 1.3f;

        if (x > 0.0f && x > 0.75f)
            return 0.75f;
        else if (x < 0.0f && x < -0.75f)
            return -0.75f;
        else
            return x;
    };

    dryWet = 0.5f;
    mixer.setMixingRule(juce::dsp::DryWetMixingRule::linear);
}

void ModellDistortion::prepareToPlay(juce::dsp::ProcessSpec spec)
{
    preGain.reset();
    mixer.reset();
    reset();

    preGain.prepare(spec);
    mixer.prepare(spec);
    prepare(spec);
}

void ModellDistortion::renderNextBlock(juce::AudioBuffer<float>& outputBuffer)
{
    juce::dsp::AudioBlock<float> dspAudioBlock{ outputBuffer };

    mixer.setWetMixProportion(dryWet);
    mixer.pushDrySamples(dspAudioBlock);

    preGain.process(juce::dsp::ProcessContextReplacing<float>(dspAudioBlock));
    process(juce::dsp::ProcessContextReplacing<float>(dspAudioBlock));

    mixer.mixWetSamples(dspAudioBlock);
}

void ModellDistortion::updateParameters(float drive, float dryWetIn)
{
    preGain.setGainLinear(drive);

    dryWet = dryWetIn;
}