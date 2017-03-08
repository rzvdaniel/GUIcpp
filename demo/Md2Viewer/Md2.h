#ifndef T_MD2_H
#define T_MD2_H
//-------------------------------------------------------------------
//  CLASS
//  TMd2
//
//  (C) 2004 R.Predescu
//-------------------------------------------------------------------
#ifndef T_TEXTURE_H
#include "guide/texture.h"
#endif

#ifndef T_STRINGS_H
#include "guide/strings.h"
#endif

#ifndef NULL
#define NULL (0L)
#endif

typedef unsigned char byte;
typedef float vec_t;
typedef vec_t vec3_t[3];

#define MD2_MAX_TRIANGLES		4096
#define MD2_MAX_VERTICES		2048
#define MD2_MAX_TEXCOORDS		2048
#define MD2_MAX_FRAMES			512
#define MD2_MAX_SKINS			32
#define MD2_MAX_FRAMESIZE		(MD2_MAX_VERTICES * 4 + 128)

typedef struct 
{ 
   int magic; 
   int version; 
   int skinWidth; 
   int skinHeight; 
   int frameSize; 
   int numSkins; 
   int numVertices; 
   int numTexCoords; 
   int numTriangles; 
   int numGlCommands; 
   int numFrames; 
   int offsetSkins; 
   int offsetTexCoords; 
   int offsetTriangles; 
   int offsetFrames; 
   int offsetGlCommands; 
   int offsetEnd; 
} md2_header_t;

typedef struct
{
   byte vertex[3];
   byte lightNormalIndex;
} md2_alias_triangleVertex_t;

typedef struct
{
   float vertex[3];
   float normal[3];
} md2_triangleVertex_t;

typedef struct
{
   short vertexIndices[3];
   short textureIndices[3];
} md2_triangle_t;

typedef struct
{
   short s, t;
} md2_textureCoordinate_t;

typedef struct
{
   float scale[3];
   float translate[3];
   char name[16];
   md2_alias_triangleVertex_t alias_vertices[1];
} md2_alias_frame_t;

typedef struct
{
   char name[16];
   md2_triangleVertex_t *vertices;
} md2_frame_t;

typedef char md2_skin_t[64];

typedef struct
{
   float s, t;
   int vertexIndex;
} md2_glCommandVertex_t;

class md2_model_t
{
public:
	md2_header_t			header;
	md2_skin_t				*skins;
	md2_textureCoordinate_t	*texCoords;
	md2_triangle_t			*triangles;
	md2_frame_t				*frames;
	int						*glCommandBuffer;

public:
	md2_model_t()
	{
		skins = NULL;
		texCoords = NULL;
		triangles = NULL;
		frames = NULL;
		glCommandBuffer = NULL;
	}
};

typedef struct animation_s
{
	char	nameAnimation[16];
	int		firstFrame;
	int		lastFrame;
} animation_t;

typedef struct md2_anim_s
{
	int			count_anim;
	animation_t anim[MD2_MAX_FRAMES];
} md2_anim_t;

enum TRenderStyle { rsLine, rsFill };

//-------------------------------------------------------------------
class TMd2
{
	TTexture* texture;
	md2_model_t* model;
	md2_anim_t	anim;
	int cframe;
	int	canim;
	int speed;
	bool pause;
	
	float color[3];
	TRenderStyle rs;
	TString name;
	TString skin;

public:  
    TMd2();
    virtual ~TMd2();
	
	void Render(void);
	void SetRenderStyle(TRenderStyle value) { rs = value; } 
	void SetPause(bool value) { pause = value; }
	bool GetPause(void) const { return pause; }
	void SetAnimation(int value);
	int GetAnimation(void) const { return canim; }
	const char* GetAnimationName(int animation);
	TString GetName(void) { return name; }
	TString GetSkin(void) { return skin; }

	bool LoadModel(const char* model_name);
	bool LoadSkin(const char* model_skin);
	void UnloadModel(void);
	void DrawFrame(int curFrame);
	void DrawFrameInt(int curFrame, int nextFrame, float pol);
	bool MakeAnim(void);
};

#endif 