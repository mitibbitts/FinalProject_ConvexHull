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

Node::Node(int x, int y, int type) {
    this->x = x;
    this->y = y;
    this->type = type;
    this->next == nullptr;
}

void Node::setEdge() {
    this->type = 1;
}

//Should be redundant but just in case
void Node::setCenter() {
    this->type = 0;
}

int Node::getX() {
    return this->x;
}

int Node::getY() {
    return this->y;
}

int Node::getType() {
    return this->type;
}