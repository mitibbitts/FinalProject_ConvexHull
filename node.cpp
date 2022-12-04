#include "node.h"
#include <string>

Node::Node() {
    this->x = 0;
    this->y = 0;
    this->next = nullptr;
}

Node::Node(int x, int y) {
    this->x = x;
    this->y = y;
    this->next == nullptr;
}

void Node::setEdge(int edge) {
    this->path = edge;
}

int Node::getX() {
    return this->x;
}

int Node::getY() {
    return this->y;
}

int Node::getPath() {
    return this->path;
}

Node Node::getNext() {
    return this->next;
}
