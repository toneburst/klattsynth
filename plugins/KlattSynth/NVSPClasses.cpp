// NVSPClasses.cpp
// Adapted from https://github.com/nvaccess/NVSpeechPlayer

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "NVSPClasses.hpp"

using namespace nvspeechplayer;
using namespace std;

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

class NoiseGenerator {
	private:
	    double lastValue;

	public:
	    NoiseGenerator(): lastValue(0.0) {};

        double getNext() {
            lastValue = ((double)rand() / RAND_MAX) + 0.75 * lastValue;
            return lastValue;
        }

};

// class FrequencyGenerator {
// 	private:
// 	int sampleRate;
// 	double lastCyclePos;

// 	public:
// 	FrequencyGenerator(int sr): sampleRate(sr), lastCyclePos(0) {}

// 	double getNext(double frequency) {
// 		double cyclePos = fmod((frequency / sampleRate) + lastCyclePos, 1);
// 		lastCyclePos = cyclePos;
// 		return cyclePos;
// 	}
// };

// class VoiceGenerator {
// 	private:
// 	FrequencyGenerator pitchGen;
// 	FrequencyGenerator vibratoGen;
// 	NoiseGenerator aspirationGen;

// 	public:
// 	bool glottisOpen;
// 	VoiceGenerator(int sr): pitchGen(sr), vibratoGen(sr), aspirationGen(), glottisOpen(false) {};

// 	double getNext(const speechPlayer_frame_t* frame) {
// 		double vibrato=(sin(vibratoGen.getNext(frame->vibratoSpeed)*PITWO)*0.06*frame->vibratoPitchOffset)+1;
// 		double voice=pitchGen.getNext(frame->voicePitch*vibrato);
// 		double aspiration=aspirationGen.getNext()*0.2;
// 		double turbulence=aspiration*frame->voiceTurbulenceAmplitude;
// 		glottisOpen=voice>=frame->glottalOpenQuotient;
// 		if(!glottisOpen) {
// 			turbulence*=0.01;
// 		}
// 		voice=(voice*2)-1;
// 		voice+=turbulence;
// 		voice*=frame->voiceAmplitude;
// 		aspiration*=frame->aspirationAmplitude;
// 		return aspiration+voice;
// 	}

// };

// class Resonator {
// 	private:
// 	//raw parameters
// 	int sampleRate;
// 	double frequency;
// 	double bandwidth;
// 	bool anti;
// 	//calculated parameters
// 	bool setOnce;
// 	double a, b, c;
// 	//Memory
// 	double p1, p2;

// 	public:
// 	Resonator(int sampleRate, bool anti=false) {
// 		this->sampleRate=sampleRate;
// 		this->anti=anti;
// 		this->setOnce=false;
// 		this->p1=0;
// 		this->p2=0;
// 	}

// 	void setParams(double frequency, double bandwidth) {
// 		if(!setOnce||(frequency!=this->frequency)||(bandwidth!=this->bandwidth)) {
// 			this->frequency=frequency;
// 			this->bandwidth=bandwidth;
// 			double r=exp(-M_PI/sampleRate*bandwidth);
// 			c=-(r*r);
// 			b=r*cos(PITWO/sampleRate*-frequency)*2.0;
// 			a=1.0-b-c;
// 			if(anti&&frequency!=0) {
// 				a=1.0/a;
// 				c*=-a;
// 				b*=-a;
// 			}
// 		}
// 		this->setOnce=true;
// 	}

// 	double resonate(double in, double frequency, double bandwidth) {
// 		setParams(frequency,bandwidth);
// 		double out=a*in+b*p1+c*p2;
// 		p2=p1;
// 		p1=anti?in:out;
// 		return out;
// 	}

// };

// class CascadeFormantGenerator { 
// 	private:
// 	int sampleRate;
// 	Resonator r1, r2, r3, r4, r5, r6, rN0, rNP;

// 	public:
// 	CascadeFormantGenerator(int sr): sampleRate(sr), r1(sr), r2(sr), r3(sr), r4(sr), r5(sr), r6(sr), rN0(sr,true), rNP(sr) {};

// 	double getNext(const speechPlayer_frame_t* frame, bool glottisOpen, double input) {
// 		input/=2.0;
// 		double n0Output=rN0.resonate(input,frame->cfN0,frame->cbN0);
// 		double output=calculateValueAtFadePosition(input,rNP.resonate(n0Output,frame->cfNP,frame->cbNP),frame->caNP);
// 		output=r6.resonate(output,frame->cf6,frame->cb6);
// 		output=r5.resonate(output,frame->cf5,frame->cb5);
// 		output=r4.resonate(output,frame->cf4,frame->cb4);
// 		output=r3.resonate(output,frame->cf3,frame->cb3);
// 		output=r2.resonate(output,frame->cf2,frame->cb2);
// 		output=r1.resonate(output,frame->cf1,frame->cb1);
// 		return output;
// 	}

// };

// class ParallelFormantGenerator { 
// 	private:
// 	int sampleRate;
// 	Resonator r1, r2, r3, r4, r5, r6;

// 	public:
// 	ParallelFormantGenerator(int sr): sampleRate(sr), r1(sr), r2(sr), r3(sr), r4(sr), r5(sr), r6(sr) {};

// 	double getNext(const speechPlayer_frame_t* frame, double input) {
// 		input/=2.0;
// 		double output=0;
// 		output+=(r1.resonate(input,frame->pf1,frame->pb1)-input)*frame->pa1;
// 		output+=(r2.resonate(input,frame->pf2,frame->pb2)-input)*frame->pa2;
// 		output+=(r3.resonate(input,frame->pf3,frame->pb3)-input)*frame->pa3;
// 		output+=(r4.resonate(input,frame->pf4,frame->pb4)-input)*frame->pa4;
// 		output+=(r5.resonate(input,frame->pf5,frame->pb5)-input)*frame->pa5;
// 		output+=(r6.resonate(input,frame->pf6,frame->pb6)-input)*frame->pa6;
// 		return calculateValueAtFadePosition(output,input,frame->parallelBypass);
// 	}

// };

// class SpeechWaveGeneratorImpl: public SpeechWaveGenerator {
// 	private:
// 	int sampleRate;
// 	VoiceGenerator voiceGenerator;
// 	NoiseGenerator fricGenerator;
// 	CascadeFormantGenerator cascade;
// 	ParallelFormantGenerator parallel;
// 	FrameManager* frameManager;

// 	public:
// 	SpeechWaveGeneratorImpl(int sr): sampleRate(sr), voiceGenerator(sr), fricGenerator(), cascade(sr), parallel(sr), frameManager(NULL) {
// 	}

// 	unsigned int generate(const unsigned int sampleCount, sample* sampleBuf) {
// 		if(!frameManager) return 0; 
// 		double val=0;
// 		for(unsigned int i=0;i<sampleCount;++i) {
// 			const speechPlayer_frame_t* frame=frameManager->getCurrentFrame();
// 			if(frame) {
// 				double voice=voiceGenerator.getNext(frame);
// 				double cascadeOut=cascade.getNext(frame,voiceGenerator.glottisOpen,voice*frame->preFormantGain);
// 				double fric=fricGenerator.getNext()*0.3*frame->fricationAmplitude;
// 				double parallelOut=parallel.getNext(frame,fric*frame->preFormantGain);
// 				double out=(cascadeOut+parallelOut)*frame->outputGain;
// 				sampleBuf[i].value=(int)max(min(out*4000,32000),-32000);
// 			} else {
// 				return i;
// 			}
// 		}
// 		return sampleCount;
// 	}

// 	void setFrameManager(FrameManager* frameManager) {
// 		this->frameManager=frameManager;
// 	}

/////////////////
// Constructor //
/////////////////

SpeechWaveGenerator::SpeechWaveGenerator(int sampleRate) {
    sr = sampleRate;
    cout << "SpeechWaveGenerator constructor saying 'hi'\n";
}

/////////////////
// Next sample //
/////////////////

 double SpeechWaveGenerator::getNext(short pindex = 0, double pitch = 440, double gain = 1.0) {

    return 1.0;//noiseGen.getNext();
}

