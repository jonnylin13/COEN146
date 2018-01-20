#include <iostream>
#include <ostream>
#include <fstream>
#include <cstring>

using namespace std;

void writeLetter(string names[], int size, char letter, ostream& output) {
    ifstream input;
    input.open('names.txt');

    string organize[size];
    string placeholder[size];

    for (int i = 0; i < size; i++) {
        input >> placeholder[size];
    }
}

int main() {
    string names[6];
    writeLetter(names, 6, );
}