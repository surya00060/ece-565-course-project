#!/bin/bash
# Paper 1, Best performing Benchmarks [Few of them from SPEC92]: mpeg, gperf, eqntott[S], sc, gawk, cc1[S], compress[S], xlisp[S], grep
# Paper 2, SPEC95 = compress, gcc, go, ijpeg, m88k, perl, lisp
# Paper 3, Best performing benchmarks SPEC2K6: bzip2, gamess, h264, gcc, mcf, hmmer OtherBench: gobmk, milc, sjeng, lbm
#benchmarks=(bzip2 gamess h264ref gcc mcf hmmer gobmk milc sjeng lbm)
benchmarks=(lbm milc sjeng)
for b in "${benchmarks[@]}"; do
    folder="VPTest_"$b
    ./build/ARM/gem5.opt -d $folder configs/spec2k6/run.py -b $b --maxinsts=1000000000 --warmup-insts=50000000 --cpu-type=TimingSimpleCPU
done