#ifndef FONTMANAGER_H
#define FONTMANAGER_H




class CFontManager
{
public:
	static			CFontManager*		GetInstance			(void);
	static			void				DestroyInstance		(void);

					void				Initialize			(void);
					void				Update				(void);
					void				LateUpdate			(void);
					void				Release				(void);

					void				AddText				(std::string textKey, std::string msg, D3DXVECTOR3 position, D3DXCOLOR color);
					void				RewriteText			(std::string textKey, std::string msg);
					void				DeleteText			(std::string textKey);
					void				DrawMyText			(Text* pText);
private:
										CFontManager		(void);
									   ~CFontManager		(void);


public:
	std::map<std::string, Text*>		m_mTextList;
					LPD3DXFONT          m_pFont;
	static			CFontManager*		m_s_pInstance;
};

#endif