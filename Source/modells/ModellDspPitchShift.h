/*
  ==============================================================================

    ModellDSPPitchShift.h
    Created: 14 Oct 2023 5:35:34pm
    Author:  Michael

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../signalsmith-stretch/signalsmith-stretch.h"

class ModellDSPPitchShift
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec spec);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer);
    void updateParameters(float semitones);

private:
    signalsmith::stretch::SignalsmithStretch<float> stretch;
};