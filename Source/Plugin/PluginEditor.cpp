/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"


/*    constructs the main PluginEditor object based on a proc   */
SmallScopeAudioProcessorEditor::SmallScopeAudioProcessorEditor (SmallScopeAudioProcessor& p, AudioProcessorValueTreeState& vts)
:   AudioProcessorEditor (&p), processor (p), valueTreeState (vts), oscilloscopeWaveform (processor.oscilloscopeWaveform.getPointer()),
    triggerModeButtonLogic (vts)
{
    //==============================================================================
    //BACKGROUND COMPONENTS SETUP
    //==============================================================================
    
    //==================
    //BACKGROUND
    //==================
    background = new ImageComponent ("Background");
    background->setImage(BG_DARK);
    background->setSize (512, 384);
    addAndMakeVisible(background);
    
    
    
    //==============================================================================
    //DISPLAY COMPONENTS SETUP
    //==============================================================================
    
    //==================
    //WAVESCOPE
    //==================
    addAndMakeVisible (oscilloscopeWaveform);
    
    //==================
    //GLARE
    //==================
    glare = new ImageComponent ("Glare");
    glare->setImage(GLARE);
    glare->setSize (340, 250);
    addAndMakeVisible(glare);

    
    
    //==============================================================================
    //GUI COMPONENTS SETUP
    //==============================================================================
    
    
    //==========================================
    //BUTTONS
    //==========================================
    
    //----BUTTON CONTAINER
    //==================
    buttonContainer = new ImageComponent ("ButtonContainer");
    addAndMakeVisible(buttonContainer);
    buttonContainer->setImage(BTN_CONTAINER);
    
    //----TRIGGER OFFF
    //==================
    triggerOffButton = new ImageButton ("TriggerOffButton");
    addAndMakeVisible (triggerOffButton);
    triggerOffButton->setSize (64, 64);
    triggerOffButton->setImages (true, false, true, BTN_FREE_NORMAL, 1.0f,
                                 Colour (0.0f,0.0f,0.0f,0.0f), BTN_FREE_NORMAL, 0.75f,
                                 Colour (0.0f,0.0f,0.0f,0.0f), BTN_FREE_DOWN, 1.0f,
                                 Colour (0.0f,0.0f,0.0f,0.0f));
    //----TRIGGER UP
    //==================
    triggerUpButton = new ImageButton ("TriggerUpButton");
    addAndMakeVisible (triggerUpButton);
    triggerUpButton->setSize (64, 64);
    triggerUpButton->setImages (true, false, true, BTN_UP_NORMAL, 1.0f,
                                Colour (0.0f,0.0f,0.0f,0.0f), BTN_UP_NORMAL, 0.75f,
                                Colour (0.0f,0.0f,0.0f,0.0f), BTN_UP_DOWN, 1.0f,
                                Colour (0.0f,0.0f,0.0f,0.0f));
    //----TRIGGER DOWN
    //==================
    triggerDownButton = new ImageButton ("triggerDownButton");
    addAndMakeVisible (triggerDownButton);
    triggerDownButton->setSize (64, 64);
    triggerDownButton->setImages (true, false, true, BTN_DOWN_NORMAL, 1.0f,
                                  Colour (0.0f,0.0f,0.0f,0.0f), BTN_DOWN_NORMAL, 0.75f,
                                  Colour (0.0f,0.0f,0.0f,0.0f), BTN_DOWN_DOWN, 1.0f,
                                  Colour (0.0f,0.0f,0.0f,0.0f));
    //----LOGIC
    //==================
    triggerModeButtonLogicSlider = triggerModeButtonLogic.returnAttachedSlider (*(triggerOffButton), *(triggerUpButton), *(triggerDownButton));
    triggerModeButtonLogicSlider->addListener (this);
    
    
    //==========================================
    //KNOBS
    //==========================================
    
    //----HUE
    //==================
    hueKnob = new CustomKnob (DIAL_BG_HUE, KNOB_DARK, "HueKnob");
    addAndMakeVisible(hueKnob);
    hueKnob->linkListener (this);
    //------------ATTACHMENT
    hueAttachment = new SliderAttachment (valueTreeState, "hue", hueKnob->grip);
    hueKnob->updateKnob();
    
    //----FILL
    //==================
    fillKnob = new CustomKnob (DIAL_BG_FILL, KNOB_DARK, "FillKnob");
    addAndMakeVisible(fillKnob);
    fillKnob->linkListener (this);
    //------------ATTACHMENT
    fillAttachment = new SliderAttachment (valueTreeState, "fill", fillKnob->grip);
    fillKnob->updateKnob();
    
    //----DECAY
    //==================
    decayKnob = new CustomKnob (DIAL_BG_DECAY, KNOB_DARK, "DecayKnob");
    addAndMakeVisible(decayKnob);
    decayKnob->linkListener (this);
    //------------ATTACHMENT
    decayAttachment = new SliderAttachment (valueTreeState, "decay", decayKnob->grip);
    decayKnob->updateKnob();
    
    //----XZOOM
    //==================
    xZoomKnob = new CustomKnob (DIAL_BG_XZOOM, KNOB_DARK, "XZoomKnob");
    addAndMakeVisible(xZoomKnob);
    xZoomKnob->linkListener (this);
    //------------ATTACHMENT
    xZoomAttachment = new SliderAttachment (valueTreeState, "xzoom", xZoomKnob->grip);
    xZoomKnob->updateKnob();
    
    //----YZOOM
    //==================
    yZoomKnob = new CustomKnob (DIAL_BG_YZOOM, KNOB_DARK, "YZoomKnob");
    addAndMakeVisible(yZoomKnob);
    yZoomKnob->linkListener (this);
    //------------ATTACHMENT
    yZoomAttachment = new SliderAttachment (valueTreeState, "yzoom", yZoomKnob->grip);
    yZoomKnob->updateKnob();
    
    setSize (512, 384);
}

SmallScopeAudioProcessorEditor::~SmallScopeAudioProcessorEditor()
{
}

//==============================================================================
void SmallScopeAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::black);
}

//==============================================================================
void SmallScopeAudioProcessorEditor::resized()
{
    
    //==================
    //BACKGROUND
    //==================
    background->setBounds (0, 0, 512, 384);
    
    //==================
    //WAVESCOPE
    //==================
    oscilloscopeWaveform->setBounds (0, 44, 512, 250);
    
    //==================
    //GLARE
    //==================
    glare->setBounds (0, 44, 340, 250);
    
    //==================
    //BUTTONS
    //==================
    buttonContainer->setBounds (352, 308, 139, 44);
    triggerOffButton->setBounds (362, 310, 40, 40);
    triggerUpButton->setBounds (402, 310, 40, 40);
    triggerDownButton->setBounds (442, 310, 40, 40);

    //==================
    //KNOBS
    //==================
    hueKnob->setBounds (24, 308, 44, 60);
    fillKnob->setBounds (78, 308, 44, 60);
    decayKnob->setBounds (132, 308, 44, 60);
    xZoomKnob->setBounds (246, 308, 44, 60);
    yZoomKnob->setBounds (300, 308, 44, 60);
}


//==============================================================================
void SmallScopeAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == triggerModeButtonLogicSlider)
    {
        oscilloscopeWaveform->setTriggerMode (slider->getValue());
    }
    else if (slider == &hueKnob->grip)
    {
        oscilloscopeWaveform->setTraceHue (slider->getValue());
        hueKnob->updateKnob();
    }
    else if (slider == &fillKnob->grip)
    {
        oscilloscopeWaveform->setWaveformFillFactor (slider->getValue());
        fillKnob->updateKnob();
    }
    else if (slider == &decayKnob->grip)
    {
        oscilloscopeWaveform->setPhosphorDecayFactor (slider->getValue());
        decayKnob->updateKnob();
    }
    else if (slider == &xZoomKnob->grip)
    {
        oscilloscopeWaveform->setNumSamplesPerPixel (slider->getValue());
        xZoomKnob->updateKnob();
    }
    else if (slider == &yZoomKnob->grip)
    {
        oscilloscopeWaveform->setVerticalZoomFactor (slider->getValue());
        yZoomKnob->updateKnob();
    }
}







