#include <stdlib.h>
#include <string.h>
#include "id3_utils.h"

/*
    Allocates and initializes a new TagData structure.
    return Pointer to the newly allocated TagData structure.
 */
TagData* create_tag_data() {
    TagData *data = (TagData *)malloc(sizeof(TagData));
    if (data) {
        data->title = NULL;
        data->artist = NULL;
        data->album = NULL;
        data->year = NULL;
        data->contentType = NULL;
        data->comment = NULL;
    }
    return data;
}

/*
    Frees memory allocated for a TagData structure.
    Parameter: data Pointer to the TagData structure to be freed.
 */
void free_tag_data(TagData *data) {
    if (data) {
        free(data->title);
        free(data->artist);
        free(data->album);
        free(data->year);
        free(data->contentType);
        free(data->comment);
        free(data);
    }
}
