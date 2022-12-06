#include<SFML/Graphics.hpp>
#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"node.h"
#include<utility>
#include<cstdlib>
#include<iostream>
#include<vector>
#include"HullGenerator.h"
#include<cmath>
#include<stack>
#include<algorithm>
#include<numeric>
#include"unistd.h"

//      read this first: In order to get this to function, you will need to get SFML downloaded
//      then the application should be able to be run in the commandline with the following commands:
//
//      g++ -c main.cpp
//
//      g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
//
//      ./sfml-app
//
//      
//
//
HullGenerator::HullGenerator(){
}

void HullGenerator::generateOutput(std::vector<Node>& pointsList){
	int lowest;
	int lowIndex;
	int closeIndex;
	int count2 = 0;
	std::vector<int> indices;
	sf::RenderWindow window(sf::VideoMode(1000,1000), "Hull Generator");
	//window.setFramerateLimit(60);
	window.setPosition(sf::Vector2i(10, 50));

	srand(time(NULL));
	sf::Clock cl;

	while(window.isOpen()){

		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(20,20));
		rectangle.setPosition(sf::Vector2f(pointsList[count2].getX() % 800, pointsList[count2].getY % 800));
		
		//The value in this conditional statement will determine the number of squares which are drawn
		if(count < 12){

			points.push_back(rectangle);
			//points.back().setSize(sf::Vector2f(5,5));
			//points.back().setFillColor(sf::Color::Black);
			//cl.restart();
			
		}
		


		sf::Event event;
		while (window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				window.close();
			}
		}

		if(points.size() == count){
			

			grahamScan(cl, pointsList);


		}



		window.clear();

		
		for(int i = 0; i < points.size(); i++){
			window.draw(points[i]);
		}

		//window.draw(shape);
		window.display();
		count++;
		count2++;
	}
}
// Here we have an O(n) function which will return the index at which the lowest
// point resides in the vector
int HullGenerator::determineLowest(){
	int index = 0;
	int lowest = 0;

	for(int i = 0; i < points.size(); i++){
		sf::Vector2f position = points[i].getPosition();
		if(position.y > lowest){
			index = i;
			lowest = position.y;
		}
		//points[index].setFillColor(sf::Color::Green);
		//std::cout << index << std::endl;
	}
	return index;
}

//this function can be used to determine how close a point is to a given index
int HullGenerator::determineClose(int index){
	int newIndex = 0;
	int closest = 25000;
	int distance;
	sf::Vector2f currPos = points[index].getPosition();
	sf::Vector2f nPos;
	for(int i = 0; i < points.size(); i++){
		if(i != index && points[i].getFillColor() == sf::Color::White){
			nPos = points[i].getPosition();
			distance = std::sqrt(std::pow(nPos.x-currPos.x,2)+std::pow(nPos.y-currPos.y,2));
			if(distance < closest){
				newIndex = i;
				closest = distance;
			}
		}
	}
	return newIndex;

}

int HullGenerator::distance(int origin, int index){
	int distance;
	sf::Vector2f originPos = points[origin].getPosition();
	sf::Vector2f pointPos = points[index].getPosition();
	distance = std::sqrt(std::pow(pointPos.x-originPos.x,2)+std::pow(pointPos.y-originPos.y,2));
	return distance;

}

/** Not currently using this function because it sucks
void HullGenerator::computeConvex(std::vector<int> indices){
		
	std::stack<sf::RectangleShape> S;
	S.push(points[indices[0]]);
	S.push(points[indices[1]]);
	S.push(points[indices[2]]);
	  
		// Process remaining n-3 points
	for (int i = 3; i < indices.size(); i++){
	  // Keep removing top while the angle formed by
	  // points next-to-top, top, and points[i] makes
	  // a non-left turn
		while (S.size()>1 && isLeftTurn(indices[i],indices[i+1], indices[i+2])){
			S.pop();
			S.push(points[indices[i]]);
		}
	}

	// Now stack has the output points, print contents of stack
	while (!S.empty()){
		sf::RectangleShape p = S.top();

		//cout << "(" << p.x << ", " << p.y <<")" << endl;
		S.pop();
	}


}*/

//this function outputs a 1 if a right turn occurs, a 2 if a left turn occurs
//and a 0 if the points are colinear
int HullGenerator::isLeftTurn(int index, int newIndex, int newestIndex){
	int isLeft = 1;
	double crossProduct = computeDeterminant(index, newIndex, newestIndex);
	if(crossProduct < 0){
		isLeft = 2;
	}
	else if(crossProduct == 0){
		isLeft = 0;
	}
	//std::cout << crossProduct << std::endl;
	return isLeft;
}

//this function computes the cross product for the vectors formed by
//the three points passed in as arguments
double HullGenerator::computeDeterminant(int index, int newIndex, int newestIndex){
	
	double vecOneX = points[newIndex].getPosition().x - points[index].getPosition().x;
	double vecOneY = points[newIndex].getPosition().y - points[index].getPosition().y;
	double vecTwoX = points[newestIndex].getPosition().x - points[newIndex].getPosition().x;
	double vecTwoY = points[newestIndex].getPosition().y - points[newIndex].getPosition().y;
	double det = vecOneX*vecTwoY - vecOneY*vecTwoX;
	//std::cout crossProduct;
	if(det == 0){ return 0;}
	return det;

}


//this function sorts and colors the points on the grid
std::vector<int> HullGenerator::sortByPolarAngle(int index){
	std::vector<double> angles;
	std::vector<int> indices(points.size());
	double polarAngle;
	double pointX;
	double pointY;
	double xLen;
	double yLen;
	double originX = points[index].getPosition().x;
	double originY = points[index].getPosition().y;
	for(int i = 0; i < points.size(); i++){
		if(i != index){
			pointX = points[i].getPosition().x;
			pointY = points[i].getPosition().y;
			xLen = originX - pointX;
			yLen = originY - pointY;
			polarAngle = (std::atan2(yLen,xLen)*(180/3.1415));
			points[i].setFillColor(sf::Color(polarAngle/2, polarAngle, polarAngle));
		}
		else{
			polarAngle = 0;
		}
		angles.push_back(polarAngle);
	}
	std::iota(indices.begin(), indices.end(), 0);
	std::sort(indices.begin(), indices.end(), [&](double A, double B) -> bool {return angles[A] > angles[B];});

	for(int i  = 0; i<indices.size(); i++){
		//std::cout << indices[i] << "   " << angles[indices[i]]<< std::endl;
	}

	return indices;
}

//this function actually computes which points are in the convex hull via the graham scan algorithm
void HullGenerator::grahamScan(sf::Clock cl, std::vector<Node>& pointsList){
	int anchorIndex = determineLowest();
	int listIndex = anchorIndex;
	std::vector<int> sortedData = sortByPolarAngle(anchorIndex);
	int tmp;

	
	int m = 1;
	for(int i = 0; i < sortedData.size(); i++){
		if(isLeftTurn(anchorIndex, sortedData[i], sortedData[i+1]) == 0){
			int dist1 = distance(anchorIndex, sortedData[i]);
			int dist2 = distance(anchorIndex, sortedData[i+1]);
			if(dist1 < dist2){
				sortedData.erase(sortedData.begin()+i);
			}
			else if(dist2 < dist1){
				sortedData.erase(sortedData.begin()+(i+1));
			}
		}
	}
	std::cout << sortedData.size();
	
	std::stack<int> hull;
	hull.push(sortedData[0]);
	hull.push(sortedData[1]);
	hull.push(sortedData[2]);

	for(int i = 3; i < sortedData.size(); i++){
		
		while(hull.size()>1 && isLeftTurn(sortedData[i],nextToTop(hull), hull/top())==1){
			//tmp = hull.top();
			points[hull.top()].setFillColor(sf::Color::Red);
			pointsList[listIndex].setNext(hull.top();
			listIndex = hull.top();
			hull.pop();
			//hull.pop();
			points[hull.top()].setFillColor(sf::Color::Red);
			//hull.push(tmp);
		}
		hull.push(sortedData[i]);
	}

	while(!hull.empty()){
		points[hull.top()].setFillColor(sf::Color::Green);
		hull.pop();
	}

}

//this function returns the value next to the top of the stack. I thought it would
//be necessary but it is not
int HullGenerator::nextToTop(std::stack<int> opStack){

	int point = opStack.top();
	opStack.pop();
	int output = opStack.top();
	opStack.push(point);
	return output;
}
