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


// merges two sections into 1
sortStuff merge(sortStuff & section1, sortStuff & section2)
{
    int newSize = section1.size + section2.size; // .size because setions are sortStuff datatype
    int* tempArr = new int[newSize]; // dynamic memory array

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

    section1.start = tempArr; // sets .start pointer to point to tempArr
    section1.size = newSize;
    return section1;
}

void mergeAll(sortStuff ss[])
{
    sortStuff sec1_2 = merge(ss[0], ss[1]);
    sortStuff sec3_4 = merge(ss[2], ss[3]);
    sortStuff sec5_6 = merge(ss[4], ss[5]);
    sortStuff sec7_8 = merge(ss[6], ss[7]);

    sortStuff sec1_2_3_4 = merge(sec1_2, sec3_4);
    sortStuff sec5_6_7_8 = merge(sec5_6, sec7_8);

    sortStuff sortedArr = merge(sec1_2_3_4, sec5_6_7_8);

    ss[0] = sortedArr;
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
        ss[i].start = &arr[size/8 * i]; // accessing memory location
        ss[i].size = size/8;
    }

    // setup pthreads
    int iret[8];

    for (int i = 0; i < 8; i++)
    {
        iret[i] = pthread_create( &t[i], NULL, bridge, (void*) &ss[i]);
    }

    // wait for all threads to finish
    for (int i = 0; i < 8; i++)
    {
        pthread_join(t[i], NULL);
    }
    
    // merging all into one array
    mergeAll(ss);

    // Copying sorted elements back to the original array arr
    int idx = 0;
    for (int j = 0; j < ss[0].size; j++) 
    {
        arr[idx++] = ss[0].start[j];
    }

    ofstream outfile;
    
    //clearing after every run
    outfile.open(outputFile, ios::trunc);
    outfile.close();

    //opening in apend mode
    outfile.open(outputFile, ios::app);

        for (int i = 0; i < size; i++)
        {
            outfile << arr[i] << endl;
        }
    
    outfile.close();


    delete[] arr; //prevent memory leak
    return 0;
}
