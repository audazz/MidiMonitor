/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class MidiMonitorAudioProcessorEditor  : public AudioProcessorEditor,
 private Slider::Listener, public Timer
{
public:
    MidiMonitorAudioProcessorEditor (MidiMonitorAudioProcessor&);
    ~MidiMonitorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
private:
    void sliderValueChanged (Slider* slider) override;
private:
    Slider midiVolume;
    juce::StringArray messages;
    MidiMonitorAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiMonitorAudioProcessorEditor)
};
