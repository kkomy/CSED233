#pragma once
#include <fstream>
#include <iostream>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647
using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph {
public:
	Graph() {};
	~Graph() {
		if (use_dist == true) {
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 20; j++) {

					delete[] short_path[i][j];

				}
			}
		}
	};

	string DFS();
	string BFS();

	int addDirectedEdge(string nodeA, string nodeB);
	int addDirectedEdge(string nodeA, string nodeB, int weight);
	int addUndirectedEdge(string nodeA, string nodeB);
	int addUndirectedEdge(string nodeA, string nodeB, int weight);

	string StronglyConnectedComponent();

	string getShortestPath_task5(string source, string destination);
	string getShortestPath_task6(string source, string destination);
	int primMST(ofstream&, string startNode);
	int kruskalMST(ofstream&, string endNode);

private:
	/////////////////////////////////////////////////////////
	//////  TODO: Add private members if required ///////////
	string vert[100] = {}; // 정점 정보
	string* adj[100] = {}; // 인접 정점 정보
	int adj_num[100] = {}; // 인접 정점 개수
	int num = 0;            // 정점 개수
	int visit[100] = {};  // 방문여부

	/*FOR BFS*/
	string queue[100] = {};
	int q_num = 0;



	/*FOR Dijkstra*/
	int* wei[100] = {};
	string* path[100] = {}; // 경로저장
	int path_num[100] = {}; // 경로 개수 저장
	int length[100] = {}; // 출발지에서 해당 위치까지의 최단거리 저장
	int check[100] = {};     // 체크 여부
	int* di_adj[100] = {};   // 경로 길이를 저장한 이차원 배열

	int short_num[100] = {}; // 최단경로의 개수
	int short_length[100][100] = {}; // 최단경로 당 경로개수
	string* short_path[100][100] = {}; // 최단경로저장
	bool use_dist = false;


	/*Kruskal*/
	string parent[100] = {}; // cycle 테스트용
	int edge[1000] = {}; // edge 오름차순 정렬
	string edge_info[1000][2] = {};
	int edge_num = 0; // edge개수

	int exist_node(string node);
	int order_node(string node);
	void adj_add(string root, string node);
	void adj_add(string root, string node, int weight);
	string sub_DFS(string node);
	string sub_BFS(string node);
	int find_nocheck(int self);
	///////////      End of Implementation      /////////////
	/////////////////////////////////////////////////////////
};
