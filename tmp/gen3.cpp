// Project Identifier: 0E04A31E0D60C01986ACB20081C9D8722A2519B6

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void generateTest0() {
    // test-0-v.txt: Priority queue tie-breaking and cascading matches
    ofstream file("test-0-v.txt");
    file << "COMMENT: Priority queue tie-breaking cascading matches\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 6\n";
    file << "NUM_STOCKS: 3\n";
    file << "0 SELL T0 S0 $50 #10\n";
    file << "1 SELL T1 S0 $50 #15\n";
    file << "2 BUY T2 S0 $50 #30\n";
    file << "3 SELL T3 S1 $20 #5\n";
    file << "4 SELL T4 S1 $25 #8\n";
    file << "5 SELL T0 S1 $30 #12\n";
    file << "6 BUY T1 S1 $35 #20\n";
    file << "7 SELL T2 S0 $40 #5\n";
    file << "8 BUY T2 S0 $45 #3\n";
    file << "9 SELL T3 S1 $100 #10\n";
    file << "10 BUY T4 S1 $50 #10\n";
    file << "11 SELL T5 S2 $70 #8\n";
    file << "12 SELL T0 S2 $75 #6\n";
    file << "13 BUY T1 S2 $80 #15\n";
    file << "14 SELL T2 S0 $35 #12\n";
    file << "15 BUY T3 S0 $38 #8\n";
    file << "16 SELL T4 S1 $60 #7\n";
    file << "17 BUY T5 S1 $65 #5\n";
    file << "18 SELL T0 S2 $72 #9\n";
    file << "19 BUY T1 S2 $76 #6\n";
    file << "20 SELL T2 S0 $33 #20\n";
    file << "21 BUY T3 S0 $36 #15\n";
    file << "22 SELL T4 S1 $58 #10\n";
    file << "23 BUY T5 S1 $62 #8\n";
    file << "24 SELL T0 S2 $69 #12\n";
    file << "25 BUY T1 S2 $73 #10\n";
    file.close();
}

void generateTest1() {
    // test-1-m.txt: Median calculations with timestamp transitions
    ofstream file("test-1-m.txt");
    file << "COMMENT: Median calculations with timestamp transitions\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 4\n";
    file << "NUM_STOCKS: 3\n";
    file << "0 SELL T0 S0 $10 #5\n";
    file << "1 BUY T1 S0 $15 #5\n";
    file << "2 SELL T0 S0 $30 #8\n";
    file << "3 BUY T1 S0 $35 #8\n";
    file << "4 SELL T0 S0 $20 #6\n";
    file << "5 BUY T1 S0 $25 #6\n";
    file << "10 SELL T2 S1 $33 #10\n";
    file << "11 BUY T3 S1 $40 #10\n";
    file << "12 SELL T2 S1 $67 #12\n";
    file << "13 BUY T3 S1 $70 #12\n";
    file << "20 SELL T0 S2 $45 #7\n";
    file << "21 BUY T1 S2 $50 #7\n";
    file << "22 SELL T2 S0 $40 #10\n";
    file << "23 BUY T3 S0 $45 #10\n";
    file << "24 SELL T0 S1 $55 #8\n";
    file << "25 BUY T1 S1 $60 #8\n";
    file << "26 SELL T2 S2 $65 #9\n";
    file << "27 BUY T3 S2 $70 #9\n";
    file << "30 SELL T0 S0 $50 #5\n";
    file << "31 BUY T1 S0 $55 #5\n";
    file << "32 SELL T2 S1 $45 #6\n";
    file << "33 BUY T3 S1 $48 #6\n";
    file << "34 SELL T0 S2 $75 #4\n";
    file << "35 BUY T1 S2 $80 #4\n";
    file << "36 SELL T2 S0 $42 #3\n";
    file << "37 BUY T3 S0 $47 #3\n";
    file.close();
}

void generateTest2() {
    // test-2-i.txt: Comprehensive trader statistics
    ofstream file("test-2-i.txt");
    file << "COMMENT: Comprehensive trader statistics scenarios\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 8\n";
    file << "NUM_STOCKS: 3\n";
    file << "0 SELL T0 S0 $20 #100\n";
    file << "1 SELL T0 S1 $30 #80\n";
    file << "2 SELL T0 S2 $40 #60\n";
    file << "3 BUY T1 S0 $25 #90\n";
    file << "4 BUY T1 S1 $35 #70\n";
    file << "5 BUY T1 S2 $45 #50\n";
    file << "6 SELL T2 S0 $18 #50\n";
    file << "7 BUY T2 S1 $32 #40\n";
    file << "8 SELL T2 S2 $42 #30\n";
    file << "9 BUY T2 S0 $22 #25\n";
    file << "10 BUY T4 S0 $50 #20\n";
    file << "11 BUY T4 S1 $60 #15\n";
    file << "12 SELL T4 S2 $10 #25\n";
    file << "13 SELL T5 S0 $5 #40\n";
    file << "14 SELL T5 S1 $8 #35\n";
    file << "15 BUY T5 S2 $80 #20\n";
    file << "16 BUY T6 S0 $55 #30\n";
    file << "17 BUY T7 S1 $65 #25\n";
    file << "18 SELL T6 S2 $12 #30\n";
    file << "19 SELL T7 S0 $48 #35\n";
    file << "20 BUY T0 S0 $52 #20\n";
    file << "21 SELL T1 S1 $55 #40\n";
    file << "22 BUY T2 S1 $58 #30\n";
    file << "23 SELL T4 S2 $75 #45\n";
    file << "24 BUY T5 S2 $78 #35\n";
    file << "25 SELL T6 S0 $46 #25\n";
    file.close();
}

void generateTest3() {
    // test-3-t.txt: Time travel profit scenarios (FIXED - strictly increasing timestamps)
    ofstream file("test-3-t.txt");
    file << "COMMENT: Time travel profit optimization scenarios\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 5\n";
    file << "NUM_STOCKS: 4\n";
    file << "0 SELL T0 S0 $30 #10\n";
    file << "1 BUY T1 S0 $50 #5\n";
    file << "2 SELL T2 S0 $25 #8\n";
    file << "3 BUY T3 S0 $60 #10\n";
    file << "4 SELL T0 S0 $20 #5\n";
    file << "5 BUY T1 S0 $65 #8\n";
    file << "6 SELL T0 S1 $50 #10\n";
    file << "7 SELL T1 S1 $45 #15\n";
    file << "8 SELL T2 S1 $40 #20\n";
    file << "9 BUY T0 S2 $60 #10\n";
    file << "10 BUY T1 S2 $65 #5\n";
    file << "11 SELL T2 S2 $30 #8\n";
    file << "12 SELL T0 S3 $10 #5\n";
    file << "13 SELL T1 S3 $10 #3\n";
    file << "14 BUY T2 S3 $25 #10\n";
    file << "15 SELL T3 S3 $8 #7\n";
    file << "16 BUY T0 S3 $23 #5\n";
    file << "17 SELL T4 S0 $15 #12\n";
    file << "18 BUY T2 S0 $70 #15\n";
    file << "19 SELL T1 S2 $25 #20\n";
    file << "20 BUY T3 S2 $40 #15\n";
    file << "21 SELL T2 S1 $35 #25\n";
    file << "22 BUY T4 S1 $55 #20\n";
    file << "23 SELL T3 S3 $5 #15\n";
    file << "24 BUY T4 S3 $28 #10\n";
    file << "25 SELL T0 S0 $12 #8\n";
    file << "26 BUY T1 S0 $68 #12\n";
    file.close();
}

void generateTest4() {
    // test-4-v.txt: Verbose partial fulfillment stress
    ofstream file("test-4-v.txt");
    file << "COMMENT: Verbose partial fulfillment stress test\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 4\n";
    file << "NUM_STOCKS: 2\n";
    file << "0 BUY T0 S0 $100 #200\n";
    file << "1 SELL T1 S0 $90 #30\n";
    file << "2 SELL T2 S0 $85 #40\n";
    file << "3 SELL T3 S0 $95 #50\n";
    file << "4 SELL T1 S0 $80 #35\n";
    file << "5 SELL T2 S0 $88 #25\n";
    file << "6 SELL T3 S0 $92 #20\n";
    file << "7 SELL T0 S1 $50 #300\n";
    file << "8 BUY T1 S1 $70 #45\n";
    file << "9 BUY T2 S1 $65 #60\n";
    file << "10 BUY T3 S1 $60 #75\n";
    file << "11 BUY T1 S1 $55 #40\n";
    file << "12 BUY T2 S1 $68 #35\n";
    file << "13 BUY T3 S1 $63 #45\n";
    file << "14 SELL T1 S0 $45 #8\n";
    file << "15 SELL T2 S0 $44 #6\n";
    file << "16 SELL T3 S0 $46 #10\n";
    file << "17 SELL T1 S0 $43 #5\n";
    file << "18 SELL T2 S0 $47 #7\n";
    file << "19 BUY T0 S0 $48 #40\n";
    file << "20 SELL T0 S1 $30 #12\n";
    file << "21 SELL T1 S1 $29 #8\n";
    file << "22 SELL T2 S1 $31 #15\n";
    file << "23 SELL T3 S1 $28 #10\n";
    file << "24 BUY T0 S1 $32 #50\n";
    file << "25 SELL T1 S0 $25 #100\n";
    file.close();
}

void generateTest5() {
    // test-5-m.txt: Median integer division edge cases
    ofstream file("test-5-m.txt");
    file << "COMMENT: Median integer division edge cases\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 4\n";
    file << "NUM_STOCKS: 2\n";
    file << "0 SELL T0 S0 $31 #10\n";
    file << "1 BUY T1 S0 $35 #10\n";
    file << "2 SELL T0 S0 $64 #12\n";
    file << "3 BUY T1 S0 $68 #12\n";
    file << "4 SELL T0 S0 $47 #8\n";
    file << "5 BUY T1 S0 $50 #8\n";
    file << "6 SELL T0 S0 $83 #15\n";
    file << "7 BUY T1 S0 $87 #15\n";
    file << "8 SELL T2 S0 $25 #6\n";
    file << "9 BUY T3 S0 $28 #6\n";
    file << "10 SELL T2 S0 $91 #9\n";
    file << "11 BUY T3 S0 $95 #9\n";
    file << "12 SELL T2 S0 $55 #7\n";
    file << "13 BUY T3 S0 $58 #7\n";
    file << "14 SELL T2 S0 $76 #11\n";
    file << "15 BUY T3 S0 $80 #11\n";
    file << "16 SELL T0 S1 $40 #20\n";
    file << "17 BUY T1 S1 $45 #20\n";
    file << "18 SELL T2 S1 $60 #25\n";
    file << "19 BUY T3 S1 $65 #25\n";
    file << "20 SELL T0 S1 $20 #15\n";
    file << "21 BUY T1 S1 $25 #15\n";
    file << "22 SELL T2 S1 $80 #18\n";
    file << "23 BUY T3 S1 $85 #18\n";
    file << "24 SELL T0 S1 $35 #12\n";
    file << "25 BUY T1 S1 $38 #12\n";
    file.close();
}

void generateTest6() {
    // test-6-i.txt: Trader info extreme scenarios (FIXED - strictly increasing timestamps)
    ofstream file("test-6-i.txt");
    file << "COMMENT: Trader info extreme scenarios and edge cases\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 10\n";
    file << "NUM_STOCKS: 3\n";
    file << "0 BUY T3 S0 $1000 #50\n";
    file << "1 BUY T3 S1 $2000 #30\n";
    file << "2 BUY T3 S2 $1500 #40\n";
    file << "3 SELL T3 S0 $100 #45\n";
    file << "4 SELL T3 S1 $200 #25\n";
    file << "5 SELL T3 S2 $150 #35\n";
    file << "6 SELL T4 S0 $10 #60\n";
    file << "7 SELL T4 S1 $20 #40\n";
    file << "8 SELL T4 S2 $15 #50\n";
    file << "9 BUY T4 S0 $800 #55\n";
    file << "10 BUY T4 S1 $1800 #35\n";
    file << "11 BUY T4 S2 $1200 #45\n";
    file << "12 BUY T5 S0 $1200 #50\n";
    file << "13 BUY T6 S1 $2200 #35\n";
    file << "14 BUY T7 S2 $1600 #45\n";
    file << "15 SELL T8 S0 $50 #55\n";
    file << "16 SELL T9 S1 $180 #35\n";
    file << "17 SELL T5 S2 $120 #45\n";
    file << "18 SELL T5 S0 $300 #25\n";
    file << "19 BUY T6 S0 $350 #20\n";
    file << "20 SELL T7 S1 $400 #30\n";
    file << "21 BUY T8 S1 $450 #25\n";
    file << "22 SELL T9 S2 $500 #35\n";
    file << "23 BUY T5 S2 $550 #30\n";
    file << "24 SELL T6 S0 $250 #40\n";
    file << "25 BUY T7 S0 $280 #35\n";
    file.close();
}

void generateTest7() {
    // test-7-t.txt: Time travel comprehensive scenarios (FIXED - strictly increasing timestamps)
    ofstream file("test-7-t.txt");
    file << "COMMENT: Comprehensive time travel profit scenarios\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 5\n";
    file << "NUM_STOCKS: 4\n";
    file << "0 SELL T0 S0 $100 #10\n";
    file << "1 SELL T1 S0 $80 #8\n";
    file << "2 SELL T2 S0 $60 #12\n";
    file << "3 SELL T3 S0 $40 #6\n";
    file << "4 BUY T4 S0 $200 #15\n";
    file << "5 BUY T0 S0 $180 #10\n";
    file << "6 BUY T1 S0 $220 #8\n";
    file << "7 SELL T0 S1 $150 #20\n";
    file << "8 SELL T1 S1 $120 #15\n";
    file << "9 SELL T2 S1 $90 #18\n";
    file << "10 BUY T3 S1 $100 #12\n";
    file << "11 BUY T4 S1 $140 #16\n";
    file << "12 BUY T0 S1 $180 #20\n";
    file << "13 BUY T0 S2 $300 #25\n";
    file << "14 BUY T1 S2 $280 #20\n";
    file << "15 BUY T2 S2 $320 #30\n";
    file << "16 SELL T3 S2 $250 #18\n";
    file << "17 SELL T4 S2 $260 #22\n";
    file << "18 SELL T0 S2 $240 #15\n";
    file << "19 SELL T0 S3 $50 #8\n";
    file << "20 SELL T1 S3 $50 #6\n";
    file << "21 BUY T2 S3 $100 #10\n";
    file << "22 SELL T3 S3 $45 #12\n";
    file << "23 BUY T4 S3 $95 #8\n";
    file << "24 SELL T2 S0 $35 #20\n";
    file << "25 BUY T3 S0 $250 #25\n";
    file.close();
}

void generateTest8() {
    // test-8-v.txt: Complex verbose ordering scenarios
    ofstream file("test-8-v.txt");
    file << "COMMENT: Complex verbose ordering and rapid trades\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 6\n";
    file << "NUM_STOCKS: 3\n";
    file << "0 SELL T0 S0 $50 #10\n";
    file << "0 SELL T1 S0 $45 #15\n";
    file << "0 BUY T2 S0 $60 #20\n";
    file << "0 BUY T3 S0 $55 #10\n";
    file << "1 SELL T0 S1 $30 #5\n";
    file << "1 SELL T1 S1 $35 #5\n";
    file << "1 SELL T2 S1 $25 #5\n";
    file << "1 SELL T3 S1 $40 #5\n";
    file << "1 BUY T4 S1 $50 #20\n";
    file << "2 SELL T0 S0 $70 #8\n";
    file << "3 SELL T1 S0 $70 #12\n";
    file << "4 BUY T2 S0 $75 #15\n";
    file << "5 SELL T0 S1 $60 #3\n";
    file << "5 SELL T1 S1 $65 #4\n";
    file << "5 SELL T2 S1 $55 #6\n";
    file << "5 SELL T3 S1 $70 #2\n";
    file << "6 BUY T4 S1 $80 #20\n";
    file << "7 SELL T5 S2 $90 #12\n";
    file << "8 SELL T0 S2 $85 #8\n";
    file << "9 SELL T1 S2 $95 #10\n";
    file << "10 BUY T2 S2 $100 #25\n";
    file << "11 SELL T3 S0 $42 #20\n";
    file << "12 BUY T4 S0 $48 #15\n";
    file << "13 SELL T5 S1 $38 #18\n";
    file << "14 BUY T0 S1 $44 #12\n";
    file << "15 SELL T1 S2 $82 #16\n";
    file.close();
}

void generateTest9() {
    // test-9-m.txt: Median with large timestamp gaps
    ofstream file("test-9-m.txt");
    file << "COMMENT: Median with timestamp gaps and final output\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 4\n";
    file << "NUM_STOCKS: 3\n";
    file << "0 SELL T0 S0 $40 #10\n";
    file << "0 BUY T1 S0 $45 #10\n";
    file << "20 SELL T0 S0 $60 #10\n";
    file << "20 BUY T1 S0 $65 #10\n";
    file << "50 SELL T0 S1 $80 #5\n";
    file << "50 BUY T1 S1 $85 #5\n";
    file << "50 SELL T0 S0 $30 #8\n";
    file << "50 BUY T2 S0 $35 #8\n";
    file << "100 SELL T0 S1 $90 #10\n";
    file << "100 BUY T1 S1 $95 #10\n";
    file << "100 SELL T2 S2 $120 #6\n";
    file << "100 BUY T3 S2 $125 #6\n";
    file << "150 SELL T0 S0 $25 #12\n";
    file << "150 BUY T1 S0 $28 #12\n";
    file << "150 SELL T2 S1 $75 #8\n";
    file << "150 BUY T3 S1 $78 #8\n";
    file << "200 SELL T0 S2 $110 #9\n";
    file << "200 BUY T1 S2 $115 #9\n";
    file << "200 SELL T2 S0 $22 #15\n";
    file << "200 BUY T3 S0 $26 #15\n";
    file << "250 SELL T0 S1 $70 #12\n";
    file << "250 BUY T1 S1 $73 #12\n";
    file << "250 SELL T2 S2 $105 #7\n";
    file << "250 BUY T3 S2 $108 #7\n";
    file << "300 SELL T0 S0 $20 #20\n";
    file << "300 BUY T1 S0 $24 #18\n";
    file.close();
}

int main() {
    cout << "Generating 10 test files...\n";
    
    generateTest0();
    cout << "Generated test-0-v.txt (Priority queue tie-breaking)\n";
    
    generateTest1();
    cout << "Generated test-1-m.txt (Median with timestamp transitions)\n";
    
    generateTest2();
    cout << "Generated test-2-i.txt (Complex trader interactions)\n";
    
    generateTest3();
    cout << "Generated test-3-t.txt (Time travel profit scenarios)\n";
    
    generateTest4();
    cout << "Generated test-4-v.txt (Partial fulfillment stress)\n";
    
    generateTest5();
    cout << "Generated test-5-m.txt (Median edge cases)\n";
    
    generateTest6();
    cout << "Generated test-6-i.txt (Trader info extremes)\n";
    
    generateTest7();
    cout << "Generated test-7-t.txt (Complex time travel)\n";
    
    generateTest8();
    cout << "Generated test-8-v.txt (Same timestamp ordering)\n";
    
    generateTest9();
    cout << "Generated test-9-m.txt (Timestamp gaps)\n";
    
    cout << "\nAll test files generated successfully!\n";
    cout << "Each test targets specific edge cases and algorithmic weaknesses.\n";
    
    return 0;
}