c++ generate.cpp -o gen
c++ mysort.cpp -o mysort
echo Generating 100 random numbers
sleep 1
./gen 100 -100 100 # you have to write generate.cpp
sleep 1
echo Starting Array bubble sort with 100
sleep 1
echo Ending bubble sort
{ time ./mysort numbers.dat mysort.out; } 2>> test.log # you have to write mysort.cpp
sleep 1
sort -c -n mysort.out 2>> sortrace.log # verify file is sorted