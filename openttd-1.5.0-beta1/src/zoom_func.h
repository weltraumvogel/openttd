/* $Id: zoom_func.h 26202 2014-01-02 11:05:42Z rubidium $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file zoom_func.h Functions related to zooming. */

#ifndef ZOOM_FUNC_H
#define ZOOM_FUNC_H

#include "zoom_type.h"

/**
 * Scale by zoom level, usually shift left (when zoom > ZOOM_LVL_NORMAL)
 * When shifting right, value is rounded up
 * @param value value to shift
 * @param zoom  zoom level to shift to
 * @return shifted value
 */
static inline int ScaleByZoom(int value, ZoomLevel zoom)
{
	assert(zoom >= 0);
	return value << zoom;
}

/**
 * Scale by zoom level, usually shift right (when zoom > ZOOM_LVL_NORMAL)
 * When shifting right, value is rounded up
 * @param value value to shift
 * @param zoom  zoom level to shift to
 * @return shifted value
 */
static inline int UnScaleByZoom(int value, ZoomLevel zoom)
{
	assert(zoom >= 0);
	return (value + (1 << zoom) - 1) >> zoom;
}

/**
 * Scale by zoom level, usually shift left (when zoom > ZOOM_LVL_NORMAL)
 * @param value value to shift
 * @param zoom  zoom level to shift to
 * @return shifted value
 */
static inline int ScaleByZoomLower(int value, ZoomLevel zoom)
{
	assert(zoom >= 0);
	return value << zoom;
}

/**
 * Scale by zoom level, usually shift right (when zoom > ZOOM_LVL_NORMAL)
 * @param value value to shift
 * @param zoom  zoom level to shift to
 * @return shifted value
 */
static inline int UnScaleByZoomLower(int value, ZoomLevel zoom)
{
	assert(zoom >= 0);
	return value >> zoom;
}

#endif /* ZOOM_FUNC_H */