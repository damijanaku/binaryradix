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

vector<int> countingSort(const vector<int>& A) {

	//find min value
	int minValue = A[0];
	for (size_t i = 1; i < A.size(); i++) {
		if (A[i] < minValue) {
			minValue = A[i];
		}
	}

	//podpora negativnim stevilom
	for (size_t i = 0; i < A.size(); i++) {
		A[i] -= minValue;
	}


	int maxValue = A[0];
	//find max value
	for (size_t i = 1; i < A.size(); i++) {
		if (A[i] > maxValue) {
			maxValue = A[i];
		}
	}

	//initicalizacija polja c
	vector<int> C(maxValue + 1, 0);


	for (size_t i = 0; i < A.size(); i++) {
		C[A[i]]++;
	}

	for (size_t i = 1; i < C.size(); i++) {
		C[i] += C[i - 1];
	}

	vector<int> B(A.size());

	for (int i = A.size() - 1; i >= 0; i--) {
		B[C[A[i]] - 1] = A[i];
		C[A[i]]--;
	}

	for (int i = 0; i < A.size(); i++) {
		A[i] = B[i] + minValue;
	}
}

int main(int argc, const char* argv[]) {
    vector<unsigned char> A;
    if (argc < 2) return 0;
    if (!Branje_Stevil(A, argv[1])) return 0;

    

    Izpis_Stevil(&A[0], A.size());
    return 0;
}

