#ifndef POPULUSSC_PGLHELPER_H
#define POPULUSSC_PGLHELPER_H

/******************************************************************************
**
**   File:        PglHelper.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include <stdint.h>

namespace pglhelper
{

struct QuadParams
{
    QuadParams()
        : x1(0U), y1(0U), u1(0U), v1(0U), x2(0U), y2(0U), u2(0U), v2(0U)
    {}

    void clear()
    {
        x1 = 0U;
        y1 = 0U;
        u1 = 0U;
        v1 = 0U;
        x2 = 0U;
        y2 = 0U;
        u2 = 0U;
        v2 = 0U;
    }

    int32_t x1;
    int32_t y1;
    int32_t u1;
    int32_t v1;
    int32_t x2;
    int32_t y2;
    int32_t u2;
    int32_t v2;
};

static QuadParams g_quadParams;

} // namespace pglhelper

#endif // POPULUSSC_PGLHELPER_H
