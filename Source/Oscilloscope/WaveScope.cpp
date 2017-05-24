#include "WaveScope.h"

//==============================================================================
WaveScope::WaveScope (TimeSliceThread* backgroundAudioThreadToUse_)
:   backgroundAudioThreadToUse (backgroundAudioThreadToUse_, backgroundAudioThreadToUse_ == nullptr ? true : false),
    triggerMode (Up),
    verticalZoomFactor (1.0f), numSamplesPerPixel (2),
    waveformFillFactor (0.0f), phosphorDecayFactor (1.0f), traceColour (0.22f, 1.0f, 1.0f, 1.0f),
    numLeftToAverage (numSamplesPerPixel),
    bufferSize (2048), bufferWritePos (0),
    samplesToProcess (32768),
    tempProcessingBlock (32768),
    currentMin (-1.0f), currentMax (1.0f),
    minBuffer (bufferSize), maxBuffer (bufferSize),
    needToUpdate (false), needToRepaint (false)
{
    const ScopedLock sl (imageLock);

    outputImage = Image (Image::ARGB, jmax (1, getWidth()), jmax (1, getHeight()), false);
    outputImage.duplicateIfShared();

    
    //CLEAR AUDIO BUFFERS
    minBuffer.clear (bufferSize);
    maxBuffer.clear (bufferSize);
    
    //PREPARE BACKGROUND AUDIO THREADS
    if (backgroundAudioThreadToUse == nullptr)
    {   
        OptionalScopedPointer<TimeSliceThread> newThread (new TimeSliceThread ("Wave Scope Audio Thread"), true);
        backgroundAudioThreadToUse = newThread;
        backgroundAudioThreadToUse->startThread (1);
    }
    
    backgroundAudioThreadToUse->addTimeSliceClient (this);
    
    //SET REFRESH RATE
    startTimerHz (60);
}

//==============================================================================
WaveScope::~WaveScope()
{
    const ScopedLock sl (imageLock);
    
    stopTimer();
    
    backgroundAudioThreadToUse->removeTimeSliceClient (this);

    if (backgroundAudioThreadToUse.willDeleteObject())
        backgroundAudioThreadToUse->stopThread (500);
}

//==============================================================================
void WaveScope::setNumSamplesPerPixel (int newNumSamplesPerPixel)
{
    numSamplesPerPixel = newNumSamplesPerPixel;
}

//==============================================================================
void WaveScope::setVerticalZoomFactor (float newVerticalZoomFactor)
{
    verticalZoomFactor = newVerticalZoomFactor;
}

//==============================================================================
void WaveScope::setTraceHue (float newTraceHue)
{
    traceColour = traceColour.withHue (newTraceHue);
}

//==============================================================================
void WaveScope::setWaveformFillFactor(float newWaveformFillFactor)
{
    waveformFillFactor = newWaveformFillFactor;
}

//==============================================================================
void WaveScope::setPhosphorDecayFactor (float newPhosphorDecayFactor)
{
    phosphorDecayFactor = newPhosphorDecayFactor;
}

//==============================================================================
void WaveScope::setTriggerMode (float newTriggerMode)
{
    if (newTriggerMode >= 0.1f && newTriggerMode < 0.333f)
        triggerMode = TriggerMode::Off;
    else if (newTriggerMode >= 0.333f && newTriggerMode < 0.666f)
        triggerMode = TriggerMode::Up;
    else
        triggerMode = TriggerMode::Down;
}

//==============================================================================
WaveScope* WaveScope::getPointer()
{
    return this;
}

//==============================================================================
void WaveScope::addSamples (const float* samples, int numSamples)
{
    // if we don't have enough space in the fifo, clear out some old samples
    const int numFreeInBuffer = samplesToProcess.getNumFree();
    if (numFreeInBuffer < numSamples)
        samplesToProcess.removeSamples (numFreeInBuffer);

    samplesToProcess.writeSamples (samples, numSamples);
    
    needToUpdate = true;
}

//==============================================================================
void WaveScope::resized()
{
    const ScopedLock sl (imageLock);

    outputImage = Image (Image::ARGB, jmax (1, getWidth()), jmax (1, getHeight()), false);

    needToRepaint = true;
}

//==============================================================================
void WaveScope::paint(Graphics& g)
{
    const ScopedLock sl (imageLock);
    
    g.drawImageAt(outputImage, 0, 0);
    
    needToRepaint = true;
}


void WaveScope::timerCallback()
{

    if (needToRepaint)
        repaint();
}

//==============================================================================
int WaveScope::useTimeSlice()
{
    if (needToUpdate)
    {
        processPendingSamples();
        renderImage();
        
        needToUpdate = false;
    }

    return 10;
}

//==============================================================================
void WaveScope::processPendingSamples()
{
    int numSamples = samplesToProcess.getNumAvailable();
    samplesToProcess.readSamples (tempProcessingBlock, numSamples);
    float* samples = tempProcessingBlock.getData();
    
    while (--numSamples >= 0)
    {
        const float currentSample = *samples++;
            
        if (currentSample < currentMin)
            currentMin = currentSample;
        
        if (currentSample > currentMax)
            currentMax = currentSample;
        
        if (--numLeftToAverage == 0)
        {
            minBuffer[bufferWritePos] = currentMin;
            maxBuffer[bufferWritePos] = currentMax;

            currentMax = -1.0f;
            currentMin = 1.0f;
            
            ++bufferWritePos %= bufferSize;
            numLeftToAverage = numSamplesPerPixel;
        }
    }
}

//==============================================================================
void WaveScope::renderImage()
{
    const ScopedLock sl (imageLock);
    
    Graphics outputFrame (outputImage);
    
    outputFrame.fillAll(Colour(0.0f, 0.0f, 0.0f, (1.0f/phosphorDecayFactor)));
    
    const int w = outputImage.getWidth();
    const int h = outputImage.getHeight();

        
    //CURRENT BUFFER POSITION
    int bufferReadPos = bufferWritePos - w;
    if (bufferReadPos < 0)
        bufferReadPos += bufferSize;
    
    //LOCATE TRIGGER
    if (triggerMode != Off)
    {
        int posToTest = bufferReadPos;
        int numToSearch = bufferSize;
        while (--numToSearch >= 0)
        {
            int prevPosToTest = posToTest - 1;
            if (prevPosToTest < 0)
                prevPosToTest += bufferSize;
            
            if (triggerMode == Up)
            {
                if (minBuffer[prevPosToTest] <= 0.0f
                    && maxBuffer[posToTest] > 0.0f)
                {
                    bufferReadPos = posToTest;
                    break;
                }
            }
            else
            {
                if (minBuffer[prevPosToTest] > 0.0f
                    && maxBuffer[posToTest] <= 0.0f)
                {
                    bufferReadPos = posToTest;
                    break;
                }
            }
        
            if (--posToTest < 0)
                posToTest += bufferSize;
        }
    }
    
    //BEGIN RENDERING
    int currentX = 0;
    while (currentX < w)
    {
        ++bufferReadPos;
        if (bufferReadPos == bufferSize)
            bufferReadPos = 0;
        
        const float top = (1.0f - (0.5f + (0.5f * verticalZoomFactor * maxBuffer[bufferReadPos]))) * h;
        const float bottom = (1.0f - (0.5f + (0.5f * verticalZoomFactor * minBuffer[bufferReadPos]))) * h;
        
        //WAVEFORM OUTLINE
        outputFrame.setColour (traceColour);
        outputFrame.drawVerticalLine (currentX, top, bottom);

        //WAVEFORM FILL
        const float fillOpacity = waveformFillFactor;
        outputFrame.setColour (traceColour.withAlpha(fillOpacity));
        if(bottom < (0.5f*h) && top < (0.5f*h))
        {
            outputFrame.drawVerticalLine (currentX, top, (0.5f*h));
        }
        else if(bottom >= (0.5f*h) && top >= (0.5f*h))
        {
            outputFrame.drawVerticalLine (currentX, (0.5f*h), bottom);
        }
        ++currentX;
    }
    needToRepaint = true;
}
