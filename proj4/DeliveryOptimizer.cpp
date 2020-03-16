#include "provided.h"
#include <vector>
using namespace std;

class DeliveryOptimizerImpl
{
public:
    DeliveryOptimizerImpl(const StreetMap* sm);
    ~DeliveryOptimizerImpl();
    void optimizeDeliveryOrder(
        const GeoCoord& depot,
        vector<DeliveryRequest>& deliveries,
        double& oldCrowDistance,
        double& newCrowDistance) const;
};

DeliveryOptimizerImpl::DeliveryOptimizerImpl(const StreetMap* sm)
{
}

DeliveryOptimizerImpl::~DeliveryOptimizerImpl()
{
}


int deliveryClosestToCurrentLocation(GeoCoord start, vector<DeliveryRequest> deliveries, vector<bool> visited)
{
    int smallestDist = -1;
    int smallestIndex = 0;
    for (int i = 0; i < deliveries.size(); i++)
    {
        double dist = distanceEarthMiles(start, deliveries[i].location);
        if (!visited[i])
        {
            if (smallestDist == -1 || smallestDist >= dist)
            {
                smallestIndex = i;
                smallestDist = dist;
            }
        }
    }
    return smallestIndex;
}

double crowDistance(GeoCoord depot, vector<DeliveryRequest> deliveries)
{
    int oldCrowDistance = 0;
    oldCrowDistance += distanceEarthMiles(depot, deliveries[0].location);
    for (int i = 1; i < deliveries.size(); i++)
    {
        oldCrowDistance += distanceEarthMiles(deliveries[i-1].location, deliveries[i].location);
    }
    oldCrowDistance += distanceEarthMiles(deliveries[deliveries.size()-1].location, depot);
    return oldCrowDistance;
}


void DeliveryOptimizerImpl::optimizeDeliveryOrder(
    const GeoCoord& depot,
    vector<DeliveryRequest>& deliveries,
    double& oldCrowDistance,
    double& newCrowDistance) const
{
    oldCrowDistance = 0;  // Delete these lines and implement this function correctly
    newCrowDistance = 0;
    
    if (!deliveries.empty())
    {
        
        oldCrowDistance = crowDistance(depot, deliveries);
        
        
        
        int size = deliveries.size();
        
        //create vector of completed deliveries
        vector<bool> visited;
        for (int i = 0; i < size; i++)
        {
            visited.push_back(false);
        }
        
        vector<DeliveryRequest> orderedVec;
        
        int closestIndex = deliveryClosestToCurrentLocation(depot, deliveries, visited);
        visited[closestIndex] = true;
        DeliveryRequest curr = deliveries[closestIndex];
        orderedVec.push_back(curr);
        
        for (int i = 0; i < size-1; i++)
        {
            closestIndex = deliveryClosestToCurrentLocation(curr.location, deliveries, visited);
            visited[closestIndex] = true;
            curr = deliveries[closestIndex];
            orderedVec.push_back(curr);
        }
        
        std::swap(deliveries, orderedVec);
        
        newCrowDistance = crowDistance(depot, deliveries); // added this
        
    }
}

//******************** DeliveryOptimizer functions ****************************

// These functions simply delegate to DeliveryOptimizerImpl's functions.
// You probably don't want to change any of this code.

DeliveryOptimizer::DeliveryOptimizer(const StreetMap* sm)
{
    m_impl = new DeliveryOptimizerImpl(sm);
}

DeliveryOptimizer::~DeliveryOptimizer()
{
    delete m_impl;
}

void DeliveryOptimizer::optimizeDeliveryOrder(
        const GeoCoord& depot,
        vector<DeliveryRequest>& deliveries,
        double& oldCrowDistance,
        double& newCrowDistance) const
{
    return m_impl->optimizeDeliveryOrder(depot, deliveries, oldCrowDistance, newCrowDistance);
}
