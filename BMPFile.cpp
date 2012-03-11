# include "BMPFile.h"

CBMPFile::CBMPFile() {
}


CBMPFile::CBMPFile(int width, int height) {

	int imageDataSize = width * 3 * height;
	
    stBitmapHeader bmpHeader = { BF_TYPE, sizeof(bmpHeader) + imageDataSize, 0, 0, 
	sizeof(bmpHeader), 40, (unsigned int)width, (unsigned int)height, 1, 
	24,0,imageDataSize,0,0,0,0}; 

    m_bitmapHeader = bmpHeader;

}

void CBMPFile::WriteHeader() {

    ofstream outputFile("image.bmp", ios::binary);

    outputFile.write((const char*)&m_bitmapHeader,sizeof(stBitmapHeader));
}

void CBMPFile::DumpPixel (int red, int green ,int blue) {

    unsigned char ucBlue = (unsigned char)blue;
    unsigned char ucGreen = (unsigned char)green;
    unsigned char ucRed = (unsigned char)red;

    ofstream outputFile ("image.bmp", ios::binary|ios::app);

    outputFile.write ((const char*)&ucBlue, 1);
    outputFile.write ((const char*)&ucGreen,1);
    outputFile.write ((const char*)&ucRed,1);

    outputFile.close();
}

void CBMPFile::PadRow (int rowLength) {

    int padding, numBytes;

    /********************************************************
    STRATEGY:
    1. Find the number of bytes needed for one row.
    2. Check if the number of bytes lies on teh 4 byte padding
       boundary.
    3. If no padding required then return.
    4. Reaching this step means padding is required. Open file
       and dump empty bytes.
    ********************************************************/

    // 1.
    numBytes = rowLength * 3;

    // 2.
    if(numBytes % 4 == 0) {
	padding = 0;
    } else {
	padding = 4 - (numBytes % 4);
    }

    // 3.
    if (! padding) {

	return ;
    }

    // 4.
    ofstream outputFile("image.bmp",ios::binary|ios::app);

    unsigned char emptyByte = 0x00;

    for (int i = 0; i < padding; i++ ) {

	outputFile.write ((const char*)&emptyByte, 1);
    }

    outputFile.close();
}
