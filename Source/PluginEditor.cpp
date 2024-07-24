#include "PluginProcessor.h"
#include "PluginEditor.h"

EternalDarknessAudioProcessorEditor::EternalDarknessAudioProcessorEditor (EternalDarknessAudioProcessor& p)
    : AudioProcessorEditor (&p),
    audioProcessor (p),
    uiControlsDspRack(audioProcessor.apvts),
    uiControlsPlugin(audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setResizable(true, false);
    setSize(200, 600);
    setResizeLimits(200, 540, 300, 810);
    getConstrainer()->setFixedAspectRatio(0.370370);
    juce::Desktop::getInstance().setGlobalScaleFactor(1.25);

    addAndMakeVisible(uiControlsDspRack);
    addAndMakeVisible(uiControlsPlugin);
}

EternalDarknessAudioProcessorEditor::~EternalDarknessAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void EternalDarknessAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillRect(0, 0, getWidth(), getHeight());
}

void EternalDarknessAudioProcessorEditor::resized()
{
    auto width = getWidth();
    auto height = getHeight();
    auto spacing = getWidth() / 20;

    uiControlsDspRack.setBounds(spacing, spacing,
        width - spacing * 2, ((height / 10) * 8.5));

    uiControlsPlugin.setBounds(spacing, uiControlsDspRack.getBottom() +  spacing * 2,
        width - spacing * 2, height - uiControlsDspRack.getBottom() + (int)spacing * 2.5f);
}
