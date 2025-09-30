// Project Identifier: 0E04A31E0D60C01986ACB20081C9D8722A2519B6

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void generateTest0() {
    // test-0-v.txt: Keep original - catches bugs 2, 4, 5, 10, 11, 12, 13, 15
    ofstream file("test-0-v.txt");
    file << "COMMENT: Same timestamp price matching and early order priority\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 4\n";
    file << "NUM_STOCKS: 2\n";
    file << "0 SELL T0 S0 $40 #20\n";
    file << "0 SELL T1 S0 $50 #15\n";
    file << "0 BUY T2 S0 $60 #30\n";
    file << "1 BUY T3 S0 $45 #10\n";
    file << "5 BUY T0 S1 $100 #25\n";
    file << "6 SELL T1 S1 $80 #10\n";
    file << "6 SELL T2 S1 $70 #15\n";
    file << "7 SELL T3 S1 $90 #5\n";
    file << "10 SELL T0 S0 $30 #5\n";
    file << "10 SELL T1 S0 $25 #8\n";
    file << "10 SELL T2 S0 $35 #6\n";
    file << "11 BUY T3 S0 $40 #15\n";
    file.close();
}

void generateTest1() {
    // test-1-m.txt: Keep original - catches bugs 3, 12, 13, 15
    ofstream file("test-1-m.txt");
    file << "COMMENT: Median with no trades on some stocks and timestamp gaps\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 3\n";
    file << "NUM_STOCKS: 4\n";
    file << "0 SELL T0 S0 $50 #10\n";
    file << "0 BUY T1 S0 $55 #10\n";
    file << "1 SELL T0 S1 $100 #5\n";
    file << "1 BUY T1 S1 $90 #5\n";
    file << "2 SELL T2 S2 $30 #8\n";
    file << "2 BUY T0 S2 $35 #8\n";
    file << "5 SELL T1 S0 $45 #7\n";
    file << "5 BUY T2 S0 $48 #7\n";
    file << "10 BUY T0 S1 $95 #3\n";
    file << "15 SELL T1 S2 $25 #12\n";
    file << "15 BUY T2 S2 $28 #12\n";
    file.close();
}

void generateTest2() {
    // test-2-i.txt: Complex test targeting bugs 1, 8, 16 - maximize 30 lines
    ofstream file("test-2-i.txt");
    file << "COMMENT: Complex self-trading, same-timestamp trades, large values\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 5\n";
    file << "NUM_STOCKS: 3\n";
    // Bug 1: Same timestamp trade price determination
    file << "0 SELL T0 S0 $76 #11\n";
    file << "0 BUY T1 S0 $100 #11\n";  // Should trade at $76 (sell came first)
    file << "0 BUY T2 S0 $100 #6\n";
    file << "0 SELL T3 S0 $100 #6\n";  // Should trade at $100 (buy came first)
    // Bug 8: Self-trading scenarios
    file << "1 SELL T0 S1 $50 #100\n";
    file << "1 BUY T0 S1 $60 #100\n";  // T0 trades with self
    file << "2 SELL T1 S1 $40 #80\n";
    file << "2 BUY T1 S1 $45 #50\n";   // T1 partial self-trade
    file << "2 BUY T2 S1 $42 #30\n";   // T2 gets remainder
    // Bug 16: Large value trades
    file << "3 SELL T3 S2 $46340 #46340\n";  // Near INT_MAX when multiplied
    file << "3 BUY T4 S2 $46341 #46340\n";
    file << "4 SELL T0 S2 $50000 #40000\n";  // 2 billion value trade
    file << "4 BUY T1 S2 $50001 #40000\n";
    // More complex scenarios
    file << "5 BUY T2 S0 $200 #15\n";
    file << "5 SELL T2 S0 $180 #15\n";  // Self-trade at buy price
    file << "6 SELL T3 S1 $35 #200\n";
    file << "6 BUY T4 S1 $38 #150\n";
    file << "6 BUY T3 S1 $36 #50\n";   // T3 buys own shares back
    file << "7 SELL T0 S0 $75 #25\n";
    file << "7 SELL T1 S0 $75 #25\n";
    file << "7 BUY T2 S0 $80 #50\n";   // Tests tie-breaking at same price
    file << "8 BUY T4 S2 $99999 #10000\n";
    file << "8 SELL T3 S2 $99998 #10000\n";  // Large value trade
    file << "9 SELL T0 S1 $1 #100000\n";     // Large quantity, small price
    file << "9 BUY T1 S1 $2 #100000\n";
    file.close();
}

void generateTest3() {
    // test-3-t.txt: Complex time travel targeting bugs 9, 14 - maximize 30 lines
    ofstream file("test-3-t.txt");
    file << "COMMENT: Complex time travel scenarios with extreme values\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 4\n";
    file << "NUM_STOCKS: 4\n";
    // Stock 0: Zero profit scenario
    file << "0 SELL T0 S0 $50 #10\n";
    file << "1 BUY T1 S0 $50 #10\n";   // Same price - zero profit
    file << "2 SELL T2 S0 $50 #8\n";
    file << "3 BUY T3 S0 $50 #8\n";
    // Stock 1: Declining prices only
    file << "4 BUY T0 S1 $1000 #5\n";
    file << "5 BUY T1 S1 $900 #6\n";
    file << "6 BUY T2 S1 $800 #7\n";
    file << "7 SELL T3 S1 $700 #8\n";
    file << "8 SELL T0 S1 $600 #9\n";  // All sells after buys - no profit
    // Stock 2: Extreme price differences (bug 14)
    file << "10 SELL T1 S2 $1 #20\n";
    file << "11 BUY T2 S2 $1000000 #20\n";  // Huge profit but tests extreme values
    file << "12 SELL T3 S2 $999999 #15\n";
    file << "13 BUY T0 S2 $1000000 #15\n";
    // Stock 3: Multiple equal profit opportunities
    file << "15 SELL T0 S3 $100 #12\n";
    file << "16 BUY T1 S3 $110 #12\n";  // $10 profit
    file << "17 SELL T2 S3 $90 #10\n";
    file << "18 BUY T3 S3 $100 #10\n";  // $10 profit (should pick earlier)
    file << "19 SELL T0 S3 $80 #8\n";
    file << "20 BUY T1 S3 $90 #8\n";   // $10 profit
    // More complex patterns
    file << "21 SELL T2 S0 $40 #25\n";
    file << "22 SELL T3 S0 $35 #30\n";
    file << "23 BUY T0 S0 $45 #50\n";   // Should use earliest low price
    file << "24 BUY T1 S0 $48 #5\n";
    file.close();
}

void generateTest4() {
    // test-4-v.txt: Complex verbose test targeting bug 1 and others - maximize 30 lines
    ofstream file("test-4-v.txt");
    file << "COMMENT: Complex verbose with same-timestamp ordering\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 6\n";
    file << "NUM_STOCKS: 3\n";
    // Multiple same-timestamp orders testing bug 1
    file << "0 SELL T0 S0 $45 #10\n";
    file << "0 BUY T1 S0 $100 #5\n";   // Trade at $45
    file << "0 SELL T2 S0 $40 #8\n";
    file << "0 BUY T3 S0 $95 #8\n";    // Trade at $40
    file << "0 SELL T4 S0 $50 #12\n";
    file << "0 BUY T5 S0 $90 #7\n";    // Partial trade at $50
    // Cascading matches
    file << "1 BUY T0 S1 $80 #100\n";
    file << "1 SELL T1 S1 $75 #20\n";
    file << "1 SELL T2 S1 $70 #25\n";
    file << "1 SELL T3 S1 $65 #30\n";
    file << "1 SELL T4 S1 $60 #25\n";  // All match with T0's buy
    // Complex partial fulfillment
    file << "2 SELL T5 S2 $100 #200\n";
    file << "2 BUY T0 S2 $105 #40\n";
    file << "2 BUY T1 S2 $110 #35\n";
    file << "2 BUY T2 S2 $115 #45\n";
    file << "2 BUY T3 S2 $120 #50\n";
    file << "2 BUY T4 S2 $125 #30\n";  // All match with T5's sell
    // More same-timestamp complexity
    file << "3 BUY T0 S0 $200 #15\n";
    file << "3 BUY T1 S0 $195 #10\n";
    file << "3 SELL T2 S0 $180 #20\n"; // Matches highest buy first
    file << "3 SELL T3 S0 $175 #5\n";  // Matches remainder
    // Self-trades mixed in
    file << "4 SELL T4 S1 $50 #60\n";
    file << "4 BUY T4 S1 $55 #30\n";   // Self-trade
    file << "4 BUY T5 S1 $52 #30\n";   // Gets remainder
    file.close();
}

void generateTest5() {
    // test-5-m.txt: Complex median targeting bugs 7, 14 - maximize 30 lines
    ofstream file("test-5-m.txt");
    file << "COMMENT: Complex median with extreme values and odd counts\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 4\n";
    file << "NUM_STOCKS: 3\n";
    // Stock 0: Odd number of trades with extreme values
    file << "0 SELL T0 S0 $1 #5\n";
    file << "0 BUY T1 S0 $2 #5\n";         // Trade at $1
    file << "1 SELL T2 S0 $999999 #3\n";
    file << "1 BUY T3 S0 $1000000 #3\n";   // Trade at $999999
    file << "2 SELL T0 S0 $500000 #7\n";
    file << "2 BUY T1 S0 $500001 #7\n";    // Trade at $500000 (median)
    // Stock 1: Single trade
    file << "3 SELL T2 S1 $42 #10\n";
    file << "3 BUY T3 S1 $50 #10\n";       // Trade at $42 (only median)
    // Stock 2: Even number with extreme range
    file << "4 SELL T0 S2 $10 #4\n";
    file << "4 BUY T1 S2 $15 #4\n";        // Trade at $10
    file << "5 SELL T2 S2 $20 #6\n";
    file << "5 BUY T3 S2 $25 #6\n";        // Trade at $20
    file << "6 SELL T0 S2 $1000 #8\n";
    file << "6 BUY T1 S2 $1005 #8\n";      // Trade at $1000
    file << "7 SELL T2 S2 $2000 #10\n";
    file << "7 BUY T3 S2 $2005 #10\n";     // Trade at $2000
    // More trades for Stock 0 (testing many trades)
    file << "10 SELL T0 S0 $100 #2\n";
    file << "10 BUY T1 S0 $101 #2\n";
    file << "11 SELL T2 S0 $200 #2\n";
    file << "11 BUY T3 S0 $201 #2\n";
    file << "12 SELL T0 S0 $300 #2\n";
    file << "12 BUY T1 S0 $301 #2\n";
    file << "13 SELL T2 S0 $400 #2\n";
    file << "13 BUY T3 S0 $401 #2\n";      // 7 total trades - odd
    file.close();
}

void generateTest6() {
    // test-6-i.txt: Complex trader info targeting bugs 8, 16 - maximize 30 lines
    ofstream file("test-6-i.txt");
    file << "COMMENT: Complex trader statistics with self-trades and large values\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 3\n";  // Fewer traders, more complex interactions
    file << "NUM_STOCKS: 3\n";
    // T0 does extensive self-trading
    file << "0 SELL T0 S0 $100 #500\n";
    file << "0 BUY T0 S0 $110 #300\n";     // T0 self-trade 300 shares
    file << "0 BUY T1 S0 $105 #200\n";     // T1 gets remainder
    file << "1 BUY T0 S1 $200 #400\n";
    file << "1 SELL T0 S1 $190 #250\n";    // T0 self-trade 250 shares
    file << "1 SELL T1 S1 $195 #150\n";    // T1 provides remainder
    // Large value trades for bug 16
    file << "2 SELL T2 S2 $46340 #46340\n";
    file << "2 BUY T0 S2 $46341 #46340\n"; // Near INT_MAX value
    file << "3 SELL T1 S2 $50000 #40000\n";
    file << "3 BUY T2 S2 $50001 #40000\n";
    // Complex multi-way trades
    file << "4 SELL T0 S0 $80 #1000\n";
    file << "4 BUY T1 S0 $85 #600\n";
    file << "4 BUY T2 S0 $82 #400\n";
    file << "5 BUY T0 S1 $150 #800\n";
    file << "5 SELL T1 S1 $145 #500\n";
    file << "5 SELL T2 S1 $140 #300\n";
    // More self-trading patterns
    file << "6 SELL T1 S0 $70 #700\n";
    file << "6 BUY T1 S0 $75 #400\n";      // T1 self-trade
    file << "6 BUY T0 S0 $72 #300\n";
    file << "7 BUY T2 S2 $99999 #10000\n";
    file << "7 SELL T2 S2 $99998 #5000\n"; // T2 self-trade large value
    file << "7 SELL T0 S2 $99997 #5000\n";
    // Final complex trades
    file << "8 SELL T0 S1 $1 #1000000\n";
    file << "8 BUY T1 S1 $2 #500000\n";
    file << "8 BUY T2 S1 $2 #500000\n";
    file.close();
}

void generateTest7() {
    // test-7-t.txt: Keep original - catches bugs 4, 5, 6, 10, 12, 13, 15
    ofstream file("test-7-t.txt");
    file << "COMMENT: Time travel tie-breaking with equal profits\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 3\n";
    file << "NUM_STOCKS: 3\n";
    file << "0 SELL T0 S0 $50 #10\n";
    file << "1 BUY T1 S0 $60 #10\n";
    file << "2 SELL T2 S0 $40 #8\n";
    file << "3 BUY T0 S0 $50 #8\n";
    file << "4 SELL T1 S0 $30 #12\n";
    file << "5 BUY T2 S0 $40 #12\n";
    file << "10 SELL T0 S1 $100 #5\n";
    file << "11 BUY T1 S1 $105 #5\n";
    file << "12 SELL T2 S1 $90 #7\n";
    file << "13 BUY T0 S1 $100 #7\n";
    file << "14 SELL T1 S1 $80 #9\n";
    file << "15 BUY T2 S1 $95 #9\n";
    file << "20 SELL T0 S2 $200 #15\n";
    file << "21 SELL T1 S2 $190 #10\n";
    file << "22 BUY T2 S2 $210 #20\n";
    file << "23 SELL T0 S2 $180 #8\n";
    file << "24 BUY T1 S2 $210 #8\n";
    file.close();
}

void generateTest8() {
    // test-8-v.txt: Complex verbose targeting bug 1 and 11 - maximize 30 lines
    ofstream file("test-8-v.txt");
    file << "COMMENT: Complex ordering with same timestamp and partial fulfillment\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 5\n";
    file << "NUM_STOCKS: 2\n";
    // Bug 1: Complex same-timestamp scenarios
    file << "0 SELL T0 S0 $76 #11\n";      // First at time 0
    file << "0 SELL T1 S0 $80 #10\n";
    file << "0 BUY T2 S0 $100 #6\n";       // Should match at $76 for 6
    file << "0 BUY T3 S0 $95 #5\n";        // Should match at $76 for 5
    file << "0 SELL T4 S0 $85 #15\n";
    file << "0 BUY T0 S0 $90 #25\n";       // Should match remaining
    // Bug 11: Complex partial fulfillment
    file << "1 BUY T1 S1 $200 #500\n";     // Large buy
    file << "1 SELL T2 S1 $195 #100\n";    // Multiple small sells
    file << "1 SELL T3 S1 $190 #100\n";
    file << "1 SELL T4 S1 $185 #100\n";
    file << "1 SELL T0 S1 $180 #100\n";
    file << "1 SELL T1 S1 $175 #100\n";    // All match the buy
    // More same-timestamp complexity
    file << "2 BUY T2 S0 $150 #20\n";      // Buy arrives first
    file << "2 SELL T3 S0 $140 #20\n";     // Should trade at $150
    file << "2 SELL T4 S0 $130 #15\n";     // Sell arrives first  
    file << "2 BUY T0 S0 $145 #15\n";      // Should trade at $130
    // Cascading partial matches
    file << "3 SELL T1 S0 $100 #300\n";
    file << "3 BUY T2 S0 $105 #50\n";
    file << "3 BUY T3 S0 $110 #75\n";
    file << "3 BUY T4 S0 $115 #100\n";
    file << "3 BUY T0 S0 $120 #75\n";      // All match the large sell
    file << "4 BUY T1 S1 $250 #40\n";
    file << "4 SELL T1 S1 $240 #40\n";     // Self-trade at complex point
    file.close();
}

void generateTest9() {
    // test-9-m.txt: Complex median targeting bugs 7, 9, 14 - maximize 30 lines
    ofstream file("test-9-m.txt");
    file << "COMMENT: Complex median with no-profit stocks and extreme values\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 4\n";
    file << "NUM_STOCKS: 4\n";
    // Stock 0: Exactly 1 trade (bug 7)
    file << "0 SELL T0 S0 $42 #20\n";
    file << "0 BUY T1 S0 $50 #20\n";       // Single trade at $42
    // Stock 1: No trades (prices don't match)
    file << "1 SELL T0 S1 $100 #10\n";
    file << "1 BUY T1 S1 $90 #10\n";       // No match
    // Stock 2: Many trades with extreme values (bug 14)
    file << "2 SELL T2 S2 $1 #5\n";
    file << "2 BUY T3 S2 $2 #5\n";
    file << "3 SELL T0 S2 $10 #5\n";
    file << "3 BUY T1 S2 $11 #5\n";
    file << "4 SELL T2 S2 $100 #5\n";
    file << "4 BUY T3 S2 $101 #5\n";
    file << "5 SELL T0 S2 $1000 #5\n";
    file << "5 BUY T1 S2 $1001 #5\n";
    file << "6 SELL T2 S2 $10000 #5\n";
    file << "6 BUY T3 S2 $10001 #5\n";
    file << "7 SELL T0 S2 $100000 #5\n";
    file << "7 BUY T1 S2 $100001 #5\n";
    file << "8 SELL T2 S2 $1000000 #5\n";
    file << "8 BUY T3 S2 $1000001 #5\n";   // 7 trades (odd) with huge range
    // Stock 3: Zero profit scenario (bug 9)
    file << "10 SELL T0 S3 $75 #15\n";
    file << "10 BUY T1 S3 $75 #15\n";      // Same price
    file << "11 SELL T2 S3 $75 #10\n";
    file << "11 BUY T3 S3 $75 #10\n";      // Still same price
    // More for Stock 1 (still no trades)
    file << "15 BUY T2 S1 $95 #8\n";       // Still no match
    file << "20 SELL T3 S1 $98 #7\n";      // Still no match
    // Final timestamp with no new trades
    file << "100 BUY T0 S1 $92 #5\n";      // Still no match for S1
    file.close();
}

int main() {
    cout << "Generating complex test files maximizing 30-line limit...\n\n";
    
    generateTest0();
    cout << "Generated test-0-v.txt (KEEP: catches bugs 2,4,5,10,11,12,13,15)\n";
    
    generateTest1();
    cout << "Generated test-1-m.txt (KEEP: catches bugs 3,12,13,15)\n";
    
    generateTest2();
    cout << "Generated test-2-i.txt (Complex: targets bugs 1,8,16)\n";
    
    generateTest3();
    cout << "Generated test-3-t.txt (Complex: targets bugs 9,14)\n";
    
    generateTest4();
    cout << "Generated test-4-v.txt (Complex: targets bug 1,11)\n";
    
    generateTest5();
    cout << "Generated test-5-m.txt (Complex: targets bugs 7,14)\n";
    
    generateTest6();
    cout << "Generated test-6-i.txt (Complex: targets bugs 8,16)\n";
    
    generateTest7();
    cout << "Generated test-7-t.txt (KEEP: catches bugs 4,5,6,10,12,13,15)\n";
    
    generateTest8();
    cout << "Generated test-8-v.txt (Complex: targets bugs 1,11)\n";
    
    generateTest9();
    cout << "Generated test-9-m.txt (Complex: targets bugs 7,9,14)\n";
    
    cout << "\nComplex test suite generated!\n";
    cout << "Tests 0,1,7 kept (catch 10 bugs already)\n";
    cout << "Tests 2-6,8-9 maximized to 25-30 lines for comprehensive coverage\n";
    cout << "Missing bugs targeted: 1, 7, 8, 9, 14, 16\n";
    
    return 0;
}