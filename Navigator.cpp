#include "provided.h"
#include "MyMap.h"
#include "support.h"
#include <string>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;
private:
    SegmentMapper segMapper;
    AttractionMapper attMapper;
    
};

NavigatorImpl::NavigatorImpl()
{
}

NavigatorImpl::~NavigatorImpl()
{
}

bool NavigatorImpl::loadMapData(string mapFile)
{
    MapLoader mpLoader;
    mpLoader.load(mapFile);
     attMapper.init(mpLoader);
    segMapper.init(mpLoader);
   
    return true;
}

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
	//start or intiaite the first segment
    StreetNode* head;
    GeoCoord startG,endG;
    StreetSegment startS;
    if(!attMapper.getGeoCoord(start, startG))//test to see if start point is valid
        return NAV_BAD_SOURCE;
    if(!attMapper.getGeoCoord(end, endG))//check to see if end is valid
        return NAV_BAD_DESTINATION;
    std::priority_queue<StreetNode*,vector<StreetNode*>,Comparator> queueLine;
    MyMap<GeoSegment,StreetNode*> closed;
    vector<StreetNode*> mem;// used to help with memory leak
    int times = 0;
    vector<StreetSegment>tracker(segMapper.getSegments(startG));
    head = new StreetNode(nullptr, tracker[0], tracker[0].segment.start, endG, startG);
    bool isFound =false;
    queueLine.push(head);
    closed.associate(head->s.segment, head);
    mem.push_back(head);
    StreetNode* goal = nullptr;
    //============================================
    while(queueLine.empty() == false && isFound == false)// loop till desitination is found
    {
        times++;
        StreetNode* m_top = queueLine.top();
        queueLine.pop();
        if(m_top->arrived == true)
        {
            isFound = true;
            goal = m_top;
            break;
        }
        else{
            vector<StreetSegment> temp;
            temp = segMapper.getSegments(m_top->endsn);
            for(int i = 0; i <temp.size(); i++)
            {
                if(closed.find(temp[i].segment) == nullptr)//is not on closed list can be added to queue and closed lists
                {
                    StreetNode* newGuy = new StreetNode(m_top, temp[i], m_top->endsn, m_top->dest,m_top->org);
                    queueLine.push(newGuy);
                    closed.associate(newGuy->s.segment, newGuy);
                    mem.push_back(newGuy);
                    isFound = newGuy->arrived;
                    if(isFound == true)
                    {
                        goal = newGuy;
                    }
                }
            }
            
        }
        
    }
    string before ="";
    vector<StreetNode*> tD;
    while (goal != nullptr)
    {
        tD.push_back(goal);
         goal = goal->parent;
    }
    
    //create NavSegments================================
    if(tD.size() == 1)
    {
        //make one segment from origin to destination
        return NAV_SUCCESS;
    }else if(tD.size() == 0)
    {
        return NAV_NO_ROUTE;
    }else
    {
       //create first segment from attaction to start of street
        GeoSegment f;
        f.start = startG;
        f.end = tD[tD.size()-1]->endsn;
        directions.push_back(NavSegment(angleToHeading(angleOfLine(f)),tD[tD.size()-1]->s.streetName, distanceEarthMiles(startG, f.end), f));
        
        //loop reverse through td and look ahead one to detect for turns
        string before = tD[tD.size()-1]->s.streetName;
        int count = 0;
        for(int j = tD.size()-2; j >= 1; j--)
        {
            GeoSegment pp;
            pp.start = tD[j]->begin;
            pp.end = tD[j]->endsn;
            if(before != tD[j]->s.streetName && before != "")//for turn semgents
            {
                //create turn thing for angle
                double an = angleBetween2Lines(pp,directions[count].m_geoSegment);
                directions.push_back(NavSegment(angleToTurn(an), tD[j]->s.streetName));
            }
            
            directions.push_back(NavSegment(angleToHeading(angleOfLine(pp)), tD[j]->s.streetName, tD[j]->length,pp));
            before = tD[j]->s.streetName;
            count++;
        }
        
        //make last one from street to attraction
        GeoSegment l;
        l.end = endG;
        l.start = tD[0]->begin;
        directions.push_back(NavSegment(angleToHeading(angleOfLine(l)),tD[0]->s.streetName, distanceEarthMiles(endG, l.start), l));
        
        
    }
    

        
    for(int v = 0; v < mem.size(); v++)
    {
       delete mem[v];
    }
        
        
        return NAV_SUCCESS;
}

//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}
