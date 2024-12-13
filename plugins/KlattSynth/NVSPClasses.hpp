// NVSPClasses.hpp
// Adapted from https://github.com/nvaccess/NVSpeechPlayer

namespace nvspeechplayer {

    class SpeechWaveGenerator {
        
        public:
            /////////////////
            // Constructor //
            /////////////////

            SpeechWaveGenerator(int sampleRate);

            /////////////////////
            // Get next sample //
            /////////////////////

            double getNext(short pindex, double pitch, double gain);

            ////////////////
            // Destructor //
            ////////////////

            // ~SpeechWaveGenerator();

        private:

            //////////////////////
            // Member variables //
            //////////////////////

            int sr;
            double sample;
            NoiseGenerator noiseGen;

            //const double sRate = sampleRate();
    
    };

}