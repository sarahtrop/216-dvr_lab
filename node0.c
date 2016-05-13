#include <stdio.h>

#include "dvr.h"
#define INFINITY 9999

// The distance table for node 0
struct distance_table dt0;

/**
 * Called by the simulation during start-up. Use this function to initialize
 * any data on node 0. You may not need to do anything with this function.
 */
void rtinit0() {
  // initializing all to INFINITY
  for (int i = 1; i < 4; i++) {
    for (int j = 1; j < 4; j++) {
      dt0.costs[i][j] = INFINITY;
    }
  }
  
  // Initializing costs we know
  dt0.costs[1][1] = 1;
  dt0.costs[2][2] = 3;
  dt0.costs[3][3] = 7;
  
  printdt(0, &dt0);

  // Sending costs to other nodes
  struct rtpkt packet1;
  creatertpkt(&packet1, 0, 1, dt0.costs[1]);
  tolayer2(packet1);
  printf("At time t=%lf, node 0 sends packet to node 1 with: 0 1 3 7.\n", get_time());

  struct rtpkt packet2;
  creatertpkt(&packet2, 0, 2, dt0.costs[2]);
  tolayer2(packet2);
  printf("At time t=%lf, node 0 sends packet to node 2 with: 0 1 3 7.\n", get_time());

  struct rtpkt packet3;
  creatertpkt(&packet3, 0, 3, dt0.costs[3]);
  tolayer2(packet3);
  printf("At time t=%lf, node 0 sends packet to node 3 with: 0 1 3 7.\n", get_time());
  
}

/**
 * Called when node 0 receives a routing packet from one of its neighbors
 *
 * \param packet  A pointer to the packet data that was received.
 */
void rtupdate0(struct rtpkt* packet) {
  printf("At time t=%lf, rtupdate0() called. node %d receives a packet from node %d\n", get_time(), packet->destid, packet->sourceid);
 
  int id = packet->destid;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int sum = dt0.costs[id][j] + packet->mincost[j];
      if (sum < dt0.costs[id][i]) {
        dt0.costs[id][i] = sum;
        struct rtpkt packet1;
        creatertpkt(&packet1, 0, i, dt0.costs[i]);
        tolayer2(packet1);
        printf("At time t=%lf, node 0 sends packet to node %d with: %d %d %d %d.\n", get_time(), i, dt0.costs[i][0], dt0.costs[i][1], dt0.costs[i][2], dt0.costs[i][3]);
      }
    }
  }
  printdt(0, &dt0);
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
