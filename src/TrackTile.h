// Piano Hero
// Copyright (c)2006 Nicholas Piegdon
// See license.txt for license information

#ifndef __TRACK_TILE_H
#define __TRACK_TILE_H

#include "GameState.h"
#include "TextWriter.h"
#include "TrackProperties.h"
#include "MenuLayout.h"
#include <vector>

class Midi;

const int TrackTileWidth = 300;
const int TrackTileHeight = 110;

enum TrackTileGraphic
{
   GraphicLeftArrow = 0,
   GraphicRightArrow,
   GraphicColor,
   GraphicPreviewTurnOn,
   GraphicPreviewTurnOff,

   Graphic_COUNT
};

class TrackTile
{
public:
   TrackTile(int x, int y, size_t track_id, TrackColor color, TrackMode mode);

   void Update(const MouseInfo &translated_mouse, Midi *midi);
   void Draw(HDC hdc, const Midi *midi) const;

   int GetX() { return m_x; }
   int GetY() { return m_y; }

   TrackMode GetMode() const { return m_mode; }
   TrackColor GetColor() const { return m_color; }

   bool HitPreviewButton() const { return button_preview.hit; }
   bool IsPreviewOn() const { return m_preview_on; }
   void TurnOffPreview() { m_preview_on = false; }

   size_t GetTrackId() const { return m_track_id; }

private:
   int m_x;
   int m_y;

   TrackMode m_mode;
   TrackColor m_color;

   bool m_preview_on;

   ButtonState whole_tile;
   ButtonState button_preview;
   ButtonState button_color;
   ButtonState button_mode_left;
   ButtonState button_mode_right;

   int LookupGraphic(TrackTileGraphic graphic, bool button_hovering) const;

   // Link to the track index of the Midi object
   size_t m_track_id;
};

#endif