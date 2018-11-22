#!/bin/bash
#SBATCH --job-name=6700
#SBATCH --exclude=compute-0-1,compute-0-2,gpu-0-0,gpu-0-1
#SBATCH --mem=30G
#SBATCH --cpus-per-task=8
#SBATCH --time=199:00:00


#SBATCH --output=6700_RadixCount.txt


date;hostname;pwd
module load devel/intel-opencl/SRB5.0
export BOOST_COMPUTE_DEFAULT_DEVICE_TYPE=CPU

#KIEKIS=1000

#for x  in radix stable merge-cpu stable-by-key radix-by-key bitonic counting
#do
#echo "N TIME" > 6700_$x.txt
#for N in 16777216  
#do
#./Sorting  $KIEKIS $N $x >> 6700_$x.txt
#done
#done


./Sorting 1000 100000000 RadixCount
