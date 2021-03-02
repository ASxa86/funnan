#pragma once

#include <funnan/Time.h>
#include <funnan/export.hxx>

namespace funnan
{
	class Scene;

	class FUNNAN_EXPORT System
	{
	public:
		virtual void fixed(funnan::Time x, Scene& scene);
		virtual void variable(funnan::Time x, Scene& scene);
		virtual void render(funnan::Time x, Scene& scene);
	};
}
