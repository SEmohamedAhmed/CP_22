// some problems are from src :: gfg
//sum of all subArrays function compute sum all sub-array
ll SubArraySum( vi &arr , int n ){
    ll result = 0; 
  for (int i=0; i<n; i++) 
      result += (arr[i] * (i+1) * (n-i));
  return result ;
}
/***************************************************/
// sum of bitwise ans of all subArrays
 vi list{1,2,3,4,5};
    ll res=0;
    for(int bits = 0; bits < 30; ++bits){
        int len = 0;
        for(int j = 0; j < sz(list); ++j){
            if(((list[j]>>bits)&1))
                len++,res = res+ (1ll*len*(1ll << bits));
            else len=0;
        }
    }
/***************************************************/

// Function to calculate the sum of XOR of all subArrays
int XorSum(const vi &arr){
    int n = sz(arr);
	int sum = 0;
	int mul = 1;
	for (int i = 0; i < 30; i++) {
		int c_odd = 0;bool odd = 0;
		for (int j = 0; j < n; j++) {
			if ((arr[j] & (1 << i)) > 0)odd = (!odd);
			if (odd)c_odd++;
		}
		for (int j = 0; j < n; j++) {
			sum += (mul * c_odd);
			if ((arr[j] & (1 << i)) > 0)c_odd = (n - j - c_odd);
		}
		mul *= 2;
	}
	return sum;
}
/***************************************************/
// Sum of XOR of all K length sub-array of an array
int FindXorSum(const vi &arr, int k){
   int n = sz(arr);
   if (n < k)return 0;
	int x[n] = { 0 };
	int result = 0;
	for (int i = 0; i < n; i++) {
		if (i > 0)x[i] = x[i - 1] ^ arr[i];
		else x[i] = arr[i];
		if (i >= k - 1) {
			int sum = 0;
			sum = x[i];
			if (i - k > -1)
				sum ^= x[i - k];
			result += sum;
		}
	}
	return result;
}
/***************************************************/
// Function to find sum of bitwise OR of all subarrays
ll SumOr(const vi &arr){
    int n = sz(arr), max = *max_element(all(arr)),
    Bits = log2(max) + 1;
	ll allSubArr = n * (n + 1) / 2, s = 0;
	for (int i = 0; i < Bits; i++) {
		int c1 = 0,sum=0,a;
        vi vec;
		for (int j = 0; j < n; j++) {
			 a = arr[j] >> i;
			if (!(a & 1))vec.push_back(j);
		}
		int NotSet = 0,cnt = 1;
		for (int j = 1; j < vec.size(); j++) {
			if (vec[j] - vec[j - 1] == 1)cnt++;
			else NotSet += cnt * (cnt + 1) / 2,cnt = 1;
		}
        NotSet += cnt * (cnt + 1) / 2;
		if (vec.size() == 0)
            NotSet = 0;
		int cntSubarrIthSet = allSubArr - NotSet;
		s += cntSubarrIthSet * pow(2, i);
	}
	return s;
}
/************************************************/
#define ones(x) __builtin_popcountll(x)     // number of bitsets in x
int getFirstSetBitPos(int n){
    return log2(n & -n);
}
/**
 * A program that get ones cnt in N and
 * convert all ones to a binary number
 * then get the decimal representation of the new num
 * */
 void solve() {
cin>>N;
bitset<33>num(N);
int oneS = num.count();        //  <-- or use ones #defined
string ss(oneS,'1');         //  <--
bitset<33>fdfd(ss);          //  <--
cout<< fdfd.to_ulong();     //  <--
if(t)cout<<el;
}
