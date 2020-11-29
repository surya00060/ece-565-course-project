#include "cpu/vpred/lvp.hh"

#include "base/intmath.hh"
// #include "base/logging.hh"
// #include "base/trace.hh"
// #include "debug/Fetch.hh"

LVP::LVP(const LVPParams *params)
    : VPredUnit(params),
      lastPredictorSize(params->lastPredictorSize),
      lastCtrBits(params->lastCtrBits)
{
    // valuePredictionTable.resize(lastPredictorSize);
}

bool
LVP::lookup(ThreadID tid, Addr inst_addr, RegVal &value)
{
    //++lookups;

    unsigned index = inst_addr%lastPredictorSize;

    uint8_t counter_val = classificationTable[index];

    /*Gets the MSB of the count.*/
    bool prediction = counter_val >> (lastCtrBits-1);

    if (prediction)
    {
        //++numPredicted;
        value = valuePredictionTable[index];
    }

    return prediction;
}

void
LVP::update(ThreadID tid, Addr inst_addr, bool taken, bool squashed, RegVal &value)
{
    if (squashed)
    {
        return;
    }
    unsigned index = inst_addr%lastPredictorSize;

    if (taken)
    {
        // The Value predicted and True values are the same.
        classificationTable[index]++; 
    }
    else
    {
        // Decrease the counter and update the value to prediction table.
        //++numIncorrectPredicted;
        classificationTable[index]++;
        valuePredictionTable[index] = value;
    }
}

 LVP*
 LVPParams::create()
 {
     return new LVP(this);
 }

