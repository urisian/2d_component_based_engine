#pragma once

typedef struct tagTexInfo
{
	LPDIRECT3DTEXTURE9 pTexture; // hBitmap과 동일한 역할이라고 생각하면 되겠다. 그림한장을 제어하기 위한 컴객체. 
	D3DXIMAGE_INFO tImageInfo;// 이미지의 정보를 파일에 읽어와 보관할 구조체. 
}TEXINFO;
