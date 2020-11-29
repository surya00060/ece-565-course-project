#include "cpu/vpred/vpred_unit.hh"

#include <vector>
#include "base/sat_counter.hh"
#include "base/types.hh"
#include "cpu/inst_seq.hh"
#include "cpu/static_inst.hh"
#include "sim/probe/pmu.hh"
#include "sim/sim_object.hh"
#include "sim/stats.hh"

VPredUnit::VPredUnit(const Params *params)
    : SimObject (params)

{

}

void 
VPredUnit::regStats()
{
    SimObject::regStats();
    lookups
        .name(name() + ".lookups")
        .desc("Number of VP lookups")
        ;

    numPredicted
        .name(name() + ".numPredicted")
        .desc("Number of value predictions")
        ;

    numIncorrectPredicted
        .name(name() + ".numIncorrectPredicted")
        .desc("Number of incorrect value predictions")
        ;
}


bool
VPredUnit::predict(ThreadID tid, Addr inst_addr, RegVal &value)
{
  ++lookups;

  bool prediction= lookup(tid,inst_addr, value);

  if (prediction){
      ++numPredicted;
  }

  return prediction;

}

void
VPredUnit::update_table(ThreadID tid, Addr inst_addr, bool taken, bool squashed, RegVal &value)
{

  update(tid, inst_addr, taken, squashed, value);

  if (!taken){
    ++numIncorrectPredicted;
  }


}




