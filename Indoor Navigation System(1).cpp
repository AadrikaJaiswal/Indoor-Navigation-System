#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm> // Include the algorithm header for the 'reverse' function

using namespace std;

#define INF numeric_limits<int>::max()

// Structure to represent an edge
struct Edge {
    string dest; // Destination node
    int weight;   // Weight (distance) of the edge
};

// Structure to represent a graph
struct Graph {
    unordered_map<string, vector<Edge>> edges; // Map to store edges for each node
};

// Function to add an edge to the graph
void addEdge(Graph &graph, const string &src, const string &dest, int weight) {
    Edge newEdge = {dest, weight};
    graph.edges[src].push_back(newEdge);
    // For undirected graph, you might want to add the reverse edge as well
    Edge reverseEdge = {src, weight};
    graph.edges[dest].push_back(reverseEdge);
}

// Function to implement Dijkstra's algorithm
pair<int, vector<string>> dijkstra(const Graph &graph, const string &start, const string &end) {
    unordered_map<string, int> distance; // Map to store the distance from the start node
    unordered_map<string, string> parent; // Map to store the parent node in the shortest path
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq; // Priority queue for selecting the next node to explore

    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        string u = pq.top().second;
        pq.pop();

        for (const Edge &edge : graph.edges.at(u)) {
            string v = edge.dest;
            int weight = edge.weight;

            // Relaxation step: Update distance if a shorter path is found
            if (!distance.count(v) || distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                pq.push({distance[v], v});
            }
        }
    }

    // Construct the path and collect the edges
    vector<string> path;
    string current = end;
    while (current != start) {
        path.push_back(current);
        current = parent[current];
    }
    path.push_back(start);

    // Reverse the path to get the correct order
    reverse(path.begin(), path.end());

    // Return the shortest path distance and the edges traveled
    return {distance[end], path};
}

int main() {
    Graph indoorMap;

    // Add edges (nodes, weight) to represent the indoor map
    addEdge(indoorMap, "Entrance", "A", 4);
    addEdge(indoorMap, "A", "B", 10);
    addEdge(indoorMap, "A", "T", 4);
    addEdge(indoorMap, "T", "Premium_Room_1", 2);
    addEdge(indoorMap, "T", "U", 2);
    addEdge(indoorMap, "U", "Premium_Room_2", 2);
    addEdge(indoorMap, "B", "C", 2);
    addEdge(indoorMap, "C", "D", 8);
    addEdge(indoorMap, "D", "E", 4);
    addEdge(indoorMap, "E", "F", 4);
    addEdge(indoorMap, "F", "G", 4);
    addEdge(indoorMap, "G", "H", 4);
    addEdge(indoorMap, "H", "I", 4);
    addEdge(indoorMap, "I", "J", 4);
    addEdge(indoorMap, "D", "Room_100", 2);
    addEdge(indoorMap, "E", "Room_101", 2);
    addEdge(indoorMap, "F", "Room_102", 2);
    addEdge(indoorMap, "G", "Room_103", 2);
    addEdge(indoorMap, "H", "Room_104", 2);
    addEdge(indoorMap, "I", "Room_105", 2);
    addEdge(indoorMap, "J", "Room_106", 2);
    addEdge(indoorMap, "I", "K", 4);
    addEdge(indoorMap, "K", "L", 4);
    addEdge(indoorMap, "L", "M", 4);
    addEdge(indoorMap, "M", "N", 4);
    addEdge(indoorMap, "N", "O", 4);
    addEdge(indoorMap, "K", "Room_107", 2);
    addEdge(indoorMap, "L", "Room_108", 2);
    addEdge(indoorMap, "M", "Room_109", 2);
    addEdge(indoorMap, "N", "Room_110", 2);
    addEdge(indoorMap, "O", "Room_111", 2);
    addEdge(indoorMap, "O", "Room_112", 2);
    addEdge(indoorMap, "L", "Q", 2);
    addEdge(indoorMap, "M", "Q", 2);
    addEdge(indoorMap, "Q", "R", 12);
    addEdge(indoorMap, "C", "R", 2);
    addEdge(indoorMap, "Q", "Room_113", 2);
    addEdge(indoorMap, "Q", "Room_116", 2);
    addEdge(indoorMap, "R", "Room_114", 2);
    addEdge(indoorMap, "R", "Room_115", 2);
    addEdge(indoorMap, "O", "P", 24);
    addEdge(indoorMap, "B", "Information_Desk", 6);
    addEdge(indoorMap, "Information_Desk", "P", 2);
    addEdge(indoorMap, "P", "V", 11);
    addEdge(indoorMap, "V", "Emergency_Room", 11);
    addEdge(indoorMap, "V", "W", 21);
    addEdge(indoorMap, "P", "Nursing_Room", 11);
    addEdge(indoorMap, "Nursing_Room", "Y", 6);
    addEdge(indoorMap, "Y", "X", 3);
    addEdge(indoorMap, "W", "X", 2);
    addEdge(indoorMap, "X", "Pharmacy", 2);
    addEdge(indoorMap, "Y", "Z", 18);
    addEdge(indoorMap, "Z", "Cafeteria", 3);
    addEdge(indoorMap, "Z", "ICU", 2);
    addEdge(indoorMap, "Z", "Washroom", 7);
    addEdge(indoorMap, "ICU", "Operating_Theater", 18);
    addEdge(indoorMap, "Washroom", "Men's_Washroom", 1);
    addEdge(indoorMap, "Washroom", "Women's_Washroom", 1);


    string start, end;

    // User input for start and end points
    cout << "Enter the start point: ";
    cin >> start;

    cout << "Enter the end point: ";
    cin >> end;

    // Find the shortest path based on user input
    auto result = dijkstra(indoorMap, start, end);

    // Display the result
    cout << "Shortest Path Distance: " << result.first << endl;

    cout << "Edges Traveled: ";
    for (const string &node : result.second) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}