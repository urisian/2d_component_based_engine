#ifndef TEXTURESHADER_H
#define TEXTURESHADER_H

#include "Shader.h"

class CTextureShader : public CShader
{
public:
	explicit										CTextureShader		(void);
												   ~CTextureShader		(void);

	virtual			void							Initialize			(void);
	virtual			void							Release				(void);


protected:
	virtual			void							InitShader			(void);
};

#endif