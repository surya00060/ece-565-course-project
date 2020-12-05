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

	numCorrectPredicted
        .name(name() + ".numCorrectPredicted")
        .desc("Number of value predictions")
        ;

    numIncorrectPredicted
        .name(name() + ".numIncorrectPredicted")
        .desc("Number of incorrect value predictions")
        ;
	
	numLoadPredicted
        .name(name() + ".numLoadPredicted")
        .desc("Number of Load value predictions")
        ;

	numLoadCorrectPredicted
        .name(name() + ".numLoadCorrectPredicted")
        .desc("Number of Correct Load value predictions")
        ;

	valuePredAccuracy
		.name(name() + ".valuePredAccuracy")
        .desc("VP Accuracy")
		.precision(6);
        ;

	valuePredAccuracy = numCorrectPredicted/numPredicted;

	valuePredCoverage
		.name(name() + ".valuePredCoverage")
        .desc("VP Coverage")
		.precision(6);
        ;

	valuePredCoverage = numCorrectPredicted/lookups; 
}


bool
VPredUnit::predict(const StaticInstPtr &inst, Addr inst_addr, RegVal &value)
{
	++lookups;

	bool prediction= lookup(inst_addr, value);

	if (prediction)
	{
		++numPredicted;
		if (inst->isLoad())
			++numLoadPredicted;
	}
	return prediction;
}

float
VPredUnit::getpredictconf(Addr inst_addr, RegVal &value)
{


	return getconf(inst_addr, value); // Returns prediction confidence


}


void
VPredUnit::update(const StaticInstPtr &inst, Addr inst_addr, bool isValuePredicted, bool isValueTaken, RegVal &trueValue)
{
	updateTable(inst_addr, isValuePredicted, isValueTaken, trueValue);

	if (isValuePredicted)
	{
		if (isValueTaken)
		{
			++numCorrectPredicted;
			if (inst->isLoad())
				++numLoadCorrectPredicted;
		}
		else
		{
			++numIncorrectPredicted;
		}
	}
}




