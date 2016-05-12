#include <stdio.h>

#include "dvr.h"
#define INFINITY 9999
// The distance table for node 1
struct distance_table dt1;

/**
 * Called by the simulation during start-up. Use this function to initialize
 * any data on node 1. You may not need to do anything with this function.
 */
void rtinit1() {
  // initializing all to INFINITY
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      dt1.costs[i][j] = INFINITY;
    }
  }
  
  // Initializing costs
  dt1.costs[0][0] = 1;
  dt1.costs[1][1] = 0;
  dt1.costs[2][2] = 1;

  printdt(1, &dt1);

  // Sending costs to other nodes
  struct rtpkt packet0;
  creatertpkt(&packet0, 1, 0, dt1.costs[0]);
  tolayer2(packet0);
  printf("At time t=%lf, node 1 sends packet to node 0 with: 1 0 1 9999.\n", get_time());
  
  struct rtpkt packet2;
  creatertpkt(&packet2, 0, 2, dt1.costs[2]);
  tolayer2(packet2);
  printf("At time t=%lf, node 1 sends packet to node 2 with: 1 0 1 9999.\n", get_time());
}

/**
 * Called when node 1 receives a routing packet from one of its neighbors
 *
 * \param packet  A pointer to the packet data that was received.
 */
void rtupdate1(struct rtpkt* packet) {
  printf("At time t=%lf, rtupdate2() called. node %d receives a packet from node %d\n", get_time(), packet->destid, packet->sourceid);
 
  int id = packet->destid;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (sum < dt2.costs[id][i]) {
        dt2.costs[id][i] = sum;
      }
    }
  }

  // Sending costs to other nodes
  struct rtpkt packet0;
  creatertpkt(&packet0, 1, 0, dt1.costs[0]);
  tolayer2(packet0);
  printf("At time t=%lf, node 1 sends packet to node 0 with: %d %d %d %d.\n", get_time(), dt1.costs[0][0], dt1.costs[0][1], dt1.costs[0][2], dt1.costs[0][3]);

  struct rtpkt packet2;
  creatertpkt(&packet2, 1, 2, dt1.costs[2]);
  tolayer2(packet2);
  printf("At time t=%lf, node 1 sends packet to node 2 with: %d %d %d %d.\n", get_time(), dt1.costs[2][0], dt1.costs[2][1], dt1.costs[2][2], dt1.costs[2][3]);

  printdt(1, &dt1);
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
