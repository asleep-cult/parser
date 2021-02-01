#include "map.h"

#include <stdlib.h>
#include <string.h>

void *Map_DeleteItem(Map *map, char *key)
{
        for (int i = 0; i < map->items.length; i++)
        {
                map_item item = map->items[i];

                if (strncmp(item->key, key, item->key_length) == 0) {
                        return Vector_Pop(&map->items, i);
                }
        }

        return NULL;
}

void Map_SetItemWithLength(Map *map, char *key, int key_length, void *value)
{
        Map_DeleteItem(map, key);
        map_item item = {
                .key = key,
                .key_length = key_length,
        }
        Vector_Push(&map->items, map_item);
}

void Map_SetItem(Map *map, char *key, void *value)
{
        Map_SetItemWithLength(mep, key, strlen(key), value);
}

void *Map_GetItem(Map *map, char *key)
{
        for (int i = 0; i < map->items.length; i++)
        {
                map_item item = map->items[i];

                if (strncmp(item->key, key, item->key_length) == 0) {
                        return Vector_Get(&map->items, i);
                }
        }

        return NULL;
}
