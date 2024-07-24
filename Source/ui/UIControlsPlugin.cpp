#include "UIControlsPlugin.h"

UIControlsPlugin::UIControlsPlugin(juce::AudioProcessorValueTreeState& apvts)
{
    // Plugin Title Text
    titleLabel.setText("ETERNAL DARKNESS", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    titleLabel.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    titleLabel.setColour(juce::Label::outlineColourId, juce::Colours::black);
    titleLabel.setColour(juce::Label::textColourId, juce::Colours::red);
    titleLabel.setFont(juce::Font(20.0f, juce::Font::bold));
    addAndMakeVisible(titleLabel);

    // Plugin Subtitle Text
    subtitleLabel.setText("DISTORTED AND SHIFTED REVERBERATION", juce::dontSendNotification);
    subtitleLabel.setJustificationType(juce::Justification::centred);
    subtitleLabel.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    subtitleLabel.setColour(juce::Label::outlineColourId, juce::Colours::black);
    subtitleLabel.setColour(juce::Label::textColourId, juce::Colours::red);
    subtitleLabel.setFont(juce::Font(8.0f, juce::Font::bold));
    addAndMakeVisible(subtitleLabel);
}

UIControlsPlugin::~UIControlsPlugin()
{
}

void UIControlsPlugin::resized()
{
    auto width = getWidth();
    auto height = getHeight() / 3.5;


    titleLabel.setBounds(0, 0,
        width, height);

    subtitleLabel.setBounds(0, titleLabel.getBottom(),
        width, height / 3);
}