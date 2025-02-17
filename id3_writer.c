/**
    Implementation of functions for writing and editing ID3 tags in MP3 files.
 */

#include <stdio.h>
#include <string.h>
#include "id3_writer.h"
#include "id3_reader.h"
#include "id3_utils.h"

/*
    Writes the ID3 tags to an MP3 file.
    fptr Pointer to the file being modified.
    option The tag option to be modified.
    value The new value to be written.
    return 1 on success, 0 on failure.
 */
int write_id3_tags(FILE *fptr, const char *option, const char *value)
{
    // Implementation for writing ID3 tags
    char tag[4];
    int size;
    unsigned char temp[4];

    // Iterate through the ID3 tags to find the one to modify
    for (int i = 0; i < 6; i++)
    {
        if (fread(tag, 1, 4, fptr) != 4)
            return 0;
        tag[4] = '\0';
        if (fread(temp, 1, 4, fptr) != 4)
            return 0;
        size = (temp[0] << 21) | (temp[1] << 14) | (temp[2] << 7) | (temp[3]);
        if ((strstr(option, "t") && !strcmp(tag, "TIT2")) ||
            (strstr(option, "a") && !strcmp(tag, "TPE1")) ||
            (strstr(option, "A") && !strcmp(tag, "TALB")) ||
            (strstr(option, "y") && !strcmp(tag, "TYER")) ||
            (strstr(option, "c") && !strcmp(tag, "TCON")) ||
            (strstr(option, "C") && !strcmp(tag, "COMM")))
        {
            fseek(fptr, 3, SEEK_CUR); // Move to tag data
            int write_size = (strlen(value) > size) ? size -1 : strlen(value);
            fwrite(value, 1, write_size, fptr);
            return 1;
        }
        // Move to the next tag
        fseek(fptr, 3 + size - 1, SEEK_CUR);
    }
    return 0; 
}

/*
    Edits an ID3 tag in an MP3 file.
    filename Name of the MP3 file.
    option The tag option to be modified.
    value The new value to be written.
    return 1 on success, 0 on failure.
*/
int edit_tag(const char *filename, const char *option, const char *value) 
{
    FILE *fptr = fopen(filename, "r+b");
    if(!fptr)
    {
        printf("Unable to open filr\n");
        return 0; 
    }
    fseek(fptr, 10, SEEK_SET);
    // Implementation for writing ID3 tags to file
    int res = write_id3_tags(fptr, option, value);
    fclose(fptr);
    return res;
}
