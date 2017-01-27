//
// Created by Kristof Buts on 1/27/17.
//

#include "Utilities.h"
#include <string>
#include <algorithm>

void Utilities::powerset(std::vector<int> &v, std::vector<std::vector<int> > &a) {
	if (v.empty())
		return;

	for (int i = 0; i <= v.size(); ++i) {
		std::string s(i, '1');
		s.resize(v.size(), '0');

		do {
			std::vector<int> l;
			for (int j = 0; j < v.size(); ++j) {
				if (s[j] == '1') {
					l.push_back(v[j]);
				}
			}
			a.push_back(l);
		} while (std::prev_permutation(s.begin(), s.end()));
	}
}