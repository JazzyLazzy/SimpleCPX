#include <expat.h>
#include <stdio.h>
#include <string.h>
#include "GPX.h"
#include "SimpleCPXParser.h"

#define BUFFSIZE 8192

char buff[BUFFSIZE];
int d;

void initialise_gpx(void *userData, const char *name, const char *args[]){
  if (strncmp(name, "gpx\0", 4) != 0){
     printf("N'est pas gpx valide.");
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

void start_element(void *userData, const char *name, const char *args[]){
  if (d == 0) {
    initialise_gpx(userData, name, args);
  }
  d++;
}

void end_element(void *userData, const char *name){
  d--;
}

void parse_GPX(char *file){
  
  XML_Parser parser = XML_ParserCreate(NULL);
  
  if (!parser) {
    fprintf(stderr, "N'était pas possible d'allouer de la mémoire pour l'analyseur.\n");
    exit(-1);
  }

  XML_SetElementHandler(parser, start_element, end_element);
 
  GPX *gpx = malloc(sizeof (GPX));
  if (gpx == NULL)
    return;

  XML_SetUserData(parser, gpx);

  FILE *gpxf = fopen(file, "r");
  fread(buff, sizeof(char), BUFFSIZE, gpxf);
  fclose(gpxf);

  if (XML_Parse(parser, buff, strlen(buff), XML_TRUE) == XML_STATUS_ERROR){
    fprintf(stderr, "Erreur d'analyse à la ligne %lu:\n%s\n",
    XML_GetCurrentLineNumber(parser),
    XML_ErrorString(XML_GetErrorCode(parser)));
    exit(1);
  }

  printf("%s, %s", gpx->creator, gpx->version);
  free(gpx);
  XML_ParserFree(parser);

  //
}
