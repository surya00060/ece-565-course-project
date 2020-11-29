#ifndef __CPU_PRED_VPRED_UNIT_HH__
#define __CPU_PRED_VPRED_UNIT_HH__

#include <vector>

#include "base/sat_counter.hh"
#include "base/types.hh"
#include "cpu/inst_seq.hh"
#include "cpu/static_inst.hh"
#include "sim/probe/pmu.hh"
#include "sim/sim_object.hh"
#include "sim/stats.hh"
#include "params/ValuePredictor.hh"

class VPredUnit : public SimObject
{
    public:
        typedef ValuePredictorParams Params;
    
    VPredUnit(const Params *p);

    void regStats() override;

    /*
    * Predicts whether to do VP and returns the predicted value by reference. 
    */
    bool predict(ThreadID tid, Addr inst_addr, RegVal &value);

    virtual bool lookup(ThreadID tid, Addr inst_addr, RegVal &value) = 0;


    /**
     */
    //void update_table(, ThreadID tid);
    
    void update_table(ThreadID tid, Addr inst_addr, bool taken, bool squashed, RegVal &value);
    virtual void update(ThreadID tid, Addr inst_addr, bool taken, bool squashed, RegVal &value) = 0;

    private:


        Stats::Scalar lookups;
        Stats::Scalar numPredicted;
        Stats::Scalar numIncorrectPredicted;


};

#endif // __CPU_PRED_VPRED_UNIT_HH__
