// Project Identifier: 0E04A31E0D60C01986ACB20081C9D8722A2519B6

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <getopt.h>
#include <climits>
#include "P2random.h"

using namespace std;

struct Order {
    int timestamp;
    int traderId;
    int stockId;
    bool isBuy;
    int price;
    int quantity;
    int orderId;  // Add unique order ID for tie-breaking
    
    Order(int ts, int tid, int sid, bool buy, int p, int q, int oid)
        : timestamp(ts), traderId(tid), stockId(sid), isBuy(buy), 
          price(p), quantity(q), orderId(oid) {}
};

// Comparator for buy orders (max-heap by price, then min-heap by orderId for tie-breaking)
struct BuyComparator {
    bool operator()(const Order& a, const Order& b) const {
        if (a.price != b.price) 
            return a.price < b.price; // Higher price has priority
        return a.orderId > b.orderId; // Earlier order (lower ID) has priority
    }
};

// Comparator for sell orders (min-heap by price, then min-heap by orderId for tie-breaking)
struct SellComparator {
    bool operator()(const Order& a, const Order& b) const {
        if (a.price != b.price) 
            return a.price > b.price; // Lower price has priority
        return a.orderId > b.orderId; // Earlier order (lower ID) has priority
    }
};

// Running median tracker
class RunningMedian {
private:
    priority_queue<int> maxHeap; // Lower half (max at top)
    priority_queue<int, vector<int>, greater<int>> minHeap; // Upper half (min at top)
    
public:
    void addPrice(int price) {
        // Add to appropriate heap
        if (maxHeap.empty() || price <= maxHeap.top()) {
            maxHeap.push(price);
        } else {
            minHeap.push(price);
        }
        
        // Rebalance heaps - keep sizes within 1 of each other
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    int getMedian() const {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        } else {
            return (maxHeap.top() + minHeap.top()) / 2;
        }
    }
    
    bool hasData() const {
        return !maxHeap.empty();
    }
};

// Trader statistics
struct TraderStats {
    int sharesBought = 0;
    int sharesSold = 0;
    int moneySpent = 0;
    int moneyReceived = 0;
    
    int getNetTransfer() const {
        return moneyReceived - moneySpent;
    }
};

// Time travel data
struct TimeTravel {
    int minSellPrice = INT_MAX;
    int minSellTime = -1;
    int maxProfit = 0;
    int bestBuyTime = -1;
    int bestSellTime = -1;
    int bestBuyPrice = -1;
    int bestSellPrice = -1;
    bool hasTrades = false;
};

// Global variables
vector<priority_queue<Order, vector<Order>, BuyComparator>> buyQueues;
vector<priority_queue<Order, vector<Order>, SellComparator>> sellQueues;
vector<RunningMedian> medianTrackers;
vector<TraderStats> traderStats;
vector<TimeTravel> timeTravelData;

bool verboseMode = false;
bool medianMode = false;
bool traderInfoMode = false;
bool timeTravelersMode = false;

int numTraders = 0;
int numStocks = 0;
int tradesCompleted = 0;
int currentTimestamp = 0;
int nextOrderId = 0;  // Global order counter for unique IDs

void printHelp() {
    cout << "Stock Market Simulation\n";
    cout << "Options:\n";
    cout << "  -h, --help          Show this help message\n";
    cout << "  -v, --verbose       Enable verbose output\n";
    cout << "  -m, --median        Enable median output\n";
    cout << "  -i, --trader_info   Enable trader info output\n";
    cout << "  -t, --time_travelers Enable time travelers output\n";
}

void parseCommandLine(int argc, char* argv[]) {
    static struct option longOptions[] = {
        {"help", no_argument, 0, 'h'},
        {"verbose", no_argument, 0, 'v'},
        {"median", no_argument, 0, 'm'},
        {"trader_info", no_argument, 0, 'i'},
        {"time_travelers", no_argument, 0, 't'},
        {0, 0, 0, 0}
    };
    
    int c;
    while ((c = getopt_long(argc, argv, "hvmit", longOptions, 0)) != -1) {
        switch (c) {
            case 'h':
                printHelp();
                exit(0);
            case 'v':
                verboseMode = true;
                break;
            case 'm':
                medianMode = true;
                break;
            case 'i':
                traderInfoMode = true;
                break;
            case 't':
                timeTravelersMode = true;
                break;
            default:
                exit(1);
        }
    }
}

void updateTimeTravel(int stockId, bool isBuy, int price, int timestamp) {
    if (!timeTravelersMode) return;
    
    auto& tt = timeTravelData[stockId];
    tt.hasTrades = true;
    
    if (!isBuy) { // SELL order - potential buy point for time traveler
        if (price < tt.minSellPrice) {
            tt.minSellPrice = price;
            tt.minSellTime = timestamp;
        }
    } else { // BUY order - potential sell point for time traveler
        if (tt.minSellTime != -1) {  // Only if we have a previous sell order
            int profit = price - tt.minSellPrice;
            if (profit > tt.maxProfit) {
                tt.maxProfit = profit;
                tt.bestBuyTime = tt.minSellTime;
                tt.bestSellTime = timestamp;
                tt.bestBuyPrice = tt.minSellPrice;
                tt.bestSellPrice = price;
            }
        }
    }
}

void executeTrade(int buyerId, int sellerId, int stockId, int quantity, int price) {
    tradesCompleted++;
    
    if (verboseMode) {
        cout << "Trader " << buyerId << " purchased " << quantity 
             << " shares of Stock " << stockId << " from Trader " 
             << sellerId << " for $" << price << "/share\n";
    }
    
    if (medianMode) {
        medianTrackers[stockId].addPrice(price);
    }
    
    if (traderInfoMode) {
        int totalValue = quantity * price;
        traderStats[buyerId].sharesBought += quantity;
        traderStats[buyerId].moneySpent += totalValue;
        traderStats[sellerId].sharesSold += quantity;
        traderStats[sellerId].moneyReceived += totalValue;
    }
}

void matchOrders(int stockId) {
    auto& buyQueue = buyQueues[stockId];
    auto& sellQueue = sellQueues[stockId];
    
    while (!buyQueue.empty() && !sellQueue.empty()) {
        Order buyOrder = buyQueue.top();
        Order sellOrder = sellQueue.top();
        
        // Check if trade is possible
        if (sellOrder.price > buyOrder.price) {
            break; // No more matches possible
        }
        
        // Determine trade price: use price of the earlier order
        // CRITICAL FIX: Use strict < instead of <=
        int tradePrice;
        if (sellOrder.orderId < buyOrder.orderId) {
            // Sell order came first, use sell price
            tradePrice = sellOrder.price;
        } else {
            // Buy order came first, use buy price
            tradePrice = buyOrder.price;
        }
        
        // Determine trade quantity
        int tradeQuantity = min(buyOrder.quantity, sellOrder.quantity);
        
        // Execute trade
        executeTrade(buyOrder.traderId, sellOrder.traderId, stockId, 
                    tradeQuantity, tradePrice);
        
        // Update orders
        buyQueue.pop();
        sellQueue.pop();
        
        if (buyOrder.quantity > tradeQuantity) {
            buyOrder.quantity -= tradeQuantity;
            buyQueue.push(buyOrder);
        }
        
        if (sellOrder.quantity > tradeQuantity) {
            sellOrder.quantity -= tradeQuantity;
            sellQueue.push(sellOrder);
        }
    }
}

void printMedianOutput(int timestamp) {
    if (!medianMode) return;
    
    for (int stockId = 0; stockId < numStocks; ++stockId) {
        if (medianTrackers[stockId].hasData()) {
            int median = medianTrackers[stockId].getMedian();
            cout << "Median match price of Stock " << stockId 
                 << " at time " << timestamp << " is $" << median << "\n";
        }
    }
}

void printSummary() {
    cout << "---End of Day---\n";
    cout << "Trades Completed: " << tradesCompleted << "\n";
}

void printTraderInfo() {
    if (!traderInfoMode) return;
    
    cout << "---Trader Info---\n";
    for (int traderId = 0; traderId < numTraders; ++traderId) {
        const auto& stats = traderStats[traderId];
        cout << "Trader " << traderId << " bought " << stats.sharesBought
             << " and sold " << stats.sharesSold 
             << " for a net transfer of $" << stats.getNetTransfer() << "\n";
    }
}

void printTimeTravelers() {
    if (!timeTravelersMode) return;
    
    cout << "---Time Travelers---\n";
    for (int stockId = 0; stockId < numStocks; ++stockId) {
        const auto& tt = timeTravelData[stockId];
        
        if (!tt.hasTrades || tt.maxProfit <= 0) {
            cout << "A time traveler could not make a profit on Stock " 
                 << stockId << "\n";
        } else {
            cout << "A time traveler would buy Stock " << stockId 
                 << " at time " << tt.bestBuyTime << " for $" << tt.bestBuyPrice
                 << " and sell it at time " << tt.bestSellTime 
                 << " for $" << tt.bestSellPrice << "\n";
        }
    }
}

void processOrders(istream& inputStream) {
    int timestamp, traderId, stockId, price, quantity;
    string buySell;
    char t, s, dollar, pound;
    
    while (inputStream >> timestamp >> buySell >> t >> traderId >> s >> stockId 
           >> dollar >> price >> pound >> quantity) {
        
        // Input validation
        if (timestamp < 0) {
            cerr << "Error: Invalid timestamp\n";
            exit(1);
        }
        if (timestamp < currentTimestamp) {
            cerr << "Error: Timestamps must be non-decreasing\n";
            exit(1);
        }
        if (traderId < 0 || traderId >= numTraders) {
            cerr << "Error: Invalid trader ID\n";
            exit(1);
        }
        if (stockId < 0 || stockId >= numStocks) {
            cerr << "Error: Invalid stock ID\n";
            exit(1);
        }
        if (price <= 0 || quantity <= 0) {
            cerr << "Error: Price and quantity must be positive\n";
            exit(1);
        }
        
        // Print median if timestamp changed
        if (timestamp != currentTimestamp) {
            printMedianOutput(currentTimestamp);
            currentTimestamp = timestamp;
        }
        
        bool isBuy = (buySell == "BUY");
        
        // Update time travel data
        updateTimeTravel(stockId, isBuy, price, timestamp);
        
        // Add order to appropriate queue with unique order ID
        Order order(timestamp, traderId, stockId, isBuy, price, quantity, nextOrderId++);
        if (isBuy) {
            buyQueues[stockId].push(order);
        } else {
            sellQueues[stockId].push(order);
        }
        
        // Try to match orders
        matchOrders(stockId);
    }
    
    // Print final median
    printMedianOutput(currentTimestamp);
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);  // Speed up I/O
    
    parseCommandLine(argc, argv);
    
    // Read header
    string commentLine, temp, actualMode;
    getline(cin, commentLine); // COMMENT line
    cin >> temp >> actualMode; // "MODE:" and actual mode (TL or PR)
    cin >> temp >> numTraders; // "NUM_TRADERS:" and value
    cin >> temp >> numStocks; // "NUM_STOCKS:" and value
    
    // Initialize data structures
    buyQueues.resize(numStocks);
    sellQueues.resize(numStocks);
    
    // Only allocate memory for enabled output modes (no dynamic allocation)
    if (medianMode) {
        medianTrackers.resize(numStocks);
    }
    if (traderInfoMode) {
        traderStats.resize(numTraders);
    }
    if (timeTravelersMode) {
        timeTravelData.resize(numStocks);
    }
    
    cout << "Processing orders...\n";
    
    if (actualMode == "TL") {
        processOrders(cin);
    } else if (actualMode == "PR") {
        unsigned int seed, numOrders, arrivalRate;
        cin >> temp >> seed; // "RANDOM_SEED:" and value
        cin >> temp >> numOrders; // "NUMBER_OF_ORDERS:" and value  
        cin >> temp >> arrivalRate; // "ARRIVAL_RATE:" and value
        
        stringstream ss;
        P2random::PR_init(ss, seed, numTraders, numStocks, numOrders, arrivalRate);
        processOrders(ss);
    } else {
        cerr << "Error: Invalid mode\n";
        exit(1);
    }
    
    printSummary();
    printTraderInfo();
    printTimeTravelers();
    
    return 0;
}