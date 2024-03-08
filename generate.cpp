#include <iostream>
#include <fstream>
#include <cstdlib> //for rand
#include <ctime> //for time

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

    if (argc != 4)
    {
        cout << "Error: Not enough arguments" << endl;
    }

    ofstream file("numbers.dat");
    if (!file)
    {
        cout << "Error: file not found" << endl;
    }
    
    //seed rand() time
    srand(time(nullptr));
    // testing

    return 0;
}