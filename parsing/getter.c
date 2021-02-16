#include "parsing.h"

char *check_is_valid_texture_path(char *texture_path) {
    int fd;
    if(strstr(texture_path, ".xpm") != NULL) {
        fd = open((const char *)texture_path, O_RDONLY);
        if(fd == -1) {
            free(texture_path);
            return (NULL);
        }
        else
            return (texture_path);
    } else {
        return (NULL);
    }
}
