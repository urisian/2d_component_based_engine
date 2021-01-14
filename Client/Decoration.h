#ifndef DECORATION_H
#define DECORATION_H

#include "Object.h"
class CDecoration final : public CObject
{
public:
	explicit								CDecoration			(std::string objectKey, std::string stateKey = "");
										   ~CDecoration			(void);

					void					Initialize			(void);
					void					Update				(void);
					void					LateUpdate			(void);
					void					Release				(void);

};

#endif