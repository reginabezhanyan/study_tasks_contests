#include <stdio.h> 
#include <string>
#include <iostream> 
#include <vector>
#include <math.h>

using namespace std;
 
int maxstr (string& c, int begin, int mid, int end, vector<vector<int>> &res) {
	int cur = 0; 
	if (begin == mid) return 0;
	if (end == mid-1) return 0;
	if (res[begin][end-mid] != -1) return res[begin][end-mid];
	if (begin == mid-1) {
		for (int i = mid; i <= end; i++) {
			if (c[begin] == c[i]) {
				res[begin][end-mid] = 1;
				return 1;
			}
		} 
		res[begin][end-mid] = 0;
		return 0;
	}
	if (end == mid) {
		for (int i = begin; i < mid; i++) {
			if (c[i] == c[end]) {
				res[begin][end-mid] = 1;
				return 1;
			}
			
		}
		res[begin][end-mid] = 0;
		return 0;
	}
	for (int i = begin; i < mid; i++) {
		if (c[i] == c[end]) {
			res[i+1][end-mid-1] = maxstr(c, i+1, mid, end-1, res);
			cur = max(cur, res[i+1][end-mid-1]+1);
			break;
		}
	}
	res[begin][end-mid] = max(cur, maxstr(c, begin, mid, end-1, res));
	return res[begin][end-mid];
}
int main () {
	string a, b,c;
	int lena, lenb; 
	vector<vector<int>> res;
	cin >> a;
	cin >> b;
	lena = a.size();
	lenb = b.size();
	c.resize(lena + lenb + 1);
	for (int i = 0; i < lena; i++) {
		c[i] = a[i];
	}
	for (int i = 0; i < lenb; i++) {
		c[lena + i] = b[lenb - 1 - i];
	}
	c[lena + lenb] = '\0';
	res.resize(lena + 1);
	for (int i = 0; i < lena + 1; i++) {
		res[i].resize(lenb);
		for (int j = 0; j < lenb; j++) {
			res[i][j] = -1;
		}
	} 
    
	cout << maxstr(c, 0, lena, lena+lenb-1, res) << endl; 
}