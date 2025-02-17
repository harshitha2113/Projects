#ifndef ID3_UTILS_H
#define ID3_UTILS_H

/*
    Structure to hold ID3 tag data.
 */
typedef struct {
    char *title;   /**< Title of the song */
    char *artist;  /**< Artist of the song */
    char *album;   /**< Album name */
    char *year;    /**< Year of release */
    char *contentType; /**< Content Type */
    char *comment;   /**< comment */
} TagData;

/*
    Creates a new TagData structure.
    Pointer to the newly created TagData structure.
 */
TagData* create_tag_data();

/*
    Frees memory allocated for a TagData structure.
    data Pointer to the TagData structure to be freed.
 */
void free_tag_data(TagData *data);

#endif 
