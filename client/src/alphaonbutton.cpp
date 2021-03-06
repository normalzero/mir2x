/*
 * =====================================================================================
 *
 *       Filename: alphaonbutton.cpp
 *        Created: 08/26/2016 13:20:23
 *    Description:
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

#include "totype.hpp"
#include "bevent.hpp"
#include "sdldevice.hpp"
#include "alphaonbutton.hpp"

extern PNGTexDB *g_progUseDB;
extern SDLDevice *g_sdlDevice;

AlphaOnButton::AlphaOnButton(
        int x,
        int y,

        int onOffX,
        int onOffY,
        int onRadius,

        uint8_t alphaMod,
        uint32_t onColor,
        uint32_t downTexID,

        const std::function<void()> &fnOnOverIn,
        const std::function<void()> &fnOnOverOut,
        const std::function<void()> &fnOnClick,

        bool    triggerOnDone,
        Widget *pwidget,
        bool    autoDelete)
    : ButtonBase
      {
          x,
          y,
          0,
          0,

          fnOnOverIn,
          fnOnOverOut,
          fnOnClick,

          0,
          0,
          0,
          0,

          triggerOnDone,
          pwidget,
          autoDelete,
      }
    , m_alphaMod(alphaMod)
    , m_onColor(onColor)
    , m_texID(downTexID)
    , m_onOffX(onOffX)
    , m_onOffY(onOffY)
    , m_onRadius(onRadius)
{

    auto texPtr = g_progUseDB->Retrieve(m_texID);
    if(!texPtr){
        throw fflerror("can't load down texture: %llu", to_llu(m_texID));
    }

    const auto [texW, texH] = SDLDevice::getTextureSize(texPtr);
    m_w = texW;
    m_h = texH;
}

void AlphaOnButton::drawEx(int dstX, int dstY, int, int, int, int)
{
    switch(m_state){
        case BEVENT_ON:
            {
                auto texPtr = g_sdlDevice->getCover(m_onRadius);
                if(!texPtr){
                    throw fflerror("can't get round cover: radius = %llu", to_llu(m_onRadius));
                }

                SDLDevice::EnableRenderBlendMode enableBlendMode(SDL_BLENDMODE_BLEND);
                SDLDevice::EnableTextureModColor enableModColor(texPtr, colorf::RGBA(m_onColor, m_onColor, m_onColor, m_alphaMod));
                g_sdlDevice->drawTexture(texPtr, dstX + m_onOffX, dstY + m_onOffY);
                break;
            }
        case BEVENT_DOWN:
            {
                auto texPtr = g_progUseDB->Retrieve(m_texID);
                if(!texPtr){
                    throw fflerror("can't get down texture: texID = %llu", to_llu(m_texID));
                }

                g_sdlDevice->drawTexture(texPtr, dstX, dstY);
                break;
            }
        default:
            {
                break;
            }
    }
}
