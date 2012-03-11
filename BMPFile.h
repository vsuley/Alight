# ifndef _BMPFILE_H
# define _BMPFILE_H

# include <fstream>

using namespace std;

# define BF_TYPE 0x4D42

typedef struct{ 

    unsigned short bfType;
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
}stBitmapHeader; 


class CBMPFile {


    public :

	CBMPFile();
	CBMPFile(int width, int height);

	void WriteHeader();
	void DumpPixel(int red, int green, int blue);
	void PadRow(int rowLength);

    protected:
	stBitmapHeader m_bitmapHeader;
};

# endif
