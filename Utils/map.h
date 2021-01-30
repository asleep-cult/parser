typedef struct map_item {
        char *key;
        int key_length;
        void *value;
};

typedef struct Map {
        map_item *items;
        int length;
} Map;

void Map_SetItem(Map *map, char *key, void *value);
void Map_SetItemWithLength(Map *map, char *key, int key_length, void *value);
void Map_DeleteItem(Map *map, char *key);
void *Map_GetItem(Map *map, char *key);
