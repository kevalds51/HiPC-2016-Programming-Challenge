import os
import sys

min_algo=10e9;
min_e2e=1000;
avg_algo=0;
avg_e2e=0;

if len(sys.argv) == 1:
	print "Format: sh ./run.sh <input_csv_file>"
 	exit(0)

in_file = sys.argv[1]
out_file = "ThreeThreads_"+in_file

if not os.path.isfile(in_file):
	print in_file+" Does not exist in this directory."
	exit(0)

os.system("wc -l "+in_file+" | awk '{print $1}' > temp_n.txt");
fn = open("temp_n.txt", "r");
n = int(fn.readline().strip());
fn.close();

for i in range(0,3):

	os.system("perl hires_time.pl ./temp "+ str(n) +" < "+in_file +" > " + out_file);
	f1=open("temp_algo_time.txt","r");
	f2=open("temp_e2e_time.txt","r");
	algo_time=float(f1.readline().strip());
	e2e_time=float(f2.readline().strip());
	if algo_time<min_algo:
		min_algo=algo_time;
	if e2e_time<min_e2e:
		min_e2e=e2e_time;
	avg_algo+=algo_time;
	avg_e2e+=e2e_time;
	# print avg_algo, avg_e2e;
	f1.close()
	f2.close()

print "Minimum Algorithm time: %d microseconds" % (int(min_algo))
print "Minimum End-to-End time: %f seconds" % float(min_e2e)
print "Average Algorithm time: %d microseconds" % (int(avg_algo/3.0))
print "Average End-to-End time: %f seconds" % (float(avg_e2e/3.0))

os.system("rm temp_n.txt");
os.system("rm temp_algo_time.txt");	# remove temporary files
os.system("rm temp_e2e_time.txt");