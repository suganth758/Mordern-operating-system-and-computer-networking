#include <iostream>
#include <string>
using namespace std;

// Function to perform XOR-based modulo-2 division
string mod2div(string dividend, string divisor) {
    int pick = divisor.length();
    string tmp = dividend.substr(0, pick);

    while (pick < dividend.length()) {
        // If leftmost bit is 1, perform XOR with divisor
        if (tmp[0] == '1') {
            for (int i = 0; i < divisor.length(); i++)
                tmp[i] = (tmp[i] == divisor[i]) ? '0' : '1';
        }
        // Remove leading zeros
        tmp.erase(0, tmp.find_first_not_of('0', 0));
        // Bring next bit down
        tmp += dividend[pick++];
    }

    // Last step of division
    if (tmp[0] == '1') {
        for (int i = 0; i < divisor.length(); i++)
            tmp[i] = (tmp[i] == divisor[i]) ? '0' : '1';
    }

    // Remove leading zeros
    tmp.erase(0, tmp.find_first_not_of('0', 0));
    if (tmp.empty()) tmp = "0";

    return tmp; // remainder
}

int main() {
    string data = "10011101";   // given data
    string divisor = "1001";    // x^3 + 1

    int m = divisor.length() - 1;

    // Step 1: Append m zeros to data
    string appended_data = data + string(m, '0');

    // Step 2: Perform division to get remainder
    string remainder = mod2div(appended_data, divisor);

    // Step 3: Transmitted frame = original data + remainder
    string transmitted = data + remainder;

    cout << "Original Data:       " << data << endl;
    cout << "Generator (divisor): " << divisor << " (x^3 + 1)" << endl;
    cout << "CRC Remainder:       " << remainder << endl;
    cout << "Transmitted Frame:   " << transmitted << endl;

    // Step 4: Simulate an error (invert 3rd bit from left)
    string received = transmitted;
    received[2] = (received[2] == '0') ? '1' : '0'; // flip 3rd bit

    cout << "\nReceived Frame (with error): " << received << endl;

    // Step 5: Receiver checks for error
    string remCheck = mod2div(received, divisor);

    if (remCheck == "0")
        cout << "Receiver: No Error Detected." << endl;
    else
        cout << "Receiver: Error Detected! (Remainder = " << remCheck << ")" << endl;

    return 0;
}
