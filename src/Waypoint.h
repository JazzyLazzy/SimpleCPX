#include "Location.h"

//Waypoint_h
#ifndef Waypoint_H
#define Waypoint_H

typedef struct {
  Location location;
  char *name;
  char *desc;
  char *sym;
} Waypoint;

#endif // !Waypoint_H

