#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define BUFFER_SIZE 128

typedef struct
{
  uint8_t buffer[BUFFER_SIZE];
  size_t head;
  size_t tail;
  size_t count;
  // In a real FreeRTOS scenario, I would add:
  // SemaphoreHandle_t lock;
} ring_buffer_t;

/**
 * @brief Initializes the buffer.
 * Senior Tip: Always initialize pointers/counts to zero to avoid garbage values.
 */
void rb_init(ring_buffer_t *rb)
{
  if (rb == NULL)
    return;
  rb->head = 0;
  rb->tail = 0;
  rb->count = 0;
}

/**
 * @brief Checks if buffer is full.
 */
bool rb_is_full(ring_buffer_t *rb)
{
  return (rb->count == BUFFER_SIZE);
}

/**
 * @brief Checks if buffer is empty.
 */
bool rb_is_empty(ring_buffer_t *rb)
{
  return (rb->count == 0);
}

/**
 * @brief Pushes a byte into the buffer.
 * @return true if successful, false if buffer overflow.
 */
bool rb_push(ring_buffer_t *rb, uint8_t data)
{
  if (rb == NULL || rb_is_full(rb))
  {
    return false; // Critical for satellites: handle overflows gracefully
  }

  rb->buffer[rb->head] = data;
  rb->head = (rb->head + 1) % BUFFER_SIZE; // Wrap around logic
  rb->count++;

  return true;
}

/**
 * @brief Pops a byte from the buffer.
 * @return true if successful, false if buffer empty.
 */
bool rb_pop(ring_buffer_t *rb, uint8_t *data)
{
  if (rb == NULL || rb_is_empty(rb) || data == NULL)
  {
    return false;
  }

  *data = rb->buffer[rb->tail];
  rb->tail = (rb->tail + 1) % BUFFER_SIZE; // Wrap around logic
  rb->count--;

  return true;
}