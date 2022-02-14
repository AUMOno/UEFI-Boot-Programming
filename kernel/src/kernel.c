// General declarations
typedef unsigned long long size_t;
/**/

// Used for graphics output
typedef struct {
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	// Software features tend to include extra bytes for added functionality
	unsigned int PixelsPerScanLine;
} Framebuffer;

typedef struct {
    unsigned char magic[2];
    unsigned char mode;
    unsigned char charsize;
} PSF1_HEADER;

typedef struct {
    PSF1_HEADER* psf1_header;
    void* glyph_buffer;
} PSF1_FONT;

typedef unsigned int UInt;

void putChar(Framebuffer* frameBuffer, PSF1_FONT* psf1Font, UInt color, char character, UInt xOff, UInt yOff)
{
    UInt* pixPtr = (UInt*)frameBuffer->BaseAddress;
    // Use base address block to add the character, AKA find the decimal value
    char* fontPtr = psf1Font->glyph_buffer + (character * psf1Font->psf1_header->charsize);
    
    // Bitmap height
    for (UInt y = yOff; y < yOff + 16; y++)
    {
        // Bitmap width
        for (UInt x = xOff; x < xOff + 8; x++)
        {
            // Check bit at offset
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
            {
                *(UInt*)(pixPtr + x + (y * frameBuffer->PixelsPerScanLine)) = color;
            }
        }
        fontPtr++;
    }
}

int _start(Framebuffer* frameBuffer, PSF1_FONT* psf1Font)
{
    UInt y = 49;
	UInt BPP = 4;

    // Incrementing by BPP sets RGB
	for (UInt x = 0; x < frameBuffer->Width / 2 * BPP; x += BPP)
	{
		*(UInt*)(x + (y * frameBuffer->PixelsPerScanLine * BPP) + frameBuffer->BaseAddress) = 0xff00ffff;
	}

    putChar(frameBuffer, psf1Font, 0xffffffff, 'A', 16, 16);

    return 255;
}