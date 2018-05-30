#include <iostream>
#include <time.h>
#include <sys/time.h>

using namespace std;

int main()
{
    struct timeval start,end;
    int gcd;
    int A;
    int B;
    int MaxA=0;
    int MaxB=0;
    int Maxcost=0;
    int Num;
    int finalgcd=0;
    cout<<"please enter a number N"<<endl;
    cin>>Num;
    //
    for(int i=8; i<= Num;i++) // calculate gcd for i=8 to i=n
    {
        gettimeofday(&start, NULL);// Start tacking time
        for(int x=0; x<=i;x++)// calculate gcd for gcd(0,i) to gcd(i,i)
        {
            int cost=0;// initialize the cost
            A=x;
            B=i;
            while (A!= 0) // break the loop until A=0
            {
                gcd =B%A;
                B=A;
                A = gcd;
                cost++;
            }
            gcd = B;    // Since gcd(0,B)=B, let gcd=B;
            if(cost>Maxcost)// record A, B and gcd, if it's cost is greater than before.
            {
                Maxcost=cost;
                MaxA=x;
                MaxB=i;
                finalgcd=gcd;
            }
        }
        gettimeofday(&end, NULL);// End tacking time
        //Output as gcd(MaxA,MaxB)=finalgcd and it's cost
        cout<<"At i="<<i<<"; "<<"gcd("<<MaxA<<","<<MaxB<<") = "<<finalgcd<<" took "<<Maxcost<<" modulus operations ";
        //Output time in ms.
        cout << "time = " <<double((end.tv_sec - start.tv_sec) * 1000.000000+(end.tv_usec - start.tv_usec)/1000.000000) << " ms.\n";
    }
    return 0;
}

