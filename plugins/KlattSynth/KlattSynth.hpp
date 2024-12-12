// PluginKlattSynth.hpp
// toneburst (the_voder@yahoo.co.uk)

#pragma once

#include "SC_PlugIn.hpp"

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

    // Methods

    double FrequencyGenerator(sr);

    void next(int nSamples);

};

} // Namespace klattsynth
