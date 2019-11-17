#include "Routing_XY.h"
// modified by JT

RoutingAlgorithmsRegister Routing_XY::routingAlgorithmsRegister("XY", getInstance());

Routing_XY * Routing_XY::routing_XY = 0;

Routing_XY * Routing_XY::getInstance() {
	if ( routing_XY == 0 )
		routing_XY = new Routing_XY();
    
	return routing_XY;
}

vector<int> Routing_XY::route(Router * router, const RouteData & routeData)
{
    // XY routing algorithm does not have any restriction on the forwarding direction of the packets
    Coord curr = id2Coord(routeData.current_id);
    Coord dest = id2Coord(routeData.dst_id);
    vector <int> directions;

    // XY routing moves the packets to the module with the same x-dimension first
    if (dest.x > curr.x) directions.push_back(DIRECTION_EAST);
    else if (dest.x < curr.x) directions.push_back(DIRECTION_WEST);
    else if (dest.y > curr.y) directions.push_back(DIRECTION_SOUTH);
    else directions.push_back(DIRECTION_NORTH);

    return directions;
   } 
