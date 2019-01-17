#!/bin/bash
#SBATCH --job-name=E5-2630
#SBATCH --exclude=compute-0-1,compute-0-2,compute-0-3,compute-0-4,compute-0-5,compute-0-6,compute-0-7,gpu-0-1
#SBATCH --mem=30G
#SBATCH --cpus-per-task=40
#SBATCH --time=199:00:00


#SBATCH --output=outputas_xeon.txt


date;hostname;pwd
module load devel/intel-opencl/SRB5.0
export BOOST_COMPUTE_DEFAULT_DEVICE_TYPE=CPU


./main







