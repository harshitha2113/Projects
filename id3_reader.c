/*
    Implementation of functions for reading ID3 tags from MP3 files.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "id3_reader.h"

/*
    Reads ID3 tags from an MP3 file.
    fptr Pointer to the MP3 file.
    return Pointer to the TagData structure containing ID3 tag data.
 */
TagData* read_id3_tags(FILE *fptr) 
{
    // Implementation for reading ID3 tags
    TagData *data = create_tag_data();
    unsigned char tag[5];
    unsigned char temp[4]; 
    unsigned int size;
    for(int i = 0; i < 6; i++)
    {
        if(fread(tag, 1, 4, fptr) != 4)
            return NULL;
        if(fread(temp, 1, 4, fptr) != 4)
            return NULL;
        size = (temp[0] << 21) | (temp[1] << 14) | (temp[2] << 7) | (temp[3]);
        fseek(fptr, 3, SEEK_CUR);
        char *tempdata = (char *)calloc(size, sizeof(char));
        if(fread(tempdata, 1, size-1, fptr) != size-1)
            return NULL;
        tempdata[size - 1] = '\0';
        if(!strcmp(tag, "TIT2"))
            data->title = tempdata;
        else if(!strcmp(tag, "TPE1"))
            data->artist = tempdata;
        else if(!strcmp(tag, "TALB"))
            data->album = tempdata;
        else if(!strcmp(tag, "TYER"))
            data->year = tempdata;
        else if(!strcmp(tag, "TCON"))
            data->contentType = tempdata;
        else if(!strcmp(tag, "COMM"))
            data->comment = tempdata;
    }
    return data;
}

/*
    Displays metadata stored in a TagData structure.
    data Pointer to the TagData structure.
 */
void display_metadata(const TagData *data) 
{
    // Implementation for displaying metadata
    printf("Tile/Song: %s\n", data->title);
    printf("Artist: %s\n", data->artist);
    printf("Album: %s\n", data->album);
    printf("Year: %s\n", data->year);
    printf("Content Type: %s\n", data->contentType);
    printf("Composer: %s\n", data->comment);
}

/*
    Opens an MP3 file and reads its ID3 tags.
    filename Name of the MP3 file.
 */
void view_tags(const char *filename) 
{
    FILE *fptr = fopen(filename, "rb");
    if(!fptr)
    {
        printf("Unable to open file\n");
        printf("View opeation failed\n");
        return; 
    }
    fseek(fptr, 10, SEEK_SET);
    TagData *data = read_id3_tags(fptr);
    if (!data) 
    {
        printf("Failed to read ID3 tags.\n");
        printf("View opeation failed\n");
        return;
    }
    display_metadata(data);
    free_tag_data(data);
    fclose(fptr);
}
