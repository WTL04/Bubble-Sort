#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <pthread.h>

using namespace std;

struct sortStuff
{
    int *start;
    int size;
};


int* createArray(ifstream& file, int size)
{
    int* arr = new int[size];

    //clears for any errors
    file.clear();

    //after using distance, pointer is at the end of the file
    //gets pointer to point at beginning of file
    file.seekg(0, ios::beg);

    for (int i = 0; i < size; i++)
    {
        file >> arr[i];
    }

    return arr;
}


int* bubbleSort(int arr[], int size)
{

    for (int i = 0; i < size-1; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            if (arr[j] < arr[i])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    return arr;
}

void* bridge(void *ptr)
{
    sortStuff *arg = (sortStuff *) ptr; // casting unknown pointer to a sortStuff pointer
    bubbleSort(arg -> start, arg -> size); // extracting data from sortStuff, calls bubble sort on corresponding section of array
    return NULL;
}


int main(int argc, char* argv[])
{
    string inputFile = argv[1];
    string outputFile = argv[2];
    
    ifstream infile;
    infile.open(inputFile);
    int size = distance(istream_iterator<int>(infile), istream_iterator<int>()); //gets num of integers in file
    int* arr = createArray(infile, size); // dynamic memory
    infile.close();

    pthread_t t0, t1, t2, t3, t4, t5, t6, t7;
    pthread_t t[8] = {t0, t1, t2, t3, t4, t5, t6, t7};

    // sections of array to sort
    sortStuff ss0, ss1, ss2, ss3, ss4, ss5, ss6, ss7;
    sortStuff ss[8] = {ss0, ss1, ss2, ss3, ss4, ss5, ss6, ss7};

    for (int i = 0; i < 8; i++)
    {
        ss[i].start = &arr[125000 * i];
        ss[i].size = 125000;
    }

    // setup pthreads
    int iret0, iret1, iret2, iret3, iret4, iret5, iret6, iret7;
    int iret[8] = {iret0, iret1, iret2, iret3, iret4, iret5, iret6, iret7};

    for (int i = 0; i < 8; i++)
    {
        iret[i] = pthread_create( &t[i], NULL, bridge, (void*) &ss[i]);
    }


    ofstream outfile;

    //clearing after every run
    outfile.open(outputFile, ios::trunc);
    if (!outfile)
    {
        cerr << "Error: file not found" << endl;
    }
    outfile.close();

    //opening in apend mode
    outfile.open(outputFile, ios::app);
    if (!outfile)
    {
        cout << "Error: file not found" << endl;
    }


    for (int i = 0; i < size; i++)
    {
        outfile << arr[i] << endl;
    }
    outfile.close();

    delete[] arr; //prevent memory leak
    return 0;
}

// c++ mysort.cpp -o mysort
// ./mysort numbers.dat sorted.out