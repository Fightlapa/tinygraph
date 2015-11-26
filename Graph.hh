/* tinygraph -- exploring graph conjectures on small graphs
   Copyright (C) 2015  Falk Hüffner

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.  */

#ifndef TINYGRAPH_GRAPH_HH_INCLUDED
#define TINYGRAPH_GRAPH_HH_INCLUDED

#include <functional>
#include <stdexcept>
#include <vector>

#include "Set.hh"

class Graph {
public:
    explicit Graph(int n, std::initializer_list<std::pair<int, int>> es = {}) : neighbors_(n) {
	assert(n <= Set::MAX_ELEMENT + 1);
	for (auto e : es)
	    addEdge(e.first, e.second);
    }

    static Graph ofNauty(word* g, int n);
    static Graph byName(std::string name);
    static Graph ofGraph6(std::string g6);

    int n() const { return neighbors_.size(); }
    Set vertices() const { return Set::ofRange(n()); }
    int m() const {
	int m = 0;
	for (int u = 0; u < n(); ++u)
	    m += deg(u);
	assert((m % 2) == 0);
	return m / 2;
    }
    int deg(int u) const { return neighbors(u).size(); }
    Set neighbors(int u) const { return neighbors_[u]; }
    Set nonneighbors(int u) const { return vertices() - neighbors(u); }
    bool hasEdge(int u, int v) const { return neighbors(u).contains(v); }

    void addEdge(int u, int v) {
	assert(u >= 0 && u < n());
	assert(v >= 0 && v < n());
	neighbors_[u].add(v);
	neighbors_[v].add(u);
    }
    void removeEdge(int u, int v) {
	assert(u >= 0 && u < n());
	assert(v >= 0 && v < n());
	neighbors_[u].remove(v);
	neighbors_[v].remove(u);
    }
    void toggleEdge(int u, int v) {
	assert(u >= 0 && u < n());
	assert(v >= 0 && v < n());
	neighbors_[u].toggle(v);
	neighbors_[v].toggle(u);
    }
    void deleteVertex(int u) {
	assert(u >= 0 && u < n());
	int i = 0;
	for (int v = 0; v < n(); ++v) {
	    if (v == u)
		continue;
	    neighbors_[i++] = Set::ofBits(delbit(neighbors(v).bits(), u));
	}
	neighbors_.pop_back();
    }

    int mSubgraph(Set vs) const {
	int m = 0;
	for (int u : vs)
	    m += (neighbors(u) & vs).size();
	assert((m % 2) == 0);
	return m / 2;
    }

    typedef std::function<void(const Graph&)> EnumerateCallback;
    typedef std::function<bool(const Graph&)> PruneCallback;
    enum { CONNECTED = 1 };
    static void enumerate(int n, EnumerateCallback f, int flags = 0);
    static void enumerate(int n, EnumerateCallback f, PruneCallback p, int flags = 0);
    static EnumerateCallback enumerateCallback() { return enumerateCallback_; }
    static PruneCallback pruneCallback() { return pruneCallback_; }

    std::string toString() const;

private:
    static void doEnumerate(int n, EnumerateCallback f, PruneCallback p, int flags);
    std::vector<Set> neighbors_;
    static EnumerateCallback enumerateCallback_;
    static PruneCallback pruneCallback_;
};

std::ostream& operator<<(std::ostream& out, const Graph& g);

#endif  // TINYGRAPH_GRAPH_HH_INCLUDED
