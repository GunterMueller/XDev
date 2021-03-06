#ifndef Math__h
#define Math__h


extern float atanf (float x);
#define Math_ArcTan atanf

extern float cosf (float x);
#define Math_Cos cosf

extern float expf (float x);
#define Math_Exp expf

extern float logf (float x);
#define Math_Ln logf

extern float powf (float x, float y);
#define Math_Pow powf

extern float sinf (float x);
#define Math_Sin sinf

extern float sqrtf (float x);
#define Math_Sqrt sqrtf

extern void Math_Randomize (void);
extern unsigned int Math_RndRange (unsigned int min, unsigned int max);

#define Math__init()


#endif
