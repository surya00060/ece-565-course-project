# BenchMarks to Run: bzip2, gamess, h264, gcc, mcf, hmmer
./build/ARM/gem5.opt -d testBzipwithSwitch configs/spec2k6/run.py -b bzip2 --maxinsts=1000000000 --standard-switch=1000000000 --warmup-insts=50000000 --cpu-type=DerivO3CPU --caches --l1d_size=32kB  --l1d_assoc=2 --l1i_size=32kB --l1i_assoc=2  --l2cache --l2_size=2mB --l2_assoc=8
./build/ARM/gem5.opt -d testBzipwoSwitch configs/spec2k6/run.py -b bzip2 --maxinsts=1000000000 --cpu-type=DerivO3CPU --caches --l1d_size=32kB  --l1d_assoc=2 --l1i_size=32kB --l1i_assoc=2  --l2cache --l2_size=2mB --l2_assoc=8
