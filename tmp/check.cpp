// Project Identifier: 0E04A31E0D60C01986ACB20081C9D8722A2519B6

#include <iostream>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

bool checkTimestampOrdering(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return false;
    }
    
    string line;
    int lineNum = 0;
    int lastTimestamp = -1;
    bool foundError = false;
    
    cout << "Checking " << filename << "..." << endl;
    
    // Skip header lines
    for (int i = 0; i < 4; ++i) {
        if (!getline(file, line)) {
            cerr << "Error: File too short, missing header" << endl;
            return false;
        }
        lineNum++;
    }
    
    // Check order lines
    int timestamp, traderId, stockId, price, quantity;
    string buySell, traderStr, stockStr, priceStr, quantityStr;
    char t, s, dollar, pound;
    
    while (file >> timestamp >> buySell >> t >> traderId >> s >> stockId 
           >> dollar >> price >> pound >> quantity) {
        lineNum++;
        
        // Check if timestamp is non-negative
        if (timestamp < 0) {
            cout << "  ❌ Line " << lineNum << ": Negative timestamp " << timestamp << endl;
            foundError = true;
        }
        
        // Check if timestamp is non-decreasing
        if (timestamp < lastTimestamp) {
            cout << "  ❌ Line " << lineNum << ": Timestamp " << timestamp 
                 << " < previous timestamp " << lastTimestamp << endl;
            foundError = true;
        }
        
        lastTimestamp = timestamp;
    }
    
    file.close();
    
    if (!foundError) {
        cout << "  ✅ All timestamps are valid and non-decreasing" << endl;
        return true;
    } else {
        cout << "  ❌ Found timestamp ordering errors" << endl;
        return false;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <test_file1> [test_file2] ..." << endl;
        cout << "Example: " << argv[0] << " test-*.txt" << endl;
        return 1;
    }
    
    bool allValid = true;
    
    for (int i = 1; i < argc; ++i) {
        bool fileValid = checkTimestampOrdering(argv[i]);
        allValid = allValid && fileValid;
        cout << endl;
    }
    
    cout << "=== Summary ===" << endl;
    if (allValid) {
        cout << "✅ All files have valid timestamp ordering" << endl;
    } else {
        cout << "❌ Some files have timestamp ordering errors" << endl;
    }
    
    return allValid ? 0 : 1;
}