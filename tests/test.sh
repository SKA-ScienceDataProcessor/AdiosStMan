#!/bin/sh

sbatch --account=$IVEC_PROJECT --time=00:10:00 --nodes=10 --ntasks-per-node=1 --dependency=singleton writeMPI.sh
