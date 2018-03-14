/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MidiMonitorAudioProcessorEditor::MidiMonitorAudioProcessorEditor (MidiMonitorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    startTimerHz( 30 );
}

MidiMonitorAudioProcessorEditor::~MidiMonitorAudioProcessorEditor()
{
}

//==============================================================================
void MidiMonitorAudioProcessorEditor::paint (Graphics& g)
{
   g.fillAll( Colour( 0xff001F36 ) );

	g.setColour( Colours::whitesmoke );
    g.setFont (15.0f);
 
    auto messages = processor.getMidiMessageArray();
    g.drawRect(10,50,getWidth() - 20, 20);
    for ( int i = 0; i < messages.size(); i++ )
		g.drawText( messages[i], 10, 50 + i * 20, getWidth() - 20, 20, Justification::Flags::centredLeft, true );
}

void MidiMonitorAudioProcessorEditor::resized()
{
     
}

void MidiMonitorAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
   
}

void MidiMonitorAudioProcessorEditor::timerCallback()
{
	const MessageManagerLock lock;
	repaint();
}
