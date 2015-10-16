/*
  ==============================================================================

    This file was auto-generated by the Jucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_526ED7A9__
#define __PLUGINPROCESSOR_H_526ED7A9__

#include "../JuceLibraryCode/JuceHeader.h"

// Geometry Declarations
class Vector3D {
public:
    // Vector Public Methods
    Vector3D() { x = y = z = 0.f; }
    Vector3D(float xx, float yy, float zz)
        : x(xx), y(yy), z(zz) {
    }
    bool HasNaNs() const { return isnan(x) || isnan(y) || isnan(z); }
    Vector3D operator+(const Vector3D &v) const {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }

    Vector3D& operator+=(const Vector3D &v) {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    Vector3D operator-(const Vector3D &v) const {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    }

    Vector3D& operator-=(const Vector3D &v) {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    Vector3D operator*(float f) const { return Vector3D(f*x, f*y, f*z); }

    Vector3D &operator*=(float f) {
        x *= f; y *= f; z *= f;
        return *this;
    }
    Vector3D operator/(float f) const {
        float inv = 1.f / f;
        return Vector3D(x * inv, y * inv, z * inv);
    }

    Vector3D &operator/=(float f) {
        float inv = 1.f / f;
        x *= inv; y *= inv; z *= inv;
        return *this;
    }
    Vector3D operator-() const { return Vector3D(-x, -y, -z); }
    float operator[](int i) const {
        return (&x)[i];
    }

    float &operator[](int i) {
        return (&x)[i];
    }
    float LengthSquared() const { return x*x + y*y + z*z; }
    float Length() const { return sqrt(LengthSquared()); }

    bool operator==(const Vector3D &v) const {
        return x == v.x && y == v.y && z == v.z;
    }
    bool operator!=(const Vector3D &v) const {
        return x != v.x || y != v.y || z != v.z;
    }
    friend std::ostream& operator<< (std::ostream &out, const Vector3D &vector);

    // Vector Public Data
    float x, y, z;
};

class Particle
{
public:
    Particle() {

    }

    Particle(Vector3D position)
        : m_position(position) {

    }

    Vector3D& position() {
        return m_position;
    }

    Vector3D& velocity() {
        return m_velocity;
    }

    Vector3D& acceleration() {
        return m_acceleration;
    }

private:
    Vector3D m_position;
    Vector3D m_velocity;
    Vector3D m_acceleration;
};

class Spring
{
public:
    Spring(Particle* fromi, Particle* toi, double constant)
        : from(fromi)
        , to(toi)
        , k(constant)
    {

    }

    Particle* from;
    Particle* to;
    double k;
};

//==============================================================================
/**
    As the name suggest, this class does the actual audio processing.
*/
class JuceDemoPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    JuceDemoPluginAudioProcessor();
    ~JuceDemoPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    void reset() override;

    //==============================================================================
    bool hasEditor() const override                  { return true; }
    AudioProcessorEditor* createEditor() override;

    //==============================================================================
    const String getName() const override            { return JucePlugin_Name; }

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override                                               { return 1; }
    int getCurrentProgram() override                                            { return 0; }
    void setCurrentProgram (int /*index*/) override                             {}
    const String getProgramName (int /*index*/) override                        { return "Default"; }
    void changeProgramName (int /*index*/, const String& /*newName*/) override  {}

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    // These properties are public so that our editor component can access them
    // A bit of a hacky way to do it, but it's only a demo! Obviously in your own
    // code you'll do this much more neatly..

    // this is kept up to date with the midi messages that arrive, and the UI component
    // registers with it so it can represent the incoming messages
    MidiKeyboardState keyboardState;

    // this keeps a copy of the last set of time info that was acquired during an audio
    // callback - the UI component will read this and display it.
    AudioPlayHead::CurrentPositionInfo lastPosInfo;

    // these are used to persist the UI's size - the values are stored along with the
    // filter's other parameters, and the UI component will update them when it gets
    // resized.
    int lastUIWidth, lastUIHeight;

    // Our parameters
    AudioProcessorParameter* equilibriumFactor;
    AudioProcessorParameter* delay;
    AudioProcessorParameter* velocityFactor;

private:
    //==============================================================================
    AudioSampleBuffer delayBuffer;
    int delayPosition;

    // the synth!
    Synthesiser synth;

    std::vector<std::vector<Particle> > m_particles;
    std::vector<std::vector<Spring> > m_springs;

    double values[2];

    double sigma = 10.0;
    double rmSigma = 1.122462048309373;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceDemoPluginAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_526ED7A9__
