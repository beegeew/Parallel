#!/bin/bash
#$ -V
#$ -cwd
#$ -S /bin/bash
#$ -N wertzp1-16
#$ -o wertzp116.txt
#$ -e $JOB_NAME.e$JOB_ID
#$ -q normal
#$ -pe fill 24
#$ -P hrothgar

cmd="$MCMD -np 16 -$MFIL $SGE_CWD_PATH/machinefile.$JOB_ID $SGE_CWD_PATH/proj1"
echo cmd=$cmd
$cmd
