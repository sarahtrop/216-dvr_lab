#include <stdio.h>

#include "dvr.h"

// The distance table for node 2
struct distance_table dt2;

/**
 * Called by the simulation during start-up. Use this function to initialize
 * any data on node 2. You may not need to do anything with this function.
 */
void rtinit2() {
  // Initializing costs
  dt2.costs[2][0] = 3;
  dt2.costs[2][1] = 1;
  dt2.costs[2][2] = 0;
  dt2.costs[2][3] = 2;

  // Sending costs to other nodes
  struct rtpkt packet0;
  packet0.sourceid = 2;
  packet0.destid = 0;
  packet0.mincost = dt2.costs[2];
  tolayer2(packet0);
  
  struct rtpkt packet1;
  packet1.sourceid = 2;
  packet1.destid = 1;
  packet1.mincost = dt2.costs[2];
  tolayer2(packet1);

  struct rtpkt packet3;
  packet3.sourceid = 2;
  packet3.destid = 3;
  packet3.mincost = dt2.costs[2];
  tolayer2(packet3);
}

/**
 * Called when node 2 receives a routing packet from one of its neighbors
 *
 * \param packet  A pointer to the packet data that was received.
 */
void rtupdate2(struct rtpkt* packet) {
  
}
