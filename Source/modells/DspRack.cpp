/*
  ==============================================================================

    DSPRack.cpp
    Created: 24 Oct 2023 3:16:37pm
    Author:  Michael

  ==============================================================================
*/

#include "DspRack.h"

void DspRack::prepareToPlay(juce::dsp::ProcessSpec spec)
{
    reverb1.prepareToPlay(spec);
    pitcher.prepareToPlay(spec);

    reverb2.prepareToPlay(spec);
    dist.prepareToPlay(spec);
    lpf.prepare(spec);

    reverb3.prepareToPlay(spec);
}

void DspRack::renderNextBlock(juce::AudioBuffer<float>& outputBuffer)
{
    reverb1.updateParameters(r1wetLevel, 0.8f, r1roomSize, 0.8f, 0.5f, false, 2200.0f);
    reverb1.renderNextBlock(outputBuffer);

    pitcher.updateParameters(pSemitones);
    pitcher.renderNextBlock(outputBuffer);

    reverb2.updateParameters(r2wetLevel, 0.0f, r2roomSize, 0.8f, 0.5f, false, 2100.0f);
    reverb2.renderNextBlock(outputBuffer);

    dist.updateParameters(dDrive, dDryWet);
    dist.renderNextBlock(outputBuffer);

    lpf.updateParameters(lpfCutoff);
    lpf.renderNextBlock(outputBuffer);

    reverb3.updateParameters(r3wetLevel, 0.0f, r3roomSize, 0.5f, 0.5f, false, 2100.0f);
    reverb3.renderNextBlock(outputBuffer);
}

void DspRack::updateParameters(float r1wetLevelIn, float r1roomSizeIn, float pSemitonesIn,
    float r2wetLevelIn, float r2roomSizeIn, float dDriveIn, float dDryWetIn, float lpfCutoffIn,
    float r3wetLevelIn, float r3roomSizeIn)
{
    r1wetLevel = r1wetLevelIn;
    r1roomSize = r1roomSizeIn;
    pSemitones = pSemitonesIn;
    r2wetLevel = r2wetLevelIn;
    r2roomSize = r2roomSizeIn;
    dDrive = dDriveIn;
    dDryWet = dDryWetIn;
    lpfCutoff = lpfCutoffIn;
    r3wetLevel = r3wetLevelIn;
    r3roomSize = r3roomSizeIn;
}