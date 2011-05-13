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

#ifndef DwgInArchive_h__
#define DwgInArchive_h__

#include "OcBsStreamIn.h"
#include "OcBsDwgCrc.h"
//#include <boost/typeof/typeof.hpp>
//#include <boost/type_traits/is_base_of.hpp>

BEGIN_OCTAVARIUM_NS

class DwgInArchive
{
public:
    enum ARCHIVE_FLAG {NOT_SET = 0, LOADING, SAVING, };
    //DwgInArchive(void);
    explicit DwgInArchive(OcBsStreamIn & in);
    virtual ~DwgInArchive(void);

    bool IsLoading();
    bool IsSaving();
    void Close();
    ARCHIVE_FLAG ArchiveFlag(void);
    OcApp::ErrorStatus Error(void);
    void ClearError(void);
    void SetError(OcApp::ErrorStatus es);
    operator void*(void) const;
    byte_t * Buffer(void) {
        return m_stream.Buffer();
    }
    DwgInArchive & Seek(std::streamoff nPos);
    std::streamoff FilePosition(void) const;
    DWG_VERSION Version(void) const;
    void SetVersion(DWG_VERSION version);

    DwgInArchive & ReadHandle(OcDbObjectId & objId);

    DwgInArchive & operator>>(OcDbObjectId & b);

    DwgInArchive & operator>>(bitcode::B & b);
    DwgInArchive & operator>>(bitcode::BB & bb);
    DwgInArchive & operator>>(bitcode::BBBB & bbbb);
    DwgInArchive & operator>>(bitcode::RC & rc);
    DwgInArchive & operator>>(bitcode::RS & rs);
    DwgInArchive & operator>>(bitcode::RL & rl);
    DwgInArchive & operator>>(bitcode::RD & rd);
    DwgInArchive & operator>>(bitcode::RD2 & rd2);
    DwgInArchive & operator>>(bitcode::RD3 & rd3);
    DwgInArchive & operator>>(bitcode::BS & bs);
    DwgInArchive & operator>>(bitcode::BL & bl);
    DwgInArchive & operator>>(bitcode::BD & bd);
    DwgInArchive & operator>>(bitcode::BD2 & bd2);
    DwgInArchive & operator>>(bitcode::BD3 & bd3);
    DwgInArchive & operator>>(bitcode::MC & mc);
    DwgInArchive & operator>>(bitcode::MS & ms);
    DwgInArchive & operator>>(bitcode::BE & be);
    DwgInArchive & operator>>(bitcode::BT & bt);
    DwgInArchive & operator>>(bitcode::CMC & cmc);
    DwgInArchive & operator>>(bitcode::TV & tv);

    DwgInArchive & operator>>(bitcode::RC rc[]);
    DwgInArchive & ReadRC(bitcode::RC * pRc, size_t size);
    DwgInArchive & ReadRC(std::vector<bitcode::RC> & rc, size_t size);
    DwgInArchive & ReadRC(std::string & rc, size_t size);


private:
    OcBsStreamIn & m_stream;
    ARCHIVE_FLAG m_archiveFlag;
    OcApp::ErrorStatus m_archiveError;
};


template<typename BC, typename T>
DwgInArchive& Archive(uint16_t & crc, DwgInArchive & ar, T & t)
{
    ar >> (BC&) t;
    crc = crc8(crc, (const char*)&t, sizeof(t));
    return ar;
}

template<typename BC, typename T>
DwgInArchive& Archive(uint16_t & crc, DwgInArchive & ar, T & t, const char * pStr)
{
    Archive<BC, T>(crc, ar, t);
    VLOG(4) << std::showbase << pStr << ": " << t;
    return ar;
}

// handle when t is a char and print t as an int
template<typename BC>
DwgInArchive& Archive(uint16_t & crc, DwgInArchive & ar, int8_t & t, const char * pStr)
{
    Archive<BC>(crc, ar, t);
    VLOG(4) << std::showbase << pStr << ": " << (int) t;
    return ar;
}

template<typename BC>
DwgInArchive& Archive(uint16_t & crc, DwgInArchive & ar, bitcode::CMC & t, const char * pStr)
{
    Archive<BC>(crc, ar, t);
    VLOG(4) << pStr << ": " << (bitcode::BCCMC&)t;
    return ar;
}

template<typename BC>
DwgInArchive& Archive(uint16_t & crc, DwgInArchive & ar, std::wstring & t, const char * pStr)
{
    Archive<BC>(crc, ar, t);
    VLOG(4) << pStr << ": " << t.c_str();
    return ar;
}

template<typename BC>
DwgInArchive& Archive(uint16_t & crc, DwgInArchive & ar, wchar_t * t, const char * pStr)
{
    Archive<BC>(crc, ar, t);
    VLOG(4) << pStr << ": " << t;
    return ar;
}


//template<typename BC>
//DwgInArchive& Archive(uint16_t & crc, DwgInArchive & ar, double * t, const char * pStr)
//{
//    Archive<BC>(crc, ar, t);
//    VLOG(4) << pStr;
////    VLOG(4) << pStr << ": " << (bitcode::BCCMC&)t;
//    return ar;
//}





// Help with dead string stripping for the Archive template, without this
// DSS only occurred with gcc compiler setting of -O3
#if GOOGLE_STRIP_LOG == 0
#  define BS_ARCHIVE(CRC, BC, AR, T, STR) Archive<BC>(CRC, AR, T, #STR);
#else
// have compiler strip away STR from code
#  define BS_ARCHIVE(CRC, BC, AR, T, STR) Archive<BC>(CRC, AR, T, "");
#endif

END_OCTAVARIUM_NS

#endif // DwgInArchive_h__
