#ifndef DEBUGPRINTER_H
#define DEBUGPRINTER_H

class CDebugger;
class CDebugPrinter
{
public:
							CDebugPrinter					(void);
							CDebugPrinter					(POINT& ltp, POINT& rbp);
							CDebugPrinter					(D3DXVECTOR2& ltp, D3DXVECTOR2& rbp);
							CDebugPrinter					(int ltpx, int ltpy, int rbpx, int rbpy);
						   ~CDebugPrinter					(void);

			void			Init							(void);
			
			void			StringSet						(const std::string& str);
			void			StringAdd						(const std::string& str);

			void			Translate						(void);
			void			Print							(HANDLE *hMainConsole);

			void			HighLight						(void);
			void			UnHighLight						(void);
			void			SetAttributes					(void);

	
			POINT			m_ltPosition;
			POINT			m_rbPosition;
			POINT			m_size;

			CHAR_INFO*		m_pPrintBuffer;

			SMALL_RECT		m_scrWriteRect;
			COORD			m_bufferSize;
			COORD			m_bufferChord;

			std::string		m_label;
			std::string		m_stringToPrint;

			unsigned		m_page;
			
			bool			m_isClear;
			bool			m_isHighLighted;

			CDebugger*		m_pDG;
};

#endif