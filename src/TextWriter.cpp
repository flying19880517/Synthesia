// Piano Hero
// Copyright (c)2006 Nicholas Piegdon
// See license.txt for license information

#include "TextWriter.h"

TextWriter::TextWriter(int in_x, int in_y, HDC in_hdc, bool in_centered, int in_size, std::wstring fontname) :
x(in_x), y(in_y), size(in_size), original_x(in_x), last_line_height(0), centered(in_centered), hdc(in_hdc)
{
   // Set up the LOGFONT structure
   LOGFONT logical_font;
   logical_font.lfHeight = get_point_size();
   logical_font.lfWidth = 0;
   logical_font.lfEscapement = 0;
   logical_font.lfOrientation = 0;
   logical_font.lfWeight = FW_NORMAL;
   logical_font.lfItalic = false;
   logical_font.lfUnderline = false;
   logical_font.lfStrikeOut = false;
   logical_font.lfCharSet = ANSI_CHARSET;
   logical_font.lfOutPrecision = OUT_DEFAULT_PRECIS;
   logical_font.lfClipPrecision = CLIP_DEFAULT_PRECIS;
   logical_font.lfQuality = PROOF_QUALITY;
   logical_font.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
   lstrcpy(logical_font.lfFaceName, fontname.c_str()); 

   font = CreateFontIndirect(&logical_font);
}

TextWriter::~TextWriter()
{
   DeleteObject(font);
}

int TextWriter::get_point_size()
{
   return MulDiv(size, GetDeviceCaps(hdc, LOGPIXELSY), 72);
}

TextWriter& TextWriter::next_line()
{
   y += max(last_line_height, get_point_size());
   x = original_x;

   last_line_height = 0;
   return *this;
}

TextWriter& operator<<(TextWriter& tw, Text& t)
{
   return t.operator <<(tw);
}

TextWriter& newline(TextWriter& tw)
{
   return tw.next_line();
}

TextWriter& Text::operator<<(TextWriter& tw)
{
   const long options = DT_LEFT | DT_NOPREFIX;

   // Set the HDC to some of our preferences
   COLORREF previous_color = SetTextColor(tw.hdc, (COLORREF)col);
   int previous_map_mode = SetMapMode(tw.hdc, MM_TEXT);

   // Create the font we want to use, and swap it out with
   // whatever is currently in there, along with our color
   HFONT previous_font = (HFONT)SelectObject(tw.hdc, tw.font);

   // Call DrawText the first time to fill in the RECT structure
   RECT drawing_rect = { tw.x, tw.y, 0, 0 };
   DrawText(tw.hdc, txt.c_str(), int(txt.length()), &drawing_rect, options | DT_CALCRECT);

   // Call it again to do the drawing, and get the line height
   if (tw.centered) drawing_rect.left -= (drawing_rect.right - drawing_rect.left) / 2;
   tw.last_line_height = DrawText(tw.hdc, txt.c_str(), int(txt.length()), &drawing_rect, options | DT_NOCLIP);

   // Update the TextWriter, with however far we just wrote
   if (!tw.centered) tw.x += drawing_rect.right - drawing_rect.left;

   // Return the hdc settings to how they previously were
   SelectObject(tw.hdc, previous_font);
   SetTextColor(tw.hdc, previous_color);
   SetMapMode(tw.hdc, previous_map_mode);

   return tw;
}

TextWriter& operator<<(TextWriter& tw, const std::wstring& s)  { return tw << Text(s, White); }
TextWriter& operator<<(TextWriter& tw, const int& i)           { return tw << Text(i, White); }
TextWriter& operator<<(TextWriter& tw, const unsigned int& i)  { return tw << Text(i, White); }
TextWriter& operator<<(TextWriter& tw, const long& l)          { return tw << Text(l, White); }
TextWriter& operator<<(TextWriter& tw, const unsigned long& l) { return tw << Text(l, White); }