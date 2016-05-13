#include <stdio.h>
#define INFINITY 9999
#include "dvr.h"

// The distance table for node 2
struct distance_table dt2;

/**
 * Called by the simulation during start-up. Use this function to initialize
 * any data on node 2. You may not need to do anything with this function.
 */
void rtinit2() {
  // initializing all to INFINITY
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      dt2.costs[i][j] = INFINITY;
    }
  }
  
  // Initializing costs
  dt2.costs[0][0] = 3;
  dt2.costs[1][1] = 1;
  dt2.costs[3][3] = 2;

  printdt(2, &dt2);

  // Sending costs to other nodes
  struct rtpkt packet0;
  creatertpkt(&packet0, 2, 0, dt2.costs[0]);
  tolayer2(packet0);
  printf("At time t=%lf, node 2 sends packet to node 0 with: 3 1 0 2.\n", get_time());
  
  struct rtpkt packet1;
  creatertpkt(&packet1, 2, 1, dt2.costs[1]);
  tolayer2(packet1);
  printf("At time t=%lf, node 2 sends packet to node 1 with: 3 1 0 2.\n", get_time());

  struct rtpkt packet3;
  creatertpkt(&packet3, 2, 3, dt2.costs[3]);
  tolayer2(packet3);
  printf("At time t=%lf, node 2 sends packet to node 3 with: 3 1 0 2.\n", get_time());
}

/**
 * Called when node 2 receives a routing packet from one of its neighbors
 *
 * \param packet  A pointer to the packet data that was received.
 */
void rtupdate2(struct rtpkt* packet) {
  printf("At time t=%lf, rtupdate2() called. node %d receives a packet from node %d\n", get_time(), packet->destid, packet->sourceid);
 
  int id = packet->destid;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int sum = dt2.costs[id][j] + packet->mincost[j];
      if (sum < dt2.costs[id][i]) {
        dt2.costs[id][i] = sum;
        struct rtpkt packet0;
        creatertpkt(&packet0, 2, i, dt2.costs[i]);
        tolayer2(packet0);
        printf("At time t=%lf, node 2 sends packet to node %d with: %d %d %d %d.\n", get_time(), i, dt2.costs[i][0], dt2.costs[i][1], dt2.costs[i][2], dt2.costs[i][3]);
      }
    }
  }
  printdt(2, &dt2);
}
