#ifndef ID3_WRITER_H
#define ID3_WRITER_H

#include "id3_utils.h"

/* Function prototypes for writer.c */
int write_id3_tags(FILE *fptr, const char *option, const char *value);
int edit_tag(const char *filename, const char *option, const char *value);

#endif 
