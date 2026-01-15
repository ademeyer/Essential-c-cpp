/**
 * @file designhasmap.c
 * @author your name (you@domain.com)
 * @brief Design a HashMap without using any built-in hash table libraries.

          Implement the MyHashMap class:
          MyHashMap() initializes the object with an empty map.
          void put(int key, int value) inserts a (key, value) pair into
          the HashMap. If the key already exists in the map, update the
          corresponding value.
          int get(int key) returns the value to which the specified key
          is mapped, or -1 if this map contains no mapping for the key.
          void remove(key) removes the key and its corresponding value
          if the map contains the mapping for the key.
 * @version 0.1
 * @date 2026-01-14
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_KEY 1000001

typedef struct
{
  int *values;
  int *keys;
} MyHashMap;

MyHashMap *myHashMapCreate()
{
  MyHashMap *map = (MyHashMap *)malloc(sizeof(MyHashMap));
  if (!map)
    return NULL;

  map->values = (int *)malloc(sizeof(int) * MAX_KEY);
  if (!map->values)
  {
    free(map);
    return NULL;
  }

  map->keys = (int *)malloc(sizeof(int) * MAX_KEY);
  if (!map->keys)
  {
    free(map->values);
    free(map);
    return NULL;
  }

  // mark all key as -1 (free)
  for (int i = 0; i < MAX_KEY; ++i)
    map->keys[i] = -1;

  return map;
}

void myHashMapPut(MyHashMap *obj, int key, int value)
{
  if (!obj || key < 0 || key >= MAX_KEY)
    return;

  obj->values[key] = value;
  obj->keys[key] = 1; // marked as occuppied;
}

int myHashMapGet(MyHashMap *obj, int key)
{
  if (!obj || key < 0 || key >= MAX_KEY)
    return -1;

  if (obj->keys[key] == -1)
    return -1;

  return obj->values[key];
}

void myHashMapRemove(MyHashMap *obj, int key)
{
  if (!obj || key < 0 || key >= MAX_KEY)
    return;
  // mark key as free
  obj->keys[key] = -1;
}

void myHashMapFree(MyHashMap *obj)
{
  if (obj)
  {
    free(obj->keys);
    free(obj->values);
    free(obj);
  }
}

int main()
{
  printf("=== Testing HashMap Implementation ===\n\n");

  // Create HashMap
  MyHashMap *map = myHashMapCreate();
  if (!map)
    return EXIT_FAILURE;

  // Test put and get
  printf("1. Testing basic put and get:\n");
  myHashMapPut(map, 1, 1);
  myHashMapPut(map, 2, 2);
  printf("   get(1) = %d (expected: 1)\n", myHashMapGet(map, 1));
  printf("   get(2) = %d (expected: 2)\n", myHashMapGet(map, 2));
  printf("   get(3) = %d (expected: -1)\n", myHashMapGet(map, 3));

  // Test update
  printf("\n2. Testing update:\n");
  myHashMapPut(map, 2, 1);
  printf("   After put(2, 1), get(2) = %d (expected: 1)\n", myHashMapGet(map, 2));

  // Test remove
  printf("\n3. Testing remove:\n");
  myHashMapRemove(map, 2);
  printf("   After remove(2), get(2) = %d (expected: -1)\n", myHashMapGet(map, 2));

  // Test with more entries
  printf("\n4. Testing with more entries:\n");
  for (int i = 0; i < 10; i++)
  {
    myHashMapPut(map, i * 100, i * 1000);
  }
  printf("   get(500) = %d (expected: 5000)\n", myHashMapGet(map, 500));
  printf("   get(900) = %d (expected: 9000)\n", myHashMapGet(map, 900));

  // Test collision handling (if using chaining version)
  printf("\n5. Testing collision handling:\n");
  myHashMapPut(map, 10007, 111); // 10007 % 10007 = 0
  myHashMapPut(map, 0, 222);     // 0 % 10007 = 0
  printf("   get(10007) = %d (expected: 111)\n", myHashMapGet(map, 10007));
  printf("   get(0) = %d (expected: 222)\n", myHashMapGet(map, 0));

  // Print all entries (for debugging)
  // myHashMapPrint(map);

  // Clean up
  myHashMapFree(map);

  printf("\n=== Test Complete ===\n");

  return 0;
}