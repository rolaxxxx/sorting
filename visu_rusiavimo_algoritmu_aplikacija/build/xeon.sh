#!/bin/bash
#SBATCH --job-name=E5-2630
#SBATCH --exclude=compute-0-1,compute-0-2,compute-0-3,compute-0-4,compute-0-5,compute-0-6,compute-0-7,gpu-0-1
#SBATCH --mem=30G
#SBATCH --cpus-per-task=40
#SBATCH --time=199:00:00


#SBATCH --output=outputas.txt


date;hostname;pwd
module load devel/intel-opencl/SRB5.0
export BOOST_COMPUTE_DEFAULT_DEVICE_TYPE=CPU

KIEKIS=1000

for x  in radix stable merge-cpu stable-by-key radix-by-key bitonic counting
do
echo "N TIME" > xeon_$x.txt
for N in 131072 262144 524288 1048576 2097152 4194304 8388608 16777216
do
./Sorting  $KIEKIS $N $x >> xeon_$x.txt
done
done







