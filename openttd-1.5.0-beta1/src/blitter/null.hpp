/* $Id: null.hpp 26209 2014-01-02 22:41:58Z rubidium $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file null.hpp The blitter that doesn't blit. */

#ifndef BLITTER_NULL_HPP
#define BLITTER_NULL_HPP

#include "factory.hpp"

/** Blitter that does nothing. */
class Blitter_Null : public Blitter {
public:
	/* virtual */ uint8 GetScreenDepth() { return 0; }
	/* virtual */ void Draw(Blitter::BlitterParams *bp, BlitterMode mode, ZoomLevel zoom) {};
	/* virtual */ void DrawColourMappingRect(void *dst, int width, int height, PaletteID pal) {};
	/* virtual */ Sprite *Encode(const SpriteLoader::Sprite *sprite, AllocatorProc *allocator);
	/* virtual */ void *MoveTo(void *video, int x, int y) { return NULL; };
	/* virtual */ void SetPixel(void *video, int x, int y, uint8 colour) {};
	/* virtual */ void DrawRect(void *video, int width, int height, uint8 colour) {};
	/* virtual */ void DrawLine(void *video, int x, int y, int x2, int y2, int screen_width, int screen_height, uint8 colour, int width, int dash) {};
	/* virtual */ void CopyFromBuffer(void *video, const void *src, int width, int height) {};
	/* virtual */ void CopyToBuffer(const void *video, void *dst, int width, int height) {};
	/* virtual */ void CopyImageToBuffer(const void *video, void *dst, int width, int height, int dst_pitch) {};
	/* virtual */ void ScrollBuffer(void *video, int &left, int &top, int &width, int &height, int scroll_x, int scroll_y) {};
	/* virtual */ int BufferSize(int width, int height) { return 0; };
	/* virtual */ void PaletteAnimate(const Palette &palette) { };
	/* virtual */ Blitter::PaletteAnimation UsePaletteAnimation() { return Blitter::PALETTE_ANIMATION_NONE; };

	/* virtual */ const char *GetName() { return "null"; }
	/* virtual */ int GetBytesPerPixel() { return 0; }
};

/** Factory for the blitter that does nothing. */
class FBlitter_Null : public BlitterFactory {
public:
	FBlitter_Null() : BlitterFactory("null", "Null Blitter (does nothing)") {}
	/* virtual */ Blitter *CreateInstance() { return new Blitter_Null(); }
};

#endif /* BLITTER_NULL_HPP */
