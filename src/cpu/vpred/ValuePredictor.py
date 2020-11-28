from m5.SimObject import SimObject
from m5.params import *
from m5.proxy import *

class LVP(SimObject):
    type = 'LVP'
    cxx_class = 'LVP'
    cxx_header = "cpu/vpred/lvp.hh"
    abstract = True

    # numThreads = Param.Unsigned(Parent.numThreads, "Number of threads")
    lastPredictorSize = Param.Unsigned(4096, "Size of LVP predictor")
    lastCtrBits = Param.Unsigned(3, "Bits per counter")