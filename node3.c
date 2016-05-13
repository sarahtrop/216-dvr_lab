#include <stdio.h>
#define INFINITY 9999
#include "dvr.h"

// Help from Reilly on rtupdate()

// The distance table for node 3
struct distance_table dt3;

int link_costs3[] = {7, INFINITY, 2, 0};

/**
 * Called by the simulation during start-up. Use this function to initialize
 * any data on node 3. You may not need to do anything with this function.
 */
void rtinit3() {
  // initializing
  for (int i = 1; i < 4; i++) {
    for (int j = 1; j < 4; j++) {
      if (i == j || i == 3) {
        dt3.costs[i][j] = link_costs3[i];
      }
      else {
        dt3.costs[i][j] = INFINITY;
      }
    }
  }
  
  printdt(3, &dt3);
  
  // Sending costs to other nodes
  struct rtpkt packet2;
  creatertpkt(&packet2, 3, 2, dt3.costs[2]);
  tolayer2(packet2);
  printf("At time t=%lf, node 3 sends packet to node 2 with: %d %d %d %d.\n", get_time(), dt3.costs[0][0], dt3.costs[1][1], dt3.costs[2][2], dt3.costs[3][3]);

  struct rtpkt packet0;
  creatertpkt(&packet0, 3, 0, dt3.costs[0]);
  tolayer2(packet0);
 printf("At time t=%lf, node 3 sends packet to node 1 with: %d %d %d %d.\n", get_time(), dt3.costs[0][0], dt3.costs[1][1], dt3.costs[2][2], dt3.costs[3][3]);
}

/**
 * Called when node 3 receives a routing packet from one of its neighbors
 *
 * \param packet  A pointer to the packet data that was received.
 */
void rtupdate3(struct rtpkt* packet) {
  printf("At time t=%lf, rtupdate3() called. node %d receives a packet from node %d\n", get_time(), packet->destid, packet->sourceid);

  int updated = 0;

    printf("received: %d %d %d %d\n", packet->mincost[0], packet->mincost[1], packet->mincost[2], packet->mincost[3]);
  
  for (int i = 0; i < 4; i++) {
    int sum = link_costs3[packet->sourceid] + packet->mincost[i];
    if (sum < dt3.costs[i][packet->sourceid]) {
      dt3.costs[i][packet->sourceid] = sum;
      updated = 1;
    }
  }

  if(updated == 1) {
    for (int i = 0; i < 3; i++) {
      if (i != 1) {
        struct rtpkt packet0;
        creatertpkt(&packet0, 3, i, dt3.costs[i]);
        tolayer2(packet0);
        printf("At time t=%lf, node 3 sends packet to node %d with: %d %d %d %d.\n", get_time(), i, dt3.costs[i][0], dt3.costs[i][1], dt3.costs[i][2], dt3.costs[i][3]);
      }
    }
  }
  
  
  printdt(3, &dt3);
}
