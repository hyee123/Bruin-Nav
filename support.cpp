//
//  support.cpp
//  CS_32_Proj4_MYMAP
//
//  Created by harry yee on 3/13/17.
//  Copyright © 2017 harry yee. All rights reserved.
//

#include "support.h"

bool operator==( const GeoCoord& lhs, const GeoCoord& rhs)
{
    return (lhs.latitude == rhs.latitude) && (lhs.longitude == rhs.longitude);
}
bool operator<( const GeoCoord& lhs,const  GeoCoord& rhs)
{
    return (lhs.latitude < rhs.latitude);
}
bool operator>( const GeoCoord& lhs,  const GeoCoord& rhs)
{
    return (lhs.latitude > rhs.latitude);
}
bool operator==( const StreetNode& lhs, const StreetNode& rhs)
{
    return (lhs.value == rhs.value);
}
bool operator<( const StreetNode& lhs,const  StreetNode& rhs)
{
    return (lhs.value < rhs.value);
}
bool operator>( const StreetNode& lhs,  const StreetNode& rhs)
{
    return (lhs.value > rhs.value);
}

StreetNode::StreetNode(StreetNode* par, StreetSegment sa, GeoCoord beg, GeoCoord destination, GeoCoord origin)
{
    s = sa;
    length = distanceEarthMiles(s.segment.start, s.segment.end);
    if(par != nullptr)
    {
        traveled = length + par->traveled;
    }
    begin = beg;
    dest = destination;
    org = origin;
    parent = par;
    if(s.segment.start == begin)
    {
        isRight = true;
        endsn = s.segment.end;
    }else
    {
        isRight = false;
        endsn = s.segment.start;
    }
    
    if(isRight)
        value =(distanceEarthMiles(s.segment.end, destination)) + traveled;
    else
        value = (distanceEarthMiles(s.segment.start, destination))  + traveled;
    
    for(int i = 0; i <s.attractions.size(); i++)
    {
        if(s.attractions[i].geocoordinates == destination)
        {
            arrived = true;
            break;
        }
    }
    
 
    
}

bool operator==(const GeoSegment& lhs, const GeoSegment& rhs)
{
    return (lhs.start == rhs.start) && (lhs.end == rhs.end);
}
bool operator<(const GeoSegment& lhs, const GeoSegment& rhs)
{
    return (lhs.start < rhs.start);
}
bool operator>(const GeoSegment& lhs, const GeoSegment& rhs)
{
    return (lhs.start > rhs.start);
}
std::string angleToHeading(double angle)
{
    if(angle >= 0 && angle <=22.5)
        return "east";
    if(angle > 22.5 && angle <=67.5)
        return "northeast";
    if(angle > 67.5 && angle <=112.5)
        return "north";
    if(angle > 112.5 && angle <=157.5)
        return "northwest";
    if(angle > 157.5 && angle <=202.5)
        return "west";
    if(angle > 202.5 && angle <= 247.5)
        return "southeast";
    if(angle > 247.5 && angle <= 292.5)
        return "south";
    if(angle > 292.5 && angle <= 337.5)
        return "southeast";
    if(angle > 337.5 && angle <= 360)
        return "east";
    return"";
}
std::string angleToTurn(double angle)
{
    if(angle >= 0 && angle < 180)
        return "right";
    else return "left";
}
