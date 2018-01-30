#include "provided.h"
#include "MyMap.h"
#include <iostream>
#include <string>
using namespace std;

class AttractionMapperImpl
{
public:
	AttractionMapperImpl();
	~AttractionMapperImpl();
	void init(const MapLoader& ml);
	bool getGeoCoord(string attraction, GeoCoord& gc) const;
private:
    MyMap<string, GeoCoord> AtMap;
};

AttractionMapperImpl::AttractionMapperImpl()
{
}

AttractionMapperImpl::~AttractionMapperImpl()
{
}

void AttractionMapperImpl::init(const MapLoader& ml)
{
    int size = ml.getNumSegments();
    StreetSegment temp;
    for(int i = 0; i < size; i++)
    {
        ml.getSegment(i, temp);
        if(temp.attractions.size() > 0)
        {
            for(int j = 0; j < temp.attractions.size();j++)
            {
                string input = "";
                for(int v = 0; v < temp.attractions[j].name.size(); v++)//change all names to lower case
                    input += tolower(temp.attractions[j].name[v]);
                AtMap.associate(input, temp.attractions[j].geocoordinates);// put in the map
            }
        }
    }
    
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const
{
	//return false;  // This compiles, but may not be correct
    string input = "";
    
    for(int i = 0; i <attraction.size(); i++)//change attraction to lower case
        input += tolower(attraction[i]);
    if(AtMap.find(input) == nullptr)
        return false;
    
    gc = *AtMap.find(input);
    return true;
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
	m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
	delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
	return m_impl->getGeoCoord(attraction, gc);
}
