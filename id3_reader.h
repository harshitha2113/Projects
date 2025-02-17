#ifndef ID3_READER_H
#define ID3_READER_H

#include "id3_utils.h"

/* Function prototypes for reader.c */
TagData* read_id3_tags(FILE *fptr);
void display_metadata(const TagData *data);
void view_tags(const char *filename);

#endif 
