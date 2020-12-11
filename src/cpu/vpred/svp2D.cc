#include "cpu/vpred/svp2D.hh"

#include "base/intmath.hh"

SVP2D::SVP2D(const SVP2DParams *params)
    : VPredUnit(params),
      lastPredictorSize(params->lastPredictorSize),
      lastCtrBits(params->lastCtrBits),
      stridehistoryLength(params->stridehistoryLength),
      classificationTable(lastPredictorSize, SatCounter(lastCtrBits)),
      valuePredictionTable(lastPredictorSize),
      stridePredictionTable(lastPredictorSize),
      strideHistoryTable(lastPredictorSize, std::vector<RegVal> (params->stridehistoryLength)),
      finalstridePredictionTable(lastPredictorSize),      
      tagTable(lastPredictorSize)
{
    // valuePredictionTable.resize(lastPredictorSize);
}

bool
SVP2D::lookup(Addr inst_addr, RegVal &value)
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
        RegVal stride = finalstridePredictionTable[index];
        value += stride;
    }

    return prediction;
    
}

float
SVP2D::getconf(Addr inst_addr, RegVal &value)
{
    unsigned index = inst_addr%lastPredictorSize;

    uint8_t counter_val = classificationTable[index];



    return float(counter_val/2^lastCtrBits); // Returning prediction confidence
}

void
SVP2D::updateTable(Addr inst_addr, bool isValuePredicted, bool isValueTaken, RegVal &trueValue)
{
    unsigned index = inst_addr%lastPredictorSize;

    RegVal prevValue = valuePredictionTable[index];
    RegVal stride = trueValue - prevValue;
    
    for(int i = 1; i < stridehistoryLength; i++)
    {
            
            strideHistoryTable[index][i-1] = strideHistoryTable[index][i];
    }

    strideHistoryTable[index][stridehistoryLength-1]=stride;

    bool changestride = (strideHistoryTable[index][stridehistoryLength-2]==strideHistoryTable[index][stridehistoryLength-1]); // checking if last 2 values are the same

    if (isValuePredicted)
    {
        if (isValueTaken)
        {
            // The Value predicted and True values are the same.
            classificationTable[index]++; 

            valuePredictionTable[index] = trueValue;

            if (changestride)
            stridePredictionTable[index] = stride;
        }
        else
        {
            // Decrease the counter and update the value to prediction table.
            classificationTable[index].reset();
            valuePredictionTable[index] = trueValue;

            if (changestride)
            stridePredictionTable[index] = stride;
        }
    }
    else
    {
        /*Increasing the Counter when the Predictor doesn't predict, so that it predicts in next instance.*/

        if (tagTable[index]==inst_addr>>(lastCtrBits)){
        classificationTable[index]++;
        valuePredictionTable[index] = trueValue;

        if (changestride)
        stridePredictionTable[index] = stride;

        }
        else{
        tagTable[index]=inst_addr>>(lastCtrBits);
        classificationTable[index].reset();
        valuePredictionTable[index] = trueValue;

        if (changestride)
        stridePredictionTable[index] = stride;
        }
    }
    
}

 SVP2D*
 SVP2DParams::create()
 {
     return new SVP2D(this);
 }

