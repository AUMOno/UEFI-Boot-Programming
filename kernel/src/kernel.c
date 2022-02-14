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

#define PSF1_MAGIC0 0x36;
#define PSF1_MAGIC1 0x04;

typedef struct {
    unsigned char magic[2];
    unsigned char mode;
    unsigned char charsize;
} PSF1_HEADER;

typedef struct {
    PSF1_HEADER* psf1_header;
    void* glyph_buffer;
} PSF1_FONT;

int _start(Framebuffer* frameBuffer)
{
    unsigned int y = 49;
	unsigned int BPP = 4;

    // Incrementing by BPP sets RGB
	for (unsigned int x = 0; x < frameBuffer->Width / 2 * BPP; x += BPP)
	{
		*(unsigned int*)(x + (y * frameBuffer->PixelsPerScanLine * BPP) + frameBuffer->BaseAddress) = 0xff00ffff;
	}

    return 255;
}