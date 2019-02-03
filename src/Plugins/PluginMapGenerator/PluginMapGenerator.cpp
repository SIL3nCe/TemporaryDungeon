#include "PluginMapGenerator.h"

#include "MapGenerator/MapGeneratorTest.h"

const CShIdentifier plugin_identifier("PluginMapGenerator");

/**
* @brief Constructor
*/
/*explicit*/ PluginMapGenerator::PluginMapGenerator(void)
: CShPlugin(plugin_identifier)
{
	// ...
}

/**
* @brief Destructor
*/
/*virtual*/ PluginMapGenerator::~PluginMapGenerator(void)
{
	// ...
}

/**
* @brief OnPlayStart
*/
/*virtual*/ void PluginMapGenerator::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
* @brief OnPlayStop
*/
/*virtual*/ void PluginMapGenerator::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
* @brief OnPlayPause
*/
/*virtual*/ void PluginMapGenerator::OnPlayPause(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
* @brief OnPlayResume
*/
/*virtual*/ void PluginMapGenerator::OnPlayResume(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
* @brief OnPreUpdate
*/
/*virtual*/ void PluginMapGenerator::OnPreUpdate(float dt)
{
	// ...
}

/**
* @brief OnPreUpdate
*/
/*virtual*/ void PluginMapGenerator::OnPostUpdate(float dt)
{
	// ...
}

/**
* @brief PluginMapGenerator::CreateMapGenerator
*/
MapGenerator * PluginMapGenerator::CreateMapGenerator(EMapGeneratorType eType)
{
	MapGenerator * pMapGenerator = shNULL;

	switch (eType)
	{
		case e_map_generator_type_test :
		{
			pMapGenerator = new MapGeneratorTest();
		}
		break;

		default :
		{
			SH_ASSERT_ALWAYS();
		}
		break;
	}

	return pMapGenerator;
}

/**
* @brief PluginMapGenerator::DestroyMapGenerator
*/
bool PluginMapGenerator::DestroyMapGenerator(MapGenerator * pMapGenerator)
{
	SH_SAFE_DELETE(pMapGenerator);
	if (shNULL != pMapGenerator)
	{
		SH_ASSERT_ALWAYS();
		return false;
	}
	else
	{
		return true;
	}
}

/**
* @brief PluginMapGenerator::GenerateMap2D
*/
Map2D PluginMapGenerator::GenerateMap2D(MapGenerator * pMapGenerator, shU32 iRowNb /*= MAP_DEFAULT_ROW_NB*/, shU32 iColumnbNb /*= MAP_DEFAULT_COLUMN_NB*/, shU32 iTileSize /*= MAP_DEFAULT_TILE_SIZE*/)
{
	Map2D map;

	if (shNULL != pMapGenerator)
	{
		map.Initialize(iRowNb, iColumnbNb, iTileSize);

		if (!pMapGenerator->GenerateMap(&map))
		{
			map.Release();
		}
	}

	return map;
}