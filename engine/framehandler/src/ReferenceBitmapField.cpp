/******************************************************************************
**
**   File:        ReferenceBitmapField.cpp
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

#include "ReferenceBitmapField.h"
#include "WidgetPool.h"

#include <Assertion.h>

#include <ReferenceBitmapFieldType.h>
#include <ExpressionTermType.h>
#include <Database.h>

#include <new>

namespace psc
{

ReferenceBitmapField* ReferenceBitmapField::create(WidgetPool& widgetPool,
                                 const Database& db,
                                 const ReferenceBitmapFieldType* pDdh,
                                 DataContext* pContext,
                                 PSCErrorCollector& error)
{
    PSCError tmpError = PSC_NO_ERROR;
    void* pRawMemory = widgetPool.referenceBitmapFieldPool().allocate(tmpError);
    error = tmpError;

    ReferenceBitmapField* pField = new (pRawMemory)ReferenceBitmapField(db, pDdh);
    if (NULL != pField && !pField->setup(pContext, error))
    {
        pField->~ReferenceBitmapField();
        error = widgetPool.referenceBitmapFieldPool().deallocate(pRawMemory);
        pField = NULL;
    }

    return pField;
}

ReferenceBitmapField::ReferenceBitmapField(const Database& db, const ReferenceBitmapFieldType* pDdh)
    : m_pDdh(pDdh)
    , m_db(db)
    , m_pContext(NULL)
{
    ASSERT(NULL != m_pDdh);
}

bool ReferenceBitmapField::setup(DataContext* pContext, PSCErrorCollector& error)
{
    ASSERT(NULL != pContext);
    ASSERT(NULL != m_pDdh);
    m_pContext = pContext;
    bool res = true;
    if (!setArea(m_pDdh->GetArea()) || !setupVisibilityExpr(pContext) || !setupBitmapExr(pContext))
    {
        error = PSC_DB_INCONSISTENT;
        res = false;
    }

    return res;
}

bool ReferenceBitmapField::setupVisibilityExpr(DataContext* pContext)
{
    bool res = false;
    const ExpressionTermType* pType = m_pDdh->GetVisible();
    if (NULL != pType)
    {
        m_visibilityExpr.setup(pType, pContext);
        setVisibilityExpression(&m_visibilityExpr);
        res = true;
    }
    return res;
}

bool ReferenceBitmapField::setupBitmapExr(DataContext* pContext)
{
    bool res = false;
    const ExpressionTermType* pType = m_pDdh->GetBitmap();
    if (NULL != pType)
    {
        m_bitmapExpr.setup(pType, pContext, NULL);
        res = true;
    }
    return res;
}

void ReferenceBitmapField::onUpdate(const U32 /* monotonicTimeMs */)
{
    BitmapId tmpValue;
    if (tryToUpdateValue(m_bitmapExpr, tmpValue))
    {
        if (m_bitmapId != tmpValue)
        {
            m_bitmapId = tmpValue;
        }
    }
}

void ReferenceBitmapField::onDraw(Canvas& /* canvas */, const Area& /* area */)
{
}

bool ReferenceBitmapField::onVerify(Canvas& canvas, const Area& area)
{
    bool verified = true;

    if (isVisible())
    {
        verified = false;
        StaticBitmap bitmap = m_db.getBitmap(m_bitmapId);
        verified = canvas.verify(bitmap, area);

        if (!verified)
        {
            IncrementErrorCounter();
        }
    }

    return verified;
}

void ReferenceBitmapField::IncrementErrorCounter()
{
    Number errorCounter;
    IDataHandler* pDataHandler = m_pContext->getDataHandler();
    ASSERT(pDataHandler);

    // TODO: move to some static variable
    const FUClassId internalFU = 255U;
    const DataId dataId = m_pDdh->GetErrorCounter();

    bool errorCounterIsCorrect = true;
    DataStatus status = pDataHandler->getNumber(internalFU, dataId, errorCounter);
    if (DataStatus::VALID != status)
    {
        setError(status.convertToPSCError());
        errorCounterIsCorrect = false;
    }

    if (DATATYPE_INTEGER != errorCounter.getType())
    {
        setError(PSC_DATASTATUS_INCONSISTENT);
        errorCounterIsCorrect = false;
    }

    if (errorCounterIsCorrect)
    {
        errorCounter = Number(errorCounter.getU32() + 1U, DATATYPE_INTEGER);
        bool result = pDataHandler->setData(internalFU, dataId, errorCounter, status);
        if (!result)
        {
            setError(PSC_DH_INVALID_DATA_ID);
        }
    }
}

} // namespace psc
