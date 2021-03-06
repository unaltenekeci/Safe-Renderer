#ifndef _DDH_DEFS_H_
#define _DDH_DEFS_H_

/******************************************************************************
**
**   File:        ddh_defs.h
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

#include "PscTypes.h"  // Common types
// If DDH_NO_NAMESPACE is defined, then put DDH classes in the
// global namespace: the compiler does not support namespace.
#if defined(DDH_NO_NAMESPACE)
#define DDH_NS_BEGIN
#define DDH_NS_END
#define DDH_NS
#else   // defined(DDH_NO_NAMESPACE)
#define DDH_NS_BEGIN namespace psc {
#define DDH_NS_END }
#define DDH_NS ddh
#endif  // #if defined(DDH_NO_NAMESPACE)

// By defining _USE_PACK_PRAGMA, the pre-processor directive
// #pragma pack(1) will be used before the structures (thus
// removing the byte padding of the structures).
#define _USE_PACK_PRAGMA 1

namespace psc
{

// Type definitions of the Id types used in the XML Schema
// The Id types used in the ODI protocol are defined in odi_types.h instead
typedef U16 ColorId;
typedef U16 BitmapId;
typedef U8 FrameId;
typedef U16 PageId;
typedef U16 PanelId;
typedef U8 FieldId;

/**
 * ExpressionOperatorEnumeration.
 * Unary operator to be used on Term1 or Binary operator to be used on Term1 and Term2
 */
enum ExpressionOperatorEnumeration
{
    EXPRESSION_OPERATOR_PLUS = 0,
    EXPRESSION_OPERATOR_MINUS = 1,
    EXPRESSION_OPERATOR_MUL = 2,
    EXPRESSION_OPERATOR_DIV = 3,
    EXPRESSION_OPERATOR_MOD = 4,
    EXPRESSION_OPERATOR_BITWISE_OR = 5,
    EXPRESSION_OPERATOR_BITWISE_AND = 6,
    EXPRESSION_OPERATOR_BITWISE_XOR = 7,
    EXPRESSION_OPERATOR_BITWISE_NOT = 8,
    EXPRESSION_OPERATOR_SHIFT = 9,
    EXPRESSION_OPERATOR_ABS = 10,
    EXPRESSION_OPERATOR_RAND = 11,
    EXPRESSION_OPERATOR_ROUND = 12,
    EXPRESSION_OPERATOR_FLOOR = 13,
    EXPRESSION_OPERATOR_CEIL = 14,
    EXPRESSION_OPERATOR_INT = 15,
    EXPRESSION_OPERATOR_MIN = 16,
    EXPRESSION_OPERATOR_MAX = 17,
    EXPRESSION_OPERATOR_MIN_MAX = 18,
    EXPRESSION_OPERATOR_SIN = 19,
    EXPRESSION_OPERATOR_COS = 20,
    EXPRESSION_OPERATOR_TAN = 21,
    EXPRESSION_OPERATOR_ASIN = 22,
    EXPRESSION_OPERATOR_ACOS = 23,
    EXPRESSION_OPERATOR_ATAN = 24,
    EXPRESSION_OPERATOR_POW = 25,
    EXPRESSION_OPERATOR_LOG = 26,
    EXPRESSION_OPERATOR_LOG10 = 27,
    EXPRESSION_OPERATOR_M2_DISTANCE_LONG = 28,
    EXPRESSION_OPERATOR_KM2_DISTANCE_LONG = 29,
    EXPRESSION_OPERATOR_M2_DISTANCE_SHORT = 30,
    EXPRESSION_OPERATOR_KM_PER_HOUR2_SPEED = 31,
    EXPRESSION_OPERATOR_LITER_PER_KM2_CONSUMPTION = 32,
    EXPRESSION_OPERATOR_LITER_PER_HOUR2_CONSUMPTION_TIME = 33,
    EXPRESSION_OPERATOR_KG_PER100KM2_CONSUMPTION_KG = 34,
    EXPRESSION_OPERATOR_CELSIUS2_TEMPERATURE = 35,
    EXPRESSION_OPERATOR_LITER2_VOLUME = 36,
    EXPRESSION_OPERATOR_KILOPASCAL2_PRESSURE = 37,
    EXPRESSION_OPERATOR_FORMAT = 38,
    EXPRESSION_OPERATOR_ITEM_AT = 39,
    EXPRESSION_OPERATOR_IF = 40,
    EXPRESSION_OPERATOR_EQUALS = 41,
    EXPRESSION_OPERATOR_NOT_EQUALS = 42,
    EXPRESSION_OPERATOR_LESS = 43,
    EXPRESSION_OPERATOR_LESS_EQUALS = 44,
    EXPRESSION_OPERATOR_GREATER = 45,
    EXPRESSION_OPERATOR_GREATER_EQUALS = 46,
    EXPRESSION_OPERATOR_AND = 47,
    EXPRESSION_OPERATOR_OR = 48,
    EXPRESSION_OPERATOR_NOT = 49,
    EXPRESSION_OPERATOR_REDUNDANCY = 50,
    EXPRESSION_OPERATOR_FALLBACK = 51,
    EXPRESSION_OPERATOR_FALLBACK2 = 52,
    EXPRESSION_OPERATOR_FALLBACK3 = 53,
    EXPRESSION_OPERATOR_ENUM_SIZE = 54
};

/**
 * DynamicDataTypeEnumeration.
 * The type of the data before any SubData is applied
 */
enum DynamicDataTypeEnumeration
{
    DATATYPE_SPEED = 0,
    DATATYPE_STRING = 1,
    DATATYPE_INTEGER = 2,
    DATATYPE_ENUMERATION_VALUE = 3,
    DATATYPE_DECIMAL = 4,
    DATATYPE_TIME = 5,
    DATATYPE_DATE = 6,
    DATATYPE_LIST = 7,
    DATATYPE_PICTOGRAM = 8,
    DATATYPE_TEXT_ID = 9,
    DATATYPE_BITMAP_ID = 10,
    DATATYPE_DISTANCE_LONG = 11,
    DATATYPE_DISTANCE_SHORT = 12,
    DATATYPE_VOLUME = 13,
    DATATYPE_TEMPERATURE = 14,
    DATATYPE_PRESSURE = 15,
    DATATYPE_FUEL_CONSUMPTION = 16,
    DATATYPE_FUEL_CONSUMPTION_INVERTED = 17,
    DATATYPE_CHARACTER = 18,
    DATATYPE_HOURS_OF_DAY = 19,
    DATATYPE_DECIMAL_SHORT = 20,
    DATATYPE_BITMAP = 21,
    DATATYPE_FUEL_CONSUMPTION_STANDING_STILL = 22,
    DATATYPE_FUEL_CONSUMPTION_C_N_G = 23,
    DATATYPE_FUEL_CONSUMPTION_C_N_G_INVERTED = 24,
    DATATYPE_FUEL_CONSUMPTION_C_N_G_STANDING_STILL = 25,
    DATATYPE_FUEL_USED_C_N_G = 26,
    DATATYPE_COORDINATE2_D = 27,
    DATATYPE_BITMAP_PATH = 28,
    DATATYPE_MATRIX4X4 = 29,
    DATATYPE_COLOR = 30,
    DATATYPE_BOOLEAN = 31,
    DATATYPE_ENUM_SIZE = 32
};

} // namespace psc

#endif  // #ifndef _DDH_DEFS_H_
