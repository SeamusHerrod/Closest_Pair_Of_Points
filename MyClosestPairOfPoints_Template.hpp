/**
 * @file MyCloestPairOfPoints_Template.h
 * @author Seamus Herrod (seamusmherrod@ku.edu)
 * @brief algorithm for finding the closest pair of points on a 2D plane 
 * @version 0.1
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _MY_CLOSEST_PAIR_OF_POINTS_TEMPLATE_HPP_
#define _MY_CLOSEST_PAIR_OF_POINTS_TEMPLATE_HPP_

#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <algorithm>

/**
 * @brief a struct that will represent a single point on the plane
 * 
 * 
 */
typedef 
    struct 
    {
        unsigned int ID;    // the ID of the point
        float x;              // the x-coordinate of the point
        float y;              // the y-coordinate of the point
    }
PointType;

void printPoints(std::vector<PointType> points){
  for (auto point : points){
    std::cout << "ID: " << point.ID << " x: " << point.x << " y: " << point.y << std::endl;
  }
}

void printPoint(PointType p){
  std::cout << "ID: " << p.ID << " x: " << p.x << " y: " << p.y << "\n";
}

/*------------------------------------------------------------------------------
  dist : find the distance between two points 
    p1 : first point 
    p2 : second point
------------------------------------------------------------------------------*/
float dist(const PointType & p1, const PointType & p2){
  return sqrt(((p2.x - p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y)));
}

/*------------------------------------------------------------------------------
  BruteMinDist : find the closest pair of points from a set of 3 or less points in a 2D plane 
    points: the set of points 
    p1: the first point of the closest pair 
    p2: the second point of the closest pair 

    returns the distance betwen the two points (round to 3-digit precision)
------------------------------------------------------------------------------*/
float BruteMinDist(const std::vector<PointType> & points, PointType & p1, PointType & p2){
  float minDist = FLT_MAX;
  for (int i = 0; i < points.size(); i++ ){
    for ( int j = i+1; j < points.size(); j++ ){
      float cur_dist = dist(points[i], points[j]);
      if (cur_dist <= minDist){
        minDist = cur_dist;
        p1 = points[j];
        p2 = points[i];
      }
    }
  }
  // Round to 3 decimal places

  return minDist;
}

/*------------------------------------------------------------------------------
  minStripDist : compute the closest pair in the strip vector 
------------------------------------------------------------------------------*/
float minStripDist(std::vector<PointType> strip, float delta, PointType & p1, PointType & p2){
  // remember that strip is already sorted by y coordinate 

  for ( int i = 0; i < strip.size(); i++){
    for (int j = i+1; j < strip.size() && ((strip[j].y - strip[i].y) <= delta); j++){
      float curDist = dist(strip[i], strip[j]);
      if (curDist <= delta){
        delta = curDist;
        p1 = strip[j];
        p2 = strip[i];
      }
    }
  }

  return delta;
}
/*------------------------------------------------------------------------------
  ClosestPairRec : recursive function that divides problem into subproblems and computes the min distance pair 
------------------------------------------------------------------------------*/
float ClosestPairRec(std::vector<PointType> & xSorted, std::vector<PointType> & ySorted, PointType & p1, PointType & p2){
  // 1. if the number of points in the vector is < 3, brute force 
  if (xSorted.size() <= 3){
    return BruteMinDist(xSorted, p1, p2);
  }
  // 2. divide xSorted into subproblems, lowerHalf and upperHalf and compute subproblem 
  size_t midIdx = (xSorted.size() / 2);
  std::vector<PointType> lowerHalfXSorted(xSorted.begin(), xSorted.begin() + midIdx);
  std::vector<PointType> upperHalfXSorted(xSorted.begin()+ midIdx + 1, xSorted.end());
std::vector<PointType> halfYSorted;
halfYSorted.reserve(ySorted.size() / 2);

  // Fill and use halfYSorted for the lower half
  for (const auto &point : ySorted){
    if (point.x <= xSorted[midIdx].x){
      halfYSorted.push_back(point);
    }
  }
  PointType lp1, lp2;
  float minLowerHalf = ClosestPairRec(lowerHalfXSorted, halfYSorted, lp1, lp2);

  // Clear and reuse halfYSorted for the upper half
  halfYSorted.clear();
  for (const auto &point : ySorted){
    if (point.x > xSorted[midIdx].x){
      halfYSorted.push_back(point);
    }
  }
  PointType rp1, rp2;
  float minUpperHalf = ClosestPairRec(upperHalfXSorted, halfYSorted, rp1, rp2);

  if (minLowerHalf < minUpperHalf){
    p1 = lp2;
    p2 = lp1;
  }
  else{
    p1 = rp2;
    p2 = rp1;
  }

  float delta = std::min(minLowerHalf, minUpperHalf);



  // 3. construct a strip vector 
  std::vector<PointType> strip;
  for (const auto &point : ySorted){
    if (abs(point.x - xSorted[midIdx].x) <= delta){
      strip.push_back(point);
    }
  }
  // 4. compute closest minimum dist in the strip 
  PointType stripP1, stripP2;
  float minStrip = minStripDist(strip, delta, stripP1, stripP2);
  
  //float minStripDelta = std::min(delta, minStrip);
  if (minStrip < delta){
    p1 = stripP1;
    p2 = stripP2;
    delta = minStrip;
  }
  return delta;

}

/*------------------------------------------------------------------------------
    ClosestPairOfPoints: find the closest pair of points from a set of points in a 2D plane 
    
        points: the set of points
        p1: the first point of the closest pair of points; should have a smaller ID
        p2: the second point of the closest pair of points; should have a larger ID
        
        returns the distance between the two points (round to 3-digit precision)
------------------------------------------------------------------------------*/
/**
 * @brief find the closest pair of points given a vector of point IDs, after execution, p1 and p2 will hold the closest points
 * 
 * @param points vector of PointType structs 
 * @param p1 PointType that will hold one of the closest points 
 * @param p2 PointType that will hold the other of the closest 2 points 
 * @return float the distance between the closest points, p1 and p2
 */
float ClosestPairOfPoints
(
    const std::vector<PointType> & points,
    PointType & p1,
    PointType & p2
)
{
  /*------ CODE BEGINS ------*/
  // sort the passed points by x and y coordinates, then call recursive function to compute the closest pair of points 
  std::vector<PointType> xSorted = points;
  std::vector<PointType> ySorted = points;
  //std::cout << "sorted by x coordinate: " << std::endl;
  std::sort(xSorted.begin(), xSorted.end(), [](const PointType &a, const PointType &b) {
        return a.x < b.x;
  });
  //printPoints(xSorted);
  //std::cout << "sorted by y coordinate: " << std::endl;
  std::sort(ySorted.begin(), ySorted.end(), [](const PointType &a, const PointType &b) {
        return a.y < b.y;
  });  
  float min = ClosestPairRec(xSorted, ySorted, p1, p2);
  if (p2.ID <= p1.ID){
    std::swap(p1, p2);
  }
  return roundf(min * 1000) / 1000;

  /*------ CODE ENDS ------*/
}



#endif
