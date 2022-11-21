/*
 * CSC-301
 * project3.cpp
 * Fall 2022
 *
 * Partner 1: Liam Walsh
 * Partner 2:
 * Date:
 * Prof Erik helped with debugging
 * and Will O helped me by comparing what cycles we got with each other
 */


#include "project3.hpp"
#include <math.h>  

using namespace std;


/*
 * createAdjacencyMatrix
    rates: list of curancy rates in vector
    curancies: list of curancies which is a list of strings stored in vector.

    return created adj matrix of log(curancy exchange rates) for a  batch of inputed curancies.
 */
vector<double> createAdjacencyMatrix(vector<double> &rates, 
                                     vector<string> &currencies) {
    // change the vector to useing log base 10 function
    // for distance calculations that are provided latter
    // apply log10 to every elment in rates 
    vector<double> logRates;
    for(int i =0; i<rates.size();i++){
        logRates.push_back(-log10(rates[i]));
    }
   //printCurrencyMatrix2(logRates,currencies);
    vector<double> adjMatrix(logRates);
    return adjMatrix;
}

/*
 * detectArbitrage
    adjMatrix : adj matrix is a vector of curancy and there rates 
    currencies: list of curancies in adj matrix
 returns if there is an arbitarge oportubity in the curancy adj matrix by searing for neg cost cyxle
 */
vector<int> detectArbitrage(vector<double> &adjMatrix, 
                            vector<string> &currencies, 
                            double tol) {
    // Get the number of vertices and initialize the dist and prev values.
    // first step get size of vertecies and inialize their distance and prev values 
    int n = currencies.size();
    vector<double> distances( n, numeric_limits<double>::infinity() );
    vector<int> previous(n,-1 );
    // implement belman ford algorithim with the requisite steps.
    // set sgtart. dsitance to 0
    distances[1] = 0;
    // for each of the v-1 itterations then do the following 
    // for each neighbor of u
    for(int i=0; i<n-1;i++){
        for (int k = 0; k < n; k++){
            for (int j = 0; j <n; j++){
                if (distances[j]> (distances[k] + adjMatrix[ (k*n)+j ]+ tol)) {
                    // update stuff for cycle detection next
                    distances[j] = distances[k]+ adjMatrix[(k*n)+j];
                    //neighbor.prev = 
                    previous[j]=k;
                }
            }
        }
    }


    int cycleStart = -1;
    for (int k = 0; k < n; k++){
        for (int j = 0; j <n; j++){
        // check code for getting edge lengths 
        if (distances[j]> (distances[k] + adjMatrix[ (k*n)+j]+ tol)) {
            // update stuff for cycle detection next
            distances[j] = distances[k]+ adjMatrix[(k*n)+j];
            //neighbor.prev  is set 
            previous[j]=k;
            // set cycle start point
            cycleStart= j;
            }
        }
    }
    // if no cycle is dectected then jut return function
    vector<int> cycle;
    if(cycleStart == -1){
        return cycle;
    }
    // Create the cycle.
    vector<int> prefiulyVistedcert; 
    int elementVisited= cycleStart;
    while(count(prefiulyVistedcert.begin(), prefiulyVistedcert.end(), elementVisited) ==0){
        cycle.insert(cycle.begin(), elementVisited);
        std:cout<<elementVisited<<endl;
        prefiulyVistedcert.insert(prefiulyVistedcert.begin(), elementVisited);
        elementVisited= previous[elementVisited];
    }
      cycle.insert(cycle.begin(), elementVisited);
    // Return the cycle.
    return cycle;
}
                    