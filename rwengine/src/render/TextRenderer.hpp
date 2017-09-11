#ifndef _RWENGINE_TEXTRENDERER_HPP_
#define _RWENGINE_TEXTRENDERER_HPP_

#include <array>
#include <memory>
#include <string>
#include <array>

#include <glm/glm.hpp>

#include <gl/DrawBuffer.hpp>
#include <gl/GeometryBuffer.hpp>

#include <fonts/GameTexts.hpp>
#include <render/OpenGLRenderer.hpp>

#define GAME_FONTS 3
#define GAME_GLYPHS 192

class GameRenderer;
/**
 * @brief Handles rendering of bitmap font textures.
 *
 * In future, strings textures might be cached to improve performance, but
 * for now, we just render each glyph on it's own quad
 */
class TextRenderer {
public:
    /**
     * @todo Can this be merged with the gamestate text entries?
     */
    struct TextInfo {
        enum TextAlignment { Left = 0, Right = 1, Center = 2 };

        /// Font index @see TextRenderer::setFontTexture
        int font{0};
        /// Message to be displayed (including markup)
        GameString text;
        /// On screen position
        glm::vec2 screenPosition{};
        /// font size
        float size{1.f};
        /// Base colour
        glm::u8vec3 baseColour{1.f, 1.f, 1.f};
        /// Background colour
        glm::u8vec4 backgroundColour{};
        /// Horizontal Alignment
        TextAlignment align = Left;
        /// Wrap width
        int wrapX{0};

        TextInfo() = default;
    };

    /**
     * Stores the information for kerning a glyph
     */
    struct GlyphInfo {
        float widthFrac;
    };

    TextRenderer(GameRenderer* renderer);
    ~TextRenderer() = default;

    void setFontTexture(int index, const std::string& font);

    void renderText(const TextInfo& ti, bool forceColour = false);

private:
    std::string fonts[GAME_FONTS];
    std::array<GlyphInfo, GAME_GLYPHS> glyphData;

    GameRenderer* renderer;
    std::unique_ptr<Renderer::ShaderProgram> textShader;

    GeometryBuffer gb;
    DrawBuffer db;
};
#endif
