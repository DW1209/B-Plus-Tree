#ifndef INDEX_H_
#define INDEX_H_

#include <bits/stdc++.h>

#define pii pair<int, int>
#define pb push_back
#define mk make_pair

using namespace std;

class Node {
public:
    Node();

private:
    bool leaf;
    int size;
	pii *data;
    Node **pointer;
    friend class Index;
};

class Index {
public:
    Index(int num_rows, vector<int> &key, vector<int> &value);

    void key_query(vector<int> &query_key);
    void range_query(vector<pii> &query_pairs);
    void clear_index();

    void insert(int k, int v);
    int searchKey(int k);
    int searchRange(int begin, int last);
    void deletion(Node *current);

    void insertInternal(pii KV, Node *current, Node *child);
    Node *traceParent(Node *current, Node *child);

private:
    Node *root;    
};

#endif
