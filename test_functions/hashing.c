#include<stdio.h>
#include<stdlib.h>

/**
 * hash - fuction that adds ASCII values of all characters
 * @str: string to convert
 *
 * Return: the hash
 */
//This is a simple sum hash that is easy to start
//but is not good for production as it does not handle collisions well
//Simple Hash: A basic hash function that sums ASCII values
unsigned int simple_hash(const char *str)
{
	unsigned int hash = 0;

	if (str == NULL)
		return 0; // Handle null pointer

	while (*str)
	{
		hash += *str;
		str++;
	}
	return (hash);
}


/**
 * hash - fuction that adds ASCII values of all characters
 * @str: string to convert
 *
 * Return: the hash
 */
//DJB2 Hash: A popular hashing function
unsigned int djb_hash(const char *str)
{
	unsigned int hash = 5381;
	int c;

	if (str == NULL)
		return 0; // Handle null pointer

	while ((c = *str++))
	{
		hash = ((hash << 5) + hash) + c; // bit shift everything left by 5 bits and add the current character
		// This is equivalent to hash = hash * 33 + c;
		// The number 33 is a prime number, which helps in reducing collisions
		// You can also use hash = hash * 31 + c; for a different prime number
		// or hash = hash * 37 + c; for another variation
		// The choice of 33 is arbitrary but has been found to work well in practice
	}
	return hash;
}


/**
 * hash - function that adds ASCII values of all characters
 * @str: string to convert
 *
 * Return: the hash
 */
//SDBM Hash: Another popular hashing function
unsigned int sdbm_hash(const char *str)
{
	unsigned int hash = 0;
	int c;

	if (str == NULL)
		return 0; // Handle null pointer

	while ((c = *str++))
	{
		hash = c + (hash << 6) + (hash << 16) - hash; // bit shift everything left by 6 bits and 16 bits, then subtract the original hash
		// This is equivalent to hash = hash * 65599 + c;
		// 65599 is a prime number, which helps in reducing collisions
		// You can also use hash = hash * 65537 + c; for a different prime number
		// or hash = hash * 65521 + c; for another variation
		// The choice of 65599 is arbitrary but has been found to work well
		// in practice, especially for strings with a lot of characters
	}
	return hash;
}

/**
 * hash - function that adds ASCII values of all characters
 * @str: string to convert
 *
 * Return: the hash
 */
 //mumurHash: A more complex hash function
unsigned int murmur_hash(const char *str)
{
	unsigned int hash = 5381;
	int c;

	if (str == NULL)
		return 0; // Handle null pointer

	while ((c = *str++))
	{
		hash ^= c; // XOR the current hash with the current character
		// XOR operation helps in mixing the bits
		hash *= 0x5bd1e995; // 0x5bd1e995 is a prime number
		// Multiplying by a prime number helps in spreading out the hash values
		hash ^= hash >> 15; // Mix the bits by shifting right by 15 bits
		// This helps in further reducing collisions
		// This is a common technique in hash functions to reduce collisions
	}
	return hash;
}

/**
 * main - Entry point for testing the hash functions
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	const char *test_str = "Hello, World!";
	unsigned int hash1 = simple_hash(test_str);
	unsigned int hash2 = djb_hash(test_str);
	unsigned int hash3 = sdbm_hash(test_str);
	unsigned int hash4 = murmur_hash(test_str);

	const char *hash_name = "The comments for each function are helpful but could be improved for clarity.";
	unsigned int hash_name_value = simple_hash(hash_name);
	unsigned int hash_name_djb = djb_hash(hash_name);
	unsigned int hash_name_sdbm = sdbm_hash(hash_name);
	unsigned int hash_name_murmur = murmur_hash(hash_name);

	printf("Hashing Example: %s\n", test_str);
	printf("Simple Hash: %u\n", hash1);
	printf("DJB2 Hash: %u\n", hash2);
	printf("SDBM Hash: %u\n", hash3);
	printf("Murmur Hash: %u\n", hash4);

	printf("\nHashing Example: %s\n", hash_name);
	printf("Simple Hash: %u\n", hash_name_value);
	printf("DJB2 Hash: %u\n", hash_name_djb);
	printf("SDBM Hash: %u\n", hash_name_sdbm);
	printf("Murmur Hash: %u\n", hash_name_murmur);

	return 0;
}
// Compile with: gcc -o hashing hashing.c
// Run with: ./hashing