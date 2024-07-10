/*
 * @Author: weick
 * @Date: 2023-12-05 23:02:19
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-20 00:03:47
 */

#pragma once
#include "../acore/inc/asinglton.h"
#include <QSettings>
#include <QDir>
#include <QStandardPaths>

class Settings: public ASinglton<Settings> {
public:
    Settings();
    void load();
    bool autoStart() const;
    void setAutoStart(const bool autoStart);

    // Convert
    QString conversionOutPath() const;
    void setConversionOutPath(const QString path);
    QString conversionOutFormat() const;
    void setConversionOutFormat(const QString format);

    // Compress
    QString compressOutPath() const;
    void setCompressOutPath(const QString path);
    QString compressOutFormat() const;
    void setCompressOutFormat(const QString format);
    int compressQuality() const;
    void setCompressQuality(const int quality);

    // 2gif
    int gifFps() const;
    void setGifFps(const int fps);
    int gifQuality() const;
    void setGifQuality(const int quality);
    int gifResolution() const;
    void setGifResolution(const int resolution);
    int gifWidth() const;
    void setGifWidth(const int width);
    int gifHeight() const;
    void setGifHeight(const int height);
    bool gifRepeat() const;
    void setGifRepeat(const bool repeat);
    QString gifOutpath() const;
    void setGifOutpath(const QString path);

private:
    QSettings m_Settings;
    // Common
    bool m_AutoStart;

    // Convert
    QString m_ConversionOutPath;
    QString m_ConversionOutFormat;

    // Compress
    QString m_CompressOutPath;
    QString m_CompressOutFormat;
    int m_CompressQuality;

    // 2gif
    int gif_fps_;
    int gif_quality_;
    int gif_resolution_;
    int gif_width_;
    int gif_height_;
    bool gif_repeat_;
    QString gif_outpath_;
};

#define SETTINGS Settings::getInstance()
