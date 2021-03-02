#pragma once

#include <funnan/Scene.h>
#include <filesystem>

namespace funnan
{
	class FUNNAN_EXPORT SceneParser
	{
	public:
		SceneParser(Scene& x);

		bool loadFile(const std::filesystem::path& x);
		bool writeFile(const std::filesystem::path& x);

	private:
		Scene& scene;
	};
}