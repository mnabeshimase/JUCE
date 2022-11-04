/*
  ==============================================================================

    SynthSound.h
    Created: 4 Nov 2022 10:53:07am
    Author:  Masaki Nabeshima

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override {return true;}
    bool appliesToChannel (int midiChannel) override {return true;}
};
