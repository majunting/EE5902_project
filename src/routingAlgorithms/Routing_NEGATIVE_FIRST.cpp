#include "Routing_NEGATIVE_FIRST.h"
// modified by JT

RoutingAlgorithmsRegister Routing_NEGATIVE_FIRST::routingAlgorithmsRegister("NEGATIVE_FIRST", getInstance());

Routing_NEGATIVE_FIRST * Routing_NEGATIVE_FIRST::routing_NEGATIVE_FIRST = 0;
RoutingAlgorithm * Routing_NEGATIVE_FIRST::xy = 0;

Routing_NEGATIVE_FIRST * Routing_NEGATIVE_FIRST::getInstance() {
	if ( routing_NEGATIVE_FIRST == 0 )
		routing_NEGATIVE_FIRST = new Routing_NEGATIVE_FIRST();
    
	return routing_NEGATIVE_FIRST;
}

vector<int> Routing_NEGATIVE_FIRST::route(Router * router, const RouteData & routeData)
{
    // negative-first routing algorithm restricts any turn towards negative direction
    // west is considered negative for x-direction and south is considered negative for y-direction
    // so south and west direction movements should have priority
    Coord curr = id2Coord(routeData.current_id);
    Coord dest = id2Coord(routeData.dst_id);
    vector <int> directions;

    if (dest.x < curr.x || dest.y > curr.y) // check negative directions first
    {
	if (dest.x < curr.x) directions.push_back(DIRECTION_WEST);
	if (dest.y > curr.y) directions.push_back(DIRECTION_SOUTH);
    } 
    else { // no negative direction to process, check if positive ones are needed
	    if (dest.x > curr.x) directions.push_back(DIRECTION_EAST);
	    if (dest.y < curr.y) directions.push_back(DIRECTION_NORTH);
    	// the destination module is reached
    	if (dest.x == curr.x && dest.y == curr.y) directions.push_back(DIRECTION_LOCAL);
    }

    return directions;
}
