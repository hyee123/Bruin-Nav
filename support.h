//
//  support.hpp
//  CS_32_Proj4_MYMAP
//
//  Created by harry yee on 3/13/17.
//  Copyright © 2017 harry yee. All rights reserved.
//

#ifndef support_hpp
#define support_hpp

#include <stdio.h>
#include "provided.h"

//overide si i can use geoCoords as keys
bool operator==( const GeoCoord& lhs, const GeoCoord& rhs);
bool operator<( const GeoCoord& lhs,const  GeoCoord& rhs);
bool operator>( const GeoCoord& lhs,  const GeoCoord& rhs);
struct StreetNode//nodes used to track for future navsegments
{
    StreetNode(StreetNode* par, StreetSegment s, GeoCoord begin, GeoCoord destination, GeoCoord origin);
    StreetNode(){}
    ~StreetNode(){}
    StreetSegment s;
    GeoCoord begin;
    GeoCoord endsn;
    bool isRight;
    bool arrived = false;
    StreetNode *parent;
    double value;
    GeoCoord dest;
    GeoCoord org;
    double length = 0;
    double traveled = 0;
};
class Comparator // comparing pointers for keys
{
    public:
        bool operator()( StreetNode* lhs, StreetNode* rhs)
        {
            return lhs->value > rhs->value;
        }
};





//comparing geosegments to use as keys
bool operator==(const GeoSegment& lhs, const GeoSegment& rhs);
bool operator<(const GeoSegment& lhs, const GeoSegment& rhs);
bool operator>(const GeoSegment& lhs, const GeoSegment& rhs);

std::string angleToHeading(double angle);
std::string angleToTurn(double angle);








#endif /* support_hpp */
