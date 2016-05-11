#include <stdio.h>

#include "dvr.h"

// The distance table for node 0
struct distance_table dt0;

/**
 * Called by the simulation during start-up. Use this function to initialize
 * any data on node 0. You may not need to do anything with this function.
 */
void rtinit0() {
  // Initializing costs
  dt0.costs[0][0] = 0;
  dt0.costs[0][1] = 1;
  dt0.costs[0][2] = 3;
  dt0.costs[0][3] = 7;

  // Sending costs to other nodes
  struct rtpkt packet1;
  packet1.sourceid = 0;
  packet1.destid = 1;
  memcpy(packet1.mincost, dt0.costs[0], 4);
  tolayer2(packet1);

  struct rtpkt packet2;
  packet2.sourceid = 0;
  packet2.destid = 2;
  memcpy(packet2.mincost, dt0.costs[0], 4);
  tolayer2(packet2);

  struct rtpkt packet3;
  packet3.sourceid = 0;
  packet3.destid = 3;
  memcpy(packet3.mincost, dt0.costs[0], 4);
  tolayer2(packet3);
}

/**
 * Called when node 0 receives a routing packet from one of its neighbors
 *
 * \param packet  A pointer to the packet data that was received.
 */
void rtupdate0(struct rtpkt* packet) {
  int* tempArr = packet->mincost;

  if (tempArr[0] < dt0.costs[0][packet->sourceid]) { 
    dt0.costs[0][packet->sourceid] = tempArr[0];
  }

  for (int i = 1; i < 4; i++) {
    if (tempArr[i] + tempArr[0] < dt0.costs[0][i]) {
      dt0.costs[0][i] = tempArr[i] + tempArr[0];
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
void linkhandler0(int linkid, int newcost) {
  
}
