// Piano Hero
// Copyright (c)2006 Nicholas Piegdon
// See license.txt for license information

#ifndef __STRING_TILE_H
#define __STRING_TILE_H

#include "GameState.h"
#include "MenuLayout.h"
#include <string>

const int StringTileWidth = 510;
const int StringTileHeight = 80;

class StringTile
{
public:
   StringTile(int x, int y);

   void Update(const MouseInfo &translated_mouse);
   void Draw(HDC hdc) const;

   int GetX() const { return m_x; }
   int GetY() const { return m_y; }

   bool Hit() const { return whole_tile.hit; }

   void SetString(const std::wstring &s) { m_string = s; }
   void SetTitle(const std::wstring &s) { m_title = s; }

private:
   int m_x;
   int m_y;

   std::wstring m_string;
   std::wstring m_title;

   ButtonState whole_tile;
};

#endif
