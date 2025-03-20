#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


bool Branje_Stevil(vector<unsigned char>& vec, const char s[]) {
    ifstream input(s);
    int st;
    if (!input.is_open()) {
        return false;
    }
    while (!input.eof()) {
        input >> st;
        // Ensure values are within the 8-bit unsigned range [0, 255]
        if (st >= 0 && st <= 255) {
            vec.push_back(static_cast<unsigned char>(st));
        }
        while (isspace(input.peek())) input.get();
    }
    input.close();
    return true;
}

void Izpis_Stevil(unsigned char* polje, unsigned int velikost) {
    ofstream output("out.txt");
    for (unsigned int i = 0; i < velikost; i++)
        output << static_cast<int>(polje[i]) << ' ';
}

int main(int argc, const char* argv[]) {
    vector<unsigned char> A;
    if (argc < 2) return 0;
    if (!Branje_Stevil(A, argv[1])) return 0;

    

    Izpis_Stevil(&A[0], A.size());
    return 0;
}

