#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{

    char block[1024];
    int length=0;
    char res;
    cout<<"Implementation of the File Handler Read Method..."<<endl;

    //FILE *f = fopen("/dev/loop0", "r");
    FILE *f = fopen("/dev/disk2", "r");
    if(f == NULL)
    {
        cout<<"Error In Opening the HardDisk File Retuning Error..."<<endl;
        return -1;
    }

    //Read One Block of Data to Buffer
    //length = fread(block, 1, sizeof(block), f);
    length = fread(block, sizeof(block),1,f);
    printf("Read %u bytes.\r\n", length);

    /* Do something with the data */
    cout<<"Length : "<<length<<endl;
    for (int currentpos=0;currentpos < 1024;currentpos++) {
      std::cout << block[currentpos]<< currentpos <<endl;
//      std::cout << block[currentpos];
    }
    return 0;
}

