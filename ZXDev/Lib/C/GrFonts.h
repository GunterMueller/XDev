#ifndef GrFonts__h
#define GrFonts__h

typedef
	int GrFonts_Font;

extern unsigned char GrFonts_ZxSpecRus8x8Font [768];
extern unsigned char GrFonts_MsDosCga8x8Font [768];
extern unsigned char GrFonts_MsDosCgaRus8x8Font [1792];
extern unsigned char GrFonts_HalfSpaceRus6x8Font [2048];

#define GrFonts_ZxSpecRom8x8 0x3D00
#define GrFonts_ZxSpecRus8x8 (int)GrFonts_ZxSpecRus8x8Font
#define GrFonts_MsDosCga8x8 (int)GrFonts_MsDosCga8x8Font
#define GrFonts_MsDosCgaRus8x8 (int)GrFonts_MsDosCgaRus8x8Font
#define GrFonts_HalfSpaceRus6x8 (int)GrFonts_HalfSpaceRus6x8Font


#define GrFonts__init()

#endif
