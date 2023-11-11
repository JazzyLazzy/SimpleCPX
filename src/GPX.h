#include "Waypoint.h"
#include "Track.h"

//GPX_H
#ifndef GPX_H
#define GPX_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  char *creator;
  char version[4];
  Waypoint *waypoints;
  Track *tracks;
  size_t size;
} GPX;

#ifdef __cplusplus
}
#endif

#endif
