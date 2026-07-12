#include "settings.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardPaths>
#include <QDir>

void loadConfig()
{
    QString sysPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)
                      + "/jasnote/config.json";
    QString localPath = QDir::currentPath() + "/config.json";

    QString path = QFile::exists(sysPath) ? sysPath : localPath;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) return;
    QJsonObject r = doc.object();

    if (auto v = r["window"].toObject(); !v.isEmpty()) {
        if (v.contains("minWidth"))        S::WIN_MIN_W = v["minWidth"].toInt();
        if (v.contains("minHeight"))       S::WIN_MIN_H = v["minHeight"].toInt();
        if (v.contains("defaultWidth"))    S::WIN_DEFAULT_W = v["defaultWidth"].toInt();
        if (v.contains("defaultHeight"))   S::WIN_DEFAULT_H = v["defaultHeight"].toInt();
        if (v.contains("opacity"))         S::WIN_OPACITY = v["opacity"].toDouble();
        if (v.contains("radius"))          S::WIN_RADIUS = v["radius"].toInt();
        if (v.contains("layoutMargin"))    S::WIN_LAYOUT_MARGIN = v["layoutMargin"].toInt();
        if (v.contains("borderWidth"))     S::WIN_BORDER_WIDTH = v["borderWidth"].toInt();
        if (v.contains("borderAlphaBase")) S::WIN_BORDER_ALPHA_BASE = v["borderAlphaBase"].toInt();
        if (v.contains("bg1")) { auto a = v["bg1"].toArray(); S::BG1_R=a[0].toInt(); S::BG1_G=a[1].toInt(); S::BG1_B=a[2].toInt(); }
        if (v.contains("bg2")) { auto a = v["bg2"].toArray(); S::BG2_R=a[0].toInt(); S::BG2_G=a[1].toInt(); S::BG2_B=a[2].toInt(); }
        if (v.contains("bg3")) { auto a = v["bg3"].toArray(); S::BG3_R=a[0].toInt(); S::BG3_G=a[1].toInt(); S::BG3_B=a[2].toInt(); }
    }

    if (auto v = r["statusBar"].toObject(); !v.isEmpty()) {
        if (v.contains("fontSize"))        S::STATUS_FONT_SIZE = v["fontSize"].toInt();
        if (v.contains("font"))            S::STATUS_FONT = v["font"].toString();
        if (v.contains("color"))           S::STATUS_COLOR = v["color"].toString();
        if (v.contains("modifiedColor"))   S::STATUS_MODIFIED = v["modifiedColor"].toString();
        if (v.contains("modifiedFontSize")) S::STATUS_MODIFIED_SIZE = v["modifiedFontSize"].toInt();
        if (v.contains("x"))               S::STATUS_X = v["x"].toInt();
        if (v.contains("yOffset"))         S::STATUS_Y_OFFSET = v["yOffset"].toInt();
        if (v.contains("width"))           S::STATUS_W = v["width"].toInt();
        if (v.contains("height"))          S::STATUS_H = v["height"].toInt();
        if (v.contains("marginLeft"))      S::STATUS_MARGIN_LEFT = v["marginLeft"].toInt();
    }

    if (auto v = r["editor"].toObject(); !v.isEmpty()) {
        if (v.contains("fontSize"))    S::ED_FONT_SIZE = v["fontSize"].toInt();
        if (v.contains("font"))        S::ED_FONT = v["font"].toString();
        if (v.contains("textColor"))   S::ED_COLOR = v["textColor"].toString();
        if (v.contains("selectionBg")) S::ED_SEL_BG = v["selectionBg"].toString();
        if (v.contains("padding"))     S::ED_PADDING = v["padding"].toInt();
        if (v.contains("tabStop"))     S::ED_TAB_STOP = v["tabStop"].toInt();
        if (v.contains("autosaveMs"))  S::ED_AUTOSAVE_MS = v["autosaveMs"].toInt();
    }

    if (auto v = r["dialog"].toObject(); !v.isEmpty()) {
        if (v.contains("width"))        S::DLG_W = v["width"].toInt();
        if (v.contains("height"))       S::DLG_H = v["height"].toInt();
        if (v.contains("bgAlpha"))      S::DLG_BG_ALPHA = v["bgAlpha"].toInt();
        if (v.contains("radius"))       S::DLG_RADIUS = v["radius"].toInt();
        if (v.contains("borderAlpha"))  S::DLG_BORDER_ALPHA = v["borderAlpha"].toInt();
        if (v.contains("borderWidth"))  S::DLG_BORDER_W = v["borderWidth"].toInt();
        if (v.contains("marginLeft"))   S::DLG_ML = v["marginLeft"].toInt();
        if (v.contains("marginTop"))    S::DLG_MT = v["marginTop"].toInt();
        if (v.contains("marginRight"))  S::DLG_MR = v["marginRight"].toInt();
        if (v.contains("marginBottom")) S::DLG_MB = v["marginBottom"].toInt();
        if (v.contains("titleColor"))   S::DLG_TITLE_COLOR = v["titleColor"].toString();
        if (v.contains("titleFontSize")) S::DLG_TITLE_SIZE = v["titleFontSize"].toInt();
    }

    if (auto v = r["dialogButtons"].toObject(); !v.isEmpty()) {
        if (v.contains("width"))          S::BTN_W = v["width"].toInt();
        if (v.contains("height"))         S::BTN_H = v["height"].toInt();
        if (v.contains("radius"))         S::BTN_RADIUS = v["radius"].toInt();
        if (v.contains("fontSize"))       S::BTN_FONT_SIZE = v["fontSize"].toInt();
        if (v.contains("textColor"))      S::BTN_COLOR = v["textColor"].toString();
        if (v.contains("cancelBg"))       S::BTN_CANCEL_BG = v["cancelBg"].toString();
        if (v.contains("cancelHover"))    S::BTN_CANCEL_HOVER = v["cancelHover"].toString();
        if (v.contains("dontSaveBg"))     S::BTN_DONTSAVE_BG = v["dontSaveBg"].toString();
        if (v.contains("dontSaveHover"))  S::BTN_DONTSAVE_HOVER = v["dontSaveHover"].toString();
        if (v.contains("saveBg"))         S::BTN_SAVE_BG = v["saveBg"].toString();
        if (v.contains("saveHover"))      S::BTN_SAVE_HOVER = v["saveHover"].toString();
    }

    if (auto v = r["titleBar"].toObject(); !v.isEmpty()) {
        if (v.contains("height"))           S::TB_HEIGHT = v["height"].toInt();
        if (v.contains("title"))            S::TB_TITLE = v["title"].toString();
        if (v.contains("font"))             S::TB_FONT = v["font"].toString();
        if (v.contains("fontSize"))         S::TB_FONT_SIZE = v["fontSize"].toInt();
        if (v.contains("color"))            S::TB_COLOR = v["color"].toString();
        if (v.contains("buttonSize"))       S::TB_BTN_SIZE = v["buttonSize"].toInt();
        if (v.contains("buttonFontSize"))   S::TB_BTN_FONT = v["buttonFontSize"].toInt();
        if (v.contains("buttonColor"))      S::TB_BTN_COLOR = v["buttonColor"].toString();
        if (v.contains("buttonHover"))      S::TB_BTN_HOVER = v["buttonHover"].toString();
        if (v.contains("closeButtonHover")) S::TB_BTN_CLOSE_HOVER = v["closeButtonHover"].toString();
    }
}
