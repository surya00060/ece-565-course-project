#ifndef __CPU_PRED_VPRED_UNIT_HH__
#define __CPU_PRED_VPRED_UNIT_HH__


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
        bool predict(Addr inst_addr, RegVal &value);

        virtual bool lookup(Addr inst_addr, RegVal &value) = 0;

        uint8_t getpredictconf(Addr inst_addr, RegVal &value);

        virtual uint8_t getconf(Addr inst_addr, RegVal &value) = 0;

        void update(Addr inst_addr, bool isValuePredicted, bool isValueTaken, RegVal &trueValue);
        
        virtual void updateTable(Addr inst_addr, bool isValuePredicted, bool isValueTaken, RegVal &trueValue) = 0;

    private:
        Stats::Scalar lookups;
        Stats::Scalar numPredicted;
        Stats::Scalar numIncorrectPredicted;
};

#endif // __CPU_PRED_VPRED_UNIT_HH__
