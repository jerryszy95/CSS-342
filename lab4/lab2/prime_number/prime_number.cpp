//
//  prime_number.cpp
//  Prime Number
//
//  Created by Jerryshen on 4/13/17.
//  Copyright © 2017 Zeyu. All rights reserved.
//
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int sieve( int n, vector<int> &primes )
{
    int cost = 0;
    bool array[n+1];
    // 1. Implement array initialization so that every value is prime except 0 and 1
    array[0]=false;
    array[1]=false;
    for(int i=2; i<=n; i++)
    {
        array[i]=true;
    }
    for (int i=2; i<n; i++)
    {
        for (int j=2; j*j<=i; j++)
        {
            if (i % j == 0)
            {
                array[i]=false;
            }
        }
        if(array[i])
        {
            
            // 2. Implement Sieve of Eratosthenes algorithm to find prime numbers
            // Add cost whenever the array becomes to prime
            cost=cost+1;
            // 3. Push back the prime numbers into primes (parameter)
            primes.push_back(i);
        }
    }
    return cost;
}

int main ()
{
    int n = 0;
    cout << "Enter n "<<endl;
    cin >> n;
    
    char printOption = 'n';
    cout << "print all primes (y|n)? "<<endl;
    cin >> printOption;
    
   for ( int i = 2; i <= n; i++ ) 
   {
        
        vector<int> primes;
        int cost = sieve( i, primes );
        
        cout << "primes[1.." << i << "] took " << cost
        << " sweeping operations" << endl;
        
        if ( printOption == 'y' ) 
        {
            cout << "all primes = ";
            for ( int j = 0; j < primes.size( ); j++ )
                cout << primes[j] << " ";
            cout << endl;
        }
        cerr << i << " " << cost << endl;
    }
   
    return 0;
}





