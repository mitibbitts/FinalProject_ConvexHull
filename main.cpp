#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"Hullgenerator.cpp"
#include "node.h"

//read input file and transform into (vector? hash? linkedList?)
void readFile(std::vector<Node>& pointList, std::string& fileName) {

    std::ifstream inFile(fileName);
    std::string line;

    while (std::getline(inFile, line)) {
        std::istringstream stream(line);
        std::vector<int> temp;
        int val;
        while (stream >> val) {
            temp.push_back(val);
        }
        //std::cout << temp[0] << ' ' << temp[1] << std::endl;
        Node node(temp[0], temp[1]);
        //std::cout << "size 2" << std::endl;
        pointList.push_back(node);
    }
}

//output file as a .dot


int main() {

    std::string file;
    std::cin >> file;
    std::vector<Node> points;
    readFile(points, file);

    HullGenerator hull;
    hull.generateOutput();


	return 0;
}


