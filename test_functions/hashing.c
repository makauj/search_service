#include<stdio.h>
#include<stdlib.h>

/**
 * hash - fuction that adds ASCII values of all characters
 * @str - string to convert
 *
 * Return: the hash
 */
//This is a simple sum hash that is easy to start
//but is not good for production
unsigned int hash(const char *str)
{
	unsigned int hash = 0;

	while (*str)
	{
		hash += *str;
		str++;
	}
	return (hash);
}


/**
 * hash - fuction that adds ASCII values of all characters
 * @str - string to convert
 *
 * Return: the hash
 */
//DJB2 Hash: A popular hashing function
unsigned int hash(const char *str)
{
	unsigned int hash = 5381;
	int c;

	while ((c = *str++))
	{
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}
