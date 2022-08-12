/*
  ==============================================================================

    Bitcrusher.h
    Created: 1 Aug 2022 3:40:45pm
    Author:  Kevin Kopczynski

  ==============================================================================
*/

#pragma once
#include "Waveshapers.h"

namespace kkaudio
{
    class Bitcrusher
    {
    public:
        Bitcrusher()
        {
            sOut = 0;
        }
        
        ~Bitcrusher() {}
        
        void prepare (double _sampleRate, int _blockSize, int _numChannels)
        {
            sampleRate = _sampleRate;
            blockSize = _blockSize;
            numChannels = _numChannels;
        }
        
        void setParams (int _bitDepth, int _downsampleRate, float _drive, size_t _clipMode)
        {
            bitDepth = pow(2, _bitDepth);
            downsampleRate = _downsampleRate;
            drive = _drive;
            clipMode = _clipMode;
        }
        
        void process (float* samples)
        {
            /* scale incoming samples by drive */
            SIMD::multiply(samples, drive, blockSize);
            
            /* Bit depth conversion and clip */
            for (int s = 0; s < blockSize; ++s)
            {
                if (fmodf(static_cast<float>(s), static_cast<float>(downsampleRate)) == 0)
                {
                    float sIn;
                                        
                    switch ( clipMode )
                    {
                        case 0: sIn = clip(samples[s]);
                        case 1: sIn = fold(samples[s]);
                        case 2: sIn = wrap(samples[s]);
                    }
                    
                    sOut = std::round(sIn * bitDepth) / bitDepth;
                }
                samples[s] = sOut;
            }
        }
        
        void process (float** samples)
        {
            for (int ch = 0; ch < numChannels; ++ch)
                process(samples[ch]);
        }
        
    private:
        double sampleRate;
        int blockSize, bitDepth, downsampleRate, numChannels;
        size_t clipMode;
        float drive, sOut;
    };
}
