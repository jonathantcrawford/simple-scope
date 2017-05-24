/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "../UI/RadioButtonLogic.h"
#include "../UI/CustomKnob.h"


//==============================================================================
/**
*/
typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class SmallScopeAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Slider::Listener
{
public:
    SmallScopeAudioProcessorEditor (SmallScopeAudioProcessor&, AudioProcessorValueTreeState&);
    ~SmallScopeAudioProcessorEditor();
    
    /*    default juce paint */
    void paint (Graphics&) override;
    
    /*    adjust visuals according to window size */
    void resized() override;
    
    /*    connects the gui and plugin status */
    void sliderValueChanged (Slider* slider) override;
    

private:
    
    /*    an accessible reference to the plugin's main processor */
    SmallScopeAudioProcessor& processor;
    
    /*    an accessible reference to the plugin's main parameter list */
    AudioProcessorValueTreeState& valueTreeState;
    
    
    
    //==============================================================================
    //IMAGE RESOURCES
    //==============================================================================
    
    //==================
    //BACKGROUND IMAGES
    //==================
    Image BG_DARK = ImageCache::getFromMemory (BinaryData::Background_Dark_png, BinaryData::Background_Dark_pngSize);
    Image GLARE = ImageCache::getFromMemory (BinaryData::Glare_png, BinaryData::Glare_pngSize);

    //==================
    //BUTTON IMAGES
    //==================
    Image BTN_FREE_NORMAL = ImageCache::getFromMemory (BinaryData::Button_FreeRun_png, BinaryData::Button_FreeRun_pngSize);
    Image BTN_FREE_DOWN = ImageCache::getFromMemory (BinaryData::Button_FreeRun_Pressed_png, BinaryData::Button_FreeRun_Pressed_pngSize);
    Image BTN_UP_NORMAL = ImageCache::getFromMemory (BinaryData::Button_SineUp_png, BinaryData::Button_SineUp_pngSize);
    Image BTN_UP_DOWN = ImageCache::getFromMemory (BinaryData::Button_SineUp_Pressed_png, BinaryData::Button_SineUp_Pressed_pngSize);
    Image BTN_DOWN_NORMAL = ImageCache::getFromMemory (BinaryData::Button_SineDown_png, BinaryData::Button_SineDown_pngSize);
    Image BTN_DOWN_DOWN = ImageCache::getFromMemory (BinaryData::Button_SineDown_Pressed_png, BinaryData::Button_SineDown_Pressed_pngSize);
    Image BTN_CONTAINER = ImageCache::getFromMemory (BinaryData::Buttons_Container_png, BinaryData::Buttons_Container_pngSize);

    //==================
    //DIAL IMAGES
    //==================
    Image DIAL_BG_HUE = ImageCache::getFromMemory (BinaryData::Dial_Background_Hue_png, BinaryData::Dial_Background_Hue_pngSize);
    Image DIAL_BG_FILL = ImageCache::getFromMemory (BinaryData::Dial_Background_Fill_png, BinaryData::Dial_Background_Fill_pngSize);
    Image DIAL_BG_DECAY = ImageCache::getFromMemory (BinaryData::Dial_Background_Decay_png, BinaryData::Dial_Background_Decay_pngSize);
    Image DIAL_BG_XZOOM = ImageCache::getFromMemory (BinaryData::Dial_Background_xZoom_png, BinaryData::Dial_Background_xZoom_pngSize);
    Image DIAL_BG_YZOOM = ImageCache::getFromMemory (BinaryData::Dial_Background_yZoom_png, BinaryData::Dial_Background_yZoom_pngSize);
    Image KNOB_DARK = ImageCache::getFromMemory (BinaryData::Knob_Dark_png, BinaryData::Knob_Dark_pngSize);

    
    
    //==============================================================================
    //BACKGROUND COMPONENTS
    //==============================================================================
    
    //==================
    //BACKGROUND
    //==================
    ScopedPointer<ImageComponent> background;
    
    
    
    //==============================================================================
    //DISPLAY COMPONENTS
    //==============================================================================
    
    //==================
    //WAVESCOPE
    //==================
    WaveScope* oscilloscopeWaveform;
    
    //==================
    //GLARE
    //==================
    ScopedPointer<ImageComponent> glare;
    
    
    
    //==============================================================================
    //GUI COMPONENTS
    //==============================================================================
    
    //==================
    //BUTTONS
    //==================
    ScopedPointer<ImageButton> triggerOffButton;
    ScopedPointer<ImageButton> triggerUpButton;
    ScopedPointer<ImageButton> triggerDownButton;
    
    //==================
    //BUTTON CONTAINER
    //==================
    ScopedPointer<ImageComponent> buttonContainer;
    Slider* triggerModeButtonLogicSlider;
    RadioButtonLogic triggerModeButtonLogic;
    
    //==================
    //KNOBS
    //==================
    ScopedPointer<CustomKnob> hueKnob;
    ScopedPointer<CustomKnob> fillKnob;
    ScopedPointer<CustomKnob> decayKnob;
    ScopedPointer<CustomKnob> xZoomKnob;
    ScopedPointer<CustomKnob> yZoomKnob;
    
    //==================
    //KNOB ATTACHMENTS
    //==================
    ScopedPointer<SliderAttachment> hueAttachment;
    ScopedPointer<SliderAttachment> fillAttachment;
    ScopedPointer<SliderAttachment> decayAttachment;
    ScopedPointer<SliderAttachment> xZoomAttachment;
    ScopedPointer<SliderAttachment> yZoomAttachment;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SmallScopeAudioProcessorEditor)
};
