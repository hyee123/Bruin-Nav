#include "provided.h"
#include "MyMap.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class MapLoaderImpl
{
public:
	MapLoaderImpl();
	~MapLoaderImpl();
	bool load(string mapFile);
	size_t getNumSegments() const;
	bool getSegment(size_t segNum, StreetSegment& seg) const;
private:
    vector<StreetSegment> holder;
    int i = 0;

};

MapLoaderImpl::MapLoaderImpl()
{
}

MapLoaderImpl::~MapLoaderImpl()
{
}

bool MapLoaderImpl::load(string mapFile)
{
	//return false;  // This compiles, but may not be correct
    std::string s;
    // getline returns infile; the while tests its success/failure state
    ifstream infile(mapFile);
    int step = 0;
   
    
    while (getline(infile, s))
    {
         int a = 0;
        if(step == 0)
        {
            holder.push_back(StreetSegment());
            holder[i].streetName = s;
            step++;
        }else if(step == 1)
        {
            bool noNum = true;
            int r =0;
            int startI;
            int lengthI = 0;
            int sp[8];
            for(int k =0; k<s.size();k++)
            {
                if((isdigit(s[k]) || s[k] == '-') && noNum == true)
                {
                    noNum = !noNum;
                    sp[r] = k;
                    r++;lengthI = 1;
                }else if((s[k] == ' ' || s[k] == ',') && noNum == false)
                {
                    sp[r] = lengthI;
                    lengthI = 0;
                    r++; noNum = !noNum;
                }else
                    lengthI++;
            }
            string slong,slat,elong,elat;
            slat = s.substr(sp[0],sp[1]);
            slong = s.substr(sp[2],sp[3]);
            elat = s.substr(sp[4],sp[5]);
            elong = s.substr(sp[6],s.size()-sp[6]);
            holder[i].segment.start = GeoCoord(slat,slong);
            holder[i].segment.end = GeoCoord(elat,elong);
            step++;
        }else if(step ==2)
        {
            int n = stoi(s);
            for(int j = 0; j <n; j++)
            {
                getline(infile,s);
            
                holder[i].attractions.push_back(Attraction());
                int st = s.find("|");
                bool noNum = false;
                int seStart = 0;
                int fiEnd;
                for(int v = st; v < s.size(); v++)
                {
                    if(noNum == false && (s[v] == ' ' || s[v] == ','))
                    {
                        noNum = true;
                        fiEnd = v;
                    }else if(noNum == true && (isdigit(s[v]) || s[v] == '-'))
                    {
                        seStart = v;
                        noNum = false;
                    }
                }
                holder[i].attractions[a].name = s.substr(0,st);
                holder[i].attractions[a].geocoordinates = GeoCoord(s.substr(st+1,seStart-(st +2)),s.substr(seStart,s.size()-seStart));
                a++;
            }
            i++;
            step =0;
        }
            
    }
    return true;
}

size_t MapLoaderImpl::getNumSegments() const
{
	//return 0; // This compiles, but may not be correct
    return i;
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
	//return false;  // This compiles, but may not be correct
    if(segNum < i)
    {
        seg = holder[segNum];
        return true;
    }
    return false;
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
	m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
	delete m_impl;
}

bool MapLoader::load(string mapFile)
{
	return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
	return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
   return m_impl->getSegment(segNum, seg);
}
