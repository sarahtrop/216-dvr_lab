#include <stdio.h>
#include <stdlib.h>
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
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j || i == 3) {
        dt3.costs[i][j] = link_costs3[i];
      }
      else {
        dt3.costs[i][j] = INFINITY;
      }
    }
  }
  
  printdt(3, &dt3);

 for (int i = 0; i < 3; i++) {
      if (i != 1) {
        struct rtpkt packet0;
        creatertpkt(&packet0, 3, i, link_costs3);
        tolayer2(packet0);
        printf("At time t=%lf, node 3 sends packet to node %d with: %d %d %d %d.\n", get_time(), i, link_costs3[0], link_costs3[1], link_costs3[2], link_costs3[3]);
      }
    }
}

/**
 * Called when node 3 receives a routing packet from one of its neighbors
 *
 * \param packet  A pointer to the packet data that was received.
 */
void rtupdate3(struct rtpkt* packet) {
  printf("At time t=%lf, rtupdate3() called. node %d receives a packet from node %d\n", get_time(), packet->destid, packet->sourceid);

  int updated = 0;
  
  for (int i = 0; i < 4; i++) {
    int sum = link_costs3[packet->sourceid] + packet->mincost[i];
    if (sum < dt3.costs[i][packet->sourceid]) {
      dt3.costs[i][packet->sourceid] = sum;
      updated = 1;
    }
  }

  int send_arr[4] = {0, 0, 0, 0};
  for (int i = 0; i < 4; i++) {
    send_arr[i] = dt3.costs[i][packet->sourceid];
  }


  if(updated == 1) {
    for (int i = 0; i < 3; i++) {
      if (i != 1) {
        struct rtpkt packet0;
        creatertpkt(&packet0, 3, i, send_arr);
        tolayer2(packet0);
        printf("At time t=%lf, node 3 sends packet to node %d with: %d %d %d %d.\n", get_time(), i, send_arr[0], send_arr[1], send_arr[2], send_arr[3]);
      }
    }
  }
  
  
  printdt(3, &dt3);
}
