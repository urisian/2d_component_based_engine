#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H



template <typename T>
void SafeDelete(T*& something)
{
	if (something)
		delete something;

	something = nullptr;
}

inline std::wstring StrToWStr(const std::string& str)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

inline std::string WStrToStr(const std::wstring& wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}


//Math helpers
inline D3DXVECTOR3 GetAngleFromDir(D3DXVECTOR2& dir)
{

	float hypotenuseSize = D3DXVec2Length(&dir);

	return D3DXVECTOR3(0, 0, D3DXToDegree(acosf(dir.x / hypotenuseSize)));
}

inline D3DXVECTOR3 GetAngleFromDir(D3DXVECTOR3& dir)
{
	D3DXVECTOR2 temp = dir;
	float hypotenuseSize = D3DXVec2Length(&temp);

	return D3DXVECTOR3(0, 0, D3DXToDegree(acosf(dir.x / hypotenuseSize)));
}

inline D3DXVECTOR3 GetDirFromAngle(float degree)
{
	return D3DXVECTOR3(cosf(D3DXToRadian(degree)), sinf(D3DXToRadian(degree)), 0);
}



//Get cur class Name
template <typename T>
std::string GetCurClassName(T* pObj)
{
	std::string className = typeid(*pObj).name();
	className.erase(0, 7);

	return className;
}




#endif // !HELPERFUNCTIONS_H
