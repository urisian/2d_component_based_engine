#ifndef MYSTRUCTURES_H
#define MYSTRUCTURES_H

typedef struct tagTexInfo
{
	LPDIRECT3DTEXTURE9 pTexture; // hBitmap�� ������ �����̶�� �����ϸ� �ǰڴ�. �׸������� �����ϱ� ���� �İ�ü. 
	D3DXIMAGE_INFO tImageInfo;// �̹����� ������ ���Ͽ� �о�� ������ ����ü. 
}TEXINFO;

struct CustomVertex
{
	CustomVertex()
		:position(0.0f, 0.0f, 0.0f),
		texture(0.0f, 0.0f)
	{}

	CustomVertex(float x, float y, float z, float u, float v)
		:position(x, y, z),
		texture(u, v)
	{}

	CustomVertex(const D3DXVECTOR3& v, const D3DXVECTOR3& uv)
		:position(v),
		texture(uv)
	{}

	D3DXVECTOR3 position;   // Position Vector
	D3DXVECTOR2 texture;    // Texture  Coordinate
};

#endif // !MYSTRUCTURES_H
