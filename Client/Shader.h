#ifndef SHADER_H
#define SHADER_H

class CShader
{
public:
	explicit										CShader				(void);
	virtual										   ~CShader				(void);

	virtual			void							Initialize			(void) PURE;
	virtual			void							Release				(void) PURE;


protected:
	virtual			void							InitShader			(void) PURE;

protected:
					IDirect3DVertexShader9*			m_pVertexShader;
					IDirect3DPixelShader9*			m_pPixelShader;
					ID3DXBuffer*					m_pShaderBuffer;
					ID3DXBuffer*					m_pErrorBuffer;

					ID3DXConstantTable*				m_pConstantTable;
};

#endif