#!/bin/bash
#SBATCH --job-name=4790
#SBATCH --exclude=compute-0-3,compute-0-4,compute-0-5,compute-0-6,compute-0-7,gpu-0-0,gpu-0-1
#SBATCH --mem=30G
#SBATCH --cpus-per-task=8
#SBATCH --time=199:00:00


#SBATCH --output=4790.txt


date;hostname;pwd
module load devel/intel-opencl/SRB5.0
export BOOST_COMPUTE_DEFAULT_DEVICE_TYPE=CPU

#KIEKIS=1000

#for x  in radix stable merge-cpu stable-by-key radix-by-key bitonic counting
#do
#echo "N TIME" > 4790_$x.txt
#for N in 16777216
#do
#./Sorting  $KIEKIS $N $x >> 4790_$x.txt
#done
#done


./main

