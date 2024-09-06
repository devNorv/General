#include<iostream>
#include<climits>
#include<list>
#include<utility>
#include<vector>
#include<queue>

# define INF 0x3f3f3f3f
using namespace std;

struct Edge
{
    int source;
    int destination;
    int weight;
};

typedef pair<int, int> iPair; // Integer Pair

class Graph 
{
private:
    int m_NumberOfVertices;
    std::list< std::pair<int, int> > *m_adjList;

public:
    Graph(int V)
    {
        m_NumberOfVertices = V;
        m_adjList = new std::list< std::pair<int, int> > [m_NumberOfVertices];
    }
    
    ~Graph()
    {
        
    }
    
    void addEdge (int s, int d, int w)
    {
        m_adjList[s].push_back(make_pair(d, w));
        m_adjList[d].push_back(make_pair(s, w));
        return;
    }
    
    void DijkstraAlgo(int source)
    {
        // Create a Priority Queue - Min Heap
        priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

        // Vector for Distances; all Values initialized to Infinity
        vector<int> distance(m_NumberOfVertices, INF);
        
        // Source is the first Element in the pq
        pq.push(make_pair(0, source));
        distance[source] = 0;
        
        while(!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();
            
            list< pair<int, int> >::iterator i;
            for (i = m_adjList[u].begin(); i != m_adjList[u].end(); ++i)
            {
                // Get vertex label and weight of current adjacent
                // of u.
                int v = (*i).first;
                int weight = (*i).second;
      
                //  If there is shorted path to v through u.
                if (distance[v] > distance[u] + weight)
                {
                    // Updating distance of v
                    distance[v] = distance[u] + weight;
                    pq.push(make_pair(distance[v], v));
                }
            }
        }
        
        cout << "Vertex Distance from Source\n";
        for (int i = 0; i < m_NumberOfVertices; ++i)
        {
            cout << i << "\t\t" << distance[i] << endl;
        }
    }
};

int main()
{
    int Vertices = 9;
    Graph g (Vertices);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    g.DijkstraAlgo(1);
    return 0;
}