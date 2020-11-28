#ifndef __CPU_PRED_VPRED_UNIT_HH__
#define __CPU_PRED_VPRED_UNIT_HH__

#include <vector>

#include "base/sat_counter.hh"
#include "base/types.hh"
#include "cpu/inst_seq.hh"
#include "cpu/static_inst.hh"
#include "sim/probe/pmu.hh"
#include "sim/sim_object.hh"


class VPredUnit : public SimObject
{
    public:
        typedef ValuePredictorParams Params;
    
    VPredUnit(const Params *p);

    //void regStats() override;

    /*
    * Predicts whether to do VP and returns the predicted value by reference. 
    */
    bool lookup(ThreadID tid, Addr inst_addr, RegVal &value);

    /**
     */
    void update(, ThreadID tid);


};

#endif // __CPU_PRED_VPRED_UNIT_HH__
