#include "cpu/vpred/lvp.hh"

#include "base/intmath.hh"
// #include "base/logging.hh"
// #include "base/trace.hh"
// #include "debug/Fetch.hh"
#include "iostream"

LVP::LVP(const LVPParams *params)
    : VPredUnit(params),
      lastPredictorSize(params->lastPredictorSize),
      lastCtrBits(params->lastCtrBits),
      classificationTable(lastPredictorSize, SatCounter(lastCtrBits)),
      valuePredictionTable(lastPredictorSize),
      tagTable(lastPredictorSize)
{
    // valuePredictionTable.resize(lastPredictorSize);
}

bool
LVP::lookup(Addr inst_addr, RegVal &value)
{
    unsigned index = inst_addr%lastPredictorSize;

    uint8_t counter_val = classificationTable[index];

    Addr tag=tagTable[index];


    /*Gets the MSB of the count.*/
    //bool prediction = counter_val >> (lastCtrBits-1);
    bool prediction = ((unsigned(counter_val) == (pow(2,lastCtrBits)-1)) && (tag==inst_addr>>(lastCtrBits)));  
    


    if (prediction)
    {   

        value = valuePredictionTable[index];
    }

    return prediction;
    
}

float
LVP::getconf(Addr inst_addr, RegVal &value)
{
    unsigned index = inst_addr%lastPredictorSize;

    uint8_t counter_val = classificationTable[index];



    return float(counter_val/2^lastCtrBits); // Returning prediction confidence
}

void
LVP::updateTable(Addr inst_addr, bool isValuePredicted, bool isValueTaken, RegVal &trueValue)
{
    unsigned index = inst_addr%lastPredictorSize;

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
            //classificationTable[index]--;
            classificationTable[index].reset();
            valuePredictionTable[index] = trueValue;

        }
    }
    else
    {
        /*Increasing the Counter when the Predictor doesn't predict, so that it predicts in next instance.*/
        
        if (tagTable[index]==inst_addr>>(lastCtrBits)){
           classificationTable[index]++;
           valuePredictionTable[index] = trueValue;
        }
        else{
            tagTable[index]=inst_addr>>(lastCtrBits);
            classificationTable[index].reset();
            valuePredictionTable[index] = trueValue;
        }



    }
    
}

 LVP*
 LVPParams::create()
 {
     return new LVP(this);
 }

