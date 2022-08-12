/*
  ==============================================================================

    Waveshapers.h
    Created: 1 Aug 2022 9:19:28pm
    Author:  Kevin Kopczynski

  ==============================================================================
*/

#pragma once
#include <math.h>

namespace kkaudio
{

    float signOf(float x)
    {
        return x / abs(x);
    }
    
    float clip(float x, float clipLevel = 1.f)
    {
        return fminf(abs(x), clipLevel) * signOf(x);
    }

    float fold(float x, float clipLevel = 1.f)
    {
        return fmodf(x * pow(-1, floor(x / clipLevel)), clipLevel) * signOf(x);
    }

    float wrap(float x, float clipLevel = 1.f)
    {
        return fmodf(abs(x), clipLevel) * signOf(x);
    }

    float arry(float x)
    {
        return ((3.f * x) / 2.f) * (1 - (pow(x, 2) / 3));
    }

    float sig(float x, float k)
    {
        return 2.f / (1 + exp(-k * x)) - 1.f;
    }

    float sig2(float x)
    {
        return ( (exp(x) - 1.f) * (exp(1.f) + 1.f) ) / ( (exp(x) + 1.f) * (exp(1.f) - 1.f) );
    }

    float tanh(float x, float k)
    {
        return tanhf(k * x) / tanhf(k);
    }

    float atan(float x, float k)
    {
        return atanf(k * x) / atanf(k);
    }

    float fExp1(float x, float k)
    {
        return signOf(x) * (1.f - exp(-1.f * abs(k * x))) / (1.f - exp(-1 * k));
    }
}
