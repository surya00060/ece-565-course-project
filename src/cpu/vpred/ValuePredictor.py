from m5.SimObject import SimObject
from m5.params import *
from m5.proxy import *

<<<<<<< HEAD
class ValuePredictor(SimObject):
    type = 'ValuePredictor'
    cxx_class = 'VPredUnit'
    cxx_header = "cpu/vpred/vpred_unit.hh"
    abstract = True

    numThreads = Param.Unsigned(Parent.numThreads, "Number of threads")

class LVP(ValuePredictor):
    type = 'LVP'
    cxx_class = 'LVP'
    cxx_header = "cpu/vpred/lvp.hh"

    localPredictorSize = Param.Unsigned(2048, "Size of local predictor")
    localCtrBits = Param.Unsigned(2, "Bits per counter")
=======
class LVP(SimObject):
    type = 'LVP'
    cxx_class = 'LVP'
    cxx_header = "cpu/vpred/lvp.hh"
    abstract = True

    # numThreads = Param.Unsigned(Parent.numThreads, "Number of threads")
    lastPredictorSize = Param.Unsigned(4096, "Size of LVP predictor")
    lastCtrBits = Param.Unsigned(3, "Bits per counter")
>>>>>>> ba3afd72dac2ec59f96266d9367c17e26f8ba958
