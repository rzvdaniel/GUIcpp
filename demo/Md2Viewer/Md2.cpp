//-------------------------------------------------------------------
//  Md2.cpp
//  (C) 2004 Ricas -- R.Predescu
//
//  All the credits for the md2 models initializing and rendering goes to 
//  mister Mustata Bogdan (LoneRunner)
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//OpenGL MD2Load
//
//Author : Mustata Bogdan (LoneRunner)
//Email  : lonerunner@planetquake.com
//Web    : http://lonerunner.cfxweb.net/
//Date   : 26/11/00
//-------------------------------------------------------------------


#ifdef WIN32
#include <windows.h>
#include <GL/gl.h>
#endif
#include <stdio.h>

#include "Md2.h"
#include "guide/debug.h"

//-------------------------------------------------------------------
//  TMd2()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
TMd2::TMd2()
{
	model = NULL;
	texture = NULL;
	cframe = 0;
	canim = 0;
	speed = 25;	
	pause = false;

	color[0] = 0.8f;
	color[1] = 0.8f;
	color[2] = 0.8f;
	rs = rsFill;
}

//-------------------------------------------------------------------
//  ~TMd2()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
TMd2::~TMd2()
{
	UnloadModel();
	
	if(texture != NULL)
		delete texture;

	t_printf("Free model...\n");
}

//-------------------------------------------------------------------
//  SetAnimation()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TMd2::SetAnimation(int value) 
{ 
	canim = value; 

	if(canim <= 0)
		canim = anim.count_anim-1;
	if(canim >= anim.count_anim-1)
		canim = 0;

	cframe = anim.anim[canim].firstFrame;
}

//-------------------------------------------------------------------
//  GetAnimationName()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
const char* TMd2::GetAnimationName(int animation)
{
	return anim.anim[canim].nameAnimation;
}

//-------------------------------------------------------------------
//  LoadSkin()
//  07-Jan-2004   rzv    created
//-------------------------------------------------------------------
bool TMd2::LoadSkin(const char* model_skin)
{
	// Free texture if we already have one
	if(texture != NULL)
	{
		delete texture;
		texture = NULL;
	}

	// Load texture
	texture = new TTexture;
	if(!texture->Load(model_skin))
	{
		delete texture;
		texture = NULL;
		return false;
	}

	skin.assign(model_skin);

	return true;
}

//-------------------------------------------------------------------
//  LoadModel()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
bool TMd2::LoadModel(const char* model_name)
{
	FILE* md2file;
	char ver[5];
	int	i, j;
	byte buffer[MD2_MAX_FRAMESIZE];
	
	// Free the model if we already have one
	UnloadModel();

	// Load model
	model = new md2_model_t;
	md2file = fopen(model_name, "rb");

	if (md2file == NULL) 
		return false;
	else
	{
		t_printf("load model %s...\n", model_name);
		fread(&model->header, 1, sizeof(md2_header_t), md2file);

		sprintf(ver, "%c%c%c%c", model->header.magic, model->header.magic>>8, model->header.magic>>16, model->header.magic>>24);

		if ( strcmp(ver, "IDP2") || model->header.version != 8) return NULL;

		fseek(md2file, model->header.offsetSkins, SEEK_SET);
		
		model->skins = new md2_skin_t[model->header.numSkins];
		for (i=0; i<model->header.numSkins; i++)
			fread(&model->skins[i], sizeof(md2_skin_t), 1, md2file);
		
		fseek(md2file, model->header.offsetTexCoords, SEEK_SET);

		model->texCoords = new md2_textureCoordinate_t[model->header.numTexCoords];
		
		for (i=0; i<model->header.numTexCoords; i++)
			fread(&model->texCoords[i], sizeof(md2_textureCoordinate_t), 1, md2file);
		
		fseek(md2file, model->header.offsetTriangles, SEEK_SET);
		
		model->triangles = new md2_triangle_t[model->header.numTriangles];
		
		for (i=0; i<model->header.numTriangles; i++)
			fread(&model->triangles[i], sizeof(md2_triangle_t), 1, md2file);
		
		fseek(md2file, model->header.offsetFrames, SEEK_SET);
		model->frames = new md2_frame_t[model->header.numFrames];

		for (i=0; i<model->header.numFrames; i++)
		{
			md2_alias_frame_t *frame = (md2_alias_frame_t *) buffer;

			model->frames[i].vertices = new md2_triangleVertex_t[model->header.numVertices];

			fread(frame, 1, model->header.frameSize, md2file);
			strcpy(model->frames[i].name, frame->name);
			
			for (j=0; j<model->header.numVertices; j++)
			{
				model->frames[i].vertices[j].vertex[0] = (float) ((int) frame->alias_vertices[j].vertex[0]) * frame->scale[0] + frame->translate[0];
				model->frames[i].vertices[j].vertex[2] = -1* ((float) ((int) frame->alias_vertices[j].vertex[1]) * frame->scale[1] + frame->translate[1]);
				model->frames[i].vertices[j].vertex[1] = (float) ((int) frame->alias_vertices[j].vertex[2]) * frame->scale[2] + frame->translate[2];

				//mdl->frames[i].vertices[j].normal[0] = avertexnormals[frame->alias_vertices[j].lightNormalIndex][0];
				//mdl->frames[i].vertices[j].normal[1] = avertexnormals[frame->alias_vertices[j].lightNormalIndex][1];
				//mdl->frames[i].vertices[j].normal[2] = avertexnormals[frame->alias_vertices[j].lightNormalIndex][2];
			}
		}

		fseek(md2file, model->header.offsetGlCommands, SEEK_SET);

		model->glCommandBuffer = new int[model->header.numGlCommands];
		fread(model->glCommandBuffer, sizeof(int), model->header.numGlCommands, md2file);
		
		fclose(md2file);
	}
	
	MakeAnim();

	// Name of the model
	name.assign(model_name);

	return true;
}

//-------------------------------------------------------------------
//  UnloadModel()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TMd2::UnloadModel(void)
{
	if(model != NULL)
	{		
		if(model->skins)
			delete[] model->skins;
		if(model->texCoords) 
			delete[] model->texCoords;
		if(model->triangles) 
			delete[] model->triangles;

		if(model->frames)
		{
			for (int i=0; i<model->header.numFrames; i++)
			{
				if (model->frames[i].vertices) 
					delete[] model->frames[i].vertices;
			}

			delete[] model->frames;
		}

		if(model->glCommandBuffer) 
			delete[] model->glCommandBuffer;
	
		delete model;
		model = NULL;
	}
}

//-------------------------------------------------------------------
//  Render()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TMd2::Render(void)
{
	static int s = 0;

	if(model != NULL)
		DrawFrameInt(cframe, cframe+1, (float)s/(float)speed);

	if(!pause)
	{ 
		if(s > speed)
		{
			if(cframe > anim.anim[canim].lastFrame-3) 
				cframe = anim.anim[canim].firstFrame;
			else 
				cframe = cframe++;

			s = 0;
		}
		else s++;
	}
}

//-------------------------------------------------------------------
//  DrawFrame()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TMd2::DrawFrame(int curFrame)
{
	int i = 0;
	int val = model->glCommandBuffer[i++];

	// Color material
	glColor3f(color[0], color[1], color[2]);

		// Polygon mode
	if(rs == rsLine)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if(rs == rsFill)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Texture
	if(texture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->GetTexId());
	}
	else
		glDisable(GL_TEXTURE_2D);

	while (val != 0)
	{
		int count;

		if (val > 0)
		{
			glBegin(GL_TRIANGLE_STRIP);
			count = val;
		}
		else
		{
			glBegin(GL_TRIANGLE_FAN);
			count = -val;
		}

		while (count--)
		{
			float s =  * (float *) &model->glCommandBuffer[i++];
			float t =  * (float *) &model->glCommandBuffer[i++];
			int index = model->glCommandBuffer[i++];

			glTexCoord2f(s, t);

			//glNormal3f(mdl->frames[curFrame].vertices[index].normal[0],
			//	mdl->frames[curFrame].vertices[index].normal[2],
			//	-mdl->frames[curFrame].vertices[index].normal[1]);

			glVertex3f(model->frames[curFrame].vertices[index].vertex[0],
				model->frames[curFrame].vertices[index].vertex[1],
				model->frames[curFrame].vertices[index].vertex[2]);			
		}

		glEnd ();

		val = model->glCommandBuffer[i++];
	}
}

//-------------------------------------------------------------------
//  DrawFrameInt()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
void TMd2::DrawFrameInt(int curFrame, int nextFrame, float pol)
{
	int i = 0;
	int val = model->glCommandBuffer[i++];
	float x1, y1, z1, x2, y2, z2;
	//float nx1, ny1, nz1, nx2, ny2, nz2;
	
	// Color material
	glColor3f(color[0], color[1], color[2]);

	// Polygon mode
	if(rs == rsLine)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if(rs == rsFill)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Texture
	if(texture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->GetTexId());
	}
	else
		glDisable(GL_TEXTURE_2D);

	while (val != 0)
	{
		int count;

		if (val > 0)
		{
			glBegin(GL_TRIANGLE_STRIP);
			count = val;
		}
		else
		{
			glBegin(GL_TRIANGLE_FAN);
			count = -val;
		}

		while (count--)
		{
			float s =  * (float *) &model->glCommandBuffer[i++];
			float t =  * (float *) &model->glCommandBuffer[i++];
			int index = model->glCommandBuffer[i++];

			glTexCoord2f(s, t);
			
			x1 = model->frames[curFrame].vertices[index].vertex[0];
			y1 = model->frames[curFrame].vertices[index].vertex[1];
			z1 = model->frames[curFrame].vertices[index].vertex[2];

			x2 = model->frames[nextFrame].vertices[index].vertex[0];
			y2 = model->frames[nextFrame].vertices[index].vertex[1];
			z2 = model->frames[nextFrame].vertices[index].vertex[2];

			//nx1 = mdl->frames[curFrame].vertices[index].normal[0];
			//ny1 = mdl->frames[curFrame].vertices[index].normal[1];
			//nz1 = mdl->frames[curFrame].vertices[index].normal[2];

			//nx2 = mdl->frames[nextFrame].vertices[index].normal[0];
			//ny2 = mdl->frames[nextFrame].vertices[index].normal[1];
			//nz2 = mdl->frames[nextFrame].vertices[index].normal[2];
			
			//glNormal3f( nx1 + pol * (nx2 - nx1), ny1 + pol * (ny2 - ny1), nz1 + pol * (nz2 - nz1) );
			glVertex3f( x1 + pol * (x2 - x1), y1 + pol * (y2 - y1), z1 + pol * (z2 - z1) );
		}

		glEnd();

		val = model->glCommandBuffer[i++];
	}
}

//-------------------------------------------------------------------
//  MakeAnim()
//  06-Jan-2004   rzv    created
//-------------------------------------------------------------------
bool TMd2::MakeAnim(void)
{
	char t_st[16], t_name[16], t_last[16];
	int	anim_vector[MD2_MAX_FRAMES];
	int	count_anim, anim_index, t_ln, i;

	anim_index = 0;
	count_anim = 0;

	for(i=0; i<MD2_MAX_FRAMES; i++) anim_vector[i] = 0;

	strcpy(anim.anim[count_anim].nameAnimation, "all frames");
	anim.anim[count_anim].firstFrame = 0;
	anim.anim[count_anim].lastFrame = model->header.numFrames;
	count_anim++;

	for (i=0; i<model->header.numFrames; i++)
	{
		strcpy(t_st, model->frames[i].name);
		t_ln = strlen(t_st);

		t_ln--;
		while (t_st[t_ln] >= '0' && t_st[t_ln] <= '9' || t_st[t_ln] == '_') t_ln--;
		t_ln++;

		strncpy(t_name, t_st, t_ln);
		t_name[t_ln] = '\0';

		if ( strcmp(t_name, t_last) )
		{
			anim_vector[anim_index] = i;
			anim_index++;
				
			strcpy(anim.anim[count_anim].nameAnimation, t_name);
			anim.anim[count_anim].firstFrame = -1;
			anim.anim[count_anim].lastFrame = -1;
			count_anim++;
		}
		
		strcpy(t_last, t_name);
	}

	anim_vector[anim_index] = model->header.numFrames;
	anim_index++;

	for(i=0; i<anim_index; i++)
	{
		anim.anim[i+1].firstFrame = anim_vector[i];
		anim.anim[i+1].lastFrame = anim_vector[i+1];
	}
	
	anim.count_anim = count_anim;

	t_printf("----------------------------\n");
	t_printf("anim: %d\n", anim.count_anim);
	for (i=0; i<anim.count_anim; i++) 
	{
		t_printf("%d %s %d %d\n", i, anim.anim[i].nameAnimation, 
		anim.anim[i].firstFrame, anim.anim[i].lastFrame);
	}

	return true;
}
