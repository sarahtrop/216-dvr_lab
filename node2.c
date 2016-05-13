#include <stdio.h>
#define INFINITY 9999
#include "dvr.h"

// The distance table for node 2
struct distance_table dt2;

int link_costs2[] = {3, 1, 0, 2};

/**
 * Called by the simulation during start-up. Use this function to initialize
 * any data on node 2. You may not need to do anything with this function.
 */
void rtinit2() {
  // initializing
  for (int i = 1; i < 4; i++) {
    for (int j = 1; j < 4; j++) {
      if (i == j || i == 3) {
        dt2.costs[i][j] = link_costs2[i];
      }
      else {
        dt2.costs[i][j] = INFINITY;
      }
    }
  }
  
  printdt(2, &dt2);

  // Sending costs to other nodes
  struct rtpkt packet0;
  creatertpkt(&packet0, 2, 0, dt2.costs[0]);
  tolayer2(packet0);
  printf("At time t=%lf, node 2 sends packet to node 0 with: %d %d %d %d.\n", get_time(), dt2.costs[0][0], dt2.costs[1][1], dt2.costs[2][2], dt2.costs[3][3]);
  
  struct rtpkt packet1;
  creatertpkt(&packet1, 2, 1, dt2.costs[1]);
  tolayer2(packet1);
  printf("At time t=%lf, node 2 sends packet to node 1 with: %d %d %d %d.\n", get_time(), dt2.costs[0][0], dt2.costs[1][1], dt2.costs[2][2], dt2.costs[3][3]);

  struct rtpkt packet3;
  creatertpkt(&packet3, 2, 3, dt2.costs[3]);
  tolayer2(packet3);
    printf("At time t=%lf, node 2 sends packet to node 3 with: %d %d %d %d.\n", get_time(), dt2.costs[0][0], dt2.costs[1][1], dt2.costs[2][2], dt2.costs[3][3]);
}

/**
 * Called when node 2 receives a routing packet from one of its neighbors
 *
 * \param packet  A pointer to the packet data that was received.
 */
void rtupdate2(struct rtpkt* packet) {
  printf("At time t=%lf, rtupdate2() called. node %d receives a packet from node %d\n", get_time(), packet->destid, packet->sourceid);


  int updated = 0;
  
  for (int i = 0; i < 4; i++) {
    int sum = link_costs2[packet->sourceid] + packet->mincost[i];
    if (sum < dt2.costs[i][packet->sourceid]) {
      dt2.costs[i][packet->sourceid] = sum;
      updated = 1;
    }
  }

  if(updated == 1) {
    for (int i = 0; i < 4; i++) {
      if (i != 2) {
        struct rtpkt packet0;
        creatertpkt(&packet0, 2, i, dt2.costs[i]);
        tolayer2(packet0);
        printf("At time t=%lf, node 2 sends packet to node %d with: %d %d %d %d.\n", get_time(), i, dt2.costs[i][0], dt2.costs[i][1], dt2.costs[i][2], dt2.costs[i][3]);
      }
    }
  }
  
  printdt(2, &dt2);
}
