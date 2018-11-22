#!/bin/bash
#SBATCH --job-name=K5000
#SBATCH --exclude=compute-0-1,compute-0-2,compute-0-3,compute-0-4,compute-0-5,compute-0-6,compute-0-7,gpu-0-0
#SBATCH --gres=gpu:quadro:0
#SBATCH --output=quadro-counting.txt
#SBATCH --mem=30G
#SBATCH --cpus-per-task=8
#SBATCH --time=199:00:00

date;hostname;pwd
rm -rf ~/.nv/ComputeCache/*
export LD_LIBRARY_PATH=/share/apps/compilers/gcc-7.3.0/lib:/share/apps/compilers/gcc-7.3.0/lib64:/share/apps/devel/hdf5-1.8.20/lib/
export LD_LIBRARY_PATH=/share/apps/graphical/vtk-8.1.0/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/share/apps/devel/boost_1_66_0/lib:$LD_LIBRARY_PATH
export BOOST_COMPUTE_DEFAULT_DEVICE_TYPE=GPU



./Sorting
