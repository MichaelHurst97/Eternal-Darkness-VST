#include <JuceHeader.h>
#include "UIComponentSlider.h"

UIComponentSlider::UIComponentSlider(juce::AudioProcessorValueTreeState& apvts, juce::String parameterID,
    juce::String labelID, juce::String labelText, juce::String labelType, juce::String fontHeightID,
    float fontHeight, double doubleClickValue)
{
    // Add parameter attachments
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);

    // Set Basic Slider attributes
    slider.setComponentID(labelID);
    slider.getProperties().set(slider.getComponentID(), labelText);
    slider.getProperties().set("labelType", labelType);
    slider.setComponentID(fontHeightID);
    slider.getProperties().set(slider.getComponentID(), fontHeight);
    slider.setDoubleClickReturnValue(true, doubleClickValue);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

    addAndMakeVisible(slider);
}

void UIComponentSlider::resized()
{
    slider.setBounds(0, 0, sliderBoundsWidth, sliderBoundsHeight);
}

// Gets called from parent that uses this class. Executed in parents resized function.
// Resizing the parent doesnt resize the slider automatically, so this workaround exists
void UIComponentSlider::updateBounds(int newSliderBoundsWidth, int newSliderBoundsHeight)
{
    sliderBoundsWidth = newSliderBoundsWidth;
    sliderBoundsHeight = newSliderBoundsHeight;
    resized();
}
