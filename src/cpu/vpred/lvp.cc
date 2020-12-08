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

    //bool prediction = (counter_val == ((2^(lastCtrBits))-1));

    if (prediction)
    {
        value = valuePredictionTable[index];
    }

    return prediction;
    
}

uint8_t
LVP::getconf(Addr inst_addr, RegVal &value)
{
    unsigned index = inst_addr%lastPredictorSize;

    uint8_t counter_val = classificationTable[index];



    return counter_val; // Returning prediction confidence
}

void
LVP::updateTable(Addr inst_addr, bool isValuePredicted, bool isValueTaken, RegVal &trueValue)
{
    unsigned index = inst_addr%lastPredictorSize;
    //uint8_t counter_val = classificationTable[index];

    if (isValuePredicted)
    {
        if (isValueTaken)
        {
            // The Value predicted and True values are the same.
            classificationTable[index]++; 
        }
        else
        {
            // Decrease the counter and update the value to prediction table.
            /*            
            if (counter_val<5){
               valuePredictionTable[index] = trueValue;
               
            }
            */
            //classificationTable[index].reset();
            classificationTable[index]--;
            valuePredictionTable[index] = trueValue;
        }
    }
    else
    {
        /*Increasing the Counter when the Predictor doesn't predict, so that it predicts in next instance.*/
        classificationTable[index]++;
        valuePredictionTable[index] = trueValue;
    }
    
}

 LVP*
 LVPParams::create()
 {
     return new LVP(this);
 }

