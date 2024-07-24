#include <JuceHeader.h>
#include "UIComponentPaintHelper.h"

UIComponentPaintHelper::UIComponentPaintHelper()
{
}

UIComponentPaintHelper::~UIComponentPaintHelper()
{
}

void UIComponentPaintHelper::paint(juce::Graphics& g)
{
    // Background
    g.setColour(juce::Colour(1.0f, 1.0f, 0.2f, 1.0f));
    g.fillRect(getLocalBounds().toFloat());

    auto width = getWidth();
    auto height = getHeight();

    // Scale off parents bounds
    int sliderBoundsWidth = (int)(width);
    int sliderBoundsHeight = (int)(height * 0.1428);
    auto widthOffsetCurrent = 0;
    auto heightOffsetCurrent = ((height / 6) / 7) / 2;

    // Vectors for graphics objects
    std::vector<juce::Rectangle<int>> rectangles;
    std::vector<juce::Colour> opaques;
    std::vector<juce::Colour> opaqueBlacks;

    // Initialize colors
    opaques.emplace_back(1.0f, 1.0f, 0.4f, 0.5f);
    opaqueBlacks.emplace_back(0.0f, 0.0f, 0.0f, 0.15f);

    for (int i = 1; i < 6; ++i) {
        opaques.emplace_back(1.0f, 1.0f, 0.4f, 0.5f);
        opaqueBlacks.emplace_back(0.0f, 0.0f, 0.0f, 0.15f + i * 0.15f);
    }

    // Initialize rectangles
    rectangles.emplace_back(widthOffsetCurrent, heightOffsetCurrent,
        sliderBoundsWidth, sliderBoundsHeight + heightOffsetCurrent * 2);

    for (int i = 1; i < 6; ++i) {
        rectangles.emplace_back(widthOffsetCurrent, rectangles[i - 1].getBottom(),
            sliderBoundsWidth, sliderBoundsHeight + heightOffsetCurrent * 2);
    }

    // Draw gradients
    for (int i = 0; i < 6; ++i) {
        juce::ColourGradient gradient(opaques[i], rectangles[i].getTopLeft().getX(), rectangles[i].getTopLeft().getY(),
            opaqueBlacks[i], rectangles[i].getBottomLeft().getX(), rectangles[i].getBottomLeft().getY(),
            false);
        g.setGradientFill(gradient);
        g.fillRect(rectangles[i]);
    }


    // Top Gradient
    auto opaqueTop = juce::Colour(0.0f, 0.0f, 0.0f, 0.1f);
    juce::ColourGradient gradientTop(opaqueTop, 0, 0,
        juce::Colours::black, getWidth(), getHeight(),
        false);
    g.setGradientFill(gradientTop);
    g.fillRect(0, 0, getWidth(), getHeight());

    // Border
    g.setColour(juce::Colours::black);
    auto border = getLocalBounds().toFloat();
    border.expand(1.0f, 1.0f);
    g.drawRect(border, 5.0f);
}

void UIComponentPaintHelper::resized()
{
}

// Used if the panel that inherits from this class should be differently coloured
void UIComponentPaintHelper::setBackgroundColour(juce::Colour colour)
{
    backgroundColour = colour;
}