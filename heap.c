#include "shell.h"

/**
 **_fill_memory - fills memory with a constant byte
 *@memory_ptr: pointer to the memory area
 *@byte: the byte to fill *memory_ptr with
 *@bytes_to_fill: the amount of bytes to be filled
 *Return: (memory_ptr) a pointer to the memory area memory_ptr
 */
char *_fill_memory(char *memory_ptr, char byte, unsigned int bytes_to_fill)
{
	unsigned int i;

	for (i = 0; i < bytes_to_fill; i++)
		memory_ptr[i] = byte;
	return (memory_ptr);
}

/**
 * free_string_of_strings - frees a string of strings
 * @string_array: string of strings
 */
void free_string_of_strings(char **string_array)
{
	char **temp = string_array;

	if (!string_array)
		return;
	while (*string_array)
		free(*string_array++);
	free(temp);
}

/**
 * reallocate_memory - reallocates a block of memory
 * @ptr: pointer to previously allocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the old block if no changes in size.
 */
void *reallocate_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}

/**
 * free_pointer_and_nullify - frees a pointer and sets it to NULL
 * @pointer_address: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_pointer_and_nullify(void **pointer_address)
{
	if (pointer_address && *pointer_address)
	{
		free(*pointer_address);
		*pointer_address = NULL;
		return (1);
	}
	return (0);
}
