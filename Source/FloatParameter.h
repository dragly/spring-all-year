#ifndef FLOATPARAMETER_H
#define FLOATPARAMETER_H

#include "../JuceLibraryCode/JuceHeader.h"

class FloatParameter : public AudioProcessorParameter
{
public:
    inline FloatParameter (float defaultParameterValue, const String& paramName);
    inline float getValue() const override;
    inline void setValue (float newValue) override;
    inline float getDefaultValue() const override;
    inline String getName (int /* maximumStringLength */) const override;
    inline String getLabel() const override;
    inline float getValueForText (const String& text) const override;

private:
    float defaultValue, value;
    String name;
};

FloatParameter::FloatParameter(float defaultParameterValue, const String &paramName)
    : defaultValue (defaultParameterValue),
      value (defaultParameterValue),
      name (paramName)
{
}

float FloatParameter::getValue() const
{
    return value;
}

void FloatParameter::setValue(float newValue)
{
    value = newValue;
}

float FloatParameter::getDefaultValue() const
{
    return defaultValue;
}

String FloatParameter::getName(int) const
{
    return name;
}

String FloatParameter::getLabel() const
{
    return String();
}

float FloatParameter::getValueForText(const String &text) const
{
    return text.getFloatValue();
}

#endif // FLOATPARAMETER_H
