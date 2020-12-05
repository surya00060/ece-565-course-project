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
        bool predict(const StaticInstPtr &inst, Addr inst_addr, RegVal &value);

        virtual bool lookup(Addr inst_addr, RegVal &value) = 0;

        float getpredictconf(Addr inst_addr, RegVal &value);

        virtual float getconf(Addr inst_addr, RegVal &value) = 0;

        void update(const StaticInstPtr &inst, Addr inst_addr, bool isValuePredicted, bool isValueTaken, RegVal &trueValue);
        
        virtual void updateTable(Addr inst_addr, bool isValuePredicted, bool isValueTaken, RegVal &trueValue) = 0;

    private:
        /*Number of Possible Value Predictions*/
        Stats::Scalar lookups;

        /*Number of Values Predicted.*/
        Stats::Scalar numPredicted;

        /*Number of Correct Predictions.*/
        Stats::Scalar numCorrectPredicted;

        /*Number of Incorrect Predictions.*/
        Stats::Scalar numIncorrectPredicted;

        /*Number of Load Values Predicted.*/
        Stats::Scalar numLoadPredicted;

        /*Number of Load Values Correctly Predicted.*/
        Stats::Scalar numLoadCorrectPredicted;

        Stats::Formula valuePredAccuracy;

        Stats::Formula valuePredCoverage;
};

#endif // __CPU_PRED_VPRED_UNIT_HH__
