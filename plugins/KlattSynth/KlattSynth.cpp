// PluginKlattSynth.cpp
// toneburst (the_voder@yahoo.co.uk)

#define _USE_MATH_DEFINES

#include "SC_PlugIn.hpp"
#include "KlattSynth.hpp"

static InterfaceTable* ft;

const double PITWO=M_PI*2;

namespace klattsynth {

class FrequencyGenerator {
	private:
	int sampleRate;
	double lastCyclePos;

	public:
	FrequencyGenerator(int sr): sampleRate(sr), lastCyclePos(0) {}

	double getNext(double frequency) {
		double cyclePos=fmod((frequency/sampleRate)+lastCyclePos,1);
		lastCyclePos=cyclePos;
		return cyclePos;
	}

};

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
