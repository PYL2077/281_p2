// Project Identifier: 0E04A31E0D60C01986ACB20081C9D8722A2519B6

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void generateTest0() {
    // test-0-v.txt: Verbose mode - Priority queue tie-breaking and cascading matches
    ofstream file("test-0-v.txt");
    file << "COMMENT: Priority queue tie-breaking and cascading matches\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 5\n";
    file << "NUM_STOCKS: 2\n";
    
    // Same price, different timestamps (tie-breaking test)
    file << "0 SELL T0 S0 $50 #10\n";
    file << "1 SELL T1 S0 $50 #15\n";  // Same price, later timestamp
    file << "2 BUY T2 S0 $50 #30\n";   // Should match T0 first (earlier timestamp)
    
    // Cascading matches - one buy order matches multiple sells
    file << "3 SELL T3 S1 $20 #5\n";
    file << "3 SELL T4 S1 $25 #8\n";
    file << "3 SELL T0 S1 $30 #12\n";
    file << "4 BUY T1 S1 $35 #20\n";   // Should match $20 and $25 sells
    
    // Self-trading
    file << "5 SELL T2 S0 $40 #5\n";
    file << "5 BUY T2 S0 $45 #3\n";    // Trader 2 buys from themselves
    
    // No matches possible
    file << "6 SELL T3 S1 $100 #10\n";
    file << "6 BUY T4 S1 $50 #10\n";   // Price gap too large
    
    file.close();
}

void generateTest1() {
    // test-1-m.txt: Median mode - Even/odd trades, timestamp transitions
    ofstream file("test-1-m.txt");
    file << "COMMENT: Median calculation with timestamp transitions\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 4\n";
    file << "NUM_STOCKS: 3\n";
    
    // Stock 0: Single trade (median = trade price)
    file << "0 SELL T0 S0 $100 #10\n";
    file << "0 BUY T1 S0 $120 #5\n";   // Trade at $100
    
    // Stock 1: Even number of trades
    file << "1 SELL T0 S1 $30 #10\n";
    file << "1 BUY T1 S1 $40 #10\n";   // Trade at $30
    file << "1 SELL T2 S1 $60 #10\n";
    file << "1 BUY T3 S1 $70 #10\n";   // Trade at $60, median = (30+60)/2 = 45
    
    // Timestamp transition (should print medians for stocks 0,1)
    file << "2 SELL T0 S1 $80 #5\n";
    file << "2 BUY T1 S1 $90 #5\n";    // Trade at $80, median = (30+60+80)/3 = 60
    
    // Stock 2: No trades (no median output)
    file << "3 SELL T0 S2 $200 #10\n";
    file << "3 BUY T1 S2 $150 #10\n";  // No match
    
    // More trades at final timestamp
    file << "4 SELL T2 S0 $110 #8\n";
    file << "4 BUY T3 S0 $130 #12\n";  // Trade at $110
    
    file.close();
}

void generateTest2() {
    // test-2-i.txt: Trader info mode - Complex trader interactions
    ofstream file("test-2-i.txt");
    file << "COMMENT: Complex trader interactions for trader info\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 6\n";
    file << "NUM_STOCKS: 2\n";
    
    // Trader 0: Only sells
    file << "0 SELL T0 S0 $50 #20\n";
    file << "0 SELL T0 S1 $75 #15\n";
    
    // Trader 1: Only buys
    file << "0 BUY T1 S0 $60 #25\n";   // Buys 20 from T0 at $50, 5 unmatched
    file << "0 BUY T1 S1 $80 #10\n";   // Buys 10 from T0 at $75
    
    // Trader 2: Both buys and sells
    file << "1 SELL T2 S0 $45 #10\n";
    file << "1 BUY T2 S0 $55 #5\n";    // Matches with own sell at $45
    file << "1 BUY T2 S1 $85 #8\n";    // Buys 5 from T0 at $75
    
    // Trader 3: No activity (should show zeros)
    
    // Trader 4: High volume trading
    file << "2 SELL T4 S0 $40 #30\n";
    file << "2 SELL T4 S1 $70 #25\n";
    file << "2 BUY T4 S0 $65 #15\n";   // Self-trade
    file << "2 BUY T4 S1 $90 #20\n";   // Self-trade
    
    // Trader 5: Late entry
    file << "3 BUY T5 S0 $70 #20\n";   // Buys from T4 and T2
    file << "3 BUY T5 S1 $95 #30\n";   // Buys from T4
    
    // Additional complex partial matches
    file << "4 SELL T1 S0 $35 #50\n";  // Large sell order
    file << "4 BUY T0 S0 $45 #15\n";   // Partial match
    file << "4 BUY T2 S0 $40 #20\n";   // Another partial match
    
    file.close();
}

void generateTest3() {
    // test-3-t.txt: Time travelers mode - Profit scenarios and edge cases
    ofstream file("test-3-t.txt");
    file << "COMMENT: Time travel profit optimization scenarios\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 4\n";
    file << "NUM_STOCKS: 4\n";
    
    // Stock 0: Clear profit opportunity
    file << "0 SELL T0 S0 $20 #10\n";  // Buy opportunity
    file << "1 SELL T1 S0 $15 #5\n";   // Better buy opportunity
    file << "2 BUY T2 S0 $40 #8\n";    // Sell opportunity, profit = 40-15 = 25
    file << "3 BUY T3 S0 $35 #12\n";   // Lower sell, profit = 35-15 = 20
    
    // Stock 1: No profit possible (only sells or only buys)
    file << "0 SELL T0 S1 $50 #10\n";
    file << "1 SELL T1 S1 $45 #15\n";
    file << "2 SELL T2 S1 $40 #20\n";  // Only sells, no buys
    
    // Stock 2: Reverse chronology (buys before sells)
    file << "0 BUY T0 S2 $60 #10\n";
    file << "1 BUY T1 S2 $65 #5\n";
    file << "2 SELL T2 S2 $30 #8\n";   // Sells come after buys - no profit
    
    // Stock 3: Multiple optimal solutions (tie-breaking test)
    file << "0 SELL T0 S3 $10 #5\n";   // First opportunity
    file << "0 SELL T1 S3 $10 #3\n";   // Same price, same time
    file << "1 BUY T2 S3 $25 #10\n";   // Same profit from both
    file << "2 SELL T3 S3 $8 #7\n";    // Even better buy opportunity
    file << "3 BUY T0 S3 $23 #5\n";    // Lower profit but from better buy
    
    // Additional orders to test tie-breaking in timestamps
    file << "1 SELL T0 S0 $12 #3\n";   // Even better buy at same time as previous sell
    file << "1 BUY T1 S0 $38 #6\n";    // Same timestamp as previous buy
    
    file.close();
}

void generateTest4() {
    // test-4-v.txt: Verbose mode - Partial fulfillment stress test
    ofstream file("test-4-v.txt");
    file << "COMMENT: Partial order fulfillment stress test\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 3\n";
    file << "NUM_STOCKS: 1\n";
    
    // Large order gets fulfilled by multiple smaller orders
    file << "0 BUY T0 S0 $100 #50\n";  // Large buy order
    file << "1 SELL T1 S0 $90 #10\n";  // Partial fill 1
    file << "2 SELL T2 S0 $85 #15\n";  // Partial fill 2
    file << "3 SELL T1 S0 $95 #20\n";  // Partial fill 3
    file << "4 SELL T2 S0 $80 #10\n";  // Final partial fill (5 shares remain unmatched)
    
    // Multiple buyers compete for single large sell order
    file << "5 SELL T0 S0 $50 #100\n"; // Large sell order
    file << "6 BUY T1 S0 $60 #25\n";   // First buyer
    file << "7 BUY T2 S0 $65 #30\n";   // Second buyer (higher price)
    file << "8 BUY T1 S0 $55 #40\n";   // Third buyer (lower price)
    file << "9 BUY T2 S0 $70 #20\n";   // Fourth buyer (highest price)
    
    // Should process in price priority: $70, $65, $60, $55
    // Trades should be: 20@$50, 30@$50, 25@$50, 25@$50 (partial)
    
    file.close();
}

void generateTest5() {
    // test-5-m.txt: Median mode - Edge cases and integer division
    ofstream file("test-5-m.txt");
    file << "COMMENT: Median edge cases and integer division\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 3\n";
    file << "NUM_STOCKS: 2\n";
    
    // Test integer division for even number of trades
    file << "0 SELL T0 S0 $33 #10\n";
    file << "0 BUY T1 S0 $40 #10\n";   // Trade at $33
    file << "1 SELL T0 S0 $66 #10\n";
    file << "1 BUY T1 S0 $70 #10\n";   // Trade at $66, median = (33+66)/2 = 49 (integer division)
    
    // Test with odd prices that don't divide evenly
    file << "2 SELL T0 S1 $45 #5\n";
    file << "2 BUY T1 S1 $50 #5\n";    // Trade at $45
    file << "3 SELL T0 S1 $46 #5\n";
    file << "3 BUY T1 S1 $50 #5\n";    // Trade at $46, median = (45+46)/2 = 45 (integer division)
    
    // More trades to test larger median sets
    file << "4 SELL T0 S0 $20 #5\n";
    file << "4 BUY T1 S0 $25 #5\n";    // Trade at $20, sequence: 33,66,20 -> median = 33
    file << "5 SELL T0 S0 $80 #5\n";
    file << "5 BUY T1 S0 $85 #5\n";    // Trade at $80, sequence: 33,66,20,80 -> median = (33+66)/2 = 49
    
    // Test same timestamp with multiple trades
    file << "6 SELL T0 S1 $10 #3\n";
    file << "6 BUY T2 S1 $15 #3\n";    // Trade at $10
    file << "6 SELL T1 S1 $12 #3\n";
    file << "6 BUY T0 S1 $18 #3\n";    // Trade at $12
    
    file.close();
}

void generateTest6() {
    // test-6-i.txt: Trader info mode - Zero activity and extreme values
    ofstream file("test-6-i.txt");
    file << "COMMENT: Trader info with zero activity and extreme scenarios\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 5\n";
    file << "NUM_STOCKS: 2\n";
    
    // Trader 0: No activity (all zeros)
    
    // Trader 1: Only unmatched orders (zeros)
    file << "0 SELL T1 S0 $1000 #10\n"; // Price too high
    file << "0 BUY T1 S1 $1 #10\n";     // Price too low
    
    // Trader 2: High positive net transfer
    file << "0 SELL T2 S0 $10 #100\n";  // Cheap sell
    file << "1 BUY T3 S0 $50 #100\n";   // Expensive buy - T2 receives $1000
    
    // Trader 3: High negative net transfer  
    file << "2 SELL T4 S1 $200 #50\n";  // Expensive sell
    file << "3 BUY T3 S1 $250 #50\n";   // T3 pays $12500 total
    
    // Trader 4: Balanced trading
    file << "4 SELL T4 S0 $100 #20\n";
    file << "4 BUY T2 S0 $120 #20\n";   // T4 receives $2000
    file << "5 BUY T4 S1 $180 #30\n";   // T4 pays $5400, net = 10000+2000-5400 = 6600
    
    // More complex cross-trading
    file << "6 SELL T2 S1 $150 #25\n";
    file << "6 BUY T4 S1 $160 #15\n";   // T2 receives more, T4 pays more
    file << "7 SELL T3 S0 $90 #30\n";
    file << "7 BUY T2 S0 $95 #25\n";    // T3 gets some money back
    
    file.close();
}

void generateTest7() {
    // test-7-t.txt: Time travelers mode - Complex profit scenarios
    ofstream file("test-7-t.txt");
    file << "COMMENT: Complex time travel profit scenarios\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 4\n";
    file << "NUM_STOCKS: 3\n";
    
    // Stock 0: Multiple local optima
    file << "0 SELL T0 S0 $30 #10\n";   // Early cheap sell
    file << "1 BUY T1 S0 $50 #5\n";     // Early profit = 20
    file << "2 SELL T2 S0 $25 #8\n";    // Even cheaper sell
    file << "3 BUY T3 S0 $60 #10\n";    // Better profit = 35
    file << "4 SELL T0 S0 $20 #5\n";    // Best buy opportunity
    file << "5 BUY T1 S0 $65 #8\n";     // Best profit = 45
    
    // Stock 1: Tie-breaking scenario
    file << "0 SELL T0 S1 $40 #10\n";   // Option 1
    file << "0 SELL T1 S1 $40 #10\n";   // Same price, same time
    file << "1 BUY T2 S1 $70 #15\n";    // Same profit from both, should pick T0 (earlier in input)
    
    // Stock 2: Decreasing prices (no profit)
    file << "0 SELL T0 S2 $100 #10\n";
    file << "1 SELL T1 S2 $90 #10\n";
    file << "2 SELL T2 S2 $80 #10\n";
    file << "3 BUY T3 S2 $70 #15\n";    // All buys are lower than sells
    
    // Additional orders for Stock 0 to test tie-breaking with timestamps
    file << "1 SELL T3 S0 $20 #3\n";    // Same price as timestamp 4 sell, earlier time
    file << "6 BUY T2 S0 $65 #5\n";     // Same profit, later time - should still use timestamp 4->5
    
    file.close();
}

void generateTest8() {
    // test-8-v.txt: Verbose mode - Same timestamp ordering and rapid trades
    ofstream file("test-8-v.txt");
    file << "COMMENT: Same timestamp ordering and rapid sequential trades\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 4\n";
    file << "NUM_STOCKS: 2\n";
    
    // Multiple orders at timestamp 0 - test processing order
    file << "0 SELL T0 S0 $50 #10\n";
    file << "0 SELL T1 S0 $45 #15\n";   // Better price
    file << "0 BUY T2 S0 $60 #20\n";    // Should match T1 first (better price)
    file << "0 BUY T3 S0 $55 #10\n";    // Should match T0 next
    
    // Rapid sequence of trades at same timestamp
    file << "1 SELL T0 S1 $30 #5\n";
    file << "1 SELL T1 S1 $35 #5\n";
    file << "1 SELL T2 S1 $25 #5\n";    // Best price
    file << "1 SELL T3 S1 $40 #5\n";
    file << "1 BUY T0 S1 $50 #20\n";    // Should match in price order: $25, $30, $35, $40
    
    // Test price-time priority interaction
    file << "2 SELL T0 S0 $70 #8\n";
    file << "3 SELL T1 S0 $70 #12\n";   // Same price, later time
    file << "4 BUY T2 S0 $75 #15\n";    // Should match T0 first (earlier time)
    
    // Large order triggering multiple matches
    file << "5 SELL T0 S1 $60 #3\n";
    file << "5 SELL T1 S1 $65 #4\n";
    file << "5 SELL T2 S1 $55 #6\n";
    file << "5 SELL T3 S1 $70 #2\n";
    file << "6 BUY T0 S1 $80 #20\n";    // Matches all in price order
    
    file.close();
}

void generateTest9() {
    // test-9-m.txt: Median mode - Timestamp gaps and final median
    ofstream file("test-9-m.txt");
    file << "COMMENT: Median with timestamp gaps and final output testing\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 3\n";
    file << "NUM_STOCKS: 2\n";
    
    // Initial trades at timestamp 0
    file << "0 SELL T0 S0 $40 #10\n";
    file << "0 BUY T1 S0 $45 #10\n";    // Trade at $40
    
    // Gap to timestamp 10 - should print median at time 0
    file << "10 SELL T0 S0 $60 #10\n";
    file << "10 BUY T1 S0 $65 #10\n";   // Trade at $60
    
    // Another gap to timestamp 25
    file << "25 SELL T0 S1 $80 #5\n";
    file << "25 BUY T1 S1 $85 #5\n";    // Trade at $80
    file << "25 SELL T0 S0 $30 #8\n";
    file << "25 BUY T2 S0 $35 #8\n";    // Trade at $30
    
    // Final gap to timestamp 50
    file << "50 SELL T0 S1 $90 #10\n";
    file << "50 BUY T1 S1 $95 #10\n";   // Trade at $90
    
    // Orders that don't match (should not affect median)
    file << "50 SELL T0 S0 $200 #5\n";
    file << "50 BUY T1 S0 $100 #5\n";
    
    // Test final median output (should show final medians for all stocks with trades)
    
    file.close();
}

void generateTest9Fixed() {
    // test-9-m.txt: Median mode - Timestamp gaps and final median (fixed)
    ofstream file("test-9-m.txt");
    file << "COMMENT: Median with timestamp gaps and final output testing\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 3\n";
    file << "NUM_STOCKS: 2\n";
    
    // Initial trades at timestamp 0
    file << "0 SELL T0 S0 $40 #10\n";
    file << "0 BUY T1 S0 $45 #10\n";    // Trade at $40
    
    // Gap to timestamp 10 - should print median at time 0
    file << "10 SELL T0 S0 $60 #10\n";
    file << "10 BUY T1 S0 $65 #10\n";   // Trade at $60
    
    // Another gap to timestamp 25
    file << "25 SELL T0 S1 $80 #5\n";
    file << "25 BUY T1 S1 $85 #5\n";    // Trade at $80
    file << "25 SELL T0 S0 $30 #8\n";
    file << "25 BUY T2 S0 $35 #8\n";    // Trade at $30
    
    // Final gap to timestamp 50
    file << "50 SELL T0 S1 $90 #10\n";
    file << "50 BUY T1 S1 $95 #10\n";   // Trade at $90
    
    // Orders that don't match (should not affect median)
    file << "50 SELL T0 S0 $200 #5\n";
    file << "50 BUY T1 S0 $100 #5\n";
    
    file.close();
}

void generateTest10Fixed() {
    // test-10-i.txt: Trader info mode - Maximum utilization edge case (fixed)
    ofstream file("test-10-i.txt");
    file << "COMMENT: Maximum utilization with all traders active\n";
    file << "MODE: TL\n";
    file << "NUM_TRADERS: 8\n";
    file << "NUM_STOCKS: 3\n";
    
    // Every trader participates in some way
    file << "0 SELL T0 S0 $50 #20\n";
    file << "0 BUY T1 S0 $60 #15\n";    // T0 sells 15, T1 buys 15
    file << "1 SELL T2 S1 $30 #25\n";
    file << "1 BUY T3 S1 $40 #20\n";    // T2 sells 20, T3 buys 20
    file << "2 SELL T4 S2 $70 #10\n";
    file << "2 BUY T5 S2 $80 #8\n";     // T4 sells 8, T5 buys 8
    
    // Cross-stock trading
    file << "3 BUY T6 S0 $55 #10\n";    // T0 sells remaining 5, T6 buys 5
    file << "3 BUY T7 S1 $35 #15\n";    // T2 sells remaining 5, T7 buys 5
    file << "4 BUY T0 S2 $75 #5\n";     // T4 sells remaining 2, T0 buys 2
    
    // More complex interactions
    file << "5 SELL T1 S0 $45 #30\n";
    file << "5 BUY T2 S0 $50 #25\n";    // T1 sells 25, T2 buys 25
    file << "6 SELL T3 S1 $25 #40\n";
    file << "6 BUY T4 S1 $30 #35\n";    // T3 sells 35, T4 buys 35
    file << "7 SELL T5 S2 $65 #20\n";
    file << "7 BUY T6 S2 $70 #18\n";    // T5 sells 18, T6 buys 18
    
    // Final round to ensure everyone has some activity
    file << "8 SELL T7 S0 $42 #12\n";   // Fixed: T7 sells with price
    file << "8 BUY T0 S0 $40 #10\n";    // T0 buys, T7 sells 10
    
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
    
    generateTest9Fixed();
    cout << "Generated test-9-m.txt (Timestamp gaps)\n";
    
    // generateTest10Fixed();
    // cout << "Generated test-10-i.txt (Maximum utilization)\n";
    
    cout << "\nAll test files generated successfully!\n";
    cout << "Each test targets specific edge cases and algorithmic weaknesses.\n";
    
    return 0;
}