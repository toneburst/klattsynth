// PluginKlattSynth.cpp
// toneburst (the_voder@yahoo.co.uk)

#include "SC_PlugIn.hpp"
#include "KlattSynth.hpp"

static InterfaceTable* ft;

const double PITWO = twopi;

namespace klattsynth {

const double PITWO=M_PI*2;

// typedef double speechPlayer_frameParam_t;

// // Klatt Synth frame parameter struct
// typedef struct {
// 	// voicing and cascaide
// 	speechPlayer_frameParam_t voicePitch; //  fundermental frequency of voice (phonation) in hz
// 	speechPlayer_frameParam_t vibratoPitchOffset; // pitch is offset up or down in fraction of a semitone
// 	speechPlayer_frameParam_t vibratoSpeed; // Speed of vibrato in hz
// 	speechPlayer_frameParam_t voiceTurbulenceAmplitude; // amplitude of voice breathiness from 0 to 1 
// 	speechPlayer_frameParam_t glottalOpenQuotient; // fraction between 0 and 1 of a voice cycle that the glottis is open (allows voice turbulance, alters f1...)
// 	speechPlayer_frameParam_t voiceAmplitude; // amplitude of voice (phonation) source between 0 and 1.
// 	speechPlayer_frameParam_t aspirationAmplitude; // amplitude of aspiration (voiceless h, whisper) source between 0 and 1.
// 	speechPlayer_frameParam_t cf1, cf2, cf3, cf4, cf5, cf6, cfN0, cfNP; // frequencies of standard cascaide formants, nasal (anti) 0 and nasal pole in hz
// 	speechPlayer_frameParam_t cb1, cb2, cb3, cb4, cb5, cb6, cbN0, cbNP; // bandwidths of standard cascaide formants, nasal (anti) 0 and nasal pole in hz
// 	speechPlayer_frameParam_t caNP; // amplitude from 0 to 1 of cascade nasal pole formant
// 	// fricatives and parallel
// 	speechPlayer_frameParam_t fricationAmplitude; // amplitude of frication noise from 0 to 1.
// 	speechPlayer_frameParam_t pf1, pf2, pf3, pf4, pf5, pf6; // parallel formants in hz
// 	speechPlayer_frameParam_t pb1, pb2, pb3, pb4, pb5, pb6; // parallel formant bandwidths in hz
// 	speechPlayer_frameParam_t pa1, pa2, pa3, pa4, pa5, pa6; // amplitude of parallel formants between 0 and 1
// 	speechPlayer_frameParam_t parallelBypass; // amount of signal which should bypass parallel resonators from 0 to 1
// 	speechPlayer_frameParam_t preFormantGain; // amplitude from 0 to 1 of all vocal tract sound (voicing, frication) before entering formant resonators. Useful for stopping/starting speech
// 	speechPlayer_frameParam_t outputGain; // amplitude from 0 to 1 of final output (master volume) 
// 	speechPlayer_frameParam_t endVoicePitch; //  pitch of voice at the end of the frame length 
// } speechPlayer_frame_t;

// Phasor
class FrequencyGenerator {
	private:
	int sampleRate;
	double lastCyclePos;

	public:
	FrequencyGenerator(int sr): sampleRate(sr), lastCyclePos(0) {}

	double getNext(double frequency) {
		double cyclePos = fmod((frequency / sampleRate) + lastCyclePos, 1);
		lastCyclePos = cyclePos;
		return cyclePos;
	}
};

// Constructor
KlattSynth::KlattSynth() {
    
    //Print("sample-rate: %f, buffer size: %d, twopi: %f\n", sRate, bufferSize(), PITWO);

    // Instantiate Freq Generator /phasor
    FrequencyGenerator pitchGen(sRate);
    

    // Set the calculation method for ugen
    mCalcFunc = make_calc_function<KlattSynth, &KlattSynth::next>();

    // Call calculation method
    next(bufferSize());
}

// 
void KlattSynth::next(int nSamples) {

    // Control rate parameter: pitch
    const float pitch = in0(0);

    // Control rate parameter: gain
    const float gain = in0(1);

    // Output buffer
    float* outbuf = out(0);

    // Fill buffer
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = pitchGen.getNext(pitch);
    }
}

} // namespace klattsynth

PluginLoad(KlattSynthUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<klattsynth::KlattSynth>(ft, "KlattSynth", false);
}
