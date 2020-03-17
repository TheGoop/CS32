#include "provided.h"
#include <vector>
using namespace std;

class DeliveryPlannerImpl
{
public:
    DeliveryPlannerImpl(const StreetMap* sm);
    ~DeliveryPlannerImpl();
    DeliveryResult generateDeliveryPlan(
        const GeoCoord& depot,
        const vector<DeliveryRequest>& deliveries,
        vector<DeliveryCommand>& commands,
        double& totalDistanceTravelled) const;
private:
    void proceed();
    
    PointToPointRouter m_map;
    DeliveryOptimizer m_optimizer;
};

DeliveryPlannerImpl::DeliveryPlannerImpl(const StreetMap* sm)
: m_map(sm), m_optimizer(sm) // added this
{
}

DeliveryPlannerImpl::~DeliveryPlannerImpl()
{
}


string processAngle(double angle)
{
    if ( 0 <= angle && angle < 22.5)
    {
        return "east";
    }
    
    if (22.5 <= angle && angle < 67.5)
    {
        return "northeast";
    }
    
    if (67.5 <= angle && angle < 112.5)
    {
        return "north";
    }
    
    if (112.5 <= angle && angle < 157.5)
    {
        return "northwest";
    }
    if (157.5 <= angle && angle < 202.5)
    {
        return "west";
    }
    if (202.5 <= angle && angle < 247.5)
    {
        return "southwest";
    }
    
    if (247.5 <= angle && angle < 292.5)
    {
        return "south";
    }
    
    if (292.5 <= angle && angle < 337.5)
    {
        return "southeast";
    }
    else
    {
        return "east";
    }
    
}



DeliveryResult DeliveryPlannerImpl::generateDeliveryPlan(
    const GeoCoord& depot,
    const vector<DeliveryRequest>& deliveries,
    vector<DeliveryCommand>& commands,
    double& totalDistanceTravelled) const
{
    
    if (deliveries.empty())
    {
        commands.clear();
        return DELIVERY_SUCCESS;
    }
    
        commands.clear();
    
    
    // added this
    vector<DeliveryRequest> optimizedCopy = deliveries;
    double oldCrow;
    double newCrow;
    m_optimizer.optimizeDeliveryOrder(depot, optimizedCopy, oldCrow, newCrow);
    vector<DeliveryRequest> bestDelivery;
    if (newCrow <= oldCrow)
    {
        bestDelivery = optimizedCopy;
    }
    else
    {
        bestDelivery = deliveries;
    }
    totalDistanceTravelled = 0;
    //generate routes from depot to delivery, then back
    vector<list<StreetSegment>> routes;
    routes.resize(bestDelivery.size()+1);
    
    double t;
    if (m_map.generatePointToPointRoute(depot, bestDelivery[0].location, routes[0], t) == BAD_COORD)
    {
        return NO_ROUTE;
    }
    totalDistanceTravelled += t;
    t= 0;
    for (int i = 1; i < bestDelivery.size(); i++)
    {
        //generate distance and route from depot to location
        if (m_map.generatePointToPointRoute(bestDelivery[i-1].location, bestDelivery[i].location, routes[i], t) == BAD_COORD)
        {
            return NO_ROUTE;
        }
        totalDistanceTravelled += t;
    }
    t = 0;
    if (m_map.generatePointToPointRoute(bestDelivery[bestDelivery.size()-1].location, depot, routes[routes.size()-1], t) == BAD_COORD)
    {
        return NO_ROUTE;
    }
    totalDistanceTravelled += t;
    //totalDistanceTravelled += t;
    //now using the segments we have accumulated into routes, we must make directions
    //iterate through the trips
    bool isLastCMDProceed = false;
    bool isLastCMDTurn = false;
    string dir = "";
    string streetName = "";
    double dist = 0;
    for (int i = 0; i < routes.size(); i++)
    {
        dist = 0;
        streetName = "";
        dir = "";
        isLastCMDProceed = false;
        isLastCMDTurn = false;
        //iterate through a trips directions
        for (auto seg = routes[i].begin(); seg != routes[i].end(); seg++)
        {
            //next point
            auto nextSeg = seg;
            nextSeg++;

            //its a valid segment and not first segment after delivery/depot, and changing streets must turn
            if (nextSeg != routes[i].end() && seg != routes[i].begin() && seg->name != nextSeg->name)
            {
                //get turn angle
                double turnAngle = angleBetween2Lines(*seg, *nextSeg);

                //if left turn
                if (turnAngle >= 1 && turnAngle < 180)
                {
                    //if the last command was a proceed, must push the cmd before we can push a turn
                    if (isLastCMDProceed)
                    {
                        DeliveryCommand proceed;
                        proceed.initAsProceedCommand(dir, streetName, dist + distanceEarthMiles(seg->start, seg->end));
                        commands.push_back(proceed);
                    }
                    //if the last command was a turn, need to proceed to the next turn before turning again
                    if (isLastCMDTurn)
                    {
                        DeliveryCommand proceed;
                        proceed.initAsProceedCommand(processAngle(angleOfLine(*seg)), nextSeg->name, distanceEarthMiles(seg->start, nextSeg->start));
                        commands.push_back(proceed);
                    }

                    //add turn
                    DeliveryCommand rightTurn;
                    rightTurn.initAsTurnCommand("left", nextSeg->name);
                    commands.push_back(rightTurn);
                    isLastCMDProceed = false;
                    isLastCMDTurn = true;
                }

                //if right turn
                else if (turnAngle >= 180 && turnAngle <= 359)
                {
                    //if the last command was a proceed, must push the cmd before we can push a turn
                    if (isLastCMDProceed)
                    {
                        DeliveryCommand proceed;
                        proceed.initAsProceedCommand(dir, streetName, dist + distanceEarthMiles(seg->start, seg->end));
                        commands.push_back(proceed);
                    }
                    //if the last command was a turn, need to proceed to the next turn before turning again
                    if (isLastCMDTurn)
                    {
                        DeliveryCommand proceed;
                        proceed.initAsProceedCommand(processAngle(angleOfLine(*seg)), nextSeg->name, distanceEarthMiles(seg->start, nextSeg->start));
                        commands.push_back(proceed);
                    }

                    //add turn
                    DeliveryCommand leftTurn;
                    leftTurn.initAsTurnCommand("right", nextSeg->name);
                    commands.push_back(leftTurn);
                    isLastCMDProceed = false;
                    isLastCMDTurn = true;
                }

                //else
                    //if lastCmd was a proceed, then add that
                        //reset loaded values and bool
                    //make a new cmd proceed
                else
                {
                    if (isLastCMDProceed)
                    {
                        DeliveryCommand proceed;
                        proceed.initAsProceedCommand(dir, streetName, dist + distanceEarthMiles(seg->start, seg->end));
                        commands.push_back(proceed);
                    }

                    DeliveryCommand straightProceed;
                    straightProceed.initAsProceedCommand(processAngle(angleOfLine(*seg)), nextSeg->name, distanceEarthMiles(seg->start, seg->end) + distanceEarthMiles(seg->end, nextSeg->start));
                    commands.push_back(straightProceed);
                    isLastCMDProceed = false;
                    isLastCMDTurn = false;
                }

            }

            //must do a proceed cmd
            else
            {
                //if last cmd was also a proceed cmd, just increment the dist
                if(isLastCMDProceed)
                {
                    int d = 0;
                    if (nextSeg != routes[i].end())
                    {
                        d = distanceEarthMiles(seg->end, nextSeg->start);
                    }
                    dist += distanceEarthMiles(seg->start, seg->end) + d;
                    isLastCMDProceed = true;
                    isLastCMDTurn = false;
                }
                //else, load variables for new proceed
                else
                {
                    int d = 0;
                    if (nextSeg != routes[i].end())
                    {
                        d = distanceEarthMiles(seg->end, nextSeg->start);
                    }
                    dist = distanceEarthMiles(seg->start, seg->end) + d;
                    streetName = seg->name;
                    dir = processAngle(angleOfLine(*seg));
                    isLastCMDProceed = true;
                    isLastCMDTurn = false;
                }
            }
            if (nextSeg == routes[i].end())
            {
                if (isLastCMDProceed)
                {
                    DeliveryCommand proceed;
                    proceed.initAsProceedCommand(dir, streetName, dist); //+ distanceEarthMiles(seg->start, seg->end) + distanceEarthMiles(seg->end, deliveries[i].location));
                    commands.push_back(proceed);
                    isLastCMDProceed = false;
                }
            }
        } //end for loop



        if (i != routes.size()-1)
        {
            //handle delivery
            DeliveryCommand temp;
            temp.initAsDeliverCommand(bestDelivery[i].item);
            commands.push_back(temp);
        }
        //else nothing


    }

    return DELIVERY_SUCCESS;  // Delete this line and implement this function correctly
}

//******************** DeliveryPlanner functions ******************************

// These functions simply delegate to DeliveryPlannerImpl's functions.
// You probably don't want to change any of this code.

DeliveryPlanner::DeliveryPlanner(const StreetMap* sm)
{
    m_impl = new DeliveryPlannerImpl(sm);
}

DeliveryPlanner::~DeliveryPlanner()
{
    delete m_impl;
}

DeliveryResult DeliveryPlanner::generateDeliveryPlan(
    const GeoCoord& depot,
    const vector<DeliveryRequest>& deliveries,
    vector<DeliveryCommand>& commands,
    double& totalDistanceTravelled) const
{
    return m_impl->generateDeliveryPlan(depot, deliveries, commands, totalDistanceTravelled);
}
