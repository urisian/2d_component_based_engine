#ifndef MYSTRUCTURES_H
#define MYSTRUCTURES_H

typedef struct tagTexInfo
{
	LPDIRECT3DTEXTURE9 pTexture; // hBitmap과 동일한 역할이라고 생각하면 되겠다. 그림한장을 제어하기 위한 컴객체. 
	D3DXIMAGE_INFO tImageInfo;// 이미지의 정보를 파일에 읽어와 보관할 구조체. 
}TEXINFO;

struct CustomVertex
{
	CustomVertex()
		:position(0.0f, 0.0f, 0.0f),
		texture(0.0f, 0.0f),
		color(0)
	{}

	CustomVertex(float x, float y, float z, float u, float v)
		:position(x, y, z),
		texture(u, v),
		color()
	{}

	CustomVertex(const D3DXVECTOR3& v, const D3DXVECTOR3& uv)
		:position(v),
		texture(uv),
		color()
	{}

	D3DXVECTOR3 position;   // Position Vector
	D3DXVECTOR2 texture;    // Texture  Coordinate
	D3DCOLOR    color;

};

#endif // !MYSTRUCTURES_H
