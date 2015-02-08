/* $Id: aircraft_gui.cpp 26951 2014-10-04 16:40:23Z peter1138 $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file aircraft_gui.cpp The GUI of aircraft. */

#include "stdafx.h"
#include "aircraft.h"
#include "vehicle_gui.h"
#include "newgrf_engine.h"
#include "strings_func.h"
#include "vehicle_func.h"
#include "window_gui.h"
#include "spritecache.h"
#include "zoom_func.h"

#include "table/strings.h"

#include "safeguards.h"

/**
 * Draw the details for the given vehicle at the given position
 *
 * @param v     current vehicle
 * @param left  The left most coordinate to draw
 * @param right The right most coordinate to draw
 * @param y     The y coordinate
 */
void DrawAircraftDetails(const Aircraft *v, int left, int right, int y)
{
	int y_offset = (v->Next()->cargo_cap != 0) ? -(FONT_HEIGHT_NORMAL + 1): 0;
	Money feeder_share = 0;

	for (const Aircraft *u = v; u != NULL; u = u->Next()) {
		if (u->IsNormalAircraft()) {
			SetDParam(0, u->engine_type);
			SetDParam(1, u->build_year);
			SetDParam(2, u->value);
			DrawString(left, right, y, STR_VEHICLE_INFO_BUILT_VALUE);

			SetDParam(0, u->cargo_type);
			SetDParam(1, u->cargo_cap);
			SetDParam(2, u->Next()->cargo_type);
			SetDParam(3, u->Next()->cargo_cap);
			SetDParam(4, GetCargoSubtypeText(u));
			DrawString(left, right, y + FONT_HEIGHT_NORMAL, (u->Next()->cargo_cap != 0) ? STR_VEHICLE_INFO_CAPACITY_CAPACITY : STR_VEHICLE_INFO_CAPACITY);
		}

		if (u->cargo_cap != 0) {
			uint cargo_count = u->cargo.StoredCount();

			y_offset += FONT_HEIGHT_NORMAL + 1;
			if (cargo_count != 0) {
				/* Cargo names (fix pluralness) */
				SetDParam(0, u->cargo_type);
				SetDParam(1, cargo_count);
				SetDParam(2, u->cargo.Source());
				DrawString(left, right, y + 2 * FONT_HEIGHT_NORMAL + 1 + y_offset, STR_VEHICLE_DETAILS_CARGO_FROM);
				feeder_share += u->cargo.FeederShare();
			}
		}
	}

	SetDParam(0, feeder_share);
	DrawString(left, right, y + 3 * FONT_HEIGHT_NORMAL + 3 + y_offset, STR_VEHICLE_INFO_FEEDER_CARGO_VALUE);
}


/**
 * Draws an image of an aircraft
 * @param v         Front vehicle
 * @param left      The minimum horizontal position
 * @param right     The maximum horizontal position
 * @param y         Vertical position to draw at
 * @param selection Selected vehicle to draw a frame around
 */
void DrawAircraftImage(const Vehicle *v, int left, int right, int y, VehicleID selection, EngineImageType image_type)
{
	bool rtl = _current_text_dir == TD_RTL;

	SpriteID sprite = v->GetImage(rtl ? DIR_E : DIR_W, image_type);
	const Sprite *real_sprite = GetSprite(sprite, ST_NORMAL);

	int width = UnScaleByZoom(real_sprite->width, ZOOM_LVL_GUI);
	int x_offs = UnScaleByZoom(real_sprite->x_offs, ZOOM_LVL_GUI);
	int x = rtl ? right - width - x_offs : left - x_offs;
	bool helicopter = v->subtype == AIR_HELICOPTER;

	int y_offs = UnScaleByZoom(4 * 10, ZOOM_LVL_GUI);
	int heli_offs = 0;

	PaletteID pal = (v->vehstatus & VS_CRASHED) ? PALETTE_CRASH : GetVehiclePalette(v);
	DrawSprite(sprite, pal, x, y + y_offs);
	if (helicopter) {
		const Aircraft *a = Aircraft::From(v);
		SpriteID rotor_sprite = GetCustomRotorSprite(a, true, image_type);
		if (rotor_sprite == 0) rotor_sprite = SPR_ROTOR_STOPPED;
		heli_offs = UnScaleByZoom(4 * 5, ZOOM_LVL_GUI);
		DrawSprite(rotor_sprite, PAL_NONE, x, y + y_offs - heli_offs);
	}
	if (v->index == selection) {
		x += x_offs;
		y += UnScaleByZoom(real_sprite->y_offs, ZOOM_LVL_GUI) + y_offs - heli_offs;
		DrawFrameRect(x - 1, y - 1, x + width + 1, y + UnScaleByZoom(real_sprite->height, ZOOM_LVL_GUI) + heli_offs + 1, COLOUR_WHITE, FR_BORDERONLY);
	}
}
