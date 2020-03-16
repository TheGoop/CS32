#include "provided.h"
#include "ExpandableHashMap.h"
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
using namespace std;

unsigned int hasher(const GeoCoord& g)
{
    return std::hash<string>()(g.latitudeText + g.longitudeText);
}


unsigned int hasher(const string &name)
{
   int i, total=0;

   for (i=0;i<name.length(); i++)
    total = total + (i+1) * name[i];

   return(total);
}


class StreetMapImpl
{
public:
    StreetMapImpl();
    ~StreetMapImpl();
    bool load(string mapFile);
    bool getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const;
    
private:
    ExpandableHashMap<GeoCoord, vector<StreetSegment>> m_map;
    ExpandableHashMap<GeoCoord, vector<StreetSegment>> m_reversedMap;
};

StreetMapImpl::StreetMapImpl()
{

}

StreetMapImpl::~StreetMapImpl()
{
    m_map.reset();
}



bool StreetMapImpl::load(string mapFile)
{
    //mapFile = "/Users/akshay/projects/helloworld/CS32/GooberEats/GooberEats/mapdata.txt";

    ifstream infile(mapFile);
    //get the name at the first line
    
    string name;
    while( std::getline(infile, name)  )
    {
//        string name;
//        std::getline(infile, name);
//        if ( ! infile)
//        {
//            cerr << "End of file when trying to read a string" << endl;
//            return false;
//        }
        
        //get the number of following lines on second line
        
        int n;
        infile >> n;
        infile.ignore(10000, '\n');
        //get the following lines and store in array
        //string lines[n];
        vector<string> lines;
        for ( int i = 0; i < n; i++)
        {
            string line;
            if (!getline(infile, line))
            {
                return false;
            }
            lines.push_back(line);
        }
        string firstCoord;
        string secondCoord;
        for (int i = 0; i < n; i++)
        {
            //get the first and second set of coords on line
            int ind = lines[i].find(' ', lines[i].find(' ') + 1);
            firstCoord = (lines[i]).substr(0, ind);
            secondCoord = (lines[i]).substr(ind + 1);
            
            //get first set of geocoords
            ind = firstCoord.find(' ');
            int colon = firstCoord.find(':');
            colon -= (ind + 1);
            string x = firstCoord.substr(0, ind);
            string y = firstCoord.substr(ind+1);
            
            
            GeoCoord f(x, y);
            
            //get second set of geocoords
            ind = secondCoord.find(' ');
            colon = secondCoord.find(':');
            colon -= (ind + 1);
            x = secondCoord.substr(0, ind);
            y = secondCoord.substr(ind+1);
            
            GeoCoord s(x, y);
            
            //add forwards and reversed segments to map
            
            StreetSegment seg(f,s,name);
            StreetSegment revSeg(s, f, name);
            
            if (m_map.find(f) == nullptr)
            {
                vector<StreetSegment> newVec;
                newVec.push_back(seg);
                m_map.associate(f, newVec);
            }
            else
            {
                vector<StreetSegment> *currVec = m_map.find(f);
                vector<StreetSegment> copyVec = *currVec;
                copyVec.push_back(seg);
                m_map.associate(f, copyVec);
            }
            

            if (m_reversedMap.find(s) == nullptr)
            {
                vector<StreetSegment> newVec;
                newVec.push_back(revSeg);
                m_reversedMap.associate(s, newVec);
            }
            else
            {
                vector<StreetSegment> *currVec = m_reversedMap.find(s);
                vector<StreetSegment> copyVec = *currVec;
                copyVec.push_back(revSeg);
                m_reversedMap.associate(s, copyVec);
            }
//if (name == "access road for water tank")
//{
//
//}
        }
    }
    
    return true;  // Delete this line and implement this function correctly
}

bool StreetMapImpl::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
    bool found = false;
    if (m_map.find(gc))
    {
        segs.insert(segs.begin(), m_map.find(gc)->begin(), m_map.find(gc)->end());
        found = true;
    }
    
    if(m_reversedMap.find(gc))
    {
        segs.insert(segs.begin(), m_reversedMap.find(gc)->begin(), m_reversedMap.find(gc)->end());
        found = true;
    }
    return found;
}

//******************** StreetMap functions ************************************

// These functions simply delegate to StreetMapImpl's functions.
// You probably don't want to change any of this code.

StreetMap::StreetMap()
{
    m_impl = new StreetMapImpl;
}

StreetMap::~StreetMap()
{
    
    delete m_impl;
}

bool StreetMap::load(string mapFile)
{
    return m_impl->load(mapFile);
}

bool StreetMap::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
   return m_impl->getSegmentsThatStartWith(gc, segs);
}
