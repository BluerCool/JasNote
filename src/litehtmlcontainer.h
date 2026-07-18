#ifndef LITEHTMLCONTAINER_H
#define LITEHTMLCONTAINER_H

#include <litehtml.h>
#include <litehtml/document_container.h>
#include <QPainter>
#include <QFont>
#include <QFontMetrics>
#include <QMap>
#include <QImage>
#include <functional>

class LiteHtmlContainer : public litehtml::document_container
{
public:
    LiteHtmlContainer();
    ~LiteHtmlContainer() override;

    void setPainter(QPainter *painter);
    void setWidgetSize(int width, int height);

    // litehtml::document_container interface
    litehtml::uint_ptr create_font(const litehtml::font_description &descr, const litehtml::document *doc,
                                   litehtml::font_metrics *fm) override;
    void delete_font(litehtml::uint_ptr hFont) override;
    litehtml::pixel_t text_width(const char *text, litehtml::uint_ptr hFont) override;
    void draw_text(litehtml::uint_ptr hdc, const char *text, litehtml::uint_ptr hFont,
                   litehtml::web_color color, const litehtml::position &pos) override;
    litehtml::pixel_t pt_to_px(float pt) const override;
    litehtml::pixel_t get_default_font_size() const override;
    const char *get_default_font_name() const override;
    void draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker &marker) override;
    void load_image(const char *src, const char *baseurl, bool redraw_on_ready) override;
    void get_image_size(const char *src, const char *baseurl, litehtml::size &sz) override;
    void draw_image(litehtml::uint_ptr hdc, const litehtml::background_layer &layer,
                    const std::string &url, const std::string &base_url) override;
    void draw_solid_fill(litehtml::uint_ptr hdc, const litehtml::background_layer &layer,
                         const litehtml::web_color &color) override;
    void draw_linear_gradient(litehtml::uint_ptr hdc, const litehtml::background_layer &layer,
                              const litehtml::background_layer::linear_gradient &gradient) override;
    void draw_radial_gradient(litehtml::uint_ptr hdc, const litehtml::background_layer &layer,
                              const litehtml::background_layer::radial_gradient &gradient) override;
    void draw_conic_gradient(litehtml::uint_ptr hdc, const litehtml::background_layer &layer,
                             const litehtml::background_layer::conic_gradient &gradient) override;
    void draw_borders(litehtml::uint_ptr hdc, const litehtml::borders &borders,
                      const litehtml::position &draw_pos, bool root) override;
    void set_caption(const char *caption) override;
    void set_base_url(const char *base_url) override;
    void link(const std::shared_ptr<litehtml::document> &doc, const litehtml::element::ptr &el) override;
    void on_anchor_click(const char *url, const litehtml::element::ptr &el) override;
    bool on_element_click(const litehtml::element::ptr &el) override;
    void on_mouse_event(const litehtml::element::ptr &el, litehtml::mouse_event event) override;
    void set_cursor(const char *cursor) override;
    void transform_text(std::string &text, litehtml::text_transform tt) override;
    void import_css(std::string &text, const std::string &url, std::string &baseurl) override;
    void set_clip(const litehtml::position &pos, const litehtml::border_radiuses &bdr_radius) override;
    void del_clip() override;
    void get_viewport(litehtml::position &viewport) const override;
    litehtml::element::ptr create_element(const char *tag_name, const litehtml::string_map &attributes,
                                          const std::shared_ptr<litehtml::document> &doc) override;
    void get_media_features(litehtml::media_features &media) const override;
    void get_language(std::string &language, std::string &culture) const override;
    litehtml::pixel_t get_screen_width() const;
    litehtml::pixel_t get_screen_height() const;

    // Scroll
    void setScrollY(int y) { m_scrollY = y; }
    int scrollY() const { return m_scrollY; }
    int documentHeight() const { return m_docHeight; }

    QPainter *painter() const { return m_painter; }

private:
    QPainter *m_painter = nullptr;
    int m_widgetWidth = 800;
    int m_widgetHeight = 600;
    int m_scrollY = 0;
    int m_docHeight = 0;

    struct FontInfo {
        QFont font;
        QFontMetrics *metrics = nullptr;
    };
    QMap<litehtml::uint_ptr, FontInfo> m_fonts;
    litehtml::uint_ptr m_nextFontId = 1;

    struct ClipRect {
        litehtml::position box;
        litehtml::border_radiuses radius;
    };
    std::vector<ClipRect> m_clips;
};

#endif // LITEHTMLCONTAINER_H
