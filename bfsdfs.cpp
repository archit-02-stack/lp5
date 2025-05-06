#include <iostream>
#include <queue>
#include <omp.h>
using namespace std;

const int MAX = 100;
int adj[MAX][MAX] = {0};
bool visited[MAX];
int V;

void parallelBFS(int start) 
{
    bool visited[MAX] = {false};
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS: ";
    while (!q.empty()) 
	{
        int curr = q.front();
        q.pop();
        cout << curr << " ";

        #pragma omp parallel for
        for (int i = 0; i < V; i++) 
		{
            if (adj[curr][i]) 
			{
                #pragma omp critical
                {
                    if (!visited[i]) 
					{
                        visited[i] = true;
                        q.push(i);
                    }
                }
            }
        }
    }
    cout << endl;
}

void dfsUtil(int node) 
{
    visited[node] = true;
    cout << node << " ";

    #pragma omp parallel for
    for (int i = 0; i < V; i++) 
	{
        if (adj[node][i]) 
		{
            #pragma omp critical
            {
                if (!visited[i]) dfsUtil(i);
            }
        }
    }
}

void parallelDFS(int start) 
{
    fill(visited, visited + MAX, false);
    cout << "DFS: ";
    dfsUtil(start);
    cout << endl;
}

int main() 
{
    int E, u, v, start;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) 
	{
        cin >> u >> v;
        adj[u][v] = adj[v][u] = 1;
    }

    cout << "Enter starting vertex: ";
    cin >> start;

    parallelBFS(start);
    parallelDFS(start);
    return 0;
}

