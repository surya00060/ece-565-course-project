#ifndef __CPU_VPRED_LVP_PRED_HH__
#define __CPU_VPRED_LVP_PRED_HH__

#include "cpu/vpred/vpred_unit.hh"
#include <vector>

#include "base/statistics.hh"
#include "base/sat_counter.hh"
#include "base/types.hh"
#include "cpu/inst_seq.hh"
#include "cpu/static_inst.hh"
#include "params/SVP2D.hh"
#include "sim/sim_object.hh"


class SVP2D : public VPredUnit
{
    public:
        
        SVP2D(const SVP2DParams *params);

        bool lookup(Addr inst_addr, RegVal &value);
        float getconf(Addr inst_addr, RegVal &value);

        void updateTable(Addr inst_addr, bool isValuePredicted, bool isValueTaken, RegVal &trueValue);
    
    private:
        /** Number of Table Entries*/
        const unsigned lastPredictorSize;

        /** Number of bits to control*/
        const unsigned lastCtrBits;

        /** Number of bits to control*/
        const unsigned stridehistoryLength;
        

        /*Array of counters*/
        std::vector<SatCounter> classificationTable;



        /*Array of value predictions*/
        std::vector<RegVal> valuePredictionTable;

        /*Array of Stride*/
        std::vector<RegVal> stridePredictionTable;

       /*Array of stride history*/
        std::vector<std::vector<RegVal>> strideHistoryTable;

        /*Array of tag value*/
        std::vector<Addr> tagTable;

};
#endif // __CPU_VPRED_LVP_PRED_HH__
