#pragma once
#include <vector>
#include <algorithm>
#include "Interval.h"

class IntervalIntersectionDetection {
	bool intersect(Interval& I1, Interval& I2) {
		return I1.left.x <= I2.right.x && I2.left.x <= I1.right.x;
	}
	void color(std::vector<Interval>& S) {
		for (int i = 0; i < S.size(); i++) {
			S[i].left.color = L;
			S[i].right.color = R;
		}
	}
	static bool compare(Point& p1, Point& p2) {
		return p1.x < p2.x || (p1.x == p2.x && p1.color == L && p2.color == R);
	}
	std::vector<Point> sort(std::vector<Interval>& S) {
		std::vector<Point> endpoints;
		for (int i = 0; i < S.size(); i++) {
			endpoints.push_back(S[i].left);
			endpoints.push_back(S[i].right);
		}
		std::sort(endpoints.begin(), endpoints.end(), compare);
		return endpoints;
	}
	bool scan(std::vector<Point>& S) {
		for (int i = 0; i < S.size() - 1; i++) {
			if (S[i].color == S[i + 1].color) {
				return true;
			}
		}
		return false;
	}
public:
	bool bruteForce(std::vector<Interval>& S) {
		for (int i = 0; i < S.size(); i++) {
			for (int j = i + 1; j < S.size(); j++) {
				if (intersect(S[i], S[j])) {
					return true;
				}
			}
		}
		return false;
	}
	bool intervalIntersectionDetection(std::vector<Interval>& S) {
		if (S.empty()) {
			return false;
		}
		color(S);
		std::vector<Point> endpoints = sort(S);
		return scan(endpoints);
	}
};
