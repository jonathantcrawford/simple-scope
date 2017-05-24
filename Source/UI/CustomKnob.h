//
//  CustomKnob.h
//  SimpleScope
//
//  Created by Jonathan Crawford on 4/28/17.
//
//

#pragma once

#include "JuceHeader.h"

class CustomKnob : public Component
{
public:
    CustomKnob (Image& dial, Image& knob, String name)
    {
        //DIAL (Backplate) Image
        dialImage = new ImageComponent (name + "Dial");
        dialImage->setImage(dial);
        dialImage->setSize (44, 60);
        addAndMakeVisible(dialImage);
        
        //KNOB (Frontplate) Image
        knobImage = new ImageComponent (name + "Knob");
        knobImage->setImage(knob);
        knobImage->setSize (36, 36);
        addAndMakeVisible(knobImage);
        
        grip.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        grip.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
        grip.setAlpha (0.0f);
        addAndMakeVisible (grip);
    };
    
    ~CustomKnob()
    {
    };
    
    void resized() override
    {
        dialImage->setBounds (0, 0, dialImage->getWidth(), dialImage->getHeight());
        knobImage->setBounds (5, 5, knobImage->getWidth(), knobImage->getHeight());
        grip.setBounds (5, 5, knobImage->getWidth(), knobImage->getHeight());
    };
    
    void paint(Graphics& g) override
    {
    };
    
    void updateKnob ()
    {
        knobImage->setTransform (AffineTransform::rotation (1.5*3.1416f*(
                                                                         (grip.getValue()-grip.getMinimum())
                                                                        /(grip.getMaximum()-grip.getMinimum())
                                                                         )-(3.1416/4.0f), 18+5, 18+5));
        repaint();
    };
    
    void linkListener (Slider::Listener* listener)
    {
        grip.addListener (listener);
    };
    
    //Transparent rotary style slider object
    Slider grip;

private:
    ScopedPointer<ImageComponent> dialImage;
    ScopedPointer<ImageComponent> knobImage;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomKnob);
    
};
