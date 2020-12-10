#include "cpu/vpred/svp.hh"

#include "base/intmath.hh"

SVP::SVP(const SVPParams *params)
    : VPredUnit(params),
      lastPredictorSize(params->lastPredictorSize),
      lastCtrBits(params->lastCtrBits),
      classificationTable(lastPredictorSize, SatCounter(lastCtrBits)),
      valuePredictionTable(lastPredictorSize),
      stridePredictionTable(lastPredictorSize),
      tagTable(lastPredictorSize)
{
    // valuePredictionTable.resize(lastPredictorSize);
}

bool
SVP::lookup(Addr inst_addr, RegVal &value)
{
    unsigned index = inst_addr%lastPredictorSize;

    uint8_t counter_val = classificationTable[index];

    /* Get tag value */
    Addr tag=tagTable[index]; 

    /*Gets the MSB of the count.*/
    //bool prediction = counter_val >> (lastCtrBits-1);
    bool prediction = ((unsigned(counter_val) == (pow(2,lastCtrBits)-1)) && (tag==inst_addr>>(lastCtrBits))); 

    if (prediction)
    {
        value = valuePredictionTable[index];
        RegVal stride = stridePredictionTable[index];
        value += stride;
    }

    return prediction;
    
}

float
SVP::getconf(Addr inst_addr, RegVal &value)
{
    unsigned index = inst_addr%lastPredictorSize;

    uint8_t counter_val = classificationTable[index];



    return float(counter_val/2^lastCtrBits); // Returning prediction confidence
}

void
SVP::updateTable(Addr inst_addr, bool isValuePredicted, bool isValueTaken, RegVal &trueValue)
{
    unsigned index = inst_addr%lastPredictorSize;

    RegVal prevValue = valuePredictionTable[index];
    RegVal stride = trueValue - prevValue;
    
    if (isValuePredicted)
    {
        if (isValueTaken)
        {
            // The Value predicted and True values are the same.
            classificationTable[index]++; 

            valuePredictionTable[index] = trueValue;
            stridePredictionTable[index] = stride;
        }
        else
        {
            // Decrease the counter and update the value to prediction table.
            classificationTable[index].reset();
            valuePredictionTable[index] = trueValue;
            stridePredictionTable[index] = stride;
        }
    }
    else
    {
        /*Increasing the Counter when the Predictor doesn't predict, so that it predicts in next instance.*/

        if (tagTable[index]==inst_addr>>(lastCtrBits)){
        classificationTable[index]++;
        valuePredictionTable[index] = trueValue;
        stridePredictionTable[index] = stride;
        }
        else{
        tagTable[index]=inst_addr>>(lastCtrBits);
        classificationTable[index].reset();
        valuePredictionTable[index] = trueValue;
        stridePredictionTable[index] = stride;
        }
    }
    
}

 SVP*
 SVPParams::create()
 {
     return new SVP(this);
 }

