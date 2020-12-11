from m5.SimObject import SimObject
from m5.params import *
from m5.proxy import *

class ValuePredictor(SimObject):
    type = 'ValuePredictor'
    cxx_class = 'VPredUnit'
    cxx_header = "cpu/vpred/vpred_unit.hh"
    abstract = True 

    #numThreads = Param.Unsigned(Parent.numThreads, "Number of threads")


class LVP(ValuePredictor):
    type = 'LVP'
    cxx_class = 'LVP'
    cxx_header = "cpu/vpred/lvp.hh"

    lastPredictorSize = Param.Unsigned(8192, "Size of LVP predictor")
    lastCtrBits = Param.Unsigned(3, "Bits per counter")


class SVP(ValuePredictor):
    type = 'SVP'
    cxx_class = 'SVP'
    cxx_header = "cpu/vpred/svp.hh"

    lastPredictorSize = Param.Unsigned(8192, "Size of SVP predictor")
    lastCtrBits = Param.Unsigned(3, "Bits per counter")

class SVP2D(ValuePredictor):
    type = 'SVP2D'
    cxx_class = 'SVP2D'
    cxx_header = "cpu/vpred/svp2D.hh"

    lastPredictorSize = Param.Unsigned(8192, "Size of SVP predictor")
    lastCtrBits = Param.Unsigned(3, "Bits per counter")
    stridehistoryLength = Param.Unsigned(2, "Size of stride history length")

class FCMVP(ValuePredictor):
    type = 'FCMVP'
    cxx_class = 'FCMVP'
    cxx_header = "cpu/vpred/fcmvp.hh"

    ctrBits = Param.Unsigned(3, "Bits per counter")
    historyLength = Param.Unsigned(4, "Size of History length")
    historyTableSize = Param.Unsigned(8192, "Size of CVP predictor")
    valuePredictorTableSize = Param.Unsigned(4096, "Size of CVP predictor")