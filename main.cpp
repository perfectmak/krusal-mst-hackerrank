#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Edge {
    Edge() {
        Edge(0, make_pair(0, 0));
    }

    Edge(int weight, pair<int, int> &&nodes) : weight(weight), nodes(nodes) {}

    Edge(int weight, pair<int, int> &nodes) : weight(weight), nodes(nodes) {}

    int weight;
    pair<int, int> nodes;
};

ostream &operator<<(ostream &out, pair<int, int> p) {
    out << "[ " << p.first << " " << p.second << " ]";
    return out;
}

int findParent(vector<int> &parent, int i) {
    if (parent[i] == -1)
        return i;
    return findParent(parent, parent[i]);
}


void mergeSet(vector<int> &parent, int x, int y) {
    int xset = findParent(parent, x);
    int yset = findParent(parent, y);
    parent[xset] = yset;
}


//struct Subset {
//    int parent;
//    int rank;
//};
//
//
//int find(Subset subsets[], int i) {
//    if (subsets[i].parent != i) {
//        subsets[i].parent = find(subsets, subsets[i].parent);
//    }
//    return subsets[i].parent;
//}
//
//void unions(Subset
//            subsets[],
//            int x,
//            int y
//) {
//    int xroot = find(subsets, x);
//    int yroot = find(subsets, y);
//
//    if (subsets[xroot].rank < subsets[yroot].rank) {
//        subsets[xroot].
//                parent = yroot;
//    } else if (subsets[xroot].rank > subsets[yroot].rank) {
//        subsets[yroot].
//                parent = xroot;
//    } else {
//        subsets[yroot].
//                parent = xroot;
//        subsets[xroot].rank++;
//    }
//
//}

int main() {
    int n, m;
    int x, y, r;
    vector<int> nodeParents;
    vector<Edge> edges;
    vector<Edge> mstEdges;

    cin >> n >> m;
    nodeParents = vector<int>(n, -1);
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> r;
        edges.push_back(Edge(r, make_pair(x, y)));
    }

    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return (a.weight < b.weight);// ||
               //((a.nodes.first + a.nodes.second + a.weight) < (b.nodes.first + b.nodes.second + b.weight));
    });

    int edgeLen = edges.size();
    for(int i = 0; i < edgeLen; i++) {
        int src = edges[i].nodes.first;
        int dst = edges[i].nodes.second;

        x = findParent(nodeParents, src);
        y = findParent(nodeParents, dst);
        if (x == y) {
            continue;
        }

        mstEdges.emplace_back(edges[i]);
        mergeSet(nodeParents, x, y);

        int size = mstEdges.size();
        if (size == n-1) {
            break;
        }

    }

    long weightSum = 0;
    int mstLen = mstEdges.size();

    for (int i = 0; i < mstLen; i++) {
        auto z = mstEdges[i];
        weightSum += z.weight;
    }

    cout << weightSum;


    return 0;
}