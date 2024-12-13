// PluginKlattSynth.cpp
// toneburst (the_voder@yahoo.co.uk)

#include "SC_PlugIn.hpp"
#include "KlattSynth.hpp"

static InterfaceTable* ft;

namespace klattsynth {

    /////////////////
    // Constructor //
    /////////////////

    KlattSynth::KlattSynth() {
        
        //Print("sample-rate: %f, buffer size: %d, twopi: %f\n", sRate, bufferSize(), PITWO);
        
        // Set the calculation method for ugen
        mCalcFunc = make_calc_function<KlattSynth, &KlattSynth::next>();

        // Call calculation method
        next(bufferSize());
    }

    /////////////////
    // Next Sample //
    /////////////////

    void KlattSynth::next(int nSamples) {

        // Control rate parameter: pitch
        const float pitch = in0(0);

        // Control rate parameter: gain
        const float gain = in0(1);

        // Output buffer
        float* outbuf = out(0);

        // Fill buffer
        for (int i = 0; i < nSamples; ++i) {
            outbuf[i] = speechWaveGen().getNext(0, (double)pitch, (double)gain);
        }
    }

} // namespace klattsynth

/////////////////
// Load plugin //
/////////////////

PluginLoad(KlattSynthUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<klattsynth::KlattSynth>(ft, "KlattSynth", false);
}
