#pragma once
#include <iostream>
using namespace std;
#include <cmath>

bool prim(int n) {
	if (n <= 1) {
		return false;
	}
	for (int k = 2;k <= n/2;k++) {
		if (n % k == 0) {
			return false;
		}
	}
	return true;
}

int cmmdc(int a, int b) {

	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

void solutie1a() {
	int v[100] = { 5};
	int d = 5;
	int ct = 0;

	for (int i = 0;i < d;i++) {
		if (cmmdc(v[i],v[i+1])==1) {
			ct++;
		}
	}
    
	cout << ct;

}
