#include "litehtmlcontainer.h"
#include <QPainterPath>
#include <QFontDatabase>
#include <cmath>

using namespace litehtml;

LiteHtmlContainer::LiteHtmlContainer() {}

LiteHtmlContainer::~LiteHtmlContainer()
{
    for (auto it = m_fonts.begin(); it != m_fonts.end(); ++it) {
        delete it->metrics;
    }
    m_fonts.clear();
}

void LiteHtmlContainer::setPainter(QPainter *painter) { m_painter = painter; }

void LiteHtmlContainer::setWidgetSize(int width, int height)
{
    m_widgetWidth = width;
    m_widgetHeight = height;
}

static QColor fromWebColor(const web_color &c)
{
    return QColor(c.red, c.green, c.blue, c.alpha);
}

// Font

uint_ptr LiteHtmlContainer::create_font(const font_description &descr, const document * /*doc*/, font_metrics *fm)
{
    QFont qfont(QString::fromUtf8(descr.family.c_str()));
    qfont.setPixelSize(descr.size);
    qfont.setWeight(static_cast<QFont::Weight>(descr.weight));
    qfont.setItalic(descr.style == litehtml::font_style_italic);

    int dec = descr.decoration_line;
    qfont.setUnderline(dec & litehtml::text_decoration_line_underline);
    qfont.setStrikeOut(dec & litehtml::text_decoration_line_line_through);

    auto *metrics = new QFontMetrics(qfont);

    fm->ascent = metrics->ascent();
    fm->descent = metrics->descent();
    fm->height = metrics->height();
    fm->x_height = metrics->xHeight();

    uint_ptr id = m_nextFontId++;
    m_fonts[id] = {qfont, metrics};
    return id;
}

void LiteHtmlContainer::delete_font(uint_ptr hFont)
{
    auto it = m_fonts.find(hFont);
    if (it != m_fonts.end()) {
        delete it->metrics;
        m_fonts.erase(it);
    }
}

pixel_t LiteHtmlContainer::text_width(const char *text, uint_ptr hFont)
{
    auto it = m_fonts.find(hFont);
    if (it == m_fonts.end() || !m_painter) return {0};

    QFont oldFont = m_painter->font();
    m_painter->setFont(it->font);
    int w = m_painter->fontMetrics().horizontalAdvance(QString::fromUtf8(text));
    m_painter->setFont(oldFont);
    return {static_cast<float>(w)};
}

void LiteHtmlContainer::draw_text(uint_ptr /*hdc*/, const char *text, uint_ptr hFont,
                                   web_color color, const position &pos)
{
    if (!m_painter) return;
    auto it = m_fonts.find(hFont);
    if (it == m_fonts.end()) return;

    QFont oldFont = m_painter->font();
    QBrush oldBrush = m_painter->brush();
    m_painter->setFont(it->font);
    m_painter->setPen(fromWebColor(color));
    m_painter->drawText(pos.left(), pos.top() + pos.height, QString::fromUtf8(text));
    m_painter->setFont(oldFont);
    m_painter->setBrush(oldBrush);
}

pixel_t LiteHtmlContainer::pt_to_px(float pt) const
{
    return {static_cast<float>(static_cast<int>(pt * 96.0 / 72.0))};
}

pixel_t LiteHtmlContainer::get_default_font_size() const
{
    return pt_to_px(14);
}

const char *LiteHtmlContainer::get_default_font_name() const
{
    return "sans-serif";
}

// List markers

void LiteHtmlContainer::draw_list_marker(uint_ptr /*hdc*/, const list_marker &marker)
{
    if (!m_painter) return;

    int x = marker.pos.left();
    int y = marker.pos.top();
    int w = marker.pos.width;
    int h = marker.pos.height;

    m_painter->save();
    m_painter->setPen(Qt::NoPen);
    m_painter->setBrush(fromWebColor(marker.color));

    switch (marker.marker_type) {
    case list_style_type_disc:
        m_painter->drawEllipse(x, y, w, h);
        break;
    case list_style_type_circle:
        m_painter->drawEllipse(x + 1, y + 1, w - 2, h - 2);
        break;
    case list_style_type_square:
        m_painter->drawRect(x, y, w, h);
        break;
    case list_style_type_decimal:
    case list_style_type_none:
    default:
        break;
    }
    m_painter->restore();
}

// Images (stub - no image loading for now)

void LiteHtmlContainer::load_image(const char * /*src*/, const char * /*baseurl*/, bool /*redraw_on_ready*/) {}
void LiteHtmlContainer::get_image_size(const char * /*src*/, const char * /*baseurl*/, size &sz)
{
    sz.width = {0};
    sz.height = {0};
}

// Drawing helpers

static QPainterPath roundedRectPath(const position &pos, const border_radiuses &radius)
{
    QPainterPath path;
    qreal x = pos.left(), y = pos.top(), w = pos.width, h = pos.height;
    qreal tlx = radius.top_left_x, tly = radius.top_left_y;
    qreal trx = radius.top_right_x, try_ = radius.top_right_y;
    qreal brx = radius.bottom_right_x, bry = radius.bottom_right_y;
    qreal blx = radius.bottom_left_x, bly = radius.bottom_left_y;

    path.moveTo(x + tlx, y);
    path.lineTo(x + w - trx, y);
    if (trx > 0) path.arcTo(x + w - 2 * trx, y, 2 * trx, 2 * try_, 90, -90);
    else path.lineTo(x + w, y);

    path.lineTo(x + w, y + h - bry);
    if (brx > 0) path.arcTo(x + w - 2 * brx, y + h - 2 * bry, 2 * brx, 2 * bry, 0, -90);
    else path.lineTo(x + w, y + h);

    path.lineTo(x + blx, y + h);
    if (blx > 0) path.arcTo(x, y + h - 2 * bly, 2 * blx, 2 * bly, 270, -90);
    else path.lineTo(x, y + h);

    path.lineTo(x, y + tly);
    if (tlx > 0) path.arcTo(x, y, 2 * tlx, 2 * tly, 180, -90);
    else path.lineTo(x, y);

    path.closeSubpath();
    return path;
}

void LiteHtmlContainer::draw_image(uint_ptr /*hdc*/, const background_layer & /*layer*/,
                                   const std::string & /*url*/, const std::string & /*base_url*/) {}

void LiteHtmlContainer::draw_solid_fill(uint_ptr /*hdc*/, const background_layer &layer,
                                        const web_color &color)
{
    if (!m_painter || color == web_color::transparent) return;

    m_painter->save();
    QPainterPath path = roundedRectPath(layer.border_box, layer.border_radius);
    m_painter->setClipPath(path, Qt::IntersectClip);
    m_painter->setPen(Qt::NoPen);
    m_painter->setBrush(fromWebColor(color));
    m_painter->drawRect(layer.clip_box.left(), layer.clip_box.top(),
                        layer.clip_box.width, layer.clip_box.height);
    m_painter->restore();
}

void LiteHtmlContainer::draw_linear_gradient(uint_ptr /*hdc*/, const background_layer & /*layer*/,
                                             const background_layer::linear_gradient & /*gradient*/) {}
void LiteHtmlContainer::draw_radial_gradient(uint_ptr /*hdc*/, const background_layer & /*layer*/,
                                             const background_layer::radial_gradient & /*gradient*/) {}
void LiteHtmlContainer::draw_conic_gradient(uint_ptr /*hdc*/, const background_layer & /*layer*/,
                                            const background_layer::conic_gradient & /*gradient*/) {}

void LiteHtmlContainer::draw_borders(uint_ptr /*hdc*/, const borders &borders,
                                     const position &draw_pos, bool /*root*/)
{
    if (!m_painter) return;

    m_painter->save();

    auto drawSide = [this](const border &b, const position &pos, int top, int left, int w, int h) {
        if (b.width == pixel_t(0) || b.style <= border_style_hidden) return;

        m_painter->setPen(Qt::NoPen);
        m_painter->setBrush(fromWebColor(b.color));
        m_painter->drawRect(pos.left() + left, pos.top() + top, w, h);
    };

    // Top
    drawSide(borders.top, draw_pos, 0, 0, draw_pos.width, static_cast<int>(borders.top.width));
    // Bottom
    drawSide(borders.bottom, draw_pos, draw_pos.height - static_cast<int>(borders.bottom.width), 0,
             draw_pos.width, static_cast<int>(borders.bottom.width));
    // Left
    drawSide(borders.left, draw_pos, 0, 0, static_cast<int>(borders.left.width), draw_pos.height);
    // Right
    drawSide(borders.right, draw_pos, 0, draw_pos.width - static_cast<int>(borders.right.width),
             static_cast<int>(borders.right.width), draw_pos.height);

    m_painter->restore();
}

// Callbacks

void LiteHtmlContainer::set_caption(const char * /*caption*/) {}
void LiteHtmlContainer::set_base_url(const char * /*base_url*/) {}
void LiteHtmlContainer::link(const std::shared_ptr<document> & /*doc*/, const element::ptr & /*el*/) {}

void LiteHtmlContainer::on_anchor_click(const char * /*url*/, const element::ptr & /*el*/) {}
bool LiteHtmlContainer::on_element_click(const element::ptr & /*el*/) { return false; }
void LiteHtmlContainer::on_mouse_event(const element::ptr & /*el*/, mouse_event /*event*/) {}
void LiteHtmlContainer::set_cursor(const char * /*cursor*/) {}

void LiteHtmlContainer::transform_text(std::string &text, text_transform tt)
{
    switch (tt) {
    case text_transform_uppercase:
        for (auto &c : text) c = std::toupper(c);
        break;
    case text_transform_lowercase:
        for (auto &c : text) c = std::tolower(c);
        break;
    case text_transform_capitalize:
        if (!text.empty()) text[0] = std::toupper(text[0]);
        break;
    default:
        break;
    }
}

void LiteHtmlContainer::import_css(std::string & /*text*/, const std::string & /*url*/, std::string & /*baseurl*/) {}

void LiteHtmlContainer::set_clip(const position &pos, const border_radiuses &bdr_radius)
{
    m_clips.push_back({pos, bdr_radius});
}

void LiteHtmlContainer::del_clip()
{
    if (!m_clips.empty()) m_clips.pop_back();
}

void LiteHtmlContainer::get_viewport(position &viewport) const
{
    viewport.x = {0};
    viewport.y = {0};
    viewport.width = {static_cast<float>(m_widgetWidth)};
    viewport.height = {static_cast<float>(m_widgetHeight)};
}

element::ptr LiteHtmlContainer::create_element(const char * /*tag_name*/, const string_map & /*attributes*/,
                                                const std::shared_ptr<document> & /*doc*/)
{
    return nullptr;
}

void LiteHtmlContainer::get_media_features(media_features &media) const
{
    media.type = media_type_screen;
    media.width = {static_cast<float>(m_widgetWidth)};
    media.height = {static_cast<float>(m_widgetHeight)};
    media.device_width = {static_cast<float>(m_widgetWidth)};
    media.device_height = {static_cast<float>(m_widgetHeight)};
    media.color = 8;
    media.monochrome = 0;
    media.color_index = 256;
    media.resolution = 96;
}

void LiteHtmlContainer::get_language(std::string &language, std::string &culture) const
{
    language = "en";
    culture = "";
}

pixel_t LiteHtmlContainer::get_screen_width() const { return {static_cast<float>(m_widgetWidth)}; }
pixel_t LiteHtmlContainer::get_screen_height() const { return {static_cast<float>(m_widgetHeight)}; }
