#pragma once
#include "HasTexture.h"
 
template <typename Area>
class ContextMenuItem : public HasTexture {
public:
	ContextMenuItem(const Area& area, RRTexture* texture) :
		area{ area },
		HasTexture{ texture }
	{
	}

	ContextMenuItem(const Area& area) :
		area{ area },
		HasTexture{}
	{
	}

	const Area& GetArea() const {
		return area;
	}
private:
	Area area;
};

