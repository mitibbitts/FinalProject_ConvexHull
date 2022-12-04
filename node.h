#include <string>

class Node {
private:
    int x;
    int y;
    int type = 0; //0 = center, 1 = edge;
    Node* next;
public:
    Node();
    Node(int x, int y);
    Node(int x, int y, int type);
    void setEdge();
    void setCenter();
    int getX();
    int getY();
    int getType();

    friend class HullGenerator;
};