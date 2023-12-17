#include <iostream>
#include <chrono>
#include "IntervalIntersectionDetection.h"

void print(Interval& I) {
	std::cout << "[" << I.left.x << ", " << I.right.x << "]";
}

void print(std::vector<Interval>& S) {
	for (int i = 0; i < S.size(); i++) {
		print(S[i]);
		std::cout << " ";
	}
	std::cout << std::endl;
}

bool isInterval(Interval& I) {
	return I.left.x < I.right.x;
}

bool addOne(std::vector<Interval>& S, int limit) {
	bool flag = true;
	S[0].left.x++;
	int i = 0;
	Color color = L;
	while (true) {
		if (color == L) {
			if (S[i].left.x == limit + 1) {
				S[i].left.x = -limit - 1;
				S[i].right.x++;
				color = R;
			}
			else {
				break;
			}
		}
		else if (color == R) {
			if (S[i].right.x == limit + 1) {
				S[i].right.x = -limit - 1;
				i++;
				color = L;
				if (i == S.size()) {
					flag = false;
					break;
				}
				else {
					S[i].left.x++;
				}
			}
			else {
				break;
			}
		}
	}
	return flag;
}

void test(int limit, int n) {
	long long int sum = 0;
	long long int product = 1;
	for (int i = 0; i <= n; i++) {
		sum += product;
		product *= (2 * limit + 1) * limit;
	}
	long long int count = 0;
	double rate;
	IntervalIntersectionDetection IID;
	Point p;
	p.x = -limit - 1;
	Interval I;
	I.left = p;
	I.right = p;
	std::vector<Interval> S(n, I);
	bool flag1 = true;
	while (flag1) {
		bool flag2 = true;
		int digit = -1;
		for (int i = n - 1; i >= 0; i--) {
			if (S[i].left.x != -limit - 1 || S[i].right.x != -limit - 1) {
				digit = i;
				break;
			}
		}
		for (int i = 0; i < digit + 1; i++) {
			if (S[i].left.x != -limit - 1 && S[i].right.x != -limit - 1) {
				if (!isInterval(S[i])) {
					flag2 = false;
					break;
				}
			}
			else {
				flag2 = false;
				break;
			}
		}
		if (flag2) {
			std::vector<Interval> T(S.begin(), S.begin() + (digit + 1));
			if (IID.bruteForce(T) != IID.intervalIntersectionDetection(T)) {
				print(T);
				std::cin.get();
			}
			count++;
			if (count % 10000 == 0) {
				rate = (double)count / (double)sum * 100;
				std::cout << rate << std::endl;
			}
		}
		flag1 = addOne(S, limit);
	}
	rate = (double)count / (double)sum * 100;
	std::cout << rate << std::endl;
}

int main() {
	test(5, 4);
	return 0;
}
