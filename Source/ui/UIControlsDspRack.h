#pragma once

#include <JuceHeader.h>
#include "UIComponentPainthelper.h"
#include "UIComponentSlider.h"

class UIControlsDspRack : public UIComponentPaintHelper
{
public:
    UIControlsDspRack(juce::AudioProcessorValueTreeState& apvts);
    ~UIControlsDspRack() override;

    void resized() override;

private:
    UIComponentSlider sliderRev1Size, sliderRev1DW, sliderPitch, 
        sliderRev2Size, sliderRev2DW, sliderDistDrive, sliderDistDW, 
        sliderFilter, sliderRev3Size, sliderRev3DW;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIControlsDspRack)
};