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

vector<int> countingSort(const vector<int>& D) {
    int minValue = D[0];
    // Find the minimum value in the array
    for (size_t i = 1; i < D.size(); i++) {
        if (D[i] < minValue) {
            minValue = D[i];
        }
    }
    // Adjust for negative numbers
    vector<int> adjustedD(D.size());
    for (size_t i = 0; i < D.size(); i++) {
        adjustedD[i] = D[i] - minValue;
    }
    int maxValue = adjustedD[0];
    // Find the maximum value in the adjusted array
    for (size_t i = 1; i < adjustedD.size(); i++) {
        if (adjustedD[i] > maxValue) {
            maxValue = adjustedD[i];
        }
    }
    // Initialize the counting array
    vector<int> C(maxValue + 1, 0);
    // Count occurrences of each value
    for (size_t i = 0; i < adjustedD.size(); i++) {
        C[adjustedD[i]]++;
    }
    // Compute cumulative sum
    for (size_t i = 1; i < C.size(); i++) {
        C[i] += C[i - 1];
    }
    vector<int> B(D.size());
    // Build the sorted array
    for (int i = D.size() - 1; i >= 0; i--) {
        B[C[adjustedD[i]] - 1] = i;  // Store the original index, not the value
        C[adjustedD[i]]--;
    }
    return B;
}

int main(int argc, const char* argv[]) {
    vector<unsigned char> A;
    if (argc < 2) return 0;
    if (!Branje_Stevil(A, argv[1])) return 0;

    for (int k = 0; k < 8; k++) {
        // Ustvari vektor D z k-tim bitom vsake številke v A
        vector<int> D(A.size());
        for (size_t i = 0; i < A.size(); i++) {
            D[i] = (A[i] >> k) & 1;
        }

        // Klic funkcije za sortiranje, ki vrne indekse
        vector<int> sortedIndices = countingSort(D);

        
    }

    Izpis_Stevil(&A[0], A.size());
    return 0;
}

