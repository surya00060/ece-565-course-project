#ifndef __CPU_VPRED_LVP_PRED_HH__
#define __CPU_VPRED_LVP_PRED_HH__

#include <vector>
#include "base/sat_counter.hh"
#include "base/types.hh"
#include "cpu/vpred/vpred_unit.hh"

class LVP : public VPredUnit
{
    public:
        LVP(const LVPParams *params);

        bool lookup(ThreadID tid, Addr inst_addr, RegVal &value);

        void update(ThreadID tid, Addr inst_addr, bool prediction, RegVal &value);
}
#endif // __CPU_VPRED_LVP_PRED_HH__
