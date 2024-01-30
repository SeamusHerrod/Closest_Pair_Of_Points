/**
 * @file MainTest.cpp
 * @author Seamus Herrod (seamusmherrod@ku.edu)
 * @brief MainTest for MyClosestPairOfPoints_Template, handles input file parsing and calls algorithm on the point vector
 * @version 0.1
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "MyClosestPairOfPoints_Template.hpp"
#include <fstream>
void loadPoints(const char* fname, std::vector<PointType>& points)
{
  std::ifstream fin(fname);
  if (!fin.is_open())	    // fail to open
  {
      std::cout << "Cannot open the test instance file " << fname << ". Abort." << std::endl;
      return;
  }
  else
  {
    while(true)
    {
      unsigned int id; float x, y;
      fin >> id; if(fin.eof()) break;
      fin >> x; if(fin.eof()) break;
      fin >> y; if(fin.eof()) break;
      points.push_back({id, x, y});
    }
  }
  fin.close();
}



int main(int argc, char* argv[]) {
  /*---------------------------
  MAINTEST CODE
  ---------------------------*/
  std::vector<PointType> points;
  loadPoints(argv[1], points);
  PointType ans1{0,0,0}, ans2{0,0,0};
  std::cout << ClosestPairOfPoints(points, ans1, ans2) << " ";
  std::cout << ans1.ID << ": (" << ans1.x << ", " << ans1.y << "), "
            << ans2.ID << ": (" << ans2.x << ", " << ans2.y << ")\n";
  
  /*--------------------------
  MY TEST CODE
  std::vector<PointType> points;
  loadPoints(argv[1], points);
  //printPoints(points);
  /*--------------------------
  TEST CODE FOR DIST FUNCTION
  
  std::cout << "points[0] = " << points[0].ID << " , x: " << points[0].x << " , y: " << points[0].y << std::endl;
  std::cout << "points[0] = " << points[1].ID << " , x: " << points[1].x << " , y: " << points[1].y << std::endl;
	std::cout << "distance between: " 
            << points[0].ID << ", " 
            << points[1].ID << ": " 
            << dist(points[0], points[1]) << std::endl;


  /*--------------------------
  TEST CODE FOR BRUTE MIN DIST 
  PointType p1; 
  PointType p2;
  std::vector<PointType> threePoints;
  threePoints.push_back(points[0]);
  threePoints.push_back(points[1]);
  threePoints.push_back(points[2]);
  float bruteMin = ClosestPairOfPoints(threePoints, p1, p2);
  std::cout << "points[0] = " << points[0].ID << " , x: " << points[0].x << " , y: " << points[0].y << std::endl;
  std::cout << "points[1] = " << points[1].ID << " , x: " << points[1].x << " , y: " << points[1].y << std::endl;
  std::cout << "points[2] = " << points[2].ID << " , x: " << points[2].x << " , y: " << points[2].y << std::endl;
	std::cout << "min distance between: " 
            << p1.ID << ", " 
            << p2.ID << ": " 
            << bruteMin << std::endl;


  PointType p1;
  PointType p2;
  float min = ClosestPairOfPoints(points, p1, p2);
  std::cout << min << " " << p1.ID << "(" << p1.x << ", " << p2.x << "), " << p2.ID << "(" << p1.x << ", " << p2.x << ")" << "\n";
  --------------------------*/
  
  return 0;
}
