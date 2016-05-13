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
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
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
  for (int i = 0; i < 4; i++) {
    if (i != 2) {
      struct rtpkt packet0;
      creatertpkt(&packet0, 2, i, link_costs2);
      tolayer2(packet0);
      printf("At time t=%lf, node 2 sends packet to node %d with: %d %d %d %d.\n", get_time(), i, link_costs2[0], link_costs2[1], link_costs2[2], link_costs2[3]);
    }
  }
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

  int send_arr[4] = {0, 0, 0, 0};
  for (int i = 0; i < 4; i++) {
    send_arr[i] = dt2.costs[i][packet->sourceid];
  }
  
  if(updated == 1) {
    for (int i = 0; i < 4; i++) {
      if (i != 2) {
        struct rtpkt packet0;
        creatertpkt(&packet0, 2, i, send_arr);
        tolayer2(packet0);
        printf("At time t=%lf, node 2 sends packet to node %d with: %d %d %d %d.\n", get_time(), i, send_arr[0], send_arr[1], send_arr[2], send_arr[3]);
      }
    }
  }
  
  printdt(2, &dt2);
}
