#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct Node {
    //1. 자식 노드들을 저장하는 맵
    // "father" -> Node* 가 가리키는 father node
    // "son" -> Node* 가 가리키는 son node
    map<string, Node*> children;

    // 2. 이노드에서 끝나는 경로가 있는지 표기
    bool is_end;

    Node() : is_end(false) {}

    // 소멸자
    ~Node() {
        for(auto const& [key, val] : children) {
            delete val;
        }
    }

};

void insert(Node* root, string path) {
    Node* currNode = root;
    istringstream iss(path);

    string word;

    while(iss >> word) {
        if(currNode->children.find(word) == currNode->children.end()) {
            currNode->children[word] = new Node();
        }
        currNode = currNode->children[word];
    }
    currNode->is_end = true;
}

void printTree(Node* currentNode, int depth) {
    
    // 1. 현재 노드의 모든 자식(children)을 순회합니다.
    for (auto const& [word, childNode] : currentNode->children) {
        
        // 2. 깊이(depth)만큼 "--"를 먼저 출력합니다.
        for (int i = 0; i < depth; i++) {
            cout << "--";
        }

        // 3. 자식 노드의 'word'를 출력합니다.
        cout << word << "\n";

        // 4. 자식 노드('childNode')를 기준으로 재귀 호출합니다.
        printTree(childNode, depth + 1);
    }
}

int main() {    

    cin.tie(0)->sync_with_stdio(0);

    Node* root = new Node();

    int T;

    cin >> T;

    while(T--) {

        int k;
        
        cin >> k;

        string line;
        getline(cin,line);
        insert(root, line);

    }
    printTree(root, 0);


    delete root;
    return 0;
}