#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define all(v) v.begin(),v.end()
const ll  MAX=1e5+5, MOD = 1e9+7,INF = 1e14;
const double EPS=1e-9,PI = acos(-1);

namespace numerTheory{ 
  ll GCD(ll x, ll y) {
      if (x == 0) return y;
      if (y == 0) return x;
      return GCD(y, x % y);
  }
  ll LCM(ll a, ll b){
      return a / GCD(a,b) * b;
  }
  ll fastPower(ll b, ll p, ll mod = MOD) {
      ll res=1;
      while(p) {
          if(p&1)
              res=res*b/*%mod*/;
          b=b*b/*%mod*/;
          p>>=1;  // --> p/=2
      }
      return res;
  }
  bool isPrime(ll n) {
      if (n <= 1) return false;
      if (n <= 3) return true;
      if (n % 2 == 0 || n % 3 == 0) return false;
      for (ll i = 5; i * i <= n; i += 6)
          if (n % i == 0 || n % (i+2) == 0)
              return false;
      return true;
  }
  
  bool prime[MAX];      // 1 -> prime, 0 -> not prime
  void sieve(int n) { 
      memset( prime, 1, sizeof(prime) );    
      prime[1] = prime[0] = 0;
      for (ll p = 2; p * p <= n; p++) {
          if (prime[p]) {
              for (ll i = p * p; i <= n; i += p)
                  prime[i] = 0;
          }
      }
  }
  
  vector<ll> primeNumbers;
  void generatePrimes(int n) {
      sieve(n + 1);
      for (ll i = 2; i <= n; i++) 
        if (prime[i]) 
          primeNumbers.push_back(i);
  }
  
   // prime factorization
  vector<ll> factors;
   void factors(ll n) {
      for (ll i = 0; primelist[i] * primelist[i] <= n && i < primelist.size(); i++) {
          if (n % primelist[i] == 0) {
              while (n % primelist[i] == 0) {
                  n /= primelist[i];
                  factors.push_back(primelist[i]);
              }
          }
      }
      if (n > 1) {
          factors.push_back(n);
      }
      sort(all(factors));
  }
  
     // divisros of int number
    vector<ll> divisros;
     void getdivs(ll n) {
      // sqrt(N)
        ll i;
        for (i = 1; i * i < n; i++) {
            if (n % i == 0) {
                divisros.push_back(i);
                divisros.push_back(n / i);
            }
        }
        if(i*i==n)
          divisros.push_back(i);
    }
    
    ull NcR(int n, int r) {
        ull res = 1;
        //  C(n, k) = C(n, n-k)
        if (r > n - r)
            r = n - r;
        for (int i = 0; i < r; ++i) {
            res *= (n - i);
            res /= (i + 1);
        }
        return res;
    }
     ull factorial(int n){ // max_n is 20 in ull
       ll res = 1;
        for(int i=2;i<=n;++i)
            res*=i;
        return res;
     }
    
    ull nPr(int n, int r){
        // to optimize this , precompute factorials in a container
        return factorial(n) / factorial(n - r);
    }
    ull npr(int n,int r) {
        if(r == 0) return 1;
        return n*npr(n-1,r-1);
    }

    vector<vector<ull>> pascalTriangle;
    void generatePascalTriangle(int numRows) {
        // src:: https://bit.ly/3bUFNdS
        pascalTriangle.resize(numRows);
        for(int i=0; i<numRows; i++){
            pascalTriangle[i].resize(i+1);
            pascalTriangle[i][0]= pascalTriangle[i][i]=1;
            for(int j = 1; j < i; j++)
                pascalTriangle[i][j] = pascalTriangle[i-1][j-1] + pascalTriangle[i-1][j];
        }
    }
    //get The exponent of a prime p in n!
    int get_powers_in_n_Factorial(ll n, ll p) {   
        ll res = 0;
        for (ll power = p; power <= n; power *= p)
            res += n / power;
        return res;
    }
    // app on prime factorization
    inline bool isPositive(int &ai){ return ai > 0; }
    int minstepsMaking_A_eq_B(vi primeFacto1,vi primeFacto2){
        int ans = 0;
        for(auto & itr1 : primeFacto1)
            for(auto & itr2 : primeFacto2)
                 if(itr1 == itr2){
                   itr1=-1;
                   itr2=-2;
                   break;
                }
        ans += count_if(all(primeFacto1),isPositive) + count_if(all(primeFacto2),isPositive);
        return ans;
      }
}
namespace numerTheory;

/*
Suppose x and y are two positive integers such that they are called co prime numbers
iff they have 1 as their only common factor and thus HCF(x, y) = 1.
In other words,  Co-prime numbers are a set of numbers or integers which have only 1 as their common factor
i.e. their highest common factor (HCF) will be 1.
Co-prime numbers are also known as relatively prime or mutually prime numbers.
It is important that there should be two numbers in order to form co-primes.
GCD(x,y) = HCF(x,y)
conclusion :  pair (1,N) : 1<=N<=INF is a co-prime pair
*/
