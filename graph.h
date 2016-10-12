#include <vector>
#include <limits>
#include <iostream>

constexpr int inf = std::numeric_limits<int>::max() / 2;
enum class color_t{black, white};
struct Edge{
	Edge(int to = -1, Edge* next = nullptr)
		:to(to), next(next) {}
	int to;
	Edge* next;
	// any attached data to edges
};

struct Vertex{
	Vertex(int from = -1):from(from), edges(nullptr){}
	int from;
	Edge* edges;
	// any attached data to vertex
	color_t color;
	int discover_time;
	int parent;
	int finish_time;
};

struct Graph 
	:public std::vector<Vertex>
{
	Graph(int size = 0)
		:vector(size)
	{
		for(int i = 0; i<this->size(); ++i){
			(*this)[i].from = i; 
		}
	}
};

inline void add_edge(Graph& graph, int from, int to){
	graph[from].edges = new Edge(to, graph[from].edges);  
}

#define FOR_EDGE(edge, vertex) \
for(Edge* edge = vertex.edges;\
edge != nullptr;\
edge = edge->next)


inline Graph transpose(Graph& graph){
	Graph result(graph.size());
	for(auto vertex:graph){
		FOR_EDGE(edge, vertex) {
			add_edge(result, edge->to, vertex.from);
		}
	}
	return result;
}

inline void clear_graph(Graph& graph){
	for(auto& vertex: graph){
		auto edge = vertex.edges;
		while(edge){
			auto next = edge->next;
			delete edge;
			edge = next;
		}
		vertex.edges = nullptr;
	}
}

void breath_first_search(Graph& graph, int source);
void depth_first_search(Graph& graph);