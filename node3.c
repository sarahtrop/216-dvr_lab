#include <stdio.h>

#include "dvr.h"

// The distance table for node 3
struct distance_table dt3;

/**
 * Called by the simulation during start-up. Use this function to initialize
 * any data on node 3. You may not need to do anything with this function.
 */
void rtinit3() {
   // Initializing costs
  dt3.costs[3][0] = 7;
  dt3.costs[3][1] = INFINITY;
  dt3.costs[3][2] = 2;
  dt3.costs[3][3] = 0;

  // Sending costs to other nodes
  struct rtpkt packet2;
  packet2.sourceid = 3;
  packet2.destid = 2;
  packet2.mincost = dt3.costs[3];
  tolayer2(packet2);

  struct rtpkt packet0;
  packet0.sourceid = 3;
  packet0.destid = 0;
  packet0.mincost = dt3.costs[3];
  tolayer2(packet0);
}

/**
 * Called when node 3 receives a routing packet from one of its neighbors
 *
 * \param packet  A pointer to the packet data that was received.
 */
void rtupdate3(struct rtpkt* packet) {
  
}
