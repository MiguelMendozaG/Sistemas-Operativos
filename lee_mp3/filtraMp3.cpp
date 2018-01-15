/* some useful headers */
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

//my headers
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

void calculatedetails(ifstream & file)	//function taking inputfilestream as argument to calculate required information and call printmp3details
{
	//file.seekg(0, ios::end);			// obtain filesize in bits
	//size_t filesize = file.tellg();		// 
    	size_t filesize = 32;		// 

	char * buffer;						//array of characters to transfer binary data prior to copying to string
	buffer = new char [filesize];		//dynamically allocate memory

	file.seekg(0, ios::beg);			//transfer binary data from file to buffer array
	file.read(buffer, filesize);		//
	file.close();						//

	int filebitsize = filesize * 8;
	char * bitstorage;
	bitstorage = new char [filebitsize];

	int * c;
	c=new int[2];
	int t,w=0;
	for(unsigned int i = 0; i < filesize; i++)
	{
		for(int k = 0; k < 8; k++)														
		{
//				cerr << "buffer=" << buffer[i] << endl;
			if((k==5||k==6) && i==1 && buffer[i]=='D'){ 
				cerr << "buffer=" << buffer[i] << endl;
					
				t=(buffer[i]>>k);
			//	cerr << "t=" << t << endl;
				c[w]=t & 1;
			//	cerr << "c=" << c[w] << endl;
			//	tipoMp3=tipoMp3 ;
			//	cerr << "tipoMp3=" << c[w] << endl;
				//cerr << "llegas" << k << i << ((buffer[i]>>k) & 1) << endl;
				w++;
			}
//		cerr << "llegas" << k << i << ((buffer[i]>>k) & 1) << endl;
		}
	}
	if(c[0]==0 && c[1]==1) cerr << "Es un archivo MP3" << endl;
	else cerr << "No es un archivo MP3" << endl;
}

/* Main function */
int main(int argc, const char* argv[])
{
	if(argc != 2)									//check correct number of command line arguments entered
	{
		cerr << "filename not included correctly" << endl;
		return(1);
	}

	const char* filename = argv[1];					//take first command line argument (apart from program name) as filename of mp3 to be opened

	ifstream mp3file(filename, ios::binary);		//open mp3 "filename" using binary i/o mode

	if(mp3file.fail() == true)						//check file opens correctly
	{
		cerr << "file failed to open" << endl;
		return(1);
	}
	
	calculatedetails(mp3file);						//call function to calculate required details
	
	return(0);
}
