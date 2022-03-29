#include "index.h"

const int MAX = 100;

Node::Node(){
    size = 0;    
    leaf = true;
    data = new pii[MAX];
    pointer = new Node *[MAX + 1];

    for (int i = 0; i < MAX + 1; i++){
        pointer[i] = NULL;
    }
}

Index::Index(int num_rows, vector<int> &key, vector<int> &value){
    root = NULL;

    for (int i = 0; i < num_rows; i++){
        insert(key[i], value[i]);
    }
}

void Index::key_query(vector<int> &query_key){
    ofstream outfile("key_query_out.txt");

    for (int i = 0; i < query_key.size(); i++){
	    outfile << searchKey(query_key[i]) << endl;
    }
       
    outfile.close();
}

void Index::range_query(vector<pii> &query_pairs){
    ofstream outfile("range_query_out.txt");

    for (int i = 0; i < query_pairs.size(); i++){
        outfile << searchRange(query_pairs[i].first, query_pairs[i].second) << endl;
    }

    outfile.close();
}

void Index::clear_index(){
    deletion(root);
}

void Index::insert(int k, int v){
    if (root == NULL){
        root = new Node;
		root->data[0] = mk(k, v);
        root->leaf = true;
        root->size = 1;
    }
    else {
        Node *parent, *current = root;

        while (!current->leaf){
            parent = current;

            for (int i = 0; i < current->size; i++){
                if (k < current->data[i].first){
                    current = current->pointer[i];
                    break;
                }
                if (i == current->size - 1){
                    current = current->pointer[i + 1];
                    break;
                }
            }
        }

        if (current->size < MAX){
            int index = 0;
            
            while (index < current->size && k > current->data[index].first){
                index++;
            }

            for (int i = current->size; i > index; i--){
                current->data[i] = current->data[i - 1];
            }

	        current->data[index] = mk(k, v);
            current->size++;

            current->pointer[current->size] = current->pointer[current->size - 1];
            current->pointer[current->size - 1] = NULL;
        }
        else {
            Node *newLeaf = new Node;
            pii virtualNode[MAX + 1];

            for (int i = 0; i < MAX; i++){
                virtualNode[i] = current->data[i];
            }

            int index = 0;

            while (index < MAX && k > virtualNode[index].first){
                index++;
            }

            for (int i = MAX; i > index; i--){
                virtualNode[i] = virtualNode[i - 1];
            }

	        virtualNode[index] = mk(k, v);
            newLeaf->leaf = true;

            current->size = (MAX + 1) / 2;
            newLeaf->size = MAX + 1 - (MAX + 1) / 2;

            current->pointer[current->size] = newLeaf;
            newLeaf->pointer[newLeaf->size] = current->pointer[MAX];
            current->pointer[MAX] = NULL;

            for (int i = 0; i < current->size; i++){
                current->data[i] = virtualNode[i];
            }

            for (int i = 0, j = current->size; i < newLeaf->size; i++, j++){
                newLeaf->data[i] = virtualNode[j];
            }

            if (current == root){
                Node *newRoot = new Node;

                newRoot->data[0] = newLeaf->data[0];
                newRoot->pointer[0] = current;
                newRoot->pointer[1] = newLeaf;
                newRoot->leaf = false;
                newRoot->size = 1;

                root = newRoot;
            }
            else insertInternal(newLeaf->data[0], parent, newLeaf);
        }
    }
}

int Index::searchKey(int k){
    Node *current = root;
    int start = 0, end = current->size - 1;

    while (!current->leaf){
        while (start <= end){
            int middle = start + (end - start) / 2;

            if (k == current->data[middle].first) return current->data[middle].second;
            else if (k > current->data[middle].first) start = middle + 1;
            else if (k < current->data[middle].first) end = middle - 1;
        }
        
        current = current->pointer[start];
        start = 0; end = current->size - 1;
    }

    while (start <= end){
        int middle = start + (end - start) / 2;

        if (k == current->data[middle].first) return current->data[middle].second;
        else if (k > current->data[middle].first) start = middle + 1;
        else if (k < current->data[middle].first) end = middle - 1;
    }

    return -1;
}

int Index::searchRange(int begin, int last){
    Node *current = root;

    int maxValue = -1;
    int start = 0, end = current->size - 1;

    while (!current->leaf){
        while (start <= end){
            int middle = start + (end - start) / 2;
            if (begin >= current->data[middle].first) start = middle + 1;
            else end = middle - 1;
        }
            
        current = current->pointer[start];
        start = 0; end = current->size - 1;
    }

    int index = 0;

    for (; index < current->size; index++){
        if (begin <= current->data[index].first) break;
    }
    
    bool stop = false;

    while (!stop){
        for (int j = index; j < current->size; j++){
            if (last < current->data[j].first){
                stop = true; break;
            }

            maxValue = max(maxValue, current->data[j].second);
        }

        index = 0;

        current = current->pointer[current->size];
        if (current == NULL) break;
    }

    return maxValue;
}

void Index::deletion(Node *current){
    if (current->leaf){
        delete [] current->data;
        delete [] current->pointer;
        delete current;
        return;  
    }

    for (int i = 0; i <= current->size; i++){
        deletion(current->pointer[i]);
    }
	
    delete [] current->data;
    delete [] current->pointer;
    delete current;
}

void Index::insertInternal(pii KV, Node *current, Node *child){
    if (current->size < MAX){
        int index = 0;

        while (index < current->size && KV.first > current->data[index].first){
            index++;
        }

        for (int i = current->size; i > index; i--){
            current->data[i] = current->data[i - 1];
            current->pointer[i + 1] = current->pointer[i];
        }

	    current->data[index] = KV;
        current->pointer[index + 1] = child;
	    current->size++;
    }
    else {
        Node *newInternal = new Node;

        pii virtualNode[MAX + 1];
        Node *virtualPointer[MAX + 2];

        for (int i = 0; i < MAX; i++){
            virtualNode[i] = current->data[i];
        }

        for (int i = 0; i < MAX + 1; i++){
            virtualPointer[i] = current->pointer[i];
        }

        int index = 0;

        while (index < MAX && KV.first > virtualNode[index].first){
            index++;
        }

        for (int i = MAX; i > index; i--){
            virtualNode[i] = virtualNode[i - 1];
            virtualPointer[i + 1] = virtualPointer[i];
        }

        virtualNode[index] = KV;
        virtualPointer[index + 1] = child;
        newInternal->leaf = false;

        current->size = (MAX + 1) / 2;
        newInternal->size = MAX - (MAX + 1) / 2;

        for (int i = 0; i < current->size; i++){
            current->data[i] = virtualNode[i];
        }

        for (int i = 0; i < current->size + 1; i++){
            current->pointer[i] = virtualPointer[i];
        }

        for (int i = 0, j = current->size + 1; i < newInternal->size; i++, j++){
	        newInternal->data[i] = virtualNode[j];
        }

        for (int i = 0, j = current->size + 1; i < newInternal->size + 1; i++, j++){
            newInternal->pointer[i] = virtualPointer[j];
        }

        if (current == root){
            Node *newRoot = new Node;

	        newRoot->data[0] = virtualNode[current->size];
            newRoot->pointer[0] = current;
            newRoot->pointer[1] = newInternal;
            newRoot->leaf = false;
            newRoot->size = 1;

            root = newRoot;
        }
        else insertInternal(virtualNode[current->size], traceParent(root, current), newInternal);
    }
}

Node *Index::traceParent(Node *current, Node *child){
    Node *parent = current;

    if (current->leaf || (current->pointer[0])->leaf) return NULL;

    for (int i = 0; i < current->size + 1; i++){
        if (current->pointer[i] == child){
            parent = current;
            return parent;
        }
        else {
            parent = traceParent(current->pointer[i], child);
            if (parent != NULL) return parent;
        }
    }

    return parent;
}
