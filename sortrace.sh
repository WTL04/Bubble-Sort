# this file is called sortrace.sh
# it must have execute privilege set to run
# run it as a background task like this:
# $ rm sortrace.log # start with fresh log file
# $ ./sortrace.sh >> sortrace.log & # this may take an hour

c++ generate.cpp -o gen # updates generate.cpp for changes
c++ mysort.cpp -o mysort # updates mysort.cpp for changes

echo Generating 10000 random numbers
sleep 1
./gen 10000 -1000 1000 # you have to write generate.cpp
sleep 1
echo Starting system sort
sleep 1
{ time sort -n numbers.dat > systemsort.out; } 2>> sortrace.log
sleep 1
echo Starting my sort
echo Starting Array bubble sort with 10000
sleep 1
echo Ending bubble sort
{ time ./mysort numbers.dat mysort.out; } 2>> sortrace.log # you have to write mysort.cpp
sleep 1
sort -c -n mysort.out 2>> sortrace.log # verify file is sorted