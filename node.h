#include <string>

class Node {
private:
    int x;
    int y;
    int path; //empty unless next != nullptr, will store index of pointed node
    Node* next;
public:
    Node();
    Node(int x, int y);
    void setEdge(int edge);
    void setEdge();
    void setCenter();
    int getX();
    int getY();
    int getPath();
    Node* getNext();
    void setNext(int path);

    friend class HullGenerator;
};
