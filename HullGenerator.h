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
		int count = 0;
		sf::Clock cl;
		std::vector<sf::RectangleShape> points;
		std::vector<double> indices;
	public:
		HullGenerator();
		void generateOutput();
		int determineLowest();
		int determineClose(int index);
		void computeConvex(std::vector<int> indices);
		int isLeftTurn(int index, int newIndex, int newestIndex);
		double computeDeterminant(int index, int newIndex, int newestIndex);
		std::vector<int> sortByPolarAngle(int index);
		void grahamScan(sf::Clock cl);
		int nextToTop(std::stack<int> opStack);
		int distance(int origin, int index);
};