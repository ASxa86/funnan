#include <funnan/SceneParser.h>
#include <funnan/TypeInfo.h>
#include <fstream>
#include <iostream>
#include <pugixml.hpp>

using namespace funnan;

namespace
{
	void ParseProperties(const pugi::xml_node& x, Properties& p)
	{
		const auto tagProperties = x.children("property");

		for(const auto& tagProperty : tagProperties)
		{
			auto property = p.getProperty(tagProperty.attribute("name").value());

			if(property != nullptr)
			{
				property->setValueString(tagProperty.text().as_string());
			}
			else
			{
				std::cerr << "Scene does not have \"" << tagProperty.name() << "\"\n";
			}
		}

		p.signalDeserialize.notify();
	}

	void WritePropertyTag(pugi::xml_node& x, const Properties& p)
	{
		const auto& properties = p.getProperties();

		for(const auto& property : properties)
		{
			auto tagProperty = x.append_child("property");
			tagProperty.append_attribute("name").set_value(property->getName().data());
			tagProperty.text() = property->getValueString().c_str();
		}

		p.signalSerialize.notify();
	}
}

SceneParser::SceneParser(Scene& x) : scene{x}
{
}

bool SceneParser::writeFile(const std::filesystem::path& x)
{
	pugi::xml_document doc;
	auto tagFunnan = doc.append_child("funnan");
	auto tagScene = tagFunnan.append_child("scene");
	WritePropertyTag(tagScene, this->scene);

	for(const auto& pool : this->scene.getPools())
	{
		auto tagPool = tagScene.append_child("pool");
		tagPool.append_attribute("type").set_value(pool->getComponentType().name.c_str());
		WritePropertyTag(tagPool, *pool);
	}

	return doc.save_file(x.c_str());
}

bool SceneParser::loadFile(const std::filesystem::path& x)
{
	// ArchiveXML archive(x);
	// archive >> Scene;

	// operator>>(Properties& x)
	// 

	pugi::xml_document doc;
	const auto result = doc.load_file(x.c_str());

	if(result.status == pugi::xml_parse_status::status_ok)
	{
		const auto root = doc.child("funnan");

		if(root.empty() == false)
		{
			const auto tagScene = root.child("scene");

			if(tagScene.empty() == false)
			{
				ParseProperties(tagScene, this->scene);

				const auto tagPools = tagScene.children("pool");

				for(const auto& tagPool : tagPools)
				{
					const auto tagPoolAttrib = tagPool.attribute("type");
					const auto pool = this->scene.getPool(tagPoolAttrib.value());

					if(pool != nullptr)
					{
						ParseProperties(tagPool, *pool);
						pool->signalSerialize.notify();
					}
				}

				this->scene.signalSerialize.notify();
			}
		}
	}
	else
	{
		std::cerr << result.description() << "\n";
	}

	return false;
}
