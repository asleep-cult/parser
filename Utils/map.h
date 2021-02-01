#include "vector.h"

typedef struct map_item {
        char *key;
        int key_length;
        void *value;
};

typedef struct Map {
        Vector *items;
        int length;
} Map;

Map *Map_New();
void Map_SetItem(Map *map, char *key, void *value);
void Map_SetItemWithLength(Map *map, char *key, int key_length, void *value);
void Map_DeleteItem(Map *map, char *key);
void *Map_GetItem(Map *map, char *key);
