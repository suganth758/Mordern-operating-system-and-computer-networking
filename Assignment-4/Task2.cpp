#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Function to calculate number of redundant bits
int calcRedundantBits(int m) {
    int r = 0;
    while (pow(2, r) < (m + r + 1)) 
        r++;
    return r;
}

int main() {
    string data;
    cout << "Enter binary data: ";
    cin >> data;

    int m = data.length();
    int r = calcRedundantBits(m);
    int n = m + r;

    vector<int> hamming(n + 1);

    // Step 1: Insert data bits and reserve parity positions
    int j = 0;  // index for data input
    for (int i = 1; i <= n; i++) {
        if ((i & (i - 1)) == 0) {
            hamming[i] = 0;  // parity bit placeholder
        } else {
            hamming[i] = data[m - j - 1] - '0';
            j++;
        }
    }

    // Step 2: Calculate parity bits using even parity
    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int parity = 0;

        for (int k = 1; k <= n; k++) {
            if (k & pos) 
                parity ^= hamming[k];
        }

        hamming[pos] = parity;
    }

    cout << "\nTransmitted Hamming Code: ";
    for (int i = n; i >= 1; i--)
        cout << hamming[i];
    cout << endl;

    // Step 3: Simulate error (receiver)
    int errPos;
    cout << "\nEnter error position to simulate (0 = no error): ";
    cin >> errPos;

    if (errPos > 0 && errPos <= n) {
        hamming[errPos] ^= 1;  // flip bit
        cout << "Received code with error: ";
        for (int i = n; i >= 1; i--)
            cout << hamming[i];
        cout << endl;
    }

    // Step 4: Recalculate parity at receiver
    int error = 0;
    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int parity = 0;

        for (int k = 1; k <= n; k++) {
            if (k & pos)
                parity ^= hamming[k];
        }

        if (parity != 0)
            error += pos;
    }

    // Step 5: Show results
    if (error == 0) {
        cout << "\nNo error detected in received data.\n";
    } else {
        cout << "\nError detected at bit position: " << error << endl;

        // Correct the error
        hamming[error] ^= 1;

        cout << "Corrected Hamming Code: ";
        for (int i = n; i >= 1; i--)
            cout << hamming[i];
        cout << endl;
    }

    return 0;
}

