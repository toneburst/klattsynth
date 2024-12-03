// PluginKlattSynth.hpp
// toneburst (the_voder@yahoo.co.uk)

#pragma once

#include "SC_PlugIn.hpp"

namespace klattsynth {

class KlattSynth : public SCUnit {
public:
    KlattSynth();

    // Destructor
    // ~KlattSynth();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace klattsynth
