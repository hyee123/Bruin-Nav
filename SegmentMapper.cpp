#include "provided.h"
#include "MyMap.h"
#include <vector>
using namespace std;

class SegmentMapperImpl
{
public:
	SegmentMapperImpl();
	~SegmentMapperImpl();
	void init(const MapLoader& ml);
	vector<StreetSegment> getSegments(const GeoCoord& gc) const;
private:
    MyMap<GeoCoord,vector<StreetSegment>>segMap;
    

};

SegmentMapperImpl::SegmentMapperImpl()
{
}

SegmentMapperImpl::~SegmentMapperImpl()
{
}

void SegmentMapperImpl::init(const MapLoader& ml)
{
     for(int i = 0; i < ml.getNumSegments(); i++)
     {
         vector<GeoCoord> allSpots;
         StreetSegment temp;
         ml.getSegment(i,temp);
         allSpots.push_back(temp.segment.start);
         allSpots.push_back(temp.segment.end);
         for(int j = 0; j <temp.attractions.size(); j++)// put all geocords from one segment into a vector
         {
             allSpots.push_back(temp.attractions[j].geocoordinates);
         }
     
         for(int k = 0; k < allSpots.size(); k++)//go through vector and insert if already there or create new spot in map
         {
     
             if(segMap.find(allSpots[k]) == nullptr)
             {
                 vector<StreetSegment> n;
                 n.push_back(temp);
                 segMap.associate(allSpots[k],n);
             }else
             {
                 segMap.find(allSpots[k])->push_back(temp);
             }
         }
     }
    
     
    
}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
	vector<StreetSegment> segments;
    
     segments = *segMap.find(gc);
    
	return segments;  // This compiles, but may not be correct
}

//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
	m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
	delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
	return m_impl->getSegments(gc);
}
