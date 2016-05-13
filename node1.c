#include <stdio.h>

#include "dvr.h"
#define INFINITY 9999

// The distance table for node 1
struct distance_table dt1;

int link_costs1[] = {1, 0, 1, INFINITY};

/**
 * Called by the simulation during start-up. Use this function to initialize
 * any data on node 1. You may not need to do anything with this function.
 */
void rtinit1() {
  // initializing
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j || i == 3) {
        dt1.costs[i][j] = link_costs1[i];
      }
      else {
        dt1.costs[i][j] = INFINITY;
      }
    }
  }
  printdt(1, &dt1);

  // Sending costs to other nodes
    for (int i = 0; i < 3; i++) {
      if (i != 1) {
        struct rtpkt packet0;
        creatertpkt(&packet0, 0, i, link_costs1);
        tolayer2(packet0);
        printf("At time t=%lf, node 1 sends packet to node %d with: %d %d %d %d.\n", get_time(), i, link_costs1[0], link_costs1[1], link_costs1[2], link_costs1[3]);
      }
    }
}

/**
 * Called when node 1 receives a routing packet from one of its neighbors
 *
 * \param packet  A pointer to the packet data that was received.
 */
void rtupdate1(struct rtpkt* packet) {
  printf("At time t=%lf, rtupdate2() called. node %d receives a packet from node %d\n", get_time(), packet->destid, packet->sourceid);


  int updated = 0;
  
  for (int i = 0; i < 4; i++) {
    int sum = link_costs1[packet->sourceid] + packet->mincost[i];
    if (sum < dt1.costs[i][packet->sourceid]) {
      dt1.costs[i][packet->sourceid] = sum;
      updated = 1;
    }
  }

  int send_arr[4] = {0, 0, 0, 0};
  for (int i = 0; i < 4; i++) {
    send_arr[i] = dt1.costs[i][packet->sourceid];
  }
  
  if(updated == 1) {
    for (int i = 0; i < 3; i++) {
      if (i != 1) {
        struct rtpkt packet0;
        creatertpkt(&packet0, 0, i, send_arr);
        tolayer2(packet0);
        printf("At time t=%lf, node 1 sends packet to node %d with: %d %d %d %d.\n", get_time(), i, send_arr[0], send_arr[1], send_arr[2], send_arr[3]);
      }
    }
  }

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
