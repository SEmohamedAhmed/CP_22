  // src:: https://www.hackerearth.com/practice/algorithms/searching/ternary-search/tutorial/
int ternary_search(int l,int r, int x){
      if(r>=l)
      {
          int mid1 = l + (r-l)/3;
          int mid2 = r -  (r-l)/3;
          if(arr[mid1] == x)
              return mid1;
          if(arr[mid2] == x)
              return mid2;
          if(x<arr[mid1])
              return ternary_search(l,mid1-1,x);
          else if(x>arr[mid2])
              return ternary_search(mid2+1,r,x);
          else
             return ternary_search(mid1+1,mid2-1,x);
      }
      return -1;
  }
  

/***********************************************************************************************************************************************************************/

// start + (end-start)/2 = (start + end) / 2    -> trick to avoid tle || overflow

int BSfindFirst(int start, int end, int val) {
	while(start < end) {
		int mid = start + (end-start)/2;
		if(f(mid) < val)		start= mid+1;
		else if(f(mid) > val)	end  = mid-1;
		else					end  = mid;
	}
	return start;
}

int BSfindLast(int start, int end, int val) {
	while(start < end) {
		int mid = start + (end-start)/2;
		if(f(mid) < val)		start= mid+1;     // f() -> implemented fn according to your problem    ,, also it maybe an operation to mid var.
		else if(f(mid) > val)	end  = mid-1;
		else					start= mid;
	}
	return start;
}

// One of great WAs sources is value of EPS. Make sure you achieve required precision
double BS_double(double start, double end, double val) {
	while(fabs(end - start) > EPS) {	// iterate 100-500 iteration
		double mid = start + (end-start)/2;
		if(f(mid) < val)	start= mid;
		else 				end  = mid;
	}
	return start;
}


double binary(double start, double end){
	lp(i, 100) {	// loop as much as u want
	    double mid = (start+end)/2;
	    if( can(mid) )
	    	end = mid;
	    else
	    	start = mid;
	}

	if( can(end) )
		return start;

	return -1;	// failed
}


/***********************************************************************************************************************************************************************/
 // -> Backtracking
/*
 * pseudocode
 *
 * Backtracking(state)
 * 		if invalid(state)	//e.g. we reached a # or the location is already visited
 * 			return
 *
 * 		if found_solution(state)
 * 			mark_solution_found
 * 			return
 *
 * 		for each child_state of state   // -> do - rec - undo
 * 			state' = do changes in state
 *
 * 			Backtracking(state')
 *
 * 			state = undo changes in state'
 */
 // examples :: 
// 8-quuens Problem , given one queen position, find all possible ways to put another 7 Queens 
  const int MX = 8;
  int x,y;
  vs ans;
  int ithColQueen[MX];
  bool visited_row[MX], diag_right[2*MX+1], diag_left[2*MX+1];

  void clearAll(){
      clrA(visited_row,0);
      clrA(diag_right,0);
      clrA(diag_left,0);
      ans.clear();
  }
  void _8_Queens_By_Col(int col) {
      if(col==8){ // get result
          string seq{""};
          rep0(i,MX){
              seq+= to_string(ithColQueen[i]+1);
              if(i!=MX-1)
                  seq+=" ";
          }
          ans.pb(seq);
          return;
      }
      if(col==y)_8_Queens_By_Col(col+1);  // or y+1   skip as it's a constant place for (x,y)Queen input
      else{
          // try all possible sol
          rep0(i,8){
              if(visited_row[i] || diag_right[i+col] || diag_left[7+i-col])   //Queen must not attack each other
                  continue;
              ithColQueen[col] = i;
              visited_row[i] = diag_right[i+col] = diag_left[7+i-col] = 1;    // do
              _8_Queens_By_Col(col+1);                                        // recurse
              visited_row[i] = diag_right[i+col] = diag_left[7+i-col] = 0;    // undo
          }
      }
  }
  void prepareAns(){
      printf("SOLN       COLUMN\n");
      printf(" #      1 2 3 4 5 6 7 8\n\n");
      //sort(all(ans));       useless as we start backtracking in the lexio.order
      rep0(i,sz(ans)){
          printf("%2d      %s\n",i+1,ans[i].c_str());     // 2d here is a print stupid trick!!!!!
      }
  }
  void solve() {
      clearAll();
      cin>>x>>y;
      x--,y--;    //zero based
      ithColQueen[y] = x;
      visited_row[x] = diag_right[x+y] = diag_left[7+x-y] = 1;
      _8_Queens_By_Col(0);
      prepareAns();
      if (t) puts("");
  }

/***********************************************************************************************************************************************************************/

