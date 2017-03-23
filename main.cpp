#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#define uL unsigned long long

using namespace std;

uL PowerMod(uL base, uL value , uL n)
{
    uL Result = 1;
    base = base % n;

    while (value > 0)
    {
        if (value % 2 == 1)
            Result = (Result * base) % n;

        value = value / 2;
        base = (base * base) % n;
    }
    return Result;
}

bool MillerTest(uL n ,  uL Que)
{
    uL z , a;
    a = 2 + rand() % (n - 4);  // 2 < a < n-2

    z = PowerMod(a ,Que , n);

    if (z == 1  || z == n-1)
    {
        return true;
    }

    while (Que != n-1)
    {
        z = (z * z) % n;
        Que *= 2;

        if (z == 1)
        {
            return false;
        }

        if (z == n-1)
        {
            return true;
        }
    }

    return false;

}

bool IsPrime( uL Number)
{
    uL que = 0 , k = 0;


    if(Number == 1)
    {
        return false;
    }
    else if(Number == 2 || Number == 3)
    {
        return true;
    }
    else if(Number % 2 == 0)
    {  //even number
        return false;
    }

    que = Number - 1;
    while(que % 2 == 0)
    {
        que /= 2;
        k++;
    }
    //now we have q and k , cauL miuLer rabin

    for(unsigned int o = 0 ; o <= k ; o++)
    {
        if(MillerTest(Number, que) == false)
        {
            return false;
        }
    }

    return true;
}

uL ExEucuLid(uL A3, uL B3)
{ uL A1 , A2, B1 , B2 , T1 , T2, T3 , M;

    A1 = 1, A2 =0 , B1 = 0 ,B2 = 1;

    while( (B3 != 0) || (B3 != 1) )
    {
        M = A3 / B3;

        T1 = A1 - (M * B1); T2 = A2 - (M * B2); T3 = A3 - (M * B3);
        A1 = B1 ; A2 = B2; A3 = B3;
        B1 = T1 ; B2 = T2; B3 = T3;

        if( B3 == 1)
        {
            return B2;
        }

        if(B3 == 0) cout << "No Inverse" << endl;
    }

}

uL CalcD(uL E , uL Phi)
{
    uL D;
    D = ExEucuLid(Phi , E);
    D = D % Phi ;
    return D;
}

void Encrypt(uL Msg , uL N , uL Key)
{
    uL C;
    C = PowerMod(Msg ,Key , N);
    cout << C <<endl;
}


int main()
{

    uL P, Q, E , tempo , D;
    string p, q, e , Temp;
    cin >> p >> q >> e;
    p= p.substr(2);
    q= q.substr(2);
    e= e.substr(2);

    stringstream convert( p );
    convert>>P;

    stringstream convert1( q );
    convert1>>Q;

    stringstream convert2( e );
    convert2>>E;

    while(true)
   {
       cin >> Temp;

       if(Temp == "IsPPrime" )
       {
           if(IsPrime(P)) cout << "Yes" <<endl;
           else cout << "No" <<endl;
       }

       else if(Temp == "IsQPrime" )
       {
           if(IsPrime(Q)) cout << "Yes" <<endl;
           else cout << "No" <<endl;
       }

       else if(Temp == "PrintN")
       {
           cout << P * Q <<endl;
       }

       else if(Temp == "PrintPhi")
       {
           cout << (P-1) * (Q-1) <<endl;
       }

       else if(Temp ==  "PrintD")
       {
           D = CalcD(E , (P-1) * (Q-1));
           cout << D <<endl;
       }

       else if(Temp == "Quit")
       {
           return 0;
       }

       else if(Temp.find("EncryptPublic") != std::string::npos)
       {
            Temp = Temp.substr(15 ,Temp.length() - 16);
            stringstream convert3( Temp );
            convert3>>tempo;
            Encrypt( tempo ,(P*Q ), E);

       }

       else if(Temp.find("EncryptPrivate") != std::string::npos)
       {
           Temp = Temp.substr(16 ,Temp.length() - 17);
           stringstream convert4( Temp );
           convert4>>tempo;
           D = CalcD(E , (P-1) * (Q-1));
           Encrypt( tempo ,(P*Q) , D );

       }

   }

    return 0;
}
