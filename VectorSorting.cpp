//============================================================================
// Name        : VectorSorting.cpp
// Author      : Joshua Hale
// Version     : 1.0
// Copyright   : Copyright © 2024 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================

#include <algorithm>  // Include algorithm library for swap function
#include <iostream>   // Include iostream for input and output
#include <time.h>     // Include time.h for clock function
#include "CSVparser.hpp"  // Include CSV parser header

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// Forward declarations
double strToDouble(string str, char ch);

// Define a structure to hold bid information
struct Bid {
    string bidId; // Unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid Struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information using console (std::in)
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath The path to the CSV file to load
 * @return A container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // Initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // Loop to read rows of a CSV file
        for (size_t i = 0; i < file.rowCount(); i++) {  // Change 'int' to 'size_t' for correct type comparison

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // Push this bid to the end
            bids.push_back(bid);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid>& bids, int begin, int end) {
    Bid pivot = bids[end];  // Set pivot as the end element
    int i = begin;
    for (int j = begin; j < end; ++j) {
        if (bids[j].title <= pivot.title) {  // Compare title with pivot
            swap(bids[i], bids[j]);
            i++;
        }
    }
    swap(bids[i], bids[end]);  // Swap pivot to the correct position
    return i;  // Return the partition index
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids Address of the vector<Bid> instance to be sorted
 * @param begin The beginning index to sort on
 * @param end The ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end) {
    if (begin >= end) {
        return;  // Base case: If the range is 1 or zero elements
    }
    int partitionIndex = partition(bids, begin, end);  // Partition the bids
    quickSort(bids, begin, partitionIndex - 1);  // Recursively sort the left partition
    quickSort(bids, partitionIndex + 1, end);    // Recursively sort the right partition
}

/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid Address of the vector<Bid> instance to be sorted
 */
void selectionSort(vector<Bid>& bids) {
    for (size_t i = 0; i < bids.size(); ++i) {  // Change 'int' to 'size_t' for correct type comparison
        size_t minIndex = i;
        for (size_t j = i + 1; j < bids.size(); ++j) {  // Change 'int' to 'size_t' for correct type comparison
            if (bids[j].title < bids[minIndex].title) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(bids[i], bids[minIndex]);
        }
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * Credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // Process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "\\\\apporto.com\\dfs\\SNHU\\Users\\joshuahale3_snhu\\Desktop\\CS 300 Vector Sorting Assignment Student Files\\CS 300 Vector Sorting Assignment Student Files\\eBid_Monthly_Sales.csv"; // Default CSV path
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t startTicks, endTicks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Selection Sort All Bids" << endl;
        cout << "  4. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Start the timer before loading bids
            startTicks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            // Stop the timer after loading bids
            endTicks = clock();

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            cout << "time: " << (endTicks - startTicks) << " clock ticks" << endl;
            cout << "time: " << (double)(endTicks - startTicks) / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the bids read
            for (size_t i = 0; i < bids.size(); ++i) {  // Change 'int' to 'size_t' for correct type comparison
                displayBid(bids[i]);
            }
            cout << endl;

            break;

        case 3:
            // Start the timer before sorting
            startTicks = clock();

            // Perform selection sort
            selectionSort(bids);

            // Stop the timer after sorting
            endTicks = clock();

            cout << bids.size() << " bids sorted" << endl;

            // Calculate elapsed time and display result
            cout << "time: " << (endTicks - startTicks) << " clock ticks" << endl;
            cout << "time: " << (double)(endTicks - startTicks) / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            // Start the timer before sorting
            startTicks = clock();

            // Perform quick sort
            quickSort(bids, 0, bids.size() - 1);

            // Stop the timer after sorting
            endTicks = clock();

            cout << bids.size() << " bids sorted" << endl;

            // Calculate elapsed time and display result
            cout << "time: " << (endTicks - startTicks) << " clock ticks" << endl;
            cout << "time: " << (double)(endTicks - startTicks) / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        }
    }

    cout << "Goodbye." << endl;

    return 0;
}
