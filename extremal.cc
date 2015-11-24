/* tinygraph -- exploring graph conjectures on small graphs
   Copyright (C) 2015  Falk Hüffner

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.	*/

#include "Graph.hh"
#include "Subgraph.hh"

int main() {
    auto p5 = Graph::byName("P5");
    std::vector<uint64_t> maxCounts;
    for (int n = 1; n <= MAXN; ++n) {
	std::cerr << "--- n = " << n << std::endl;
	uint64_t maxCount = 0;
	Graph::enumerate(n, [&maxCount, &p5](const Graph& g) {
		uint64_t count = countP5s(g);
		//assert(count == countSubgraphs(g, p5));
                if (count > maxCount) {
		    std::cout << count << ": " << g.toString() << std::endl;
		    maxCount = count;
		}
	    });
	maxCounts.push_back(maxCount);
	std::cout << "sequence: " << std::endl;
	for (size_t i = 0; i < maxCounts.size(); ++i) {
	    if (i)
		std::cout << ", ";
	    std::cout << maxCounts[i];
	}
	std::cout << std::endl;
    }

    return 0;
}
