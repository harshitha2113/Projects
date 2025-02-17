/*
    Main entry point for the MP3 Tag Reader application.
 */

#include <stdio.h>
#include <string.h>
#include "id3_reader.h"
#include "id3_writer.h"

/*
    Displays the help message for the MP3 Tag Reader application.
 */
void display_help() 
{
    printf("Usage: mp3tagreader [options] filename\n");
    printf("Options:\n");
    printf("Display help  -h\n");
    printf("View tags     -v mp3filename\n");
    printf("Edit tags     -e -t/-a/-A/-y/-c/-C <value> mp3filename\n");
    printf("    (song title) -t\n");
    printf("   (artist name) -a\n");
    printf("    (album name) -A\n");
    printf("          (year) -y\n");
    printf("  (content type) -c\n");
    printf("       (comment) -C \n");
}

/*
    Main function to handle command-line arguments and execute appropriate actions.
    argc Argument count.
    argv Argument vector.
    return 0 on success, non-zero on failure.
 */
int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        display_help();
        return 0;
    }

    if (strcmp(argv[1], "-h") == 0) 
    {
        display_help();
        return 0;
    } 
    else if (strcmp(argv[1], "-v") == 0 && argc == 3) 
    {
        view_tags(argv[2]);
    } 
    else if (strcmp(argv[1], "-e") == 0 && argc == 5) 
    {
        char *option = argv[2];
        char *value = argv[3];
        char *filename = argv[4];
        if (edit_tag(filename, option, value) == 0) 
        {
            printf("Failed to edit tag.");
            return 0;
        }
        printf("Tag edited successfully.\n");
    } 
    else 
    {
        display_help();
        return 0;
    }
    return 0;
}
