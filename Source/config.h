/*
  ==============================================================================

    config.h
    Created: 1 Aug 2022 3:55:45pm
    Author:  Kevin Kopczynski

  ==============================================================================
*/

#pragma once


namespace kkaudio
{
    using SIMD = juce::FloatVectorOperations;
    using APVTS = juce::AudioProcessorValueTreeState;

    enum ClipModes
    {
        clipChoice,
        foldChoice,
        wrapChoice
    };
}
