#include "cpu/vpred/fcmvp.hh"

#include "base/intmath.hh"

FCMVP::FCMVP(const FCMVPParams *params)
    : VPredUnit(params),
      historyLength(params->historyLength),
      historyTableSize(params->historyTableSize),
      valuePredictorTableSize(params->valuePredictorTableSize),
      ctrBits(params->ctrBits),
      classificationTable(historyTableSize, SatCounter(ctrBits)),
      valueHistoryTable(historyTableSize, std::vector<RegVal> (historyLength)),
      valuePredictionTable(valuePredictorTableSize),
      tagTable(historyTableSize)
{
    // valuePredictionTable.resize(lastPredictorSize);
}

bool
FCMVP::lookup(Addr inst_addr, RegVal &value)
{
    unsigned indexVHT = inst_addr%historyTableSize;

    uint8_t counter_val = classificationTable[indexVHT];

    Addr tag=tagTable[indexVHT];

    /*Gets the MSB of the count.*/
    //bool prediction = counter_val >> (ctrBits-1);
    bool prediction = ((unsigned(counter_val) == (pow(2,ctrBits)-1)) && (tag==inst_addr));

    if (prediction)
    {
        RegVal hashedHistory = valueHistoryTable[indexVHT][0];

        for(int i = 1; i < historyLength; ++i)
        {
            hashedHistory = hashedHistory ^ valueHistoryTable[indexVHT][i];
        }
        unsigned indexVPT = hashedHistory%valuePredictorTableSize;
        value = valuePredictionTable[indexVPT];
    }

    return prediction;
    
}

float
FCMVP::getconf(Addr inst_addr, RegVal &value)
{
    unsigned index = inst_addr%historyTableSize;

    uint8_t counter_val = classificationTable[index];

    return float(counter_val/2^ctrBits); // Returning prediction confidence
}

void
FCMVP::updateTable(Addr inst_addr, bool isValuePredicted, bool isValueTaken, RegVal &trueValue)
{
    unsigned indexVHT = inst_addr%historyTableSize;;

    // Value is predicted only if tag matches and high confidence. 
    if (isValuePredicted)
    {
        if (isValueTaken)
        {
            // The Value predicted and True values are the same.
            classificationTable[indexVHT]++;
        }
        else
        {
            // Decrease the counter and update the value to prediction table.
            classificationTable[indexVHT].reset();
        }

        // Update History and Tables for tag match case.
        // Add the new data history at historyLength-1. O is the Least recently used.
        RegVal hashedHistory = valueHistoryTable[indexVHT][0];

        for(int i = 1; i < historyLength; i++)
        {
            hashedHistory = hashedHistory ^ valueHistoryTable[indexVHT][i];
            valueHistoryTable[indexVHT][i-1] = valueHistoryTable[indexVHT][i];
        }

        valueHistoryTable[indexVHT][historyLength-1] = trueValue;

        unsigned indexVPT = hashedHistory%valuePredictorTableSize;
        valuePredictionTable[indexVPT] = trueValue;
    }
    // Tag matches but counter satration not reached.
    else if (tagTable[indexVHT]==inst_addr)
    {
        classificationTable[indexVHT]++;

        RegVal hashedHistory = valueHistoryTable[indexVHT][0];

        for(int i = 1; i < historyLength; i++)
        {
            hashedHistory = hashedHistory ^ valueHistoryTable[indexVHT][i];
            valueHistoryTable[indexVHT][i-1] = valueHistoryTable[indexVHT][i];
        }

        valueHistoryTable[indexVHT][historyLength-1] = trueValue;

        unsigned indexVPT = hashedHistory%valuePredictorTableSize;
        valuePredictionTable[indexVPT] = trueValue;
    }
    // Tag doesn't match. So, reset the counter. Reset the history values to zero.
    else
    {
        tagTable[indexVHT]=inst_addr;
        classificationTable[indexVHT].reset();
        classificationTable[indexVHT]++;
        
        for(int i = 0; i < historyLength; i++)
        {
            valueHistoryTable[indexVHT][i] = 0;
        }
        valueHistoryTable[indexVHT][historyLength-1] = trueValue;
        RegVal hashedHistory = trueValue;

        unsigned indexVPT = hashedHistory%valuePredictorTableSize;
        valuePredictionTable[indexVPT] = trueValue;
    }
}

 FCMVP*
 FCMVPParams::create()
 {
     return new FCMVP(this);
 }

