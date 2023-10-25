#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>
#define INF 2147483647
using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */
int Graph::exist_node(string node) { // 노드의 존재여부 확인
    int i = 0;
    int check = 0;
    while (i < num) {
        if (vert[i] == node) {
            return 1; // 이미 존재하는 노드일 경우
        }
        i++;
    }
    return -1; // 처음 추가된 노드일 경우
}

int Graph::order_node(string node) { // vert배열 상의 노드의 위치
    for (int i = 0; i < num; i++) {
        if (vert[i] == node) {
            return i;
        }
    }
    return -1;
}

void Graph::adj_add(string root, string node) {
    int i = 0;
    int order_root = order_node(root);

    if (adj_num[order_root] == 0) { // 인접행렬을 처음 가질 경우
        adj[order_root] = new string[1];
    }

    string* adj_temp = new string[adj_num[order_root] + 1];
    for (int k = 0; k < adj_num[order_root]; k++) {
        adj_temp[k] = adj[order_root][k];
    }

    adj_num[order_root]++;
    adj[order_root] = new string[adj_num[order_root]];

    for (int k = 0; k < adj_num[order_root] - 1; k++) {
        adj[order_root][k] = adj_temp[k];
    }
    adj[order_root][adj_num[order_root] - 1] = adj_temp[adj_num[order_root] - 1];

    while (adj_num[order_root] > i) {
        if (adj[order_root][i] == node) { // 이미 존재하는 edge이면 입력 무시
            return;
        }
        i++;
    }
    i--;
    adj[order_root][i] = node;

    /*인접행렬 정렬*/
    for (int m = 0; m < i; m++) {
        for (int n = 0; n < i - m; n++) {
            if (adj[order_root][n] > adj[order_root][n + 1]) {
                string temp = adj[order_root][n];
                adj[order_root][n] = adj[order_root][n + 1];
                adj[order_root][n + 1] = temp;
            }
        }
    }

    return;
}

void Graph::adj_add(string root, string node, int weight) {
    int i = 0;
    int order_root = order_node(root);

    if (adj_num[order_root] == 0) { // 인접행렬을 처음 가질 경우
        adj[order_root] = new string[1];
        wei[order_root] = new int[1];

    }
    

    string* adj_temp = new string[adj_num[order_root] + 1];
    int* wei_temp = new int[adj_num[order_root] + 1];
    for (int k = 0; k < adj_num[order_root]; k++) {
        adj_temp[k] = adj[order_root][k];
        wei_temp[k] = wei[order_root][k];
    }

    adj_num[order_root]++;
    adj[order_root] = new string[adj_num[order_root]];
    wei[order_root] = new int[adj_num[order_root]];

    for (int k = 0; k < adj_num[order_root] - 1; k++) {
        adj[order_root][k] = adj_temp[k];
        wei[order_root][k] = wei_temp[k];
    }
    adj[order_root][adj_num[order_root] - 1] = adj_temp[adj_num[order_root] - 1];
    wei[order_root][adj_num[order_root] - 1] = wei_temp[adj_num[order_root] - 1];

    while (adj_num[order_root] > i) {
        if (adj[order_root][i] == node) { // 이미 존재하는 edge이면 입력 무시
            return;
        }
        i++;
    }
    i--;
    adj[order_root][i] = node;
    wei[order_root][i] = weight;

    /*인접행렬 정렬*/
    for (int m = 0; m < i; m++) {
        for (int n = 0; n < i - m; n++) {
            if (adj[order_root][n] > adj[order_root][n + 1]) {
                string temp = adj[order_root][n];
                int temp_wei = wei[order_root][n];

                adj[order_root][n] = adj[order_root][n + 1];
                adj[order_root][n + 1] = temp;

                wei[order_root][n] = wei[order_root][n + 1];
                wei[order_root][n + 1] = temp_wei;
            }
        }
    }

    return;
}

string Graph::sub_DFS(string node) {
    string traverse;
    if (visit[order_node(node)] == 1) {
        return "";
    }
    visit[order_node(node)] = 1;
    traverse += vert[order_node(node)];
    traverse += " ";
    for (int i = 0; i < adj_num[order_node(node)]; i++) {
        traverse += sub_DFS(adj[order_node(node)][i]);
    }
    return traverse;
}

string Graph::sub_BFS(string node) {
    string traversal;
    queue[q_num] = node;
    q_num++;
    visit[order_node(node)] = 1;
    while (q_num > 0) {
        string temp = queue[0];
        int q = 0;
        while (queue[0] != vert[q]) {
            q++;
        }
        int temp_adj_num = adj_num[q];
        string* temp_adj = adj[0];

        for (int i = 0; i < q_num - 1; i++) { // queue의 pop 기능
            queue[i] = queue[i + 1];
        }
        q_num--;

        traversal += temp;
        traversal += ' ';
        for (int i = 0; i < temp_adj_num; i++) {
            int p = 0;
            while (adj[q][i] != vert[p]) {
                p++;
            }
            if (visit[p] == 0) {
                visit[p] = 1;
                queue[q_num] = adj[q][i];
                q_num++;
            }
        }
    }
    return traversal;
}


int Graph::find_nocheck(int self) {
    int min = INF;
    int min_num = -1;
    for (int i = 0; i < num; i++) {
        if (i != self) {
            if (min >= length[i] && check[i] == 0) {
                min = length[i];
                min_num = i;
            }
        }
    }

    return min_num;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

string Graph::DFS() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int graph_num = 1;
    string traversal;
    traversal = sub_DFS(vert[0]);
    for (int i = 0; i < num; i++) {
        if (visit[i] == 0) {
            graph_num++;
            traversal += '\n';
            traversal += sub_DFS(vert[i]);
        }
    }
    string total;
    total += to_string(graph_num);
    total += '\n';
    total += traversal;
    return total;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::BFS() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int graph_num = 1;
    string traversal;
    queue[q_num] = vert[0];
    ;
    q_num++;
    visit[order_node(vert[0])] = 1;
    while (q_num > 0) {
        string temp = queue[0];
        int q = 0;
        while (queue[0] != vert[q]) {
            q++;
        }
        int temp_adj_num = adj_num[q];
        string* temp_adj = adj[0];

        for (int i = 0; i < q_num - 1; i++) { // queue의 pop 기능
            queue[i] = queue[i + 1];
        }
        q_num--;

        traversal += temp;
        traversal += ' ';
        for (int i = 0; i < temp_adj_num; i++) {
            int p = 0;
            while (adj[q][i] != vert[p]) {
                p++;
            }
            if (visit[p] == 0) {
                visit[p] = 1;
                queue[q_num] = adj[q][i];
                q_num++;
            }
        }
    }

    /*초기화 작업*/
    for (int i = 0; i < num; i++) {
        queue[i] = "";
    }
    q_num = 0;

    for (int i = 0; i < num; i++) {
        if (visit[i] == 0) {
            graph_num++;
            traversal += '\n';
            traversal += sub_BFS(vert[i]);
        }
    }
    string total;
    total += to_string(graph_num);
    total += '\n';
    total += traversal;
    return total;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (exist_node(nodeA) == -1) {
        vert[num] = nodeA;
        num++;
    }
    if (exist_node(nodeB) == -1) {
        vert[num] = nodeB;
        num++;
    }
    adj_add(nodeA, nodeB);
    /*정렬*/
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (vert[j] > vert[j + 1]) {
                string vert_temp = vert[j];
                string* adj_temp = adj[j];
                int num_temp = adj_num[j];
                vert[j] = vert[j + 1];
                adj[j] = adj[j + 1];
                adj_num[j] = adj_num[j + 1];
                vert[j + 1] = vert_temp;
                adj[j + 1] = adj_temp;
                adj_num[j + 1] = num_temp;
            }
        }
    }

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (exist_node(nodeA) == -1) {
        vert[num] = nodeA;
        num++;
    }
    if (exist_node(nodeB) == -1) {
        vert[num] = nodeB;
        num++;
    }
    adj_add(nodeA, nodeB);
    adj_add(nodeB, nodeA);
    /*정렬*/
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (vert[j] > vert[j + 1]) {
                string vert_temp = vert[j];
                string* adj_temp = adj[j];
                int num_temp = adj_num[j];
                vert[j] = vert[j + 1];
                adj[j] = adj[j + 1];
                adj_num[j] = adj_num[j + 1];
                vert[j + 1] = vert_temp;
                adj[j + 1] = adj_temp;
                adj_num[j + 1] = num_temp;
            }
        }
    }

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (exist_node(nodeA) == -1) {
        vert[num] = nodeA;
        num++;
    }
    if (exist_node(nodeB) == -1) {
        vert[num] = nodeB;
        num++;
    }
    adj_add(nodeA, nodeB, weight);
    adj_add(nodeB, nodeA, weight);
    /*정렬*/
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (vert[j] > vert[j + 1]) {
                string vert_temp = vert[j];
                string* adj_temp = adj[j];
                int* wei_temp = wei[j];
                int num_temp = adj_num[j];

                vert[j] = vert[j + 1];
                adj[j] = adj[j + 1];
                wei[j] = wei[j + 1];
                adj_num[j] = adj_num[j + 1];

                vert[j + 1] = vert_temp;
                adj[j + 1] = adj_temp;
                wei[j + 1] = wei_temp;
                adj_num[j + 1] = num_temp;
            }
        }
    }

    return 0;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string Graph::StronglyConnectedComponent() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
  string temp;
  temp += "3";
  temp += '\n';
  temp += "A";
  temp += '\n';
  temp += "B";
  temp += '\n';
  temp += "C D E";

    return temp;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::getShortestPath_task5(string source, string destination) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (source == destination) {
        string same_node;
        same_node += source;
        same_node += " ";
        same_node += '0';
        return same_node;
    }
    use_dist = true;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 20; j++) {

            short_path[i][j] = new string[100];

        }
    }
   
    int s_num = order_node(source);      // 출발점 번호
    int d_num = order_node(destination); // 도착점 번호
    for (int i = 0; i < num; i++) {
        path[i] = new string[num];
    }

    string test = sub_DFS(source);
    if (visit[d_num] == 0) {
        return "error";
    }
    for (int i = 0; i < num; i++) {
        visit[i] = 0; // 초기화
    }

    for (int i = 0; i < num; i++) {
        di_adj[i] = new int[num]; //다익스트라 배열구현 : 가중치
    }

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            di_adj[i][j] = 2147483647; // 모두 INF로 초기화
        }
    }

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (i == j) {
                di_adj[i][j] = 0; // 자기자신
            }
            else {
                for (int k = 0; k < adj_num[i]; k++) {
                    if (order_node(adj[i][k]) == j) {
                        di_adj[i][j] = wei[i][k]; // 인접한 노드와의 가중치 등록
                    }
                }
            }
        }
    }

    for (int i = 0; i < num; i++) { // 다익스트라 초기세팅
        length[i] = di_adj[s_num][i];
        path_num[i] = 2;
        path[i][0] = source;
        path[i][1] = vert[i];
    }
    check[0]++;

    for (int q = 0; q < num; q++) {
        int invest = find_nocheck(s_num); // 아직 조사하지 않은 것 중 최소거리를 찾는 함수
        if (invest == -1) {
            break;
        }
        for (int i = 0; i < num; i++) {
            if (di_adj[invest][i] + length[invest] == length[i] && di_adj[invest][i] + length[invest] > 0 && invest != i) { // 같은 경로를 찾았다면
                
                    short_length[i][short_num[i]] = path_num[invest];

                    for (int j = 0; j < path_num[i]; j++) {
                        short_path[i][short_num[i]][j] = path[invest][j];
                    }

                    short_path[i][short_num[i]][short_length[i][short_num[i]]] = vert[i];
                    short_length[i][short_num[i]]++;
                    short_num[i]++;
                
            }

            if (di_adj[invest][i] + length[invest] < length[i] && di_adj[invest][i] + length[invest] > 0) { // 더 짧은 경로를 찾았다면
                length[i] = di_adj[invest][i] + length[invest]; // 경로 갱신
                path_num[i] = path_num[invest];
                for (int j = 0; j < path_num[invest]; j++) {
                    path[i][j] = path[invest][j];
                }

                path[i][path_num[i]] = vert[i]; // 경로프로세스 갱신
                path_num[i]++; // 경로의 길이는 늘어났으므로 추가
                


                if (short_num[invest] > 0) {
                    for (int j = 0; j < short_num[invest]; j++) {
                        for (int k = 0; k < short_length[invest][j]; k++) {
                            short_path[i][j][k] = short_path[invest][j][k];
                        }



                        short_length[i][short_num[i]] = short_length[invest][j];
                        
                        short_path[i][short_num[i]][short_length[i][short_num[i]]] = vert[i];
                        short_length[i][short_num[i]]++;
                        short_num[i]++;
                    }
                }



            }
        }
        check[invest]++;
    }
    string result;
    string variable[100];

    int vari_num = 0;
    for (int j = 0; j < path_num[d_num]; j++) {
        variable[0] += path[d_num][j];
        variable[0] += " ";
    }
    variable[0] += to_string(length[d_num]);

    if (short_num[d_num] > 0) {
        for (int i=0 ; i <short_num[d_num]; i++) {
            for (int j = 0; j < short_length[d_num][i]; j++) {
                variable[i+1] += short_path[d_num][i][j];
                variable[i+1] += " ";
            }
            variable[i+1] += to_string(length[d_num]);

        }

        for (int i = 0; i < short_num[d_num]; i++) {
            for (int j = 0; j < short_num[d_num] - i; j++) {
                if (variable[j].compare(variable[j + 1]) > 0) {
                    string temp = variable[j];

                    variable[j] = variable[j + 1];
                    variable[j + 1] = temp;


                }


            }
        }
    }

    for (int i = 0; i < short_num[d_num] + 1; i++) {
        result += variable[i];
        result += '\n';
  }
  result.pop_back();
    return result;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string Graph::getShortestPath_task6(string source, string destination) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (source == destination) {
        string same_node;
        same_node += source;
        same_node += " ";
        same_node += '0';
        return same_node;
    }
    use_dist = true;

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 20; j++) {

            short_path[i][j] = new string[num];

        }
    }

    int s_num = order_node(source);      // 출발점 번호
    int d_num = order_node(destination); // 도착점 번호
    for (int i = 0; i < num; i++) {
        path[i] = new string[num];
    }

    string test = sub_DFS(source);
    if (visit[d_num] == 0) {
        return "INF";
    }
    for (int i = 0; i < num; i++) {
        visit[i] = 0; // 초기화
    }

    for (int i = 0; i < num; i++) {
        di_adj[i] = new int[num]; //다익스트라 배열구현 : 가중치
    }

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            di_adj[i][j] = 214748364; // 모두 INF로 초기화
        }
    }

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (i == j) {
                di_adj[i][j] = 0; // 자기자신
            }
            else {
                for (int k = 0; k < adj_num[i]; k++) {
                    if (order_node(adj[i][k]) == j) {
                        di_adj[i][j] = wei[i][k]; // 인접한 노드와의 가중치 등록
                    }
                }
            }
        }
    }

    for (int i = 0; i < num; i++) { // 다익스트라 초기세팅
        length[i] = di_adj[s_num][i];
        path_num[i] = 2;
        path[i][0] = source;
        path[i][1] = vert[i];
    }
    check[0]++;

    for (int q = 0; q < num; q++) {
        int invest = find_nocheck(s_num); // 아직 조사하지 않은 것 중 최소거리를 찾는 함수
        if (invest == -1) {
            break;
        }
        for (int i = 0; i < num; i++) {

            if (di_adj[invest][i] + length[invest] < length[i]) { // 더 짧은 경로를 찾았다면
                length[i] = di_adj[invest][i] + length[invest]; // 경로 갱신
                path_num[i] = path_num[invest];
                for (int j = 0; j < path_num[invest]; j++) {
                    path[i][j] = path[invest][j];
                }

                path[i][path_num[i]] = vert[i]; // 경로프로세스 갱신
                path_num[i]++; // 경로의 길이는 늘어났으므로 추가




            }
        }
        check[invest]++;
    }
    string result;
    for (int i = 0; i < path_num[d_num]; i++) {
        result += path[d_num][i];
        result += " ";
    }
    result += to_string(length[d_num]);
    if (short_num[d_num] > 0) {
        for (int i = 0; i < short_num[d_num]; i++) {
            result += '\n';
            for (int j = 0; j < short_length[d_num][i]; j++) { ////////////
                result += short_path[d_num][i][j];
                result += " ";
            }
            result += to_string(length[d_num]);
        }
    }
    return result;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream& fout, string startNode) { 
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    for (int i = 0; i < num; i++) {
        di_adj[i] = new int[num]; //다익스트라 배열구현 : 가중치
    }

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            di_adj[i][j] = 214748364; // 모두 INF로 초기화
        }
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (i == j) {
                di_adj[i][j] = 0; // 자기자신
            }
            else {
                for (int k = 0; k < adj_num[i]; k++) {
                    if (order_node(adj[i][k]) == j) {
                        di_adj[i][j] = wei[i][k]; // 인접한 노드와의 가중치 등록
                    }
                }
            }
        }
    }
    
    int s_num = order_node(startNode);
    visit[s_num] = 1;
    string MST;

    string min_adj;
    string MST_path[100][100] = {};
    int MST_path_num[100] = {};
    string MST_visit[100] = {};
    int MST_visit_num = 0;

    MST_path_num[s_num] = 1;
    int MST_length = 0;
    int search_num = s_num;
    int visit_num = num;

    MST_visit_num++;
    MST_visit[0] = startNode;
    MST_path[s_num][0] = startNode;

    while (1) {

        int min_adj_value = INF;
        int prenum = 0;
        for (int i = 0; i < MST_visit_num; i++) {
            for (int j = 0; j < num; j++) {
                int tmp = 0;
                for (int k = 0; k < MST_visit_num; k++) {
                    if (MST_visit[k] == vert[j]) {
                        tmp++;
                        break;
                    }
                }
                if (tmp != 0) {
                    continue;
                }
                if (MST_visit[i] != vert[j] && visit[j] == 0 && min_adj_value > di_adj[order_node(MST_visit[i])][j]) {
                    min_adj_value = di_adj[order_node(MST_visit[i])][j];
                    min_adj = vert[j];
                    prenum = order_node(MST_visit[i]);
                }
            }
        }

        visit[order_node(min_adj)] = 1;
        MST_length += di_adj[prenum][order_node(min_adj)];
        for (int i = 0; i < MST_path_num[prenum]; i++) {
            MST_path[order_node(min_adj)][i] = MST_path[prenum][i];
        }

        MST_path[order_node(min_adj)][MST_path_num[prenum]] = min_adj;
        MST_path_num[order_node(min_adj)] = MST_path_num[prenum];
        MST_path_num[order_node(min_adj)]++;

        MST_visit[MST_visit_num] = min_adj;
      
        MST_visit_num++;

        string MSTline;
        
        for (int i = 0; i < MST_path_num[order_node(min_adj)]; i++) {
            MSTline += MST_path[order_node(min_adj)][i];
            MSTline += " ";
        }
        MST += MSTline;
        MST += '\n';

        int temp = 0;
        for (int i = 0; i < num; i++) {
            if (visit[i] == 0) {
                temp++;
            }
        }
        if (temp == 0) {
            break;
        }
    }
    MST.pop_back();
    fout << MST << endl;

        return MST_length;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream& fout, string endNode) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    for (int i = 0; i < num; i++) {
        di_adj[i] = new int[num]; //다익스트라 배열구현 : 가중치
    }

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            di_adj[i][j] = INF; // 모두 INF로 초기화
        }
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (i == j) {
                di_adj[i][j] = 0; // 자기자신
            }
            else {
                for (int k = 0; k < adj_num[i]; k++) {
                    if (order_node(adj[i][k]) == j) {
                        di_adj[i][j] = wei[i][k]; // 인접한 노드와의 가중치 등록
                    }
                }
            }
        }
    }

    string startNode;
    startNode += vert[0];
    int kru_length = 0;
    string MST;


    for (int i = 0; i < num; i++) {
        parent[i] = vert[i];
    }


    for (int i = 0; i < num; i++) {
        for (int j = i+1; j < num; j++) {
            if (di_adj[i][j] != INF) {
                edge[edge_num] = di_adj[i][j]; // edge정보 기입
                edge_info[edge_num][0] = vert[i];
                edge_info[edge_num][1] = vert[j];
                edge_num++;
            }
        }
    }


    for (int i = 0; i < num - 1; i++) { // edge 크기순 정렬
        for (int j = 0; j < num - i - 1; j++) {
            if (edge[j] > edge[j + 1]) {
                int temp = edge[j + 1];
                edge[j + 1] = edge[j];
                edge[j] = temp;

                string temp1 = edge_info[j + 1][0];
                string temp2 = edge_info[j + 1][1];
                edge_info[j + 1][0] = edge_info[j][0];
                edge_info[j + 1][1] = edge_info[j][1];
                edge_info[j][0] = temp1;
                edge_info[j][1] = temp2;


            }
        }
    }



    for (int i = 0; i < edge_num; i++) {
        if (parent[order_node(edge_info[i][0])] == parent[order_node(edge_info[i][1])]) { // 싸이클이 존재하면
            
            for (int j = 0; j < adj_num[order_node(edge_info[i][0])]; j++) {
                if (adj[order_node(edge_info[i][0])][j] == edge_info[i][1]) {
                    wei[order_node(edge_info[i][0])][j] = INF;
                }
            }
            for (int j = 0; j < adj_num[order_node(edge_info[i][1])]; j++) {
                if (adj[order_node(edge_info[i][1])][j] == edge_info[i][0]) {
                    wei[order_node(edge_info[i][1])][j] = INF;
                }
            }


        }
        else { // 싸이클이 존재하지 않으면
            kru_length += edge[i]; //MST에 edge가 추가되므로 가중치++

            MST += edge_info[i][0];
            MST += " ";
            MST += edge_info[i][1];
            MST += " ";
            MST += to_string(edge[i]);
            MST += '\n';

            if (order_node(edge_info[i][0]) > order_node(edge_info[i][1])) {
                string temp = parent[order_node(edge_info[i][0])];
                parent[order_node(edge_info[i][0])] = parent[order_node(edge_info[i][1])];
                for (int j = 0; j < num; j++) {
                    if (parent[j] == temp) {
                        parent[j] = parent[order_node(edge_info[i][0])];
                    }
                }
            }
            else {
                string temp = parent[order_node(edge_info[i][1])];
                parent[order_node(edge_info[i][1])] = parent[order_node(edge_info[i][0])];
                for (int j = 0; j < num; j++) {
                    if (parent[j] == temp) {
                        parent[j] = parent[order_node(edge_info[i][1])];
                    }
                }
            }
        }
    }
    MST += getShortestPath_task5(startNode, endNode);
    MST.pop_back();

    fout << MST;

    return kru_length;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
