KlattSynth : UGen {
	*ar { |pitch=440, gain=1.0|
		/* TODO */
		^this.multiNew('audio', pitch, gain);
	}
	checkInputs {
		/* TODO */
		^this.checkValidInputs;
	}
}
