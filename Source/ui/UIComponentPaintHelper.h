#pragma once

#include <JuceHeader.h>

// Acts as a container class for the other UI components to be drawn and therefore only implements basic paint functionality.
class UIComponentPaintHelper : public juce::Component
{
public:
    UIComponentPaintHelper();
    ~UIComponentPaintHelper() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void setBackgroundColour(juce::Colour colour);

private:
    juce::Colour backgroundColour = juce::Colours::white;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIComponentPaintHelper)
};