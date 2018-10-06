#ifndef _GLOBAL_H
#define _GLOBAL_H

#define DEBUG

#define NULL 0

typedef unsigned short int WORD;
typedef unsigned int DWORD;
typedef unsigned char BYTE;

enum MODE {ENCRYPT,DECRYPT};

void printbits(WORD n);

void generate_round_keys(WORD* roundKeys);
void setup_key(DWORD newKey);

void encrypt (WORD& out, WORD in);
void encrypt (WORD& out, WORD in, WORD* sbox, WORD* pbox, WORD* roundKeys);

void decrypt (WORD& out, WORD in);
void decrypt (WORD& out, WORD in, WORD* sbox, WORD* pbox, WORD* roundKeys);

void deencrypt (WORD& out, WORD in, WORD* sbox, WORD* pbox, WORD* roundKeys, MODE mode);


void test_sub(WORD& out, WORD in);

void test_permute(WORD& out, WORD in);

#endif