#ifndef _SDL_HELPERS_HPP_
#define _SDL_HELPERS_HPP_
#include <vector>
#include <SDL2/SDL_stdinc.h>

struct SdlStrings
{
	std::vector<char*> v;

	char* const* begin()
	{
		return &v.front();
	}

	char* const* end()
	{
		return (&v.back()) + 1;
	}

	void destory()
	{
		for (auto& s : v)
			SDL_free(s);
	}

	void clear()
	{
		destory();
		v.resize(0);
	}

	~SdlStrings()
	{
		destory();
	}
};

#endif // !_SDL_HELPERS_HPP_