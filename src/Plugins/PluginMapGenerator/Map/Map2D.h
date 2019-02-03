#pragma once

#include "ShSDK/ShSDK.h"
#include "Map.h"

#define MAP_DEFAULT_ROW_NB 50
#define MAP_DEFAULT_COLUMN_NB 50
#define MAP_DEFAULT_TILE_SIZE 20

typedef shU32 Map2DTile;

class Map2D : public Map
{
	friend class MapGeneratorTest;
	friend class PluginMapGenerator;
public:
	//
	// Constructor/Destructor
	explicit				Map2D			(void);
	virtual					~Map2D			(void);

	//
	// operators
	virtual explicit		operator bool	(void) const SH_ATTRIBUTE_OVERRIDE;

	//
	// Getters/Setters
	virtual EMapType		GetType			(void) const SH_ATTRIBUTE_OVERRIDE;
	shU32					GetRowNb		(void) const;
	shU32					GetColumnNb		(void) const;
	shU32					GetTileSize		(void) const;
	Map2DTile ** const		GetTiles		(void) const;
protected:
private:
	//
	// Initiale/Release
	bool					Initialize		(shU32 iRowNb, shU32 iColumnNb, shU32 iTileSize);
	bool					Release			(void);
private:

	shU32			m_iRow;
	shU32			m_iColumn;
	shU32			m_iTileSize;

	Map2DTile **	m_aaTiles;
};