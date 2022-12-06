#include<SFML/Graphics.hpp>
#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include<utility>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<stack>

class HullGenerator{
	private:
		std::vector<sf::RectangleShape> drawCircles();
		//int count = 0;
		sf::Clock cl;
		std::vector<sf::RectangleShape> *points = new std::vector<sf::RectangleShape>;
		std::vector<double> indices;
	public:
		HullGenerator();
		void generateOutput(std::string inFName);

		void populateGrid(int count, double xMin, double xMax, double yMin, double yMax, sf::RectangleShape rectangle, std::vector<std::pair<double,double>> pointInput);

		std::vector<std::pair<double,double>> normalizeVector(std::vector<std::pair<double,double>> inputVec, double xMin, double xMax, double yMin, double yMax);
		std::vector<std::pair<double, double>> splitInput(std::vector<double> pointInput);
		int determineLowest();
		int determineClose(int index);
		void computeConvex(std::vector<int> indices);
		int isLeftTurn(int index, int newIndex, int newestIndex);
		double computeDeterminant(int index, int newIndex, int newestIndex);
		std::vector<int> sortByPolarAngle(int index);
		std::stack<int> grahamScan();
		int nextToTop(std::stack<int> opStack);
		int distance(int origin, int index);
		std::vector<double> readFile(std::string inFile);
};
