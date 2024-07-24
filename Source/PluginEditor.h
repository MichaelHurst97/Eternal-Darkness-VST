#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ui/UICustomLookAndFeel.h"
#include "ui/UIControlsDspRack.h"
#include "ui/UIControlsPlugin.h"

class EternalDarknessAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    EternalDarknessAudioProcessorEditor (EternalDarknessAudioProcessor&);
    ~EternalDarknessAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    EternalDarknessAudioProcessor& audioProcessor;

    UIControlsDspRack uiControlsDspRack;
    UIControlsPlugin uiControlsPlugin;

    CustomLookAndFeel customLook;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EternalDarknessAudioProcessorEditor)
};
