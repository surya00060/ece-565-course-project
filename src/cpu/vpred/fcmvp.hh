#ifndef __CPU_VPRED_LVP_PRED_HH__
#define __CPU_VPRED_LVP_PRED_HH__

#include "cpu/vpred/vpred_unit.hh"
#include <vector>

#include "base/statistics.hh"
#include "base/sat_counter.hh"
#include "base/types.hh"
#include "cpu/inst_seq.hh"
#include "cpu/static_inst.hh"
#include "params/FCMVP.hh"
#include "sim/sim_object.hh"


class FCMVP : public VPredUnit
{
    public:
        
        FCMVP(const FCMVPParams *params);

        bool lookup(Addr inst_addr, RegVal &value);
        
        float getconf(Addr inst_addr, RegVal &value);

        void updateTable(Addr inst_addr, bool isValuePredicted, bool isValueTaken, RegVal &trueValue);

        static inline RegVal computeHash(RegVal data)
        {
            RegVal hash = 0;
            RegVal bits = 0;
            for (int i = 0; i < 8; ++i)
            {
                 bits = ((1 << 8) - 1) & (data >> (8*i));
                 hash = hash ^ bits;
            }
            return hash;
        }
    
    private:
        /*Number of history values to track*/
        const unsigned historyLength;

        /** Number of History Table Entries*/
        const unsigned historyTableSize;

        /** Number of History Table Entries*/
        const unsigned valuePredictorTableSize;

        /** Number of bits to control*/
        const unsigned ctrBits;

        /*Array of counters*/
        std::vector<SatCounter> classificationTable;

        /*Array of value predictions*/
        std::vector<std::vector<RegVal>> valueHistoryTable;

        std::vector<RegVal> valuePredictionTable;

        /*Array of tag value*/
        std::vector<Addr> tagTable;
        
};
#endif // __CPU_VPRED_LVP_PRED_HH__
