/******************************************************************************
**
**   File:        DatabaseMock.cpp
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

#include "Database.h"
#include "ResourceBuffer.h"
#include "DDHType.h"
#include "DatabaseAccessor.h"

namespace psc
{

Database::Database(const ResourceBuffer& ddhbin, const ResourceBuffer& imgbin)
    : m_ddh(static_cast<const DDHType*>(ddhbin.getData()))
    , m_bitmapAccess(m_ddh, imgbin)
    , m_error(PSC_NO_ERROR)
{
}

StaticBitmap Database::getBitmap(BitmapId id) const
{
    DatabaseAccessor& accessor = DatabaseAccessor::instance();
    accessor.setRequestedBitmapId(id);

    return StaticBitmap(m_bitmapAccess, NULL);
}

} // namespace ddh
