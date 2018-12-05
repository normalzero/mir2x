/*
 * =====================================================================================
 *
 *       Filename: actormonitortable.cpp
 *        Created: 12/04/2018 23:39:19
 *    Description: check FLTK/examples/table-*.cxx
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

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "actormonitortable.hpp"

ActorMonitorTable::ActorMonitorTable(int nX, int nY, int nW, int nH, const char *szLabel)
    : Fl_TableImpl(nX, nY, nW, nH, szLabel)
    , m_ColumnName
      {
          "UID", "Type", "SEQ", "MessageCount"
      }
{
    rows(100);
    row_header(1);
    row_height_all(20);
    row_resize(0);

    cols(m_ColumnName.size());
    col_header(1);
    col_width_all(80);
    col_resize(1);
    end();
}

void ActorMonitorTable::draw_cell(TableContext nContext, int nRow, int nCol, int nX, int nY, int nW, int nH)
{
    switch(nContext)
    {
        case CONTEXT_STARTPAGE:
            {
                return; 
            }
        case CONTEXT_COL_HEADER:
            {
                DrawHeader(m_ColumnName[nCol].c_str(), nX, nY, nW, nH);
                return;
            }
        case CONTEXT_ROW_HEADER:
            {
                DrawHeader("TEST", nX, nY, nW, nH);
                return;
            }
        case CONTEXT_CELL:
            {
                DrawData(std::to_string(nRow).c_str(), nX, nY, nW, nH);
                return;
            }
        default:
            {
                return;
            }
    }
}

void ActorMonitorTable::DrawHeader(const char *szInfo, int nX, int nY, int nW, int nH)
{
    fl_push_clip(nX, nY, nW, nH);
    {
        fl_draw_box(FL_THIN_UP_BOX, nX, nY, nW, nH, row_header_color());
        fl_color(FL_BLACK);
        fl_draw(szInfo, nX, nY, nW, nH, FL_ALIGN_CENTER);
    }
    fl_pop_clip();
}

void ActorMonitorTable::DrawData(const char *szInfo, int nX, int nY, int nW, int nH)
{
    fl_push_clip(nX, nY, nW, nH);
    {
        fl_color(FL_WHITE);
        fl_rectf(nX, nY, nW, nH);

        fl_color(FL_GRAY0);
        fl_draw(szInfo, nX, nY, nW, nH, FL_ALIGN_CENTER);

        fl_color(color());
        fl_rect(nX, nY, nW, nH);
    }
    fl_pop_clip();
}