//  -------------------------------------------------------------------------
//  Copyright (C) 2015 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#ifndef RAMSES_TEXTSCENE_H
#define RAMSES_TEXTSCENE_H

#include "TextScene_Base.h"

namespace ramses_internal
{
    class TextScene : public TextScene_Base
    {
    public:

        /// State of the text scene.
        /** EState_INITIAL:                 Show text string "ÄÖÜß0123" in a red, 64pt font.
         *  EState_DELETED_TEXTS_AND_NODE:  Delete a text, an unassigned text, and a text node.
         *  EState_YELLOW_TEXT:             Change the style to a yellow, 64pt font.
         *  EState_FORCE_AUTO_HINTING:      Show the text string "au7ohint1ng ON" with autohinting disabled and enabled
         *  EState_FONT_CASCADE_WITH_VERTICAL_OFFSET: Show text using two fonts in a cascade, and one font moved by a vertical offset
         *  EState_SHAPING:                 Show shaped text with and without force autohinting
         */
        enum EState
        {
            EState_INITIAL = 0,
            EState_INITIAL_128_BY_64_VIEWPORT,
            EState_DELETED_TEXTS,
            EState_FORCE_AUTO_HINTING,
            EState_FONT_CASCADE,
            EState_FONT_CASCADE_WITH_VERTICAL_OFFSET,
            EState_SHAPING
        };

        TextScene(ramses::RamsesClient& ramsesClient, ramses::Scene& scene, UInt32 state, const Vector3& cameraPosition);

        void setState(UInt32 state);

    private:
        ramses::FontInstanceId m_font{ ramses::InvalidFontInstanceId };
        ramses::FontInstanceId m_chineseFont{ ramses::InvalidFontInstanceId };
        ramses::FontInstanceId m_lightFont{ ramses::InvalidFontInstanceId };
        ramses::FontInstanceId m_lightAutoHintFont{ ramses::InvalidFontInstanceId };
        ramses::FontInstanceId m_lightAutoHintAndReshapeFont{ ramses::InvalidFontInstanceId };
        ramses::FontInstanceId m_shapingArabicFont{ ramses::InvalidFontInstanceId };
        ramses::FontInstanceId m_shapingArabicAutoHintFont{ ramses::InvalidFontInstanceId };

        ramses::TextLineId m_textUTF{ ramses::InvalidTextLineId };
        ramses::TextLineId m_textASCII{ ramses::InvalidTextLineId };
        ramses::TextLineId m_textDigits{ ramses::InvalidTextLineId };
        ramses::TextLineId m_textChinese{ ramses::InvalidTextLineId };
        ramses::TextLineId m_textLight{ ramses::InvalidTextLineId };
        ramses::TextLineId m_textLightAutoHinting{ ramses::InvalidTextLineId };
        ramses::TextLineId m_textFontCascade{ ramses::InvalidTextLineId };
        ramses::TextLineId m_textFontCascadeWithVerticalOffset{ ramses::InvalidTextLineId };
        ramses::TextLineId m_textShaping{ ramses::InvalidTextLineId };
        ramses::TextLineId m_textShapingAutoHint{ ramses::InvalidTextLineId };

        ramses::MeshNode* m_meshUTF = nullptr;
        ramses::MeshNode* m_meshASCII = nullptr;
        ramses::MeshNode* m_meshDigits = nullptr;
        ramses::MeshNode* m_meshChinese = nullptr;
        ramses::MeshNode* m_meshLight = nullptr;
        ramses::MeshNode* m_meshLightAutoHinting = nullptr;
        ramses::MeshNode* m_meshFontCascade = nullptr;
        ramses::MeshNode* m_meshFontCascadeWithVerticalOffset = nullptr;
        ramses::MeshNode* m_meshShaping = nullptr;
        ramses::MeshNode* m_meshShapingAutoHint = nullptr;
    };
}

#endif
