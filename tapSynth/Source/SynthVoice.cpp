/*
  ==============================================================================

    SynthVoice.cpp
    Created: 4 Nov 2022 10:52:24am
    Author:  Masaki Nabeshima

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) {
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
    
}
void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) {
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
    
}
void SynthVoice::stopNote (float velocity, bool allowTailOff) {
    adsr.noteOff();
}
void SynthVoice::controllerMoved(int controlelrNumber, int newControllerValue) {
}
void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
//    jassert (isPrepared);
    
    juce::dsp::AudioBlock<float> audioBlock {outputBuffer};
    osc.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}
void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {
     
};

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outpuChannels) {
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outpuChannels;
    
    osc.prepare(spec);
    gain.prepare(spec);
    
    
    gain.setGainLinear(0.01f);
    
    isPrepared = true;
}
