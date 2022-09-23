# -APSP_Using_Different_Priority_Queues
Implemented Johnson's Graph Algorithm to find the shortest path between all pairs of nodes using different data structures as priority queues namely 1D array , binary heap , binomial heap and fibonacci heap and their performance is analyzed on dense as well as sparse graphs.All the queues are implemented and built from scratch and by defining different structs for nodes of different heaps.No particular predefined functions or containers are used except list(simply used as a doubly linked list) and unordered_map(simply used as a hashmap which was required in fibonacci heap) containers are used.

# How To Run 
Simply compile the file JohnsonAPSP.cpp using g++ compiler and execute it.

# Input Format
First line: An integer between 1 and 4 , specifying which data structure to use as the priority queue in the algorithm\
1.Sorted Array\
2.Binary Heap\
3.Binomial Heap\
4.Fibonacci Heap\
Second line: A positive integer T which specifies the number of test cases and then follows their description\
For each test case,\
First line contains as input 2 integers N D (single space separated) where:-\
N is the number of vertices in the graph where vertices are labelled from 1 to N (not 0 indexing)\
D specifies whether Directed Graph or undirected graph (D=0 means undirected, D=1 means it is directed)\
This is then followed by N lines each containing N integers (basically NxN Adjacency matrix representation of the graph of that test case).\
The NxN matrix integers denote the edge-weights,it is assumed that there are no self-loops in the input graph,\
hence the diagonal entries are always zero in the input matrix and the weight=999999 indicates that there is no edge \
between the two concerned vertices.

# Output Format
For each test case,\
If there is any negative weight cycle in graph, simply -1 is printed as the shortest path is not well defined for atleast\
some source vertices because one can keep on traversing the loop and the path length would keep on reducing.\
Else the output for that test case is as followed:\
A 2 dimensional N x N matrix is printed (N rows each containing N single space separated values) \
The kth entry in the ith row (element i,k) contains the distance of kth vertex from the ith vertex (source vertex) . (Basically a N x N shortest path matrix) \
The number 999999 is printed in a particular entry if the vertex is not reachable from the source vertex considered. \
The last row contains T space seperated floating point numbers which indicate the time in seconds needed to produce the output after each test case. \
The Tth entry in the last row indicates the time taken by the Tth test case. 
