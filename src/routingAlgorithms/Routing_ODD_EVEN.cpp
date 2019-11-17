#include "Routing_ODD_EVEN.h"
// modified by JT

RoutingAlgorithmsRegister Routing_ODD_EVEN::routingAlgorithmsRegister("ODD_EVEN", getInstance());

Routing_ODD_EVEN * Routing_ODD_EVEN::routing_ODD_EVEN = 0;

Routing_ODD_EVEN * Routing_ODD_EVEN::getInstance() {
	if ( routing_ODD_EVEN == 0 )
		routing_ODD_EVEN = new Routing_ODD_EVEN();
    
	return routing_ODD_EVEN;
}

vector<int> Routing_ODD_EVEN::route(Router * router, const RouteData & routeData)
{
    // odd-even routing algorithm restricts different turns in odd and even cycles
    Coord curr = id2Coord(routeData.current_id);
    Coord dest = id2Coord(routeData.dst_id);
    Coord source = id2Coord(routeData.src_id);
    vector <int> directions;

    int c0 = curr.x;
    int c1 = curr.y;
    int s0 = source.x;
    int d0 = dest.x;
    int d1 = dest.y;
    int e0, e1;

    e0 = d0 - c0; // e0 is positive if the current location is at the west side of destination location
    e1 = -(d1 - c1); // e1 is positive if the current location is at the south side of destination location

    if (e0 == 0) { // current module has the same x-coordinate as the destination module
        if (e1 > 0) 
            directions.push_back(DIRECTION_NORTH);
        else
            directions.push_back(DIRECTION_SOUTH);
    } else { // current module does not have the same x-coordinate as the destination module
        if (e0 > 0) { // current module is at the west side of destination module
            if (e1 == 0) // current module has the same y-coordinate as the destination module
                directions.push_back(DIRECTION_EAST);
            else { // both x and y coordinates are different
                if ((c0 % 2 == 1) || (c0 == s0)) { 
                // current x-coordinate is odd or current x-coordinate is the same as source x-coordinate
                // move in x-direction
                    if (e1 > 0)
                        directions.push_back(DIRECTION_NORTH);
                    else
                        directions.push_back(DIRECTION_SOUTH);
                }
                // if destination x-direction is odd, or the current module is not 1 module away from destination x-coordinate
                // move to east direction
                if ((d0 % 2 == 1) || (e0 != 1))
                    directions.push_back(DIRECTION_EAST);
            }
        } else { // current module is at east side of destination module
            directions.push_back(DIRECTION_WEST);
            if (c0 % 2 == 0) { // if current x-coordinate is even, move in y-direction
                if (e1 > 0)
                    directions.push_back(DIRECTION_NORTH);
                if (e1 < 0)
                    directions.push_back(DIRECTION_SOUTH);
            }
        }
    }

    assert(directions.size() > 0 && directions.size() <= 2);

    return directions;
}
