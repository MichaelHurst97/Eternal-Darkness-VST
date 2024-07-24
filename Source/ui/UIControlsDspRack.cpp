/*
  ==============================================================================

    UIControlsDspRack.cpp
    Created: 1 Jun 2024 5:11:05pm
    Author:  Michael

  ==============================================================================
*/

#include "UIControlsDspRack.h"

UIControlsDspRack::UIControlsDspRack(juce::AudioProcessorValueTreeState& apvts)
    : sliderRev1Size(apvts, "r1roomSize", "labelText", "REV SIZE", "typeNone", "fontHeight", 13.0f, 0.5f),
    sliderRev1DW(apvts, "r1wetLevel", "labelText", "WET LEVEL", "typeSimpleHalved", "fontHeight", 11.5f, 0.5f),
    sliderPitch(apvts, "p1semitones", "labelText", "PITCH", "typeSemitones", "fontHeight", 13.0f, -12.0f),
    sliderRev2Size(apvts, "r2roomSize", "labelText", "REV SIZE", "typeNone", "fontHeight", 13.0f, 0.5f),
    sliderRev2DW(apvts, "r2wetLevel", "labelText", "WET LEVEL", "typeSimpleHalved", "fontHeight", 11.5f, 0.5f),
    sliderDistDrive(apvts, "d1drive", "labelText", "DRIVE", "typeNone", "fontHeight", 13.0f, 1.5f),
    sliderDistDW(apvts, "d1dryWet", "labelText", "DRY/WET", "typeSimple", "fontHeight", 11.5f, 0.5f),
    sliderFilter(apvts, "f1cutoff", "labelText", "FILTER", "typeFilter", "fontHeight", 13.0f, 2000.0f),
    sliderRev3Size(apvts, "r3roomSize", "labelText", "REV SIZE", "typeNone", "fontHeight", 13.0f, 0.5f),
    sliderRev3DW(apvts, "r3wetLevel", "labelText", "WET LEVEL", "typeSimpleHalved", "fontHeight", 11.5f, 0.5f)
{
    // Background Colour of the panel
    setBackgroundColour(juce::Colour(0.0f, 0.0f, 0.95f, 0.0f));

    addAndMakeVisible(sliderRev1Size);
    addAndMakeVisible(sliderRev1DW);
    addAndMakeVisible(sliderPitch);
    addAndMakeVisible(sliderRev2Size);
    addAndMakeVisible(sliderRev2DW);
    addAndMakeVisible(sliderDistDrive);
    addAndMakeVisible(sliderDistDW);
    addAndMakeVisible(sliderFilter);
    addAndMakeVisible(sliderRev3Size);
    addAndMakeVisible(sliderRev3DW);
}

UIControlsDspRack::~UIControlsDspRack()
{
}

void UIControlsDspRack::resized()
{
    auto width = getWidth();
    auto height = getHeight();

    // Scale off parents bounds
    int sliderBoundsWidth = (int)(width * 0.5);
    int sliderBoundsHeight = (int)(height * 0.1428);
    auto widthOffsetCurrent = 0;
    auto heightOffsetCurrent = (height  / 6) / 7;

    // Initial bounds setting
    sliderRev1Size.setBounds(widthOffsetCurrent, heightOffsetCurrent,
        sliderBoundsWidth, sliderBoundsHeight);
    sliderRev1DW.setBounds(widthOffsetCurrent * 2 + sliderBoundsWidth, heightOffsetCurrent,
        sliderBoundsWidth, sliderBoundsHeight);

    sliderPitch.setBounds(widthOffsetCurrent, sliderRev1Size.getBottom() + heightOffsetCurrent,
        sliderBoundsWidth, sliderBoundsHeight);

    sliderRev2Size.setBounds(widthOffsetCurrent, sliderPitch.getBottom() + heightOffsetCurrent,
        sliderBoundsWidth, sliderBoundsHeight);
    sliderRev2DW.setBounds(widthOffsetCurrent * 2 + sliderBoundsWidth, sliderPitch.getBottom() + heightOffsetCurrent,
        sliderBoundsWidth, sliderBoundsHeight);

    sliderDistDrive.setBounds(widthOffsetCurrent, sliderRev2DW.getBottom() + heightOffsetCurrent,
        sliderBoundsWidth, sliderBoundsHeight);
    sliderDistDW.setBounds(widthOffsetCurrent * 2 + sliderBoundsWidth, sliderRev2DW.getBottom() + heightOffsetCurrent,
        sliderBoundsWidth, sliderBoundsHeight);

    sliderFilter.setBounds(widthOffsetCurrent, sliderDistDW.getBottom() + heightOffsetCurrent,
        sliderBoundsWidth, sliderBoundsHeight);

    sliderRev3Size.setBounds(widthOffsetCurrent, sliderFilter.getBottom() + heightOffsetCurrent,
        sliderBoundsWidth, sliderBoundsHeight);
    sliderRev3DW.setBounds(widthOffsetCurrent * 2 + sliderBoundsWidth, sliderFilter.getBottom() + heightOffsetCurrent,
        sliderBoundsWidth, sliderBoundsHeight);


    // Need to call this, because resized() by slider object doesnt get called automatically when parent resizes,
    // also new bounds relative to parent object must be passed, so we scale off this objects width and height
    sliderRev1Size.updateBounds(sliderBoundsWidth, sliderBoundsHeight);
    sliderRev1DW.updateBounds(sliderBoundsWidth, sliderBoundsHeight);
    sliderPitch.updateBounds(sliderBoundsWidth, sliderBoundsHeight);
    sliderRev2Size.updateBounds(sliderBoundsWidth, sliderBoundsHeight);
    sliderRev2DW.updateBounds(sliderBoundsWidth, sliderBoundsHeight);
    sliderDistDrive.updateBounds(sliderBoundsWidth, sliderBoundsHeight);
    sliderDistDW.updateBounds(sliderBoundsWidth, sliderBoundsHeight);
    sliderFilter.updateBounds(sliderBoundsWidth, sliderBoundsHeight);
    sliderRev3Size.updateBounds(sliderBoundsWidth, sliderBoundsHeight);
    sliderRev3DW.updateBounds(sliderBoundsWidth, sliderBoundsHeight);
}