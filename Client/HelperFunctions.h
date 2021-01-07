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

template <typename T>
std::string GetComponentName(T* pObj)
{
	std::string className = typeid(pObj).name();
	className.erase(0, 6);

	return className;
}
#endif // !HELPERFUNCTIONS_H