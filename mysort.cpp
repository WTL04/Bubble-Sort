#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

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

    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (arr[j] > arr[i])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    return arr;
}


int main(int argc, char* argv[])
{
    string inputFile = argv[1];
    string outputFile = argv[2];
    
    ifstream infile;
    infile.open(inputFile);

    int size = distance(istream_iterator<int>(infile), istream_iterator<int>()); //gets num of integers in file
    int* arr = createArray(infile, size);
    infile.close();

    bubbleSort(arr, size);

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
        outfile << arr[i] << " ";
    }
    outfile.close();

    delete[] arr; //prevent memory leak
    return 0;
}

// c++ mysort.cpp -o mysort
// ./mysort numbers.dat sorted.out