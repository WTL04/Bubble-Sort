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

void merge(sortStuff & section1, sortStuff & section2)
{
    int tempArr[section1.size + section2.size]; // .size because setions are sortStuff datatype

    int i = 0; // index of section1
    int j = 0; // index of section2
    int k = 0; // index of temp

    // merging elements from section1 and section2 into tempArr
    while (i < section1.size && j < section2.size)
    {
        // adding values to tempArr in ascending order
        if (section1.start[i] <= section2.start[j])
        {
            tempArr[k] = section1.start[i];
            i++;
        }
        else if (section2.start[j] <= section1.start[i])
        {
            tempArr[k] = section2.start[j];
            j++;
        }
        k++;
    }

    // loops to add any remainding elements to temp
    while (i < section1.size)
    {
        tempArr[k] = section1.start[i];
        i++;
        k++;
    }

    while (j < section2.size)
    {
        tempArr[k] = section2.start[j];
        j++;
        k++;
    }

    // copying merged elements from temp to section1
    for (int i = 0; i < section1.size + section2.size; i++)
    {
        section1.start[i] = tempArr[i];
    }
    
}

void mergeAll(sortStuff (&ss)[8], int numSections) // passing array as reference, array decay to pointers when passed to functions
{

    while (numSections > 1)
    {
        int merged = 0;
        for (int i = 0; i < numSections; i += 2) // by 2 because you want adjacency sections
        {
            if (i + 1 < numSections)
            {
                merge(ss[i], ss[i+1]); // merges the two into ss[i]
                ss[merged] = ss[i]; // sets merged section into original array
                merged++;

            }
        } 
        numSections = merged; // update num of sections after merging
    }

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
    int* arr = createArray(infile, size); // dynamic memory array
    infile.close();

    pthread_t t0, t1, t2, t3, t4, t5, t6, t7;
    pthread_t t[8] = {t0, t1, t2, t3, t4, t5, t6, t7};

    // sections of array to sort
    sortStuff ss[8];

    for (int i = 0; i < 8; i++)
    {
        ss[i].start = &arr[125000 * i]; // accessing memory location
        ss[i].size = 125000;
    }

    // setup pthreads
    int iret[8];

    for (int i = 0; i < 8; i++)
    {
        iret[i] = pthread_create( &t[i], NULL, bridge, (void*) &ss[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 8; i++)
    {
        pthread_join(t[i], NULL);
    }
    
    // merging all into one array
    mergeAll(ss, 8);

    // Copying sorted elements back to the original array arr
    int idx = 0;
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < ss[i].size; j++) 
        {
            arr[idx++] = ss[i].start[j];
        }
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