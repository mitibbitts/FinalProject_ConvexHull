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
void exportFile(std::vector<Node>& pointList, std::string& fileName) {
    std::ofstream outFile(fileName + "_convexHull.dot");
    outFile << "{\n";
    for (int i = 0; i < pointList.size(); i++) {
        outFile << "\t" << i;
        if (!(pointList[i].getNext() == nullptr)) {
            outFile << " -> " << pointList[i].getPath();
        }
        outFile << " xCoord: " << pointsList[i].getX() << " yCoord: " << pointsList[i].getY() << std::endl;
    }
    outFile << "\n}";
}

int main() {

	//when polar angles are found:
	//using the vector find the current node and the node that is pathed to:
	//  points[current].setNext(&points[pathed])
	// initializes file name and vector then open text file
    std::string file;
    std::cin >> file;
    std::vector<Node> points;
    readFile(points, file);

    HullGenerator hull;
    hull.generateOutput(points);
    exportFile(points, file);


    return 0;
}


