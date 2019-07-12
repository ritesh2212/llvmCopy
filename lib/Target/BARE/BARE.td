def : Processor<"simulator", NoItineraries, [FeatureA]>;

def BARE : Target {
        // Pull in Instruction Info:
        let InstructionSet = BAREInstrInfo;
}
