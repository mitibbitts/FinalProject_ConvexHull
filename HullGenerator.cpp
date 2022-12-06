#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"stdio.h"
#include"stdlib.h"
#include"time.h"
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
#include<fstream>
#include<sstream>

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
HullGenerator::HullGenerator(){
}

//behold the most disgusting function ever. I'll burn for not refactoring
//this draws and initializes everything
void HullGenerator::generateOutput(std::string inFName){
	//std::string inFName = "gold";
	int count = 0;
	int lowest;
	int lowIndex;
	int closeIndex;
	int count2;
	std::vector<int> *indices = new std::vector<int>;
	sf::RenderWindow window(sf::VideoMode(1000,1000), "Hull Generator");
	std::string filename = "image.png";
	window.setFramerateLimit(60);
	window.setPosition(sf::Vector2i(0, 0));
	sf::View view = window.getDefaultView();
	int count3=0;

	//sf::Music music;

	//if(!music.openFromFile("doWhile.wav")){
	//error
	//}
	//music.setPosition(200,400,100);
	//music.setVolume(20.f);
	//if(music.getStatus() == sf::SoundSource::Status::Stopped && count >1){
	//	music.play();
	//}

	sf::Font font;
	if (!font.loadFromFile("times.ttf"))
	{
    // error...
	}

	sf::Font font2;
	if (!font.loadFromFile("arial.ttf"))
	{
    // error...
	}

	
	sf::Text text;
   // sf::Text playerText;
	text.setString(inFName);
	text.setFont(font);
	text.setCharacterSize(147);
	//player.setString("Hello");
    //playerInput.SetPosition(sf::Vector2f(60,300));
    text.setFillColor(sf::Color(137,197,250));
	//playerInput.SetText("Hello");
	sf::Text trackID;	
	trackID.setFont(font2);
	trackID.setCharacterSize(140);
	trackID.setFillColor(sf::Color::Black);
	trackID.setString("'Do While', Oval");
	
	sf::Clock cl;
	sf::ConvexShape convex;
	convex.setFillColor(sf::Color::Transparent);
	convex.setOutlineColor(sf::Color(236,242,153));
	convex.setOutlineThickness(2);
	std::vector<double> fileIn;
	std::vector<std::pair<double,double>> splitPoints;
	double *xMin = new double;
	double *xMax = new double;
	double *yMin = new double;
	double *yMax = new double;
	//Prompt the user to enter the name of the file
	//std::cout << "Enter The Name of the File You Would Like to Read: ";
	//std::cin >> inFName;

	text.setString(inFName);

	int count4 = 0;

	//read the file
	if(inFName != "drawmode"){
		
		text.setScale(1, -1);
		text.setPosition(sf::Vector2f(40,950));
		trackID.setScale(1,-1);
		trackID.setPosition(950,40);
		view.setSize(1000, -1000); 
		window.setView(view);
		fileIn = readFile(inFName+".txt");
		splitPoints = splitInput(fileIn);
		//count2 = splitPoints.size();

		auto minX = *std::min_element(splitPoints.begin(), splitPoints.end(), [](auto lhs, auto rhs){
			return lhs.first < rhs.first;
		});

		auto minY = *std::min_element(splitPoints.begin(), splitPoints.end(), [](auto lhs1, auto rhs1){
			return lhs1.second < rhs1.second;
		});
		
		auto maxX = *std::max_element(splitPoints.begin(), splitPoints.end(), [](auto lhs2, auto rhs2){
			return lhs2.first < rhs2.first;
		});

		auto maxY = *std::max_element(splitPoints.begin(), splitPoints.end(), [](auto lhs3, auto rhs3){
			return lhs3.second < rhs3.second;
		});

		*xMin = minX.first;
		*xMax = maxX.first;
		*yMin = minY.second;
		*yMax = maxY.second;

	}

	while(window.isOpen()){
		if(cl.getElapsedTime().asMilliseconds() > 10){
		std::stack<int> convexHull;
		sf::RectangleShape rectangle;

		if(inFName != "drawmode"){
			populateGrid(count, *xMin, *xMax, *yMin, *yMax, rectangle, splitPoints);
		}
		//close the window if the window close button is pressed
		sf::Event event;
		while (window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				sf::Texture texture;
				texture.create(window.getSize().x, window.getSize().y);
				texture.update(window);
				if (texture.copyToImage().saveToFile(filename))
				{
					std::cout << "screenshot saved to " << filename << std::endl;
				}
				window.close();
			}
			else if(event.type == sf::Event::MouseButtonPressed){
				sf::RectangleShape *shape = new sf::RectangleShape(sf::Vector2f(5,5));
				shape->setPosition(event.mouseButton.x,event.mouseButton.y);
				shape->setFillColor(sf::Color(100, 250, 50));
				points->push_back(*shape);
             }
			else if (event.type == sf::Event::TextEntered){
				if(event.text.unicode <= 122 && event.text.unicode >= 65){
					sf::String newText = text.getString();
					newText += event.text.unicode;
					
					if(newText.getSize() == 2 && count4 < 1){
						newText.erase(0);
					}
					count4++;
					text.setString(newText);
				}
            }
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)){
				sf::String emptyText = text.getString();
				emptyText.clear();
				text.setString(emptyText);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
				std::string newFile = text.getString();
				points->clear();
				splitPoints.clear();
				fileIn.clear();
				window.close();
				generateOutput(newFile);
			}

		}
	
		//if the vector of points is full, the graham scan algorithm will be used 
		if(points->size() >= 3){

			convexHull = grahamScan();
			convex.setPointCount(convexHull.size());
			int pointCount = 0;

			while(!convexHull.empty()){

				(*points)[convexHull.top()].setFillColor(sf::Color(67,94,82));
				sf::Vector2f vertices = (*points)[convexHull.top()].getPosition();
				vertices.y += 3.5;
				vertices.x += 3.5;
				convex.setPoint(pointCount, sf::Vector2f(vertices));
				convexHull.pop();
				pointCount++;
			}
		}
		//clear the window each time around the loop
		window.clear(sf::Color(221,199,160));

		//print all the points on the screen
		for(int i = 0; i < points->size(); i++){
			window.draw((*points)[i]);
		}

        window.draw(text);
		window.draw(trackID);
		//draw the lines between the points
		if(points->size()>2){
			window.draw(convex);
		}

		//window.draw(shape);
		window.display();
		count++;
		cl.restart();
		}
	}
		
}

std::vector<double> HullGenerator::readFile(std::string inFile){
	std::ifstream file(inFile);
	std::string str;
	std::vector<double> line;

	while (std::getline(file, str)) {

		std::istringstream ss(str);

		double token;
		while(ss >> token){
			line.push_back(token);

		}
	}
	return line;		
}

std::vector<std::pair<double, double>> HullGenerator::splitInput(std::vector<double> pointInput){
	double xPos;
	double yPos;
	double scale = 10;
	if(pointInput[0] > 1000){scale = 1000;}
	if(pointInput[0] > 1000000){scale = 1000000;}
	std::pair<double,double> tempPoints;
	std::vector<std::pair<double,double>> splitPoints;
	for(int i = 0; i < pointInput.size(); i++){
		if(!(i%2)){
			xPos = pointInput[i]/scale;	
		}
		else{
			yPos = pointInput[i];
			tempPoints.first = xPos;
			tempPoints.second = yPos;
			//xPos *= 100;
			splitPoints.push_back(tempPoints);
		}
	}
	return splitPoints;
}

void HullGenerator::populateGrid(int count, double xMin, double xMax, double yMin, double yMax, sf::RectangleShape rectangle, std::vector<std::pair<double,double>> pointInput){
	//std::vector<double> fileIn = readFile("points.txt");
	double xPos;
	double yPos;

	if(count < pointInput.size()){
		xPos = pointInput[count].first;
		yPos = pointInput[count].second;

		float xVelocity;
		double xMinimum = pointInput[xMin].first;

		double yMinimum = pointInput[yMin].second;
		double bufferX = xMax-xMinimum;
		double bufferY = yMax-yMinimum;


		double xNorm = (800-100)*((xPos-xMin)/(xMax-xMin))+100;
		double yNorm = (800-100)*((yPos-yMin)/(yMax-yMin))+100;
	
		rectangle.setSize(sf::Vector2f(7,7));
		sf::Vector2f rectanglePosition(xNorm,yNorm);
	
		rectangle.setPosition(sf::Vector2f(rectanglePosition));
		//rectangle.setPosition(sf::Vector2f(xNorm, yNorm));
		points->push_back(rectangle);
	}
}

// Here we have an O(n) function which will return the index at which the lowest
// point resides in the vector
int HullGenerator::determineLowest(){
	int index = 0;
	int lowest = 0;

	for(int i = 0; i < points->size(); i++){
		sf::Vector2f position = (*points)[i].getPosition();
		if(position.y > lowest){
			index = i;
			lowest = position.y;
		}
	}
	return index;
}

//this function can be used to determine how close a point is to a given index
int HullGenerator::determineClose(int index){
	int newIndex = 0;
	int closest = 25000;
	int distance;
	sf::Vector2f currPos = (*points)[index].getPosition();
	sf::Vector2f nPos;
	for(int i = 0; i < points->size(); i++){
		if(i != index && (*points)[i].getFillColor() == sf::Color::White){
			nPos = (*points)[i].getPosition();
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
	sf::Vector2f originPos = (*points)[origin].getPosition();
	sf::Vector2f pointPos = (*points)[index].getPosition();
	distance = std::sqrt(std::pow(pointPos.x-originPos.x,2)+std::pow(pointPos.y-originPos.y,2));
	return distance;

}

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
	
	double vecOneX = (*points)[newIndex].getPosition().x - (*points)[index].getPosition().x;
	double vecOneY = (*points)[newIndex].getPosition().y - (*points)[index].getPosition().y;
	double vecTwoX = (*points)[newestIndex].getPosition().x - (*points)[newIndex].getPosition().x;
	double vecTwoY = (*points)[newestIndex].getPosition().y - (*points)[newIndex].getPosition().y;
	double det = vecOneX*vecTwoY - vecOneY*vecTwoX;
	//std::cout crossProduct;
	//if(det == 0){ return 0;}
	return det;

}
//this function sorts and colors the points on the grid
std::vector<int> HullGenerator::sortByPolarAngle(int index){
	std::vector<double> angles;
	std::vector<int> indices(points->size());
	double polarAngle;
	double pointX;
	double pointY;
	double xLen;
	double yLen;
	double originX = (*points)[index].getPosition().x;
	double originY = (*points)[index].getPosition().y;
	for(int i = 0; i < points->size(); i++){
		if(i != index){
			pointX = (*points)[i].getPosition().x;
			pointY = (*points)[i].getPosition().y;
			xLen = originX - pointX;
			yLen = originY - pointY;
			polarAngle = (std::atan2(yLen,xLen)*(180/3.1415));
			(*points)[i].setFillColor(sf::Color(153,122,143));
		}
		else{
			polarAngle = 0;
		}
		angles.push_back(polarAngle);
	}

	//you may be wondering why an std::sort is used here instead of a quicksort and the
	//answer is I thought it would be easier to implement the lamba and the 20% or so 
	//slowdown is approximately meaningless to me because SFML is so darn slow (on purpose)
	std::iota(indices.begin(), indices.end(), 0);
	std::sort(indices.begin(), indices.end(), 
		   [&](double A, double B) -> bool {
			   return angles[A] > angles[B];
			});

	return indices;
}

//this function actually computes which points are in the convex hull via the graham scan algorithm
std::stack<int> HullGenerator::grahamScan(){
	//we need the lowest point on the entire grid
	int anchorIndex = determineLowest();
	//the points are then sorted by polar angle
	std::vector<int> sortedData = sortByPolarAngle(anchorIndex);
	//this temp variable will be necessary later when we pop the top of the stack containing the 
	//points on the hull
	int tmp;
	
	//we'll need this shortly
	int tempIndex = sortedData[sortedData.size()-1];
	
	//as in now...this makes sure that the origin point gets wrapped around
	//getting this right was the hardest part of the actual implementation of the 
	//algorithm itself
	sortedData.insert(sortedData.begin(), 1, tempIndex);
	int sizeData = sortedData.size();

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
	//int tempIndex = sortedData[sortedData.size()-1];
	
	sortedData.insert(sortedData.begin(), 1, tempIndex);

	std::stack<int> hull;
	hull.push(sortedData[(sizeData-1)]);
	hull.push(sortedData[0]);
	hull.push(sortedData[1]);
	if(isLeftTurn(sortedData[0],sortedData[1],sortedData[2]) == 1){
		tmp = hull.top();
		hull.pop();
		hull.pop();
		hull.push(tmp);
	}

	for(int i = 0; i < sortedData.size(); i++){
		while(hull.size()>2 && isLeftTurn(sortedData[i],nextToTop(hull), hull.top()) == 1){
			(*points)[sortedData[i]].setFillColor(sf::Color(145,86,104));
			hull.pop();
		}
		if(isLeftTurn(sortedData[i],nextToTop(hull), hull.top()) == 2){
			hull.push(sortedData[i]);
		}
		
	}
	return hull;
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

