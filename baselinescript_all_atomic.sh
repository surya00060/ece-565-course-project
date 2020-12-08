
#!/bin/bash
# Script to run SPEC benchmarks: Baseline
# ISA: ARM; CPU: DerivO3; System Parameters: Default; No.of Ins: 1 Billion; Warmup Ins: 100 Million; AtomicCPU Ins: 1 Billion
# Paper 1, Best performing Benchmarks [Few of them from SPEC92]: mpeg, gperf, eqntott[S], sc, gawk, cc1[S], compress[S], xlisp[S], grep 
# Paper 2, SPEC95 = compress, gcc, go, ijpeg, m88k, perl, lisp
# Paper 3, Best performing benchmarks SPEC2K6: bzip2, gamess, h264, gcc, mcf, hmmer OtherBench: gobmk, milc, sjeng, lbm
benchmarks=(mcf gobmk)
#benchmarks=(bzip2 gcc milc lbm sjeng)
#benchmarks=(bzip2 gcc mcf gobmk milc lbm sjeng)
for b in "${benchmarks[@]}"; do
    folder=$b
    echo $b, $folder
    ./build/ARM/gem5.opt -d VPresults/LVP/$folder configs/spec2k6/run.py -b $b --maxinsts=1000000000 --cpu-type=AtomicSimpleCPU &
    #./build/ARM/gem5.opt -d LVPstats configs/spec2k6/run.py -b bzip2 --maxinsts=1000000000 --cpu-type=AtomicSimpleCPU &
done 

echo "I'm done!!!"