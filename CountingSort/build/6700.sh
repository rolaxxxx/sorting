#!/bin/bash
#SBATCH --job-name=6700
#SBATCH --exclude=compute-0-1,compute-0-2,gpu-0-0,gpu-0-1
#SBATCH --mem=30G
#SBATCH --cpus-per-task=8
#SBATCH --time=199:00:00


#SBATCH --output=6700_out.txt


date;hostname;pwd
module load devel/intel-opencl/SRB5.0
export BOOST_COMPUTE_DEFAULT_DEVICE_TYPE=CPU


./main
