#include "includes.h"


int main(int argc, char argv[])
{

	WORD roundKeys[5];


	DWORD key;
	WORD plaintext,ciphertext,decrypted;
	key=B32(00111010,10010100,11010110,00111111);

	setup_key(key);

	plaintext=B16(00100110,10110111);
	
	cout << "This is project1 for CIS 515 course - Spring 2018" << endl;
	cout << "Name: Sai Krishna Ganji" << endl;
	cout << "BU ID # 272754" << endl;
	cout << "Mail Id: sganji@mail.bradley.edu" << endl;
	cout << "***********************************************************************" << endl;
	cout << "The encryption starts here" << endl;
	
	encrypt(ciphertext,plaintext);
	cout << "The ciphertext after encryption" << endl;
	cout << "Y  : ";
	printbits(ciphertext);

	cout<<"------------------------------------------------------"<<endl;
	cout << "The decryption starts here" <<endl;

	decrypt(decrypted,ciphertext);

	
	cout <<"The plaintext after decryption" << endl;
	cout << "W0 : ";
	printbits(decrypted);
	

	system("pause");
	return 0;
}