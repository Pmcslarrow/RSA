
//RSA.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#define PRIME_LEN 3
//#define RAND_SEED 451

//Functions:


uint64_t square_root(uint64_t n)
{
    uint64_t root = 0;
	while (((root + 1) * (root + 1)) <= n)
	{
		root++;
	}
	return root;
}

//returns 1 if it is prime, returns 0 if it is not
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

//returns the number that happens to be prime
uint64_t getPrime()
{
    time_t t;
    srand((unsigned) time(&t));


    uint64_t i = rand() % 10000;
    while (1) {
        if (isPrime(i))
        {
            break;
        }
        i++;
    }
    return i;
}

uint64_t *getPrimes(){
    //malloc -- allocates memory location with a pointer to it
	uint64_t *ret = (uint64_t *)malloc(sizeof(uint64_t));
	ret[0]= getPrime();
	return ret;
}

uint64_t get_second_prime(uint64_t p)
{
    p++;
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

//Returns a coprime number greater than 2 and less than the totient whose gcd between itself and totient is 1. 
uint64_t coprime(uint64_t totient)
{
    //iterates cand each loop through and checks to see coPrime
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

//Takes an integer and uses my algorithm to turn it into a new integer value!
uint64_t string_to_int1(char* s)
{
    uint64_t i = 0, end=0;
    while(s[i])
    {
        end += (uint64_t)s[i++];
    }
    return end;
}


//Takes in an integer and returns a character array (string)
char * int_to_string(uint64_t integer)
{
    static char word_array[10];
    uint64_t i = 0;
    while (integer > 0)
    {
        char letter = (char) integer % 256;
        printf("character:  %c\n", letter);
        word_array[i] = letter;
        integer = integer / 256;
        i++;
    }
    
    return word_array;
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
    for (uint64_t i = 3; i < totient; i++){
        if ((coP * i) % totient == 1){
            return i;
        }
    }
    return 0;
}

//I genuinely didn't trust using the pow() function that takes doubles, so I got this ipow from here:
//https://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int
uint64_t ipow(uint64_t base, uint64_t exp)
{
    uint64_t result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

//c = m^e mod n
uint64_t encrypt(uint64_t int_message, uint64_t coP, uint64_t n)
{
    return ipow(int_message, coP);
}

//m = c ^ d mod n
uint64_t decrypt(uint64_t cipher, uint64_t d, uint64_t n)
{
    return power(cipher, d, n);
}


//Prints the final word after all the steps
void print_final(char* word)
{
    printf("###################\n");
    printf("PRINTING FINAL WORD:\n");
    for (int i = sizeof(word) / sizeof(char); i >= 0; i--){
            printf("%c", word[i]);
            word[i] = word[i];
        }
    printf("###################\n");
}



int main(){
    uint64_t p, q, n, totient, coP, k, d, c, m, greatest_common_div, cipher, int_as_string, decrypt_messsage, string_as_int, z, exp;
    //prime_location[0] holds an allocated pointer in memory wth unsigned 64 bit integer size.
    uint64_t *prime_location = getPrimes();
    p = prime_location[0];
    q = get_second_prime(p);
    n = p * q;
    totient = (p - 1) * (q - 1);
    coP = coprime(totient);
    d = find_d(coP, totient);

    //POST VARIABLE
    char *str = "pau";
    string_as_int = string_to_int1(str);
    cipher = encrypt(string_as_int, coP, n);
    decrypt_messsage = decrypt(cipher, d, n);

    printf("p:  %d\n", p);
    printf("q:  %d\n", q);
    printf("n:  %d\n", n);
    printf("totient:  %d\n", totient);
    printf("CoPrime:  %d\n", coP);
    printf("d:  %d\n", d);
    printf("String as an integer:  %d\n", string_as_int);
    printf("CIPHER:  %d\n", cipher);
    printf("DECIPHER:  %d\n", decrypt_messsage);



    //You finally made it decipher. Now figure out how to change the number back into characters
    int_as_string = int_to_string(decrypt_messsage);

}
