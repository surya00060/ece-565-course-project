#include "cpu/vpred/lvp.hh"

#include "base/intmath.hh"
// #include "base/logging.hh"
// #include "base/trace.hh"
// #include "debug/Fetch.hh"

LVP::LVP(const LVPParams *params)
    : VPredUnit(params),
      lastPredictorSize(params->lastPredictorSize),
      lastCtrBits(params->lastCtrBits),
      classificationTable(lastPredictorSize, SatCounter(lastCtrBits)),
      valuePredictionTable(lastPredictorSize)
{
    // valuePredictionTable.resize(lastPredictorSize);
}

bool
LVP::lookup(Addr inst_addr, RegVal &value)
{
    unsigned index = inst_addr%lastPredictorSize;

    uint8_t counter_val = classificationTable[index];

    /*Gets the MSB of the count.*/
    bool prediction = counter_val >> (lastCtrBits-1);

    if (prediction)
    {
        value = valuePredictionTable[index];
    }

    return prediction;
}

void
LVP::updateTable(Addr inst_addr, bool valueTaken, RegVal &trueValue)
{
    unsigned index = inst_addr%lastPredictorSize;

    if (valueTaken)
    {
        // The Value predicted and True values are the same.
        classificationTable[index]++; 
    }
    else
    {
        // Decrease the counter and update the value to prediction table.
        classificationTable[index]++;
        valuePredictionTable[index] = trueValue;
    }
}

 LVP*
 LVPParams::create()
 {
     return new LVP(this);
 }

