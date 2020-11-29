#ifndef __CPU_VPRED_LVP_PRED_HH__
#define __CPU_VPRED_LVP_PRED_HH__

#include <vector>

#include "base/statistics.hh"
#include "base/sat_counter.hh"
#include "base/types.hh"
#include "cpu/inst_seq.hh"
#include "cpu/static_inst.hh"
#include "params/LVP.hh"
#include "sim/sim_object.hh"

class LVP : public VPredUnit
{
    public:
        
        LVP(const LVPParams *params);

        void regStats();

        bool lookup(ThreadID tid, Addr inst_addr, RegVal &value);

        void update(ThreadID tid, Addr inst_addr, bool taken, bool squashed, RegVal &value);
    
    private:
        /** Number of Table Entries*/
        const unsigned lastPredictorSize;

        /** Number of bits to control*/
        const unsigned lastCtrBits;

        /*Array of counters*/
        std::vector<SatCounter> classificationTable;

        /*Array of value predictions*/
        std::vector<RegVal> valuePredictionTable;

        Stats::Scalar lookups;
        Stats::Scalar numPredicted;
        Stats::Scalar numIncorrectPredicted;

};
#endif // __CPU_VPRED_LVP_PRED_HH__
