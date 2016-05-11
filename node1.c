#include <stdio.h>

#include "dvr.h"

// The distance table for node 1
struct distance_table dt1;

/**
 * Called by the simulation during start-up. Use this function to initialize
 * any data on node 1. You may not need to do anything with this function.
 */
void rtinit1() {
  // Initializing costs
  dt1.costs[1][0] = 1;
  dt1.costs[1][1] = 0;
  dt1.costs[1][2] = 1;
  dt1.costs[1][3] = INFINITY;

  // Sending costs to other nodes
  struct rtpkt packet0;
  packet0.sourceid = 1;
  packet0.destid = 0;
  memcpy(packet0.mincost, dt1.costs[1], 4);
  tolayer2(packet0);

  struct rtpkt packet2;
  packet2.sourceid = 1;
  packet2.destid = 2;
  memcpy(packet2.mincost, dt1.costs[1], 4);
  tolayer2(packet2);
}

/**
 * Called when node 1 receives a routing packet from one of its neighbors
 *
 * \param packet  A pointer to the packet data that was received.
 */
void rtupdate1(struct rtpkt* packet) {
  int* tempArr = packet->mincost;

  if (tempArr[1] < dt1.costs[1][packet->sourceid]) { 
    dt1.costs[1][packet->sourceid] = tempArr[1];
  }

  for (int i = 1; i < 4; i++) {
    if (tempArr[1] + tempArr[1] < dt1.costs[1][i]) {
      dt1.costs[1][i] = tempArr[i] + tempArr[1];
    }
  }
}

/**
 * Handle an update to the cost of one of the links from this node. You only
 * need to implement this function if you complete the advanced assignment.
 * You must also set LINKCHANGE to 1 in dvr.h.
 *
 * \param linkid  The id of the node connected on the link that changed cost
 * \param newcost The new cost of this link
 */
void linkhandler1(int linkid, int newcost) {
  
}
