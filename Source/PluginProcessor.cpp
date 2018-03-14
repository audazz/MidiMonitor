/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MidiMonitorAudioProcessor::MidiMonitorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

MidiMonitorAudioProcessor::~MidiMonitorAudioProcessor()
{
}

//==============================================================================
const String MidiMonitorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiMonitorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiMonitorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidiMonitorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidiMonitorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiMonitorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidiMonitorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidiMonitorAudioProcessor::setCurrentProgram (int index)
{
}

const String MidiMonitorAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidiMonitorAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MidiMonitorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
     midiCollector.reset (sampleRate);
}

void MidiMonitorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiMonitorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MidiMonitorAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
     buffer.clear();
     
    MidiBuffer processedMidi;
    int time;
    MidiMessage m;
 
    
    
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        midiMessagesToStringArray(m );
        //midiCollector.addMessageToQueue (message); //not used
    }
    
    //midiMessages.swapWith (processedMidi); // not used
}

//==============================================================================
bool MidiMonitorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MidiMonitorAudioProcessor::createEditor()
{
    return new MidiMonitorAudioProcessorEditor (*this);
}

//==============================================================================
void MidiMonitorAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidiMonitorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void MidiMonitorAudioProcessor::midiMessagesToStringArray(const MidiMessage& message )
{
	String receivedMessage = " Channel: " + String( message.getChannel() ) + ", ";

	if ( message.isController() )
		receivedMessage += "CC: " + String( message.getControllerNumber() ) + ", Value: " + String( message.getControllerValue() );

	else if ( message.isNoteOn() )
		receivedMessage += "Note On: " + String( message.getNoteNumber() ) + ", Value: " + String( message.getVelocity() );

	else if ( message.isNoteOff() )
		receivedMessage += "Note Off: " + String( message.getNoteNumber() ) + ", Value: " + String( message.getVelocity() );

	messages.insert ( 0, receivedMessage );
	
	int maxLength = 15;
	if ( messages.size() > maxLength )
		messages.removeRange( maxLength, messages.size() - maxLength );
	
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiMonitorAudioProcessor();
}
