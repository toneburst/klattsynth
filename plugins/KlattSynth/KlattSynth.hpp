// PluginKlattSynth.hpp
// toneburst (the_voder@yahoo.co.uk)

#pragma once

#include "SC_PlugIn.hpp"
#include "NVSPClasses.hpp"

namespace klattsynth {

    class KlattSynth : public SCUnit {
        public:
            /////////////////
            // Constructor //
            /////////////////

            KlattSynth();

            ////////////////
            // Destructor //
            ////////////////

            // ~KlattSynth();

        private:

            // Member variables

            const double sRate = sampleRate();

            nvspeechplayer::SpeechWaveGenerator speechWaveGen();

            // Methods

            void next(int nSamples);

    };

} // Namespace klattsynth
