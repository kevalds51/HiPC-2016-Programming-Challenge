Team: Three Threads
Members:

	1. Keval D. Shah
	2. Abhi Shah
	3. Parswha Shah

Registered E-mail: kevalds51@gmail.com

Please follow these Instructions for Compiling and executing:

Run the following commands on the bash prompt:

1. Move into the src folder inside the Three_Threads_intel folder in the extracted directory.

	$cd Intel_Three_Threads_phase2/src/

2. Do the following to run the shell script and thus build the executables:

	$sh ./compile.sh

3. Run the following shell script with input file as a parameter to print the output in an ASCII file in csv format.
   (Please see to it that the input csv file is in the src folder)

   (NOTE: The below command will run the code 3 times, printing average and minimun times on stdout)

	$sh ./run.sh <input_file.csv>

4. Generated ‘<output_file>.csv’ contains the connected-set index to which the corresponding points belong.
	The code times are diplayed on stdout.

Example:

	Suppose you want to execute the code for file: "LargeDataSet_IntelTrack.csv" (to be placed in src). Then after compilation, execute as:

		$sh ./run.sh LargeDataSet_IntelTrack.csv

		The output file for this: ThreeThreads_LargeDataSet_IntelTrack.csv is generated in the same folder.

