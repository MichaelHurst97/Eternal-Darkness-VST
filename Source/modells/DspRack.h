/*
  ==============================================================================

    DSPRack.h
    Created: 24 Oct 2023 3:16:37pm
    Author:  Michael

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ModellReverb.h"
#include "ModellDistortion.h"
#include "ModellLPFilter.h"
#include "ModellDSPPitchShift.h"


class DspRack {

public:
    void prepareToPlay(juce::dsp::ProcessSpec spec);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer);
    void updateParameters(float r1wetLevelIn, float r1roomSizeIn, float pSemitonesIn,
        float r2wetLevelIn, float r2roomSizeIn, float dDriveIn, float dDryWetIn, 
        float lpfCutoffIn, float r3wetLevelIn, float r3roomSizeIn);

private:

    ModellReverb reverb1;
    ModellReverb reverb2;
    ModellReverb reverb3;

    ModellDistortion dist;

    ModellLPFilter lpf;

    ModellDSPPitchShift pitcher;

    float r1wetLevel, r1roomSize, pSemitones, r2wetLevel,
        r2roomSize, dDrive, dDryWet, lpfCutoff, r3wetLevel, r3roomSize;
};