#include <stdio.h>
#define INFINITY 9999
#include "dvr.h"

// The distance table for node 3
struct distance_table dt3;

/**
 * Called by the simulation during start-up. Use this function to initialize
 * any data on node 3. You may not need to do anything with this function.
 */
void rtinit3() {
  // initializing all to INFINITY
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      dt3.costs[i][j] = INFINITY;
    }
  }
  
   // Initializing costs
  dt3.costs[0][0] = 7;
  dt3.costs[2][2] = 2;
  
  printdt(3, &dt3);
  
  // Sending costs to other nodes
  struct rtpkt packet2;
  creatertpkt(&packet2, 3, 2, dt3.costs[2]);
  tolayer2(packet2);
  printf("At time t=%lf, node 3 sends packet to node 2 with: 7 9999 2 0.\n", get_time());

  struct rtpkt packet0;
  creatertpkt(&packet0, 3, 0, dt3.costs[0]);
  tolayer2(packet0);
  printf("At time t=%lf, node 3 sends packet to node 0 with: 7 9999 2 0.\n", get_time());
}

/**
 * Called when node 3 receives a routing packet from one of its neighbors
 *
 * \param packet  A pointer to the packet data that was received.
 */
void rtupdate3(struct rtpkt* packet) {
  printf("At time t=%lf, rtupdate3() called. node %d receives a packet from node %d\n", get_time(), packet->destid, packet->sourceid);
 
  int id = packet->destid;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      //printf("               ids: %d, %d\n", i, j);
      //printf("             costs: %d, %d, %d, %d\n", tempArr[i], tempArr[j], tempArr[i] + tempArr[j], dt3.costs[id][i]);
      int sum = dt3.costs[id][j] + packet->mincost[j];
      printf("from: %d %d\n", id, j);
      printf("parts: %d %d\n", dt3.costs[id][j], packet->mincost[j]);
      printf("sum: %d\n", sum);
      if (sum < dt3.costs[id][i]) {
        dt3.costs[id][i] = sum;
        tolayer2(*packet);
        //printf("At time t=%lf, node 3 sends packet to node %d with: 7 9999 2 0.\n", get_time(), j);
      }
    }
  }
  printdt(3, &dt3);
}
