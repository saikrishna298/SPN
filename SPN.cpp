#include "includes.h"

WORD sbox[]= {0x0E, 0x04, 0x0D, 0x01, 0x02, 0x0F, 0x0B, 0x08, 0x03, 0x0A, 0x06, 0x0C, 0x05, 0x09, 0x00, 0x07};

WORD rev_sbox[] = {0x0E, 0x03, 0x04, 0x08, 0x01, 0x0C, 0x0A, 0x0F, 0x07, 0x0D, 0x09, 0x06, 0x0B, 0x02, 0x00, 0x05};
WORD pbox[]= {0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15};

WORD num_rounds=4;

DWORD key;

void printbits(WORD n) {

	WORD mask = B16(10000000,00000000);
	int counter=0;
	WORD temp=0;

	while ( mask ){

		temp = n & mask;

		if (temp){
			cout<<"1";
		}
		else{
			cout<<"0";
		}

		mask = mask >> 1;

		counter++;

		if (counter % 4 == 0){
			cout<<" ";
		}
		
	}
	cout<<endl;


}

void setup_key(DWORD newKey){
	key=newKey;
	//cout<<"KEY: "<<key<<endl;
}

void generate_round_keys(WORD* roundKeys){

	int counter=0;
	WORD temp;

	/*
	write a loop that loops 5 times
		shift the KEY left 4*counter, shift the key right 16 times,
		store the result in roundKeys[counter]


	*/

	for (counter=0; counter < 5; counter++){

		//temp = (key << counter * 4) >> 16;
		//temp = temp >> 16;
		//roundKeys[counter] = temp;

		roundKeys[counter] = (key << counter * 4) >> 16;

		//printbits(roundKeys[counter]);


	}

}

void encrypt (WORD& out, WORD in){
	/* //WORD roundKeys[]={0,0,0,0,0};
	WORD roundKeys[5];
	WORD temp;
	WORD ciphertext;

	int x = 0;

	generate_round_keys(roundKeys);
	// print the keys */

	/*
	for (x=0; x< 5; x++){
	printbits(roundKeys[x]);
	}
	*/
	

	WORD roundKeys[5];
	generate_round_keys(roundKeys);

	encrypt(out,in,sbox,pbox,roundKeys);

}

void decrypt (WORD& out, WORD in){
	WORD roundKeys[5];
	generate_round_keys(roundKeys);
	decrypt(out, in, rev_sbox, pbox, roundKeys);
	}

void substitute(WORD& out, WORD in, WORD* sbox){

	WORD temp;
	WORD mask = B16(00000000,00001111);

	int counter=0;


	out = 0;

	/*
	 write a for loop that loops 4 times
	{
		1. mask off the bits from input,  put them into temp, shift them properly
		2. feed temp into the sbox, store the result back in temp;
		3. shift temp left properly, put the result into out at correct location


	}
			*/

	//printbits(in);

	for (counter=0; counter<4; counter++){
		
		temp = in & (mask << (4 * counter));
		temp = temp >> (4 * counter);

		temp = sbox[temp];
		temp = temp << (4 * counter);

		//printbits(temp);
		out = out | temp;
		//out = out | (sbox[(in & mask << 4*counter) >> 4* counter] << 4 * counter);

	}



}


void substitute_noloop(WORD& out, WORD in, WORD* sbox){

	WORD inp1, inp2, inp3, inp4;
	WORD out1, out2, out3, out4;

	WORD mask = B16(00000000,00001111);

	inp4 = in & mask;

	mask<<=4;
	inp3 = in & mask;
	inp3 >>=4;

	mask<<=4;
	inp2 = in & mask;
	inp2 >>=8;

	mask<<=4;
	inp1 = in & mask;
	inp1 >>=12; 

	printf("%d %d %d %d\n", inp1, inp2, inp3, inp4);


	out1 = sbox[inp1];
	out2 = sbox[inp2];
	out3 = sbox[inp3];
	out4 = sbox[inp4];


	printf("%d %d %d %d\n", out1, out2, out3, out4);


	out = 0;
	
	out1 = out1 << 12;
	out = out | out1;
	
	out2 = out2 << 8;
	out = out | out2;

	out3 = out3 << 4;
	out = out | out3;

	out = out | out4;

	printbits(out);
	

}

void permute(WORD& out, WORD in, WORD* pbox){

	WORD mask = B16(10000000,00000000);

	WORD temp = 0;

	int loc = 0;
	int counter = 0;

	out = 0;


	/*

	write a loop with the counter that goes 0 to 15
		mask off the bit, store the result in temp;
		if temp is non-zero (true){
			go to pbox at index counter, get the output bit location, store that in loc
			binary or the output with the mask shifted right loc times
		}

	*/


	//printbits(in);

	for (int counter = 0; counter < 16; counter++){
		temp = in & (mask >> counter);

		if (temp){
			loc = pbox[counter];
			out = out | (mask >> loc);

		}


	}

	//printbits(out);

}

void deencrypt (WORD& out, WORD in, WORD* sbox, WORD* pbox, WORD* roundKeys, MODE mode){

}

void encrypt (WORD& out, WORD in, WORD* sbox, WORD* pbox, WORD* roundKeys){

	WORD w, u, v;
	w=0;
	u=0;
	v=0;

	w = in;
	u = w ^ roundKeys[0];

	cout<<"W0 : ";
	printbits(w);

	cout << "K1 : ";
	printbits(roundKeys[0]);

	cout<<"U1 : ";
	printbits(u);

	substitute(v,u,sbox);
	cout << "V1 : ";
	printbits(v);

	permute(w, v, pbox);
	cout << "W1 : ";
	printbits(w);

	u = w ^ roundKeys[1];

	cout << "K2 : ";
	printbits(roundKeys[1]);

	cout << "U2 : ";
	printbits(u);

	substitute(v, u, sbox);
	cout << "V2 : ";
	printbits(v);

	permute(w, v, pbox);
	cout << "W2 : ";
	printbits(w);

	u = w ^ roundKeys[2];

	cout << "K3 : ";
	printbits(roundKeys[2]);


	cout << "U3 : ";
	printbits(u);

	substitute(v, u, sbox);
	cout << "V3 : ";
	printbits(v);

	permute(w, v, pbox);
	cout << "W3 : ";
	printbits(w);

	u = w ^ roundKeys[3];
	cout << "K4 : ";
	printbits(roundKeys[3]);

	cout << "U4 : ";
	printbits(u);

	substitute(v, u, sbox);
	cout << "V4 : ";
	printbits(v);

	out = v ^ roundKeys[4];

	cout << "K5 : ";
	printbits(roundKeys[4]);
	
}


void decrypt(WORD& out, WORD in, WORD* rev_sbox, WORD* pbox, WORD* roundKeys){


	WORD w, u, v;
	w = 0;
	u = 0;
	v = 0;

	w = in;
	u = w ^ roundKeys[4];

	cout << "The cipher text is:" <<endl;
	cout << "Y  : ";
	printbits(w);

	cout << "K5 : ";
	printbits(roundKeys[4]);

	cout << "V4 : ";
	printbits(u);

	substitute(v, u, rev_sbox);
	cout << "U4 : ";
	printbits(v);

	u = v ^ roundKeys[3];

	cout << "K4 : ";
	printbits(roundKeys[3]);

	cout << "W3 : ";
	printbits(u);

	permute(w, u, pbox);
	cout << "V3 : ";
	printbits(w);

	substitute(v, w, rev_sbox);
	cout << "U3 : ";
	printbits(v);

	u = v ^ roundKeys[2];
	cout << "K3 : ";
	printbits(roundKeys[2]);

	cout << "W2 : ";
	printbits(u);

	permute(w, u, pbox);
	cout << "V2 : ";
	printbits(w);

	substitute(v, w, rev_sbox);
	cout << "U2 : ";
	printbits(v);

	u = v ^ roundKeys[1];
	cout << "K2 : ";
	printbits(roundKeys[1]);

	cout << "W1 : ";
	printbits(u);

	permute(w, u, pbox);
	cout << "V1 : ";
	printbits(w);

	substitute(v, w, rev_sbox);
	cout << "U1 : ";
	printbits(v);

	out = v ^ roundKeys[0];
	cout << "K1 : ";
	printbits(roundKeys[0]);

}