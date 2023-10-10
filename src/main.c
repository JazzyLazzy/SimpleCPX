#include <stdio.h>
#include <stdlib.h>
//#include "GPX.h"
//#include "Waypoint.h"
#include <SimpleCPXParser.h>
//#include "Location.h"

int main(int argc, char **argv){
  //printf("%s", argv[1]);
  GPX *gpx = parse_GPX(argv[1]);
  printf("%s", gpx->creator);
  Waypoint *wpt = gpx->waypoints;
  while (wpt){
    Location *location = wpt->location;
    printf("%s: %f | %f\n", wpt->name, location->latitude, location->longitude);
    wpt = wpt->next;
  }
  free(gpx->creator);
  free(gpx);
  return 0;
}
