/*
  ==============================================================================

  This file is part of the dRowAudio JUCE module
  Copyright 2004-13 by dRowAudio.

  ------------------------------------------------------------------------------

  dRowAudio is provided under the terms of The MIT License (MIT):

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
  SOFTWARE.

  ==============================================================================
*/

#pragma once

#include <cmath>

#include "JuceHeader.h"
#include "FifoBuffer.h"



class WaveScope :   public Component,
                    private Timer,
                    private TimeSliceClient
{
public:
    //==============================================================================
    /** The enum to use when setting the trace trigger mode.
     */
    enum TriggerMode
    {
        Off,/**<< The trace will just refresh at a constant rate. */
        Up,     /**<< The start of the trace will be a rising edge. */
        Down    /**<< The start of the trace will be a falling edge. */
    };
    
    //==============================================================================
    /** Creates a Triggered scope.
        You should really specify a backGroundThread to use and make sure you start
        it before creating the scope. If you pass a nullptr in here it will create
        its own thread and manage its lifetime internally.
     */
    WaveScope (TimeSliceThread* backgroundAudioThreadToUse = nullptr);
    
    /** Destructor. */
    ~WaveScope();

    //==============================================================================
    void setNumSamplesPerPixel (int newNumSamplesPerPixel);
    
    void setVerticalZoomFactor (float newVerticalZoomFactor);
    
    void setTraceHue (float newTraceHue);
    
    void setWaveformFillFactor (float newWaveformFillFactor);
    
    void setPhosphorDecayFactor (float newPhosphorDecayFactor);
    
    void setTriggerMode (float newTriggerMode);
    
    WaveScope* getPointer();
    
    /** Adds a block of samples to the scope.
        
        Simply call this from your audio callback or similar to render the scope.
        This is a very quick method as it only takes a copy of the samples. All the
        processing and image rendering is performed on a background thread.
     */
    void addSamples (const float* samples, int numSamples);

    /** @internal */
    void timerCallback() override;
    
    /** @internal */
    void resized() override;
    
    /** @internal */
    void paint(Graphics& g) override;
    
    /** @internal */
    int useTimeSlice() override;
    
private:
    //==============================================================================
    //PROCESSING THREAD
    OptionalScopedPointer<TimeSliceThread> backgroundAudioThreadToUse;

    //VISUAL PARAMETERS
    TriggerMode triggerMode;
    float verticalZoomFactor;
    int numSamplesPerPixel;
    float waveformFillFactor;
    float phosphorDecayFactor;
    Colour traceColour;
    
    //AUDIO PROCESSING MEMBERS
    int numLeftToAverage;
    int bufferSize, bufferWritePos;
    FifoBuffer<float> samplesToProcess;
    HeapBlock<float> tempProcessingBlock;
    float currentMin, currentMax;
    HeapBlock<float> minBuffer, maxBuffer;
    
    //IMAGE LOCK
    Image outputImage;
    bool needToUpdate;
    bool needToRepaint;
    CriticalSection imageLock;
    
    //==============================================================================
    void processPendingSamples();
    void renderImage();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveScope);
};
