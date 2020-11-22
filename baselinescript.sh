# BenchMarks to Run: bzip2, gamess, h264, gcc, mcf, hmmer
./build/ARM/gem5.opt -d testBzip configs/spec2k6/run.py -b bzip2 --maxinsts=1000000000 --standard-switch --warmup-insts=100000000 --fast-forward=1000000000 --cpu-type=DerivO3CPU --caches --l1d_size=32kB  --l1d_assoc=2 --l1i_size=32kB --l1i_assoc=2  --l2cache --l2_size=2048kB --l2_assoc=8
