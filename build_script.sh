#!/bin/bash
# Paper 1, Best performing Benchmarks [Few of them from SPEC92]: mpeg, gperf, eqntott[S], sc, gawk, cc1[S], compress[S], xlisp[S], grep
# Paper 2, SPEC95 = compress, gcc, go, ijpeg, m88k, perl, lisp
# Paper 3, Best performing benchmarks SPEC2K6: bzip2, gamess, h264, gcc, mcf, hmmer OtherBench: gobmk, milc, sjeng, lbm
#benchmarks=(bzip2 gamess h264ref gcc mcf hmmer gobmk milc sjeng lbm)
scons-3 -j 4 ./build/ARM/gem5.opt