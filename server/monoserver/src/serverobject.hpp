/*
 * =====================================================================================
 *
 *       Filename: serverobject.hpp
 *        Created: 04/13/2016 20:04:39
 *  Last Modified: 04/13/2016 20:13:52
 *
 *    Description: asyncobject with ID() and AddTime()
 *
 *        Version: 1.0
 *       Revision: none
 *       Compiler: gcc
 *
 *         Author: ANHONG
 *          Email: anhonghe@gmail.com
 *   Organization: USTC
 *
 * =====================================================================================
 */

#pragma once
#include <cstdint>
#include "asyncobject.hpp"

enum ObjectCategory: uint8_t {
    CATEGORY_NONE,
    CATEGORY_ITEM,
    CATEGORY_EVENT,
    CATEGORY_ACTIVEOBJECT,
};

class ServerObject: public AsyncObject
{
    protected:
        uint32_t m_UID;
        uint32_t m_AddTime;

    protected:
        uint8_t m_Category;

    public:
        ServerObject()
            : AsyncObject()
            , m_UID(0)
            , m_AddTime(0)
            , m_Category(CATEGORY_NONE)
        {}

        ~ServerObject() = default;

    public:
        uint32_t UID()
        {
            return m_UID;
        }

        uint32_t AddTime()
        {
            return m_AddTime;
        }

};