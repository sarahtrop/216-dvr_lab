#include <stdio.h>

#include "dvr.h"
#define INFINITY 9999

// The distance table for node 0
struct distance_table dt0;

int link_costs0[] = {0, 1, 3, 7};

/**
 * Called by the simulation during start-up. Use this function to initialize
 * any data on node 0. You may not need to do anything with this function.
 */
void rtinit0() {
  // initializing all to INFINITY
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j || i == 0) {
        dt0.costs[i][j] = link_costs0[i];
      }
      else {
        dt0.costs[i][j] = INFINITY;
      }
    }
  }
  
  printdt(0, &dt0);
  
  // Sending costs to other nodes
    for (int i = 1; i < 4; i++) {
      struct rtpkt packet0;
      creatertpkt(&packet0, 0, i, link_costs0);
      tolayer2(packet0);
      printf("At time t=%lf, node 0 sends packet to node %d with: %d %d %d %d.\n", get_time(), i, link_costs0[0], link_costs0[1], link_costs0[2], link_costs0[3]);
    }
}

/**
 * Called when node 0 receives a routing packet from one of its neighbors
 *
 * \param packet  A pointer to the packet data that was received.
 */
void rtupdate0(struct rtpkt* packet) {
  printf("At time t=%lf, rtupdate0() called. node %d receives a packet from node %d\n", get_time(), packet->destid, packet->sourceid);

  int updated = 0;
  
  for (int i = 0; i < 4; i++) {
    int sum = link_costs0[packet->sourceid] + packet->mincost[i];
    if (sum < dt0.costs[i][packet->sourceid]) {
      dt0.costs[i][packet->sourceid] = sum;
      updated = 1;
    }
  }

  int send_arr[4] = {0, 0, 0, 0};
  for (int i = 0; i < 4; i++) {
    send_arr[i] = dt0.costs[i][packet->sourceid];
  }

  if(updated == 1) {
    for (int i = 1; i < 4; i++) {
      struct rtpkt packet0;
      creatertpkt(&packet0, 0, i, send_arr);
      tolayer2(packet0);
      printf("At time t=%lf, node 0 sends packet to node %d with: %d %d %d %d.\n", get_time(), i, send_arr[0], send_arr[1], send_arr[2], send_arr[3]);
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
