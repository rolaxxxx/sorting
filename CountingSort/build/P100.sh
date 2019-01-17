#!/bin/bash
#SBATCH --job-name=P100
#SBATCH --gres=gpu:tesla:0
#SBATCH --mem=30G
#SBATCH --cpus-per-task=40
#SBATCH --time=199:00:00


#SBATCH --output=outputas_P100.txt


date;hostname;pwd
rm -rf ~/.nv/ComputeCache/*
export LD_LIBRARY_PATH=/share/apps/compilers/gcc-7.3.0/lib:/share/apps/compilers/gcc-7.3.0/lib64:/share/apps/devel/hdf5-1.8.20/lib/
export LD_LIBRARY_PATH=/share/apps/graphical/vtk-8.1.0/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/share/apps/devel/boost_1_66_0/lib:$LD_LIBRARY_PATH
export BOOST_COMPUTE_DEFAULT_DEVICE_TYPE=GPU



./main






