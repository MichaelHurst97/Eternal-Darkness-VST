#pragma once

#include <JuceHeader.h>

// Plugin Name and Noise Type Selector Panel for UI
class UIControlsPlugin : public juce::Component
{
public:
    UIControlsPlugin(juce::AudioProcessorValueTreeState& apvts);
    ~UIControlsPlugin() override;

    void resized() override;

private:
    juce::Label titleLabel;
    juce::Label subtitleLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIControlsPlugin)
};