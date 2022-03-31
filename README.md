# B+ Tree

## Introduction
B+ tree is a common form of index in the database. Therefore, this program implements a B+ tree class and uses it as a simple index for given data. The B+ tree class can not only be capable to insert some key, value pairs into itself, but also release used memory before terminating.

## Execution
```console
$ make
$ ./bplustree
```

## Explanation
* **Makefile**:
    * Provided to compile the code by typing `make` command in terminal.
* **main.cpp**:
    * Contain the main function which will read the all input files, as well as record time used by each task.
* **utils.h**:
    * Header file for "utils.cpp".
* **utils.cpp**:
    * Contain some utility functions for file reading and used time output.
* **index.h**:
    * Header file for "index.cpp".
* **index.cpp**:
    * Include `constructor Index()`, `key_query`, `range_query`, and `clear_index` these four functions.
    * `Index(num_row, key, value)` takes three inputs, which are an integer indicating the number of data rows, a vector of integer represents keys and a vector of integer represents values. This function will insert the key, value pairs into the B+ tree one by one.
    * `key_query(query_keys)` takes one input, which is a vector of integer indicating the key used for query. In this function, it will output a file named "key_query_out.txt", each row consists of an integer which is the value corresponding to the keys in the input `query_keys`. And the output will be -1 if the key is not found.
    * `range_query(query_pairs)` takes one input, which is a vector of pairs of two integers indicating the range of query. In this function, it will output a file named "range_query_out.txt", each row consists of an integer which is the maximum value in the given query key range. And the output will be -1 if no key found in the range.
    * `clear_index()` takes no input. It will free all the memory used by the B+ tree index in this function.
* **data.txt**:
    * Contain the input data to test the code.
    * Each line consists of a key and a value, both are integer and are separated with a comma.
    * The data is not sorted on key or value.
    * It will be loaded as two vectors of integer in the main function.
* **key_query.txt**:
    * Contain the queries to test the index.
    * Each line consists of a key, which is an integer.
    * It will be loaded as a vector of integer in the main function.
    * Some of the key may not exist in the data.
* **key_query_ans.txt**:
    * Answer of the "key_query.txt" file.
* **range_query.txt**:
    * Contain the queries to test the index on range search.
    * Each line consists of two keys, which are integers. The first one is always smaller than the second one, and they are seperated by a comma.
    * It will be loaded as a vector of pair of two integers in the main function.
* **range_query_ans.txt**:
    * Answer to the "range_query.txt" file.
* **time_used.txt**:
    * Record the time used on each task.
    * It consists of three numbers separated by commas. The first one is the time used on inserting key, value pairs into the B+ Tree; the second is the time spending on the "key_query.txt" test; and the last one is the time consuming on the "range_query.txt" test.