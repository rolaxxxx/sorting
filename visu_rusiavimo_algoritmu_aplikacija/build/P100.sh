#!/bin/bash
#SBATCH --job-name=P100
#SBATCH --gres=gpu:tesla:0
#SBATCH --mem=30G
#SBATCH --cpus-per-task=40
#SBATCH --time=199:00:00


#SBATCH --output=outputas.txt


date;hostname;pwd
rm -rf ~/.nv/ComputeCache/*
export LD_LIBRARY_PATH=/share/apps/compilers/gcc-7.3.0/lib:/share/apps/compilers/gcc-7.3.0/lib64:/share/apps/devel/hdf5-1.8.20/lib/
export LD_LIBRARY_PATH=/share/apps/graphical/vtk-8.1.0/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/share/apps/devel/boost_1_66_0/lib:$LD_LIBRARY_PATH
export BOOST_COMPUTE_DEFAULT_DEVICE_TYPE=GPU



#KIEKIS=1000

#for x  in radix stable merge-gpu stable-by-key radix-by-key bitonic counting
#do
#echo "N TIME" > P100_$x.txt
#for N in 131072 262144 524288 1048576 2097152 4194304 8388608 16777216
#do
#./Sorting  $KIEKIS $N $x >> P100_$x.txt
#done
#done



./Sorting 1000 16777216 RadixCount






