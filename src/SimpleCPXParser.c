#include <expat.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "GPX.h"
#include "Waypoint.h"
#include "Location.h"
#include "SimpleCPXParser.h"

#define BUFFSIZE 8192

bool is_wpt = false;
char buff[BUFFSIZE];
int d;
bool is_name = false;

void initialise_gpx(void *userData, const char *name, const char *args[]){
  if (strncmp(name, "gpx\0", 4) != 0){
     printf("N'est pas gpx valide.");
     exit(1);
  }
  GPX *gpx = userData;

  for (int i = 0; args[i]; i+=2){
//    printf("%d", i);
    if (strncmp(args[i], "creator\0", 8) == 0){
  //    printf("%s: %s", args[i], args[i+1]);
      gpx->creator = malloc(sizeof (args[i+1]) + 1);
      strcpy(gpx->creator, args[i+1]);
    }else if(strncmp(args[i], "version\0", 8) == 0){
      strncpy(gpx->version, args[i+1], 4);
    }
  } 
}

void handle_waypoint(void *userData, const char *args[]){
  GPX *gpx = userData;
  Waypoint *wpt = malloc(sizeof (Waypoint));
  if (gpx->waypoints == NULL){
    wpt->next = NULL;
    gpx->waypoints = wpt;
  }else{
    printf("%s", wpt->name);
    wpt->next = gpx->waypoints;
    gpx->waypoints = wpt;
  }
  Location *location = malloc(sizeof (Location));
  wpt->location = location;
  for (int i=0; args[i]; i+=2){
    if (strncmp(args[i], "lat\0", 4) == 0){
      location->latitude = atof(args[i+1]);
    }else if(strncmp(args[i], "lon\0", 4) == 0){
      location->longitude = atof(args[i+1]);
    }
  }
}

void start_element(void *userData, const char *name, const char *args[]){
  if (d == 0) {
    initialise_gpx(userData, name, args);
  }else if (strncmp(name, "wpt\0", 4) == 0){
    is_wpt = true;
    handle_waypoint(userData, args);
  }else if (is_wpt && strncmp(name, "name\0", 5) == 0){
    is_name = true;
  }
  d++;
}

void read_text(void *userData, const XML_Char *s, int len){
  if (is_wpt && is_name){
    GPX *gpx = userData;
    char *name = malloc(sizeof (XML_Char) * (len + 1));
    strncpy(name, s, len);
    gpx->waypoints->name = name;
  }
}

void end_element(void *userData, const char *name){
  if(strncmp(name, "wpt\0", 4) == 0){
    is_wpt = false;
  }else if(strncmp(name, "name\0", 5) == 0){
    is_name = false;
  }
  d--;
}

GPX *parse_GPX(char *file){

  //printf("hello parser");
  //printf("%s", file);
  //is_wpt = false;
  XML_Parser parser = XML_ParserCreate(NULL);
  
  if (!parser) {
    fprintf(stderr, "N'était pas possible d'allouer de la mémoire pour l'analyseur.\n");
    exit(-1);
  }

  XML_SetElementHandler(parser, start_element, end_element);
  XML_SetCharacterDataHandler(parser, read_text);
 
  GPX *gpx = malloc(sizeof (GPX));
  if (gpx == NULL)
    return NULL;

  XML_SetUserData(parser, gpx);

  FILE *gpxf = fopen(file, "r");
  if (!gpxf) {
    perror("Failed to open file");
    free(gpx);
    XML_ParserFree(parser);
    return NULL;
  }
  fread(buff, sizeof(char), BUFFSIZE, gpxf);
  fclose(gpxf);

  if (XML_Parse(parser, buff, strlen(buff), XML_TRUE) == XML_STATUS_ERROR){
    fprintf(stderr, "Erreur d'analyse à la ligne %lu:\n%s\n",
    XML_GetCurrentLineNumber(parser),
    XML_ErrorString(XML_GetErrorCode(parser)));
    exit(1);
  }

  //printf("finish parse");
  //printf("%s", gpx->creator); 
  //free(gpx->creator);
  //free(gpx);
  XML_ParserFree(parser);
  return gpx;
  //
}
