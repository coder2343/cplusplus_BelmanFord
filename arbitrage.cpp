/*
 * CSC-301
 * arbitrage.cpp
 * Fall 2022
 * Eric A. Autry
 * 10/03/22
 */

#include "arbitrage.hpp"

using namespace std;

/*
 * getRates: given an exchange number indicating the scenario to run, will 
 *           output a pair of the exchange rates and the currency labels.
 *
 * INPUTS
 * int exchangeNum: an int indicating the scenario to run.
 *                  0: The small example from the writeup.
 *                  1: Some actual currency rates from 11/12/18.
 *                  2: Rates from 1, with USD undervalued w.r.t. GBP.
 *                  3: Rates from 1, with USD undervalued w.r.t. GBP,
 *                                        JPY overvalued w.r.t. INR,
 *                                        SAR overvalued w.r.t. HKD.
 *
 * OUTPUTS
 * vector<double> rates: the 1D array representing the exchange rates matrix.
 * vector<string> currencies: the array of currency label strings.
 */
pair<vector<double>, vector<string>> getRates(int exchangeNum) {
    // Pick the set of rates.
    switch (exchangeNum) {
        case 0: {
            // Small example from class.
            vector<string> currencies = {"Dollar", "Euro", "Yen", "Lira"};
            int n = currencies.size();
            vector<double> rates = {0,      0.82, 0,     0,  // Dollar to Euro
                                    0,      0,    129.7, 0,  // Euro to Yen
                                    0,      0,    0,     12, // Yen to Lira
                                    0.0008, 0,    0,     0}; // Lira to Dollar

            rates[0*n + 2] = rates[0*n + 1] * rates[1*n + 2]; // Dollar to Yen
            rates[1*n + 3] = rates[1*n + 2] * rates[2*n + 3]; // Euro to Lira

            // Fill the reverse directions with the reciprocals.
            rates[1*n + 0] = 1/rates[0*n + 1];
            rates[2*n + 1] = 1/rates[1*n + 2];
            rates[3*n + 2] = 1/rates[2*n + 3];
            rates[0*n + 3] = 1/rates[3*n + 0];
            rates[2*n + 0] = 1/rates[0*n + 2];
            rates[3*n + 1] = 1/rates[1*n + 3];

            // Package as a pair and return.
            pair<vector<double>, vector<string>> exchange;
            exchange.first = rates;
            exchange.second = currencies;
            return exchange;
        }
        case 1: {
            // Some actual currency rates from 11/12/18.
            // Euro rates to 13 others.
            vector<double> EUrates = {1.0000, 0.8750, 1.1342, 1.1245, 1.5630, 
                                      1.4857, 8.8100, 81.9811, 127.9574, 
                                      4.2180, 1.5553, 16.2280, 10.2656, 4.1305};
            vector<string> currencies = {"EUR","GBP","CHF","USD","AUD","CAD",
                                         "HKD","INR","JPY","SAR","SGD","ZAR",
                                         "SEK","AED"};
            int n = currencies.size();
            vector<double> rates(n*n, 0);

            // Fill the first row with the Euro rates.
            // And the first column with their reciprocals.
            for (int i=0; i<EUrates.size(); i++) {
                rates[i] = EUrates[i];
                rates[i*n] = 1/EUrates[i];
            }

            // Fill in the remaining rates.
            // Note: GBP->USD = (GBP->EUR)*(EUR->USD)
            // (assuming no arbitrage in the real rates)
            for (int r=1; r<n; r++) {
                rates[r*n + r] = 1.0;
                for (int c=r+1; c<n; c++) {
                    rates[r*n + c] = rates[r*n] * rates[c];
                    rates[c*n + r] = 1/rates[r*n + c];
                }
            }

            // Package as a pair and return.
            pair<vector<double>, vector<string>> exchange;
            exchange.first = rates;
            exchange.second = currencies;
            return exchange;
        }
        case 2: {
            // Get the rates from case 1.
            pair<vector<double>, vector<string>> exchange = getRates(1);
            vector<double> &rates = exchange.first;
            vector<string> &currencies = exchange.second;
            int n = currencies.size();

            // Underprice the dollar (3) with repect to the pound (1).
            rates[3*n+1] -= 0.01;
            rates[1*n+3] = 1/rates[3*n+1];

            // Package as a pair and return.
            return exchange;
        }
        case 3: {
            // Get the rates from case 2 with the undervalued USD.
            pair<vector<double>, vector<string>> exchange = getRates(2);
            vector<double> &rates = exchange.first;
            vector<string> &currencies = exchange.second;
            int n = currencies.size();

            // Overprice the yen (8) with repect to the rupee (7).
            rates[8*n + 7] += 0.01;
            rates[7*n + 8] = 1/rates[8*n + 7];

            // Overprice the riyal (9) with repect to the HK dollar (6).
            rates[9*n + 6] += 0.07;
            rates[6*n + 9] = 1/rates[9*n + 6];

            // Return.
            return exchange;
        }
        default: {
            // Small example from class.
            vector<string> currencies = {"Dollar", "Euro", "Yen", "Lira"};
            int n = currencies.size();
            vector<double> rates = {0,      0.82, 0,     0,  // Dollar to Euro
                                    0,      0,    129.7, 0,  // Euro to Yen
                                    0,      0,    0,     12, // Yen to Lira
                                    0.0008, 0,    0,     0}; // Lira to Dollar

            rates[0*n + 2] = rates[0*n + 1] * rates[1*n + 2]; // Dollar to Yen
            rates[1*n + 3] = rates[1*n + 2] * rates[2*n + 3]; // Euro to Lira

            // Fill the reverse directions with the reciprocals.
            rates[1*n + 0] = 1/rates[0*n + 1];
            rates[2*n + 1] = 1/rates[1*n + 2];
            rates[3*n + 2] = 1/rates[2*n + 3];
            rates[0*n + 3] = 1/rates[3*n + 0];
            rates[2*n + 0] = 1/rates[0*n + 2];
            rates[3*n + 1] = 1/rates[1*n + 3];

            // Package as a pair and return.
            pair<vector<double>, vector<string>> exchange;
            exchange.first = rates;
            exchange.second = currencies;
            return exchange;
        }
    }
}

/*
 * testExchange: tests the exchange specified by exchangeNum and reports the 
 *               result - will print extra info if verbosity is on.
 *
 * INPUTS
 * int exchangeNum: specifies the scenario when calling getRates.
 * bool cycleExpected: whether a cycle was expected for this test.
 * bool verbosity: set to true to enable printing extra info.
 *
 * OUTPUTS
 * bool passed: indicates whether the test passed or failed.
 */
bool testExchange(int exchangeNum, bool cycleExpected, bool verbosity) {
    if (verbosity) {
        cout << "Testing Exchange Number: " << exchangeNum << endl;
    }

    bool passed = true;

    // Get the rates and currencies for this exchange.
    pair<vector<double>, vector<string>> exchange = getRates(exchangeNum);
    vector<double> rates = exchange.first;
    vector<string> currencies = exchange.second;
    int n = currencies.size();

    // Create the corresponding adjacency matrix.
    vector<double> adjMatrix = createAdjacencyMatrix(rates, currencies);

    // Find the negative cost cycle.
    vector<int> cycle = detectArbitrage(adjMatrix, currencies);

    // Print the cycle.
    if (verbosity) {
        cout << endl << "\tReported Cycle:" << " ";
        for (int i=0; i<cycle.size(); i++) {
            cout << currencies[cycle[i]] << " ";
        }
        cout << endl << endl;
    }

    // Check for a cycle.
    if (cycle.size() == 0) {
        // No cycle.
        if (verbosity) {
            cout << "\tNo Cycle Detected" << endl;
        }
        if (cycleExpected) {
            passed = false;
        }
    } else {
        // Cycle reported. Ensure it was a cycle.
        if (cycle.size() < 2) {
            passed = false;
            if (verbosity) {
                cout << "\tInvalid cycle: only 1 vertex." << endl;
            }
        } else if (cycle[0] != cycle[cycle.size()-1]) {
            passed = false;
            if (verbosity) {
                cout << "\tInvalid cycle: start != end." << endl;
            }
        } else {
            // A cycle was given, check to ensure arbitrage.
            double arb = 1;
            for (int i=0; i<cycle.size()-1; i++) {
                arb *= rates[cycle[i]*n + cycle[i+1]];
            }
            if (arb <= 1) {
                passed = false;
                if (verbosity) {
                    cout << "\tNo arbitrage in reported cycle." << endl;
                    cout << "\t1 " << currencies[cycle[0]] << " became ";
                    cout << arb << " " << currencies[cycle[0]] << "." << endl;
                }
            } else {
                if (verbosity) {
                    cout << "\tArbitrage in cycle for gain of: ";
                    cout << arb-1 << " " << currencies[cycle[0]] << "." << endl;
                }
                if (not cycleExpected) {
                    passed = false;
                    if (verbosity) {
                        cout << "\tInvalid: found arbitrage when none existed.";
                        cout << endl;
                    }
                }
            }
        }
    }

    // Indicate if the test passed.
    if (verbosity) {
        cout << endl;
        if (passed) {
            cout << "\tTest Passed!" << endl;
        } else {
            cout << "\tTest Failed!" << endl;
        }
    }
    return passed;
}

/*
 * printCurrencyMatrix: prints an nxn matrix and its n labels so it looks nice.
 *                      well... assuming that everything is formatted right.
 *
 * INPUTS
 * vector<double> &mat: the nxn matrix to print.
 * vector<string> &labels: the n-length vector of vertex labels.
 * int labelWidth: string width for printing the vertex labels, should be at
 *                 least the length of the longest label. Default to 3.
 * int prec: the precision to use when printing numbers, using fixed format (so
 *           this is really specifying the number of digits after the decimal 
 *           point). Default to 4.
 * int numWidth: the width of printing for the numbers, should be at least the
 *               length of the biggest number (out to prec decimal places), 
 *               plus one. Default to 8.
 *
 * OUTPUTS
 * string matString.str(): the pretty string.
 */
string printCurrencyMatrix(vector<double> &mat, vector<string> &labels,
                           int labelWidth=3, int prec=4, int numWidth=8) {
    // Create the stringstream for the matrix.
    stringstream matString;

    // Shift the first row for the labels and write the labels.
    matString << setw(labelWidth) << fixed;
    matString << " " << " ";
    for (int i=0; i<labels.size(); i++) {
        matString << setprecision(prec) << setw(numWidth) << fixed;
        matString << labels[i] << " ";
    }
    matString << endl;

    // Write each line of the matrix, with the proper label at front.
    for (int i=0; i<labels.size(); i++) {
        matString << setw(labelWidth) << fixed;
        matString << labels[i] << " ";
        for (int j=0; j<labels.size(); j++) {
            matString << setprecision(prec) << setw(numWidth) << fixed;
            matString << mat[i*labels.size()+j] << " ";
        }
        matString << endl;
    }
    matString << endl;

    return matString.str();
}

/* main
 * 
 * Runs all four of the test scenarios and prints the results.
 *
 * Compile with:
 *
 *     make
 *
 * Run with:
 *
 *     arbitrage
 *
 */
int main(int argc, char* argv[]) {
    bool verb = true;
    int passed = 0;
    int tried = 0;

    cout << endl;

    tried++;
    if (testExchange(0, true, verb)) {
        passed++;
    }
    if (verb) {cout << endl;}

    tried++;
    if (testExchange(1, false, verb)) {
        passed++;
    }
    if (verb) {cout << endl;}

    tried++;
    if (testExchange(2, true, verb)) {
        passed++;
    }
    if (verb) {cout << endl;}

    tried++;
    if (testExchange(3, true, verb)) {
        passed++;
    }
    if (verb) {cout << endl;}

    cout << "Passed " << passed << "/" << tried << " tests!" << endl;
    cout << endl;

    return 0;
}