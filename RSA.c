//RSA.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#define PRIME_LEN 3

//Functions:

//My own square root function
uint64_t square_root(uint64_t n)
{
    uint64_t root = 0;
	while (((root + 1) * (root + 1)) <= n)
	{
		root++;
	}
	return root;
}

//Returns true if isPrime and false if not(isPrime)
bool isPrime(uint64_t n)
{

    if (n == 1)
    {
        return false;
    }

    uint64_t root = square_root(n);
    for (int d = 2; d <= root; d++)
    {
        if (n % d == 0)
        {
            return false;
        }
    }
    return true;
}

//Returns a prime number
uint64_t getPrime()
{
    time_t t;
    srand((unsigned) time(&t));

    uint64_t i = rand() % 99999;
    while (1) {
        if (isPrime(i) && i > 20000)
        {
            break;
        }
        i++;
    }
    return i;
}


uint64_t *getPrimes(){
	uint64_t *ret = (uint64_t *)malloc(sizeof(uint64_t));
	ret[0]= getPrime();
	return ret;
}

uint64_t get_second_prime(uint64_t p)
{
    p += 4051;
    while(1)
    {
        if (isPrime(p)){
            break;
        }
        p++;
    }
    return p;
}

//returns the greatest common divisor using the Euclidean Algorithm
uint64_t gcd(uint64_t a, uint64_t b)
{

    int temp;
    while (1)
    {
        temp = a % b;
        if (temp == 0)
        {
            return b;
        }
        a = b;
        b = temp;
    }

}

uint64_t coprime(uint64_t totient)
{
    uint64_t cand = 3;
    for (uint64_t i = 3; i < totient; i++)
    {
        uint64_t common = gcd(i, totient);
        if (common == 1)
        {
            return i;
        }
    }
}

uint64_t stoi(char *s)
{
    uint64_t i = 0, end = 0;
    for ( int i = 0 ; s[i] ; i++ ) 
    {
        end = end * 256 + s[i];
    }
    return end;
}

char *itos(uint64_t integer)
{
    char str[8], i = 0, j = 0;
    for (; integer > 0 && i < 8 ; i++)
    {
        str[i] = integer % 256;
        integer /= 256;
    }
    char *ret = (char *)malloc(sizeof(uint64_t));
    i = strlen(str) - 1;
    for ( ; i >= 0 ; i-- )
    {
        ret[j++] = str[i];
    }
    return ret;
}

//Modular Exponentiation from (https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/)
uint64_t power(uint64_t x, uint64_t y, uint64_t p)
{
    uint64_t res = 1;     // Initialize result
 
    x = x % p; // Update x if it is more than or
                // equal to p
  
    if (x == 0) return 0; // In case x is divisible by p;
 
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;
 
        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}

uint64_t find_d(uint64_t coP, uint64_t totient)
{
    
    for (uint64_t i = 2; i < totient; i++){
        if (((coP * i) % totient) == 1){
            return i;
        }
    }
    return 0;
}

//c = m^e mod n
uint64_t encrypt(uint64_t int_message, uint64_t coP, uint64_t n)
{
    return power(int_message, coP, n);
}

//m = c ^ d mod n
uint64_t decrypt(uint64_t cipher, uint64_t d, uint64_t n)
{
    return power(cipher, d, n);
}


int main(){
    uint64_t p, q, n, totient, coP, k, d, d2, c, m, greatest_common_div, cipher, decrypt_messsage, int_message, z, exp;
    char* int_as_string, *end;
    //prime_location[0] holds an allocated pointer in memory wth unsigned 64 bit integer size.
    uint64_t *prime_location = getPrimes();
    p = prime_location[0];
    q = get_second_prime(p);
    n = p * q;
    totient = (p - 1) * (q - 1);
    coP = coprime(totient);
    d = find_d(coP, totient);

    //POST VARIABLE
    //THIS PROGRAM ONLY WILL WORK FOR STRINGS WITH 3 CHARACTERS
    char *str = "pau";
    int_message = stoi(str);
    cipher = encrypt(int_message, coP, n);
    decrypt_messsage = decrypt(cipher, d, n);

    printf("p:  %d\n", p);
    printf("q:  %d\n", q);
    printf("n:  %d\n", n);
    printf("totient:  %d\n", totient);
    printf("CoPrime:  %d\n", coP);
    printf("d:  %d\n", d);
    printf("String as an integer:  %d\n", int_message);
    printf("CIPHER:  %d\n", cipher);
    printf("DECIPHER:  %d\n", decrypt_messsage);

    end = itos(decrypt_messsage);
    printf("FINAL: %s", end);
    return 0;
}
