/*
  ==============================================================================

    RadioButtonGroup.h
    Created: 14 Apr 2017 7:54:46am
    Author:  Jonathan Crawford

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
class RadioButtonLogic :    public Slider::Listener,
                            public Button::Listener
{
public:
    RadioButtonLogic(AudioProcessorValueTreeState& vts)
    :   valueTreeState (vts)
    {
        parameter = valueTreeState.getParameter("triggermode");
        
        radioButtonGroupSlider = new Slider();

    };
    
    ~RadioButtonLogic(){
        choice_1->removeListener(this);
        choice_2->removeListener(this);
        choice_3->removeListener(this);
    };


/** monitors plugin parameter state*/
void sliderValueChanged(Slider* slider) override
{
    const ScopedLock sl (radioButtonLock);
    
    if (slider->getValue() >= 0.1 && slider->getValue() < 0.333f)
    {
        choice_1->setToggleState(true, dontSendNotification);
        
        choice_1->setClickingTogglesState(false);
        choice_2->setClickingTogglesState(true);
        choice_3->setClickingTogglesState(true);
        
        if (choice_2->isMouseOver())
            choice_2->setState(Button::ButtonState::buttonOver);
        else
            choice_2->setState(Button::ButtonState::buttonNormal);
        
        if (choice_3->isMouseOver())
            choice_3->setState(Button::ButtonState::buttonOver);
        
        else
            choice_3->setState(Button::ButtonState::buttonNormal);
        
    }
    else if (slider->getValue() >= 0.333f && slider->getValue() < 0.666f)
    {
        choice_2->setToggleState(true, dontSendNotification);
        
        choice_1->setClickingTogglesState(true);
        choice_2->setClickingTogglesState(false);
        choice_3->setClickingTogglesState(true);
        
        if (choice_1->isMouseOver())
            choice_1->setState(Button::ButtonState::buttonOver);
        else
            choice_1->setState(Button::ButtonState::buttonNormal);
        
        if (choice_3->isMouseOver())
            choice_3->setState(Button::ButtonState::buttonOver);
        
        else
            choice_3->setState(Button::ButtonState::buttonNormal);
    }
    else if (slider->getValue() >= 0.666f)
    {
        choice_3->setToggleState(true, dontSendNotification);
        
        choice_1->setClickingTogglesState(true);
        choice_2->setClickingTogglesState(true);
        choice_3->setClickingTogglesState(false);
        
        if (choice_1->isMouseOver())
            choice_1->setState(Button::ButtonState::buttonOver);
        else
            choice_1->setState(Button::ButtonState::buttonNormal);
        
        if (choice_2->isMouseOver())
            choice_2->setState(Button::ButtonState::buttonOver);
        
        else
            choice_2->setState(Button::ButtonState::buttonNormal);
    }
};
    
/** watches for user button clicks*/
void buttonClicked (Button* button) override
{
    const ScopedLock sl (radioButtonLock);
    if (button == choice_1)
    {
        if (choice_1->getState() == Button::ButtonState::buttonOver)
        {
            choice_1->setToggleState(true, dontSendNotification);
            
            choice_1->setClickingTogglesState(false);
            choice_2->setClickingTogglesState(true);
            choice_3->setClickingTogglesState(true);
            parameter->setValueNotifyingHost (0.15f);
        }
        else if (choice_1->getState() == Button::ButtonState::buttonDown)
        {
            parameter->setValueNotifyingHost (0.15f);
        }
    }
    else if (button == choice_2)
    {
        if (choice_2->getState() == Button::ButtonState::buttonOver)
        {
            choice_2->setToggleState(true, dontSendNotification);
            
            choice_1->setClickingTogglesState(true);
            choice_2->setClickingTogglesState(false);
            choice_3->setClickingTogglesState(true);
            parameter->setValueNotifyingHost (0.45f);
        }
        else if (choice_1->getState() == Button::ButtonState::buttonDown)
        {
            parameter->setValueNotifyingHost (0.45f);
        }
    }
    else if (button == choice_3)
    {
        if (choice_3->getState() == Button::ButtonState::buttonOver)
        {
            choice_3->setToggleState(true, dontSendNotification);
            
            choice_1->setClickingTogglesState(true);
            choice_2->setClickingTogglesState(true);
            choice_3->setClickingTogglesState(false);
            parameter->setValueNotifyingHost (0.75f);
        }
        else if (choice_1->getState() == Button::ButtonState::buttonDown)
        {
            parameter->setValueNotifyingHost (0.75f);
        }
    }
};
    
Slider* returnAttachedSlider (Button& btn1, Button& btn2, Button& btn3)
{
    choice_1 = &btn1;
    choice_2 = &btn2;
    choice_3 = &btn3;
    
    choice_1->addListener(this);
    choice_2->addListener(this);
    choice_3->addListener(this);
    choice_1->setRadioGroupId(1, sendNotification);
    choice_2->setRadioGroupId(1, sendNotification);
    choice_3->setRadioGroupId(1, sendNotification);
    choice_1->setClickingTogglesState(true);
    choice_2->setClickingTogglesState(true);
    choice_3->setClickingTogglesState(true);
    
    radioButtonGroupSlider->setRange(0.1f, 1.0f);
    radioButtonGroupSlider->addListener(this);

    radioButtonGroupSliderAttachment = new SliderAttachment (valueTreeState, "triggermode", *radioButtonGroupSlider);
    
    parameter->setValueNotifyingHost (parameter->getValue());
    
    return radioButtonGroupSlider.get();
};

private:
    AudioProcessorValueTreeState& valueTreeState;
    AudioProcessorParameter* parameter;
    float currentValue;
    Button* choice_1;
    Button* choice_2;
    Button* choice_3;
    
    ScopedPointer<Slider> radioButtonGroupSlider;
    ScopedPointer<SliderAttachment> radioButtonGroupSliderAttachment;
    
    CriticalSection radioButtonLock;

//==============================================================================
JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RadioButtonLogic);
};
