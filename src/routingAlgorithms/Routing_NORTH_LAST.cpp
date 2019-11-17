#include "Routing_NORTH_LAST.h"
// modified by JT

RoutingAlgorithmsRegister Routing_NORTH_LAST::routingAlgorithmsRegister("NORTH_LAST", getInstance());

Routing_NORTH_LAST * Routing_NORTH_LAST::routing_NORTH_LAST = 0;
RoutingAlgorithm * Routing_NORTH_LAST::xy = 0;

Routing_NORTH_LAST * Routing_NORTH_LAST::getInstance() {
	if ( routing_NORTH_LAST == 0 )
		routing_NORTH_LAST = new Routing_NORTH_LAST();

    return routing_NORTH_LAST;
}

vector<int> Routing_NORTH_LAST::route(Router * router, const RouteData & routeData)
{
    // north-last routing algorithm handles turns towards north direction last
    // movements to the other directions are processed first
    Coord curr = id2Coord(routeData.current_id);
    Coord dest = id2Coord(routeData.dst_id);
    vector <int> directions;

    if (dest.x == curr.x || dest.y <= curr.y)
    {
        if(!xy)
        {
            xy = RoutingAlgorithms::get("XY");
            
            if (!xy)
                assert(false);
        }

        return xy->route(router, routeData);
    }
    if (dest.x < curr.x) 
    {
        directions.push_back(DIRECTION_SOUTH);
        directions.push_back(DIRECTION_WEST);
    } 
    else 
    {
        directions.push_back(DIRECTION_SOUTH);
        directions.push_back(DIRECTION_EAST);
    }

    return directions;
}
