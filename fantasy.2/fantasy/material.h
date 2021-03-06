#ifndef MATERIAL_H
#define MATERIAL_H

#ifdef WINDOZE
#include <windows.h>
#endif

#include <GL/gl.h>
#ifdef WINDOZE
 #include <GL/glext.h>
#else
 #include <GL/glext.h>
 #include <ctype.h>
#endif

#include "textura.h"

// Tipos de blend

#define BLEND_BLEND 0    // Blend normal  GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA
#define BLEND_ADD   1    // Blend aditivo GL_SRC_ALPHA, GL_ONE
#define BLEND_MULTIPLY 2 // Blend multiplicativo GL_DST_COLOR, GL_ZERO
#define BLEND_MODULATE 3 // Multitexturing...
#define BLEND_REPLACE  4 // Multitexturing...
#define BLEND_MASK	5 // Multitexturing, requiere de la extensi�n TEXTURE_ENV_COMBINE
#define BLEND_DOT3      6 // Multitexturing, requiere de la extensi�n TEXTURE_ENV_DOT3
#define BLEND_SUB	7 // Blend substractivo, depende de la extensi�n EXT_blend_substract
#define BLEND_MASK2	8 // Multitexturing, requiere de la extensi�n TEXTURE_ENV_COMBINE (experimental)

// Tipos de generaci�n de coordenadas de textura

#define TEXGEN_UV 0  // This texture unit will use the uv coords from the 3ds file
#define TEXGEN_EYE_LINEAR 1
#define TEXGEN_OBJECT_LINEAR 2
#define TEXGEN_SPHERE_MAP 3
#define TEXGEN_CUBE_MAP 4


//Parametros para el shader(rellenado en el script)
struct ShaderParam
{
	int used;
	char *name[4];
	float paramf[4];
};

struct shader_info
{
    GLhandleARB programObj;
    GLhandleARB vertexShader;
    GLhandleARB fragmentShader;	
    GLuint loc_TexUnit[8];
    GLuint loc_Camera;
    GLuint loc_NLights;
    float Camera[3];
    int nlights;
    // Parametros para los shaders pasados por script
    ShaderParam params;
};

struct material
{
 char matname[256];
 int shader_based;	 // 0: static (texture-based) 1: dynamic (shader-based)
 int opaque;	 // 1: opaque 	0: translucent
 int twosided;	 // 0: 1 cara; 1: 2 caras
 int blend_type;
 int ntextures;
 int *textures;
 int *multitexblend;
 int *texcoordgen;
 float *linearmultiplier;
 float specular[4];	 // Valor de iluminaci�n especular
 float shininess;        // Exponente especular
 float emission[4];      // color que emite el material
 struct shader_info shader;
};
typedef struct material material;


class Material
{
 protected:

 // Los siguientes par�metros son el plan switch, para no hacer llamadas repetidas a glEnable y glDisable

	int blend_enabled;
	int culling_enabled;
	int force_always_blend; // Si tenemos un alpha distinto de 1, habr� que forzar el blend siempre
	int last_used_material;
 public:
     	int numero_materiales;
        material *materiales;
        int texture_env_combine_supported;
        int texture_env_dot3_supported;
        int texture_cube_map_supported;
        int blend_substract_supported;
	
        int MatReader(char *filename);
	void SelectMaterial(int nmat, int force);
	int FindMaterial(char *cadena);
	int isOpaque (int nmat);
	void ResetMatParameters(void);
        void SetForceAlwaysBlend(int yesno);
        void CleanupTextures(void);
        void CleanupShaderObjects(void);
        int Material::NumTextures(int nmat);

	Material()
	{
	 numero_materiales=0;
	 materiales=NULL;
	 blend_enabled=0;
	 culling_enabled=1;
         force_always_blend=0;
         texture_env_combine_supported=0;
         texture_env_dot3_supported=0;
         texture_cube_map_supported=0;
         blend_substract_supported=0;
         last_used_material = -1;
	};
};



#endif
