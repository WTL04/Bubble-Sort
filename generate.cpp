// William Luu
// Class (CECS 325-02)
// Program 3 - Bubble Sort
// 3/12/2024
// I certify that this program is my own original work. I did not copy any part of this program from any other source. I further certify that I typed each and every line of code in this program.


#include <iostream>
#include <fstream>
#include <cstdlib> //for rand
#include <ctime> //for time
#include <string>

using namespace std;

int generateRandInt(int min, int max)
{
    return min + rand() % (max - min + 1); //get num in range (min to max)
}

// COUNT, MIN, MAX
int main(int argc, char* argv[])  //argc: keeps count of # of arguments, argv: the arguments
{
    //argv[0] = name of prog
    //argv[1] = 1st arg
    //argv[2] = 2nd arg
    //argv[3] = 3rd arg
    // so argc is 4

    int count = stoi(argv[1]);
    int min = stoi(argv[2]);
    int max = stoi(argv[3]);

    cout << "argv[0]: " << argv[0] << endl;
    cout << "argv[1]: " << count << endl;
    cout << "argv[2]: " << min << endl;
    cout << "argv[3]: " << max << endl;

    if (argc != 4)
    {
        cerr << "Error: Not enough arguments" << endl;
    }

    ofstream outfile;
    outfile.open("numbers.dat", ios::trunc); //opens file and clears it out
    if (!outfile)
    {
        cerr << "Error: file not found" << endl;
    }
    outfile.close();

    //reopened file
    outfile.open("numbers.dat", ios::app); //opens file in append mode
    if (!outfile)
    {
        cerr << "Error: file not found" << endl;
    }


    //seed rand() time
    srand(time(nullptr));

    for (int i = 0; i < count; i++)
    {
        int randInt = generateRandInt(min, max);
        outfile << randInt << endl;
    }

    outfile.close();


    return 0;
}

// c++ generate.cpp -o gen
// ./gen 10000 -10000 10000