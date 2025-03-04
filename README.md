ECE 250: Project 4 (Emergency Response) Design Document
Tuesday, December 5, 2023
#### This should be in the DSA portfolio 
1. Class Overview

Class Vertex: Represents a one way Edge in a Graph. Each edge has a distance, speed limit, vertex number (between 1 and 500000) and adjustment factor for traffic. Vertexes are stored in an adjacency list, and a Vertex is a node in one of the VertexLists. Each one way edge has a next and previous pointer to handle linked list operations necessary for insert, print, and other functions in the Graph.

Member Variables:
d (data type: double)			Double value that represents the edge’s distance
s (data type: double)			Double value that represents the edge’s speed limit
A (data type: double)			Double value that represents the edge’s traffic adjustment factor
travel_time (data type: double)		Double value that represents the edge’s travel time (d / (s * A))
vertex_num (data type: int)		Integer value that represents the vertex number (Range: 1-500000)
next (data type: Vertex*)			Pointer to the next edge in a vertex’s adjacency list	
prev (data type: Vertex*)			Pointer to the previous edge in a vertex’s adjacency list	

Class VertexList: Implementation of a doubly Linked List that holds the adjacent edges (Vertices) of one vertex. 
Member Variables:
head (data type: Vertex*)			Address of the first Node in the linked list

Class PQ_elements:  This class stores the travel time, the vertex number, and the parent vertex number of every vertex in the graph. The minimum heap of the PQ class is an array of PQ_element instances.
Member Variables:
travel_time (data type: double)		Stores the travel time of a vertex from point a in PATH
vertex (data type: int)			Integer value that represents the vertex number 
parent (data type: int)			Integer value that represents the vertex’s parent from PATH

Member Functions: 
Format: return_type function_name(parameter_type parameters)
void modify_elements(double tt_p, int v_p, int p_p): Used to modify the member variables of PQ_elements after it has been initialized. Used when inserting into the heap, as well as modifying/resetting the minimum heap after PATH has been completed.

Class PQ:  Implementation of a Priority Queue. This class stores a minimum heap array, as well as an array that maps a vertex to its index in the priority queue.
Member Variables:
min_heap (data type: PQ_elements**)	Stores an array of PQ_elements to form the minimum heap array
PQ_index (data type: int*)			Maps the vertices of the graph to its priority queue array index
cap_size (data type: int)			Stores the maximum capacity of the priority queue (vertices in Graph)
curr_size (data type: int)			Stores the current number of vertices currently stored in the min heap

Member Functions: 
Format: return_type function_name(parameter_type parameters)
void swap_pq(int index1, int index2): Swaps two elements in the min heap. The PQ indexes from the PQ_index array are first swapped, then their elements in the min_heap array.
int get_left(int i): An implicit tree link; gets the left child of node i.
int get_right(int i): An implicit tree link; gets the right child of node i.
int get_parent(int i): An implicit tree link; gets the parent of node i.
void insert(double tt_p, int v_p, int p_p): Increases the current size of the min heap before modifying the member variables of the last PQ_element instance at the end of the min_heap array. After modifying the variables, heap_upwards is called to check for any violations with the parent node.
void modify_heap(int vertex_num): Resets all of the elements in the min heap from the previous iteration of PATH, setting the travel time of every min heap element to infinity, and two vertices to zero. Then, curr_size is set to zero, and cap_size is set to the number of vertices currently in the graph.
void heapify(int i): Checks if the travel time of the children of node i are less than the node’s travel time. If it isn’t, the violating child and node i are swapped, and heapify is then recursively called on the smallest (violating) child.
PQ_elements* extract_min(): Extracts the vertex with the minimum travel time from the min heap by 
bool is_empty(): Checks if there are any vertices left in the priority queue by checking if curr_size is zero.
void heap_upwards(int vertex, double tt): Maintains the minimum heap property by repeatedly checking if there is a violation at the PQ_index of parameter vertex (index_PQ). If the travel time of the parent of index_PQ is less than the travel time of index_PQ, they are swapped, and index_PQ is set to its parent. Then, the process continues until there is no longer a violation, or index_PQ is at the root.

Class Graph:  Implementation of a graph through an adjacency list. This class stores an adjacency list. It also stores a priority queue, parent array, and travel time arrays, which are used by PATH/LOWEST and in turn, Djikstra’s algorithm.
Member Variables:
t_vertex_num (data type: int)	Integer value that represents the total number of vertices currently in Graph
adj_list (data type: VertexList**)	Array of adjacency list, each element points to the head of a VertexList
Queue (data type: PQ*)		A Min-PQ that maintains vertex travel times, allowing for minimum extraction and more
is_vertex (data type: bool*)	Array that keeps track of whether a vertex is or is not in the Graph
parent_array (data type: int)	Indices of this array are the vertices, and the elements are the parents of the vertices
travel_time (data type: double*)	Indices of this array are the vertices, and the elements are the travel time of the vertices
d_lowest (data type: double)	Integer value that stores the weight of the lowest path from a to b

Member Functions: 
Format: return_type function_name(parameter_type parameters)
std::string load(std::fstream &filename): Given a file with multiple INSERT commands, this function handles all inserts then returns success once.
std::string insert(int a, int b, double d, double s): This function throws an exception if a and b are outside the range of 1-500000. If this is not the case, two new edge nodes (Vertex) are created. An edge to b is inserted into the adjacency list of a, and an edge to a is inserted into the adjacency list of b. The vertices are added to the graph with is_vertex.
void basic_insert(int tbi, Vertex *curr): This function inserts an edge into the adjacency list of a vertex. It traverses the linked list of vertex tbi until it finds a duplicate edge or hits a nullptr. If there is a duplicate, the d, s, and travel time values are modified appropriately. Otherwise, the edge is inserted at the end of the linked list. If the vertex tbi wasn’t previously in the graph, the total vertex count is incremented.              
std::string print(int a): If the vertex a is not in the graph, the function returns “failure.” Otherwise, it iterates through all of the nodes in the VertexList of vertex a and concatenates them to a string that is returned once all of the adjacent vertices have been added.
std::string delete_vertex(int a): Removes vertex from a graph by deleting its VertexList element in the adjacency list, as well as its Vertex nodes from the lists of its adjacent vertices. Returns success if a is in the Graph.
void basic_delete(int pair, int a): A helper function to delete a from the lists of its adjacent vertices. It iterates through the VertexList of “pair” until the vertex number is a, then it deletes the appropriate node by using prev and next pointers.            
std::string traffic(int a, int b, double A): Throws an exception if a and b are outside the range of 1-500000, and returns failure if either a or b are not in the graph. If an edge exists between a and b (AinB and BinA are not nullptr), which is checked using LL_content, A and travel time are adjusted accordingly, “success” is returned. If no edge exists, “failure” is returned.
Vertex* LL_content(int x_pair, VertexList *list_x): Checks through a linked list to check if it holds an edge to x_pair. It returns a pointer to the edge (Vertex) if found, and nullptr otherwise.
std::string path(int a, int b): Returns failure if a and b are equal, not in the graph, or beyond the range of vertices. 
Setting up the Queue: Heap is modified to hold the number of vertices in the graph. For vertices in the graph, travel time is set to infinity, parent vertex is set to -1, and travel time is zero if the vertex is a (first vertex in path). All vertices in the graph are inserted into the Min-PQ.
Djikstra’s: Extracts the vertex with minimum travel time, relaxes adjacent vertices using the adjacency list, then updates the travel times and parent vertices of the adjacent vertices. This process continues until the PQ is empty. The shortest paths from a are calculated for all vertices.
Path Construction: No path can be formed if the travel time of vertex b is still infinity. Otherwise, the parent_array is used to concatenate a string of vertices that form the shortest path.
std::string lowest(int a, int b): Throws an exception if a and b are outside the range of 1-500000. d_lowest holds the value of the weight of the shortest path from a to b from the most recent call of path, so this function runs the path function to update d_lowest. It returns d_lowest if the result of the path(a, b) function call is not failure.
std::string update(std::fstream &filename): Given a file with multiple TRAFFIC commands, this function handles all commands then returns success if the traffic adjustment factor of at least 1 edge has been modified.


Class illegal_exception: Used by the Graph class to throw an exception when vertices a and b are within the range of 1-500000.
const char* what(): A virtual member function, returns a null-terminated character sequence that is outputted with cout by main to describe the exception with “illegal argument.”


2. UML Class Diagram


3. Constructors/Destructors

Class Vertex
Default Constructor: Initializes a new Vertex element. Since a Vertex element essentially represents an edge, its distance, speed limit, and traffic adjustment factor are set to 0, 0, and 1, respectively. Its vertex number is also set to zero. 
Parameterized Constructor: Initializes a new Vertex element. Its distance, vertex number, and speed are changed according to the parameters passed through the constructor. Its adjustment factor is set to 1 since this parameterized constructor is used by INSERT, which assumes A = 1. Prev and next pointers are set to nullptr.

Class VertexList
Default Constructor: Initializes an empty linked list with no nodes by setting the head of the list to nullptr.
Default Destructor: While the linked list is not empty, a temporary node tbd (to be deleted) is set to the head and head is set to the next node. The temporary node is then deleted. This design ensures the linked list is deleted by the destructor.

Class PQ_element
Default constructor: Initializes a new PQ_element. The element’s travel time, vertex, and parent vertex are set to zero.

Class PQ
Default Constructor: Initializes an array of 500001 PQ_elements, all elements are initialized with default constructor. PQ_index memory is also allocated. Cap_size is set to 1, curr_size is set to 0.
Default Destructor: Both arrays with memory allocated in the constructor are deleted after all elements in the array of PQ_elements are deleted.

Class Graph
Default Constructor: Set the total number of vertices in the graph to zero. Create 4 arrays of size 500001: the adjacency list, is_vertex, parent_array, and travel_time. Then set all elements in the adjacency list to nullptr, all is_vertex to false, travel times to infinity, and parent array elements to -1. The Priority Queue constructor is called for Queue.
Default Destructor: Deletes all linked lists from the adjacency list before deleting all 4 arrays. Queue is also deleted using its destructor.

4. Performance
Under the assumption that the graph is connected, it is impossible for the travel time to be infinite. 
Adding all the vertices of the graph into the queue takes O(|V|) time where |V| is the number of vertices in the connected graph. Operations from the Min-PQ have a runtime of O(log|V|). These operations include extracting and inserting into the Min-PQ. These operations happen to a vertex during relaxation at most once for each of its neighbors in the worst case. This will thus happen |E| times where |E| is the number of edges for a connected graph. Thus, in the worst case, the time complexity of Djikstra’s is |V| + |E|log(|V|) = O(|E|log(|V|)).

