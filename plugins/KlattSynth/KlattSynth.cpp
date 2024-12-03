// PluginKlattSynth.cpp
// toneburst (the_voder@yahoo.co.uk)

#include "SC_PlugIn.hpp"
#include "KlattSynth.hpp"

static InterfaceTable* ft;

namespace klattsynth {

KlattSynth::KlattSynth() {
    mCalcFunc = make_calc_function<KlattSynth, &KlattSynth::next>();
    next(1);
}

void KlattSynth::next(int nSamples) {

    // Audio rate input
    const float* input = in(0);

    // Control rate parameter: gain.
    const float gain = in0(1);

    // Output buffer
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain;
    }
}

} // namespace klattsynth

PluginLoad(KlattSynthUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<klattsynth::KlattSynth>(ft, "KlattSynth", false);
}
