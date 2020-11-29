#include "cpu/vpred/vpred_unit.hh"


VPredUnit::VPredUnit(const Params *params)
    : SimObject (params)
{
}

void 
VPredUnit::regStats()
{
    SimObject::regStats();
    lookups
        .name(name() + ".lookups")
        .desc("Number of VP lookups")
        ;

    numPredicted
        .name(name() + ".numPredicted")
        .desc("Number of value predictions")
        ;

    numIncorrectPredicted
        .name(name() + ".numIncorrectPredicted")
        .desc("Number of incorrect value predictions")
        ;
}


bool
VPredUnit::predict(Addr inst_addr, RegVal &value)
{
	++lookups;

	// TheISA::PCState pc = inst->pcState()
	// Addr inst_addr = pc.instAddr()

	bool prediction= lookup(inst_addr, value);

	if (prediction)
	{
		++numPredicted;
	}
	return prediction;
}

void
VPredUnit::update(Addr inst_addr, RegVal &trueValue, RegVal &predValue)
{
	// TheISA::PCState pc = inst->pcState()
	// Addr inst_addr = pc.instAddr()

	bool valueTaken = trueValue == predValue;
	updateTable(inst_addr, valueTaken, trueValue);

	if (!valueTaken)
	{
		++numIncorrectPredicted;
	}
}




