/*
  ==============================================================================

    Params.h
    Created: 1 Aug 2022 5:37:40pm
    Author:  Kevin Kopczynski

  ==============================================================================
*/

#pragma once

using namespace kkaudio;

struct ChainSettings
{
    float drive             { 0 };
    int bitDepth            { 0 };
    int downsampleRate      { 0 };
    ClipModes clipMode      { ClipModes::clipChoice };
};

ChainSettings getChainSettings(APVTS& apvts)
{
    ChainSettings settings;
    
    settings.drive = apvts.getRawParameterValue("Drive")->load();
    settings.bitDepth = apvts.getRawParameterValue("Bit Depth")->load();
    settings.downsampleRate = apvts.getRawParameterValue("Downsample Rate")->load();
    settings.clipMode = static_cast<ClipModes>(apvts.getRawParameterValue("Clip Mode")->load());
    
    return settings;
}

static APVTS::ParameterLayout createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    auto pDrive = std::make_unique<juce::AudioParameterFloat>
        (juce::ParameterID("Drive", 1), "Drive", 0.f , 10.f, 1.f);
    auto pBitDepth = std::make_unique<juce::AudioParameterInt>
        (juce::ParameterID("Bit Depth", 1), "Bit Depth", 1, 24, 8);
    auto pDownsampleRate = std::make_unique<juce::AudioParameterInt>
        (juce::ParameterID("Downsample Rate", 1), "Downsample Rate", 1, 40, 1);
    
    juce::StringArray sArray = {"Clip", "Fold", "Wrap"};
    
    auto pClipMode = std::make_unique<juce::AudioParameterChoice>
        (juce::ParameterID("Clip Mode", 1), "Clip Mode", sArray, 0);
    
    params.push_back(std::move(pDrive));
    params.push_back(std::move(pBitDepth));
    params.push_back(std::move(pDownsampleRate));
    params.push_back(std::move(pClipMode));
    
    return { params.begin(), params.end() };
}
