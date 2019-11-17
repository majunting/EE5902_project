#include "Routing_WEST_FIRST.h"
// modified by JT

RoutingAlgorithmsRegister Routing_WEST_FIRST::routingAlgorithmsRegister("WEST_FIRST", getInstance());

Routing_WEST_FIRST * Routing_WEST_FIRST::routing_WEST_FIRST = 0;
RoutingAlgorithm * Routing_WEST_FIRST::xy = 0;

Routing_WEST_FIRST * Routing_WEST_FIRST::getInstance() {
	if ( routing_WEST_FIRST == 0 )
        routing_WEST_FIRST = new Routing_WEST_FIRST();

    return routing_WEST_FIRST;
}

vector<int> Routing_WEST_FIRST::route(Router * router, const RouteData & routeData)
{
    // west-first routing algorithm restricts all turns to west direction, so the movement towards west needs to be taken care of first
    Coord current = id2Coord(routeData.current_id);
    Coord destination = id2Coord(routeData.dst_id);
    vector <int> directions;

    // if the current location and destination location have the same y-coordinate, call XY routing algorithm
    // if destination x-coordinate is smaller than current x-coordinate, means destination is at the west side, call XY routing algorithm to take care of west first
    if (destination.x <= current.x || destination.y == current.y)
    {
        if(!xy)
        {
            xy = RoutingAlgorithms::get("XY");
            
            if (!xy)
                assert(false);
        }

        return xy->route(router, routeData);
    }

    // destination is at north east direction of current location (destination.x > current.x, destination.y < current.y)
    if (destination.y < current.y)
    {
        directions.push_back(DIRECTION_NORTH);
        directions.push_back(DIRECTION_EAST);
    }
    // destination is at south east direction of current location (destination.x > current.x, destination.y > current.y)
    else 
    {
        directions.push_back(DIRECTION_SOUTH);
        directions.push_back(DIRECTION_EAST);
    }

    return directions;
}
