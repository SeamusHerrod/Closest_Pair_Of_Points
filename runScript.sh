#!/bin/bash

# Define the directory containing the input files
INPUT_DIR="Inputs"

#Define the directory containing the output files
OUTPUT_DIR="Outputs"

#Define the directory containing the log files 
LOG_DIR="Logs"
# Define the log file


# Define your CPU clock rate
CPU_CLOCK_RATE="3504.00"

# Loop over all input files in the directory
for i in {1..10}
do
    # Define the input and output files
    INPUT_FILE="${INPUT_DIR}/input_${i}.txt"
    OUTPUT_FILE="result_${i}.txt"

    LOG_FILE_CHECK="${LOG_DIR}/log_${i}.txt"
    
    CHECK_OUT="${OUTPUT_DIR}/output_${i}.txt"

    LOG_FILE="time_log_${i}.txt"

    # Run the command
    /usr/bin/time -v -o ${LOG_FILE} ./Lab04 ${INPUT_FILE} >${OUTPUT_FILE} 

    # Run the grading script for each output file
    python3 GradingScript.py ${OUTPUT_FILE} ${CHECK_OUT} ${LOG_FILE} ${LOG_FILE_CHECK} ${CPU_CLOCK_RATE}

    echo "Iteration ${i} finished."

done
