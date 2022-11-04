/*
  ==============================================================================

    SynthVoice.h
    Created: 4 Nov 2022 10:52:24am
    Author:  Masaki Nabeshima

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"


class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved(int controlelrNumber, int newControllerValue) override;
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    
private:
    juce::dsp::Oscillator<float> osc {[](float x) {return x / juce::MathConstants<float >::pi; }};
    juce::dsp::Gain<float> gain;
    bool isPrepared { false };
    
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
};
