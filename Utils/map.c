#include "map.h"

#include <stdlib.h>
#include <string.h>

void map_resize(Map *map, int length, int move_index)
{
        if (map->length < length) {
                memove(
                        map->items + move_index,
                        map->items + move_index + 1
                        sizeof(map_item) * length
                );
        }
        map->items = realloc(map->items, sizeof(map_item) * length);
        map->length = length;
}

void Map_DeleteItem(Map *map, char *key)
{
        for (int i = 0; i < map->length; i++)
        {
                map_item item = map->items[i];
                if (strncmp(item->key, key, item->key_length) == 0) {
                        map_resize(map, map->length - 1, i);
                        return;
                }
        }
}

void Map_SetItemWithLength(Map *map, char *key, int key_length, void *value)
{
        Map_DeleteItem(map, key);
        map_resize(map, map->length + 1, 0);
        map->items[map->length - 1] = (map_item){key, key_length, value};
}

void Map_SetItem(Map *map, char *key, void *value)
{
        Map_SetItemWithLength(mep, key, strlen(key), value);
}

void *Map_GetItem(Map *map, char *key)
{
        for (int i = 0; i < map->length; i++)
        {
                map_item item = map->items[i];
                if (strncmp(item->key, key, item->key_length) == 0) {
                        return item->value;
                }
        }
        return NULL;
}
