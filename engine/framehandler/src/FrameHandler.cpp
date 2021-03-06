/******************************************************************************
**
**   File:        FrameHandler.cpp
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

#include "FrameHandler.h"

#include <DDHType.h>
#include <Database.h>
#include <HMIGlobalSettingsType.h>

#include <WindowDefinition.h>
#include <DisplaySizeType.h>

namespace psc
{

FrameHandler::FrameHandler(Database& db, IDataHandler& dataHandler, DisplayManager& dsp)
    : m_db(db)
    , m_widgetPool()
    , m_dataHandler(dataHandler)
    , m_dataContext(dataHandler)
    , m_display(dsp)
    , m_error(PSC_NO_ERROR)
    , m_pWindow(NULL)
{
    // since we don't use exceptions we need an extra initialize method to capture errors (start())
}

FrameHandler::~FrameHandler()
{
    Window::dispose(m_widgetPool, m_pWindow);
}

bool FrameHandler::start()
{
    ASSERT(m_db.getError() == PSC_NO_ERROR);

    if (m_pWindow != NULL)
    {
        Window::dispose(m_widgetPool, m_pWindow);
        m_pWindow = NULL;
    }

    const HMIGlobalSettingsType* pSettings = m_db.getDdh()->GetHMIGlobalSettings();
    ASSERT(pSettings != NULL);
    const DisplaySizeType* pDisplaySize = pSettings->GetDisplaySize();
    ASSERT(pDisplaySize != NULL);

    WindowDefinition winDef;
    winDef.width = pDisplaySize->GetWidth();
    winDef.height = pDisplaySize->GetHeight();
    winDef.xPos = 0;
    winDef.yPos = 0;
    winDef.id = 0U; // for multi display support

    m_pWindow = Window::create(m_widgetPool, m_db, m_display, winDef, &m_dataContext, m_error);

    return (m_pWindow != NULL);
}

void FrameHandler::update(U32 monotonicTimeMs)
{
    ASSERT(NULL != m_pWindow);

    m_pWindow->update(monotonicTimeMs);
}

bool FrameHandler::render()
{
    ASSERT(NULL != m_pWindow);

    return m_pWindow->render();
}

bool FrameHandler::verify()
{
    ASSERT(NULL != m_pWindow);

    return m_pWindow->verify();
}

bool FrameHandler::handleWindowEvents()
{
    ASSERT(NULL != m_pWindow);

    return m_pWindow->handleWindowEvents();
}

PSCError FrameHandler::getError()
{
    if (NULL != m_pWindow)
    {
        m_error = m_pWindow->getError();
    }

    m_error = m_widgetPool.getError();

    return m_error.get();
}

}
