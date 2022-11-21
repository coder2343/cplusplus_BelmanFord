/*
 * CSC-301
 * arbitrage.hpp
 * Fall 2022
 * Eric A. Autry
 * 10/03/22
 */

#ifndef ARBITRAGE_HPP_
#define ARBITRAGE_HPP_

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>

#include "project3.hpp"

/*
 * getRates: given an exchange number indicating the scenario to run, will 
 *           output a pair of the exchange rates and the currency labels.
 *
 * INPUTS
 * exchangeNum: an int indicating the scenario to run.
 *              0: The small example from the writeup.
 *              1: Some actual currency rates from 11/12/18.
 *              2: Rates from 1, with USD undervalued w.r.t. GBP.
 *              3: Rates from 1, with USD undervalued w.r.t. GBP,
 *                                    JPY overvalued w.r.t. INR,
 *                                    SAR overvalued w.r.t. HKD.
 *
 * OUTPUTS
 * vector<double> rates: the 1D array representing the exchange rates matrix.
 * vector<string> currencies: the array of currency label strings.
 */
std::pair< std::vector<double>,
           std::vector<std::string> > getRates(int exchangeNum);

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
bool testExchange(int exchangeNum, bool cycleExpected, bool verbosity);

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
std::string printCurrencyMatrix(std::vector<double> &mat,
                                std::vector<std::string> &labels,
                                int labelWidth, int prec, int numWidth);

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
int main(int argc, char* argv[]);

#endif  // ARBITRAGE_HPP_