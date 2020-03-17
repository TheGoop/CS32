#include "provided.h"
#include <list>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
using namespace std;

namespace std {
/* implement hash function so we can put GridLocation into an unordered_set */
template <> struct hash<GeoCoord> {
  typedef GeoCoord argument_type;
  typedef std::size_t result_type;
  std::size_t operator()(const GeoCoord& gc) const noexcept
    {
    return std::hash<string>()(gc.latitudeText + gc.longitudeText);
  }
};
}


class PointToPointRouterImpl
{
public:
    PointToPointRouterImpl(const StreetMap* sm);
    ~PointToPointRouterImpl();
    DeliveryResult generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const;

private:
    const StreetMap* m_map;
};

PointToPointRouterImpl::PointToPointRouterImpl(const StreetMap* sm)
{
    m_map = sm;
}

PointToPointRouterImpl::~PointToPointRouterImpl()
{
    
}



//size_t GeoCoord_hash( const GeoCoord & gc )
//{
//    return std::hash<string>()(gc.latitudeText + gc.longitudeText);
//}

vector<GeoCoord> reconstruct_path(GeoCoord start, GeoCoord end, unordered_map<GeoCoord, GeoCoord> came_from)
{
    std::vector<GeoCoord> path;
    GeoCoord curr = end;
    while( curr != start)
    {
        path.push_back(curr);
        curr = came_from[curr];;
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}




DeliveryResult PointToPointRouterImpl::generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const
{
    //check for bad coord
    std::vector<StreetSegment> test;
    if (!m_map->getSegmentsThatStartWith(start, test))
    {
        return BAD_COORD;
    }
    if (!m_map->getSegmentsThatStartWith(end, test))
    {
        return BAD_COORD;
    }
    //if start point is same as end point, nothing to be done
    bool found = false;
    if (start == end)
    {
        found = true;
        totalDistanceTravelled = 0;
        route.clear();
        return DELIVERY_SUCCESS;
    }
    
    unordered_map<GeoCoord, GeoCoord> came_from;
    unordered_map<GeoCoord, double> cost_so_far;
    
    unordered_set<GeoCoord> visited;
    
    priority_queue< pair<double, GeoCoord>, vector<pair<double, GeoCoord>>,  std::greater<pair<double, GeoCoord>>  > frontier;
    
    frontier.emplace(distanceEarthMiles(start, end), start);
    visited.insert(start);
    
    came_from[start] = start;
    cost_so_far[start] = 0;
    
    GeoCoord curr;
    while (!frontier.empty())
    {
        curr = frontier.top().second;
        frontier.pop();
        visited.erase(curr);
        
        if (curr == end)
        {
            found = true;
            break;
        }
        vector<StreetSegment> segs;
        m_map->getSegmentsThatStartWith(curr, segs);
        for (int i = 0; i < segs.size(); i++)
        {
            GeoCoord nxt = segs[i].end;
            double newCost = cost_so_far[curr] + distanceEarthMiles(curr, nxt);
            if (cost_so_far.find(nxt) == cost_so_far.end() || newCost < cost_so_far[nxt])
            {
                cost_so_far[nxt] = newCost;
                if (visited.find(nxt) == visited.end())
                {
                    double priority = newCost + distanceEarthMiles(nxt, end);//(std::abs(nxt.latitude - end.latitude) + std::abs(nxt.longitude - end.longitude));
                    frontier.emplace(priority, nxt);
                    visited.insert(nxt);
                }
                came_from[nxt] = curr;
                
            }
        }
    }
    
    
    if (found)
    {
        vector<GeoCoord> pathGeoCoord = reconstruct_path(start, end, came_from);
        for (int i = 0; i < pathGeoCoord.size() - 1; i++)
        {
            GeoCoord startPoint = pathGeoCoord[i];
            GeoCoord nextPoint = pathGeoCoord[i+1];
            std::vector<StreetSegment> segs;
            m_map->getSegmentsThatStartWith(startPoint, segs);
            for (int j = 0; j < segs.size(); j++)
            {
                
                if (segs[j].end == nextPoint)
                {
                    route.push_back(segs[j]);
                    totalDistanceTravelled += distanceEarthMiles(segs[j].start, segs[j].end);
                    break;
                }
            }
        }
        
        return DELIVERY_SUCCESS;
    }
    
    return NO_ROUTE;  // Delete this line and implement this function correctly
}

//******************** PointToPointRouter functions ***************************

// These functions simply delegate to PointToPointRouterImpl's functions.
// You probably don't want to change any of this code.

PointToPointRouter::PointToPointRouter(const StreetMap* sm)
{
    m_impl = new PointToPointRouterImpl(sm);
}

PointToPointRouter::~PointToPointRouter()
{
    delete m_impl;
}

DeliveryResult PointToPointRouter::generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const
{
    return m_impl->generatePointToPointRoute(start, end, route, totalDistanceTravelled);
}


//totalDistanceTravelled = 0;
//for (auto seg = route.begin(); seg != route.end(); seg++)
//{
//    auto nextSeg = seg;
//    nextSeg++;
//    totalDistanceTravelled += distanceEarthMiles(seg->start, seg->end);
//    if (nextSeg != route.end())
//    {
//        totalDistanceTravelled += distanceEarthMiles(seg->end, nextSeg->start);
//    }
//}
