/****************************************************************************
**
** This file is part of DrawGin library. A C++ framework to read and
** write .dwg files formats.
**
** Copyright (C) 2011 Paul Kohut.
** All rights reserved.
** Author: Paul Kohut (pkohut2@gmail.com)
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 3 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with this library; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** DrawGin project hosted at: http://code.google.com/p/drawgin/
**
** Authors:
**      pk          Paul Kohut <pkohut2@gmail.com>
**
****************************************************************************/

#include "stdafx.h"
#include "OcCommon.h"
//#include "../Oc/OcTypes.h"
//#include "OcBsTypes.h"
//#include "OcTypes.h"
#include "OcBsTypes.h"
#include "OcBsDwgSentinels.h"

BEGIN_OCTAVARIUM_NS

bool CompareSentinels(const byte_t * pSentinel1, const byte_t * pSentinel2)
{
    for(int i = 0; i < 16; ++i) {
        if(pSentinel1[i] != pSentinel2[i]) {
            return false;
        }
    }
    return true;
}

bool CompareSentinels(const byte_t * pSentinel1, const bitcode::RC * pSentinel2)
{
    return CompareSentinels(pSentinel1, (const byte_t*) pSentinel2);
}


const byte_t sentinelR13_R2000[] = {
    0x95, 0xa0, 0x4e, 0x28, 0x99, 0x82, 0x1a, 0xe5,
    0x5e, 0x41, 0xe0, 0x5f, 0x9d, 0x3a, 0x4d, 0x00,
};
const byte_t sentinelImageDataStart[] = {
    0x1F, 0x25, 0x6D, 0x07, 0xD4, 0x36, 0x28, 0x28,
    0x9D, 0x57, 0xCA, 0x3F, 0x9D, 0x44, 0x10, 0x2B,
};
const byte_t sentinelImageDataEnd[] = {
    0xE0, 0xDA, 0x92, 0xF8, 0x2B, 0xc9, 0xD7, 0xD7,
    0x62, 0xA8, 0x35, 0xC0, 0x62, 0xBB, 0xEF, 0xD4,
};

const byte_t sentinelHeaderVarsStart[] = {
    0xCF, 0x7B, 0x1F, 0x23, 0xFD, 0xDE, 0x38, 0xA9,
    0x5F, 0x7C, 0x68, 0xB8, 0x4E, 0x6D, 0x33, 0x5F,
};

const byte_t sentinelHeaderVarsEnd[] = {
    0x30, 0x84, 0xE0, 0xDC, 0x02, 0x21, 0xC7, 0x56,
    0xA0, 0x83, 0x97, 0x47, 0xB1, 0x92, 0xCC, 0xA0,
};


END_OCTAVARIUM_NS