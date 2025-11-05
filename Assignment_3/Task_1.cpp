#include <iostream>
#include <string>
using namespace std;

// Function to perform XOR operation between two binary strings
string xor1(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// Function to perform Mod-2 division
string mod2div(string dividend, string divisor) {
    int pick = divisor.length();
    string tmp = dividend.substr(0, pick);

    int n = dividend.length();

    while (pick < n) {
        if (tmp[0] == '1')
            tmp = xor1(divisor, tmp) + dividend[pick];
        else
            tmp = xor1(string(pick, '0'), tmp) + dividend[pick];
        pick++;
    }

    // For the last n bits
    if (tmp[0] == '1')
        tmp = xor1(divisor, tmp);
    else
        tmp = xor1(string(pick, '0'), tmp);

    // The remainder is the last (divisor_length - 1) bits
    return tmp.substr(tmp.length() - (divisor.length() - 1));
}

int main() {
    string data = "1101011011";
    string generator = "10011";  // x^4 + x + 1

    int m = generator.length();
    string appended_data = data + string(m - 1, '0');

    cout << "Appended data: " << appended_data << endl;

    string remainder = mod2div(appended_data, generator);

    cout << "Remainder: " << remainder << endl;

    string transmitted = data + remainder;
    cout << "Transmitted bit string: " << transmitted << endl;

    return 0;
}

