#pragma once

#include <JuceHeader.h>

// Creates a slider and does some basic style changes to it in one go
class UIComponentSlider : public juce::Component
{
public:
    UIComponentSlider(juce::AudioProcessorValueTreeState& apvts, juce::String parameterID, juce::String labelID, juce::String labelText, juce::String labelType,
        juce::String fontHeightID, float fontHeight, double doubleClickValue);

    void resized() override;

    void updateBounds(int newSliderBoundsWidth, int newSldierBoundsHeight);

    juce::Slider slider;

private:
    int sliderBoundsWidth;
    int sliderBoundsHeight;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIComponentSlider)
};