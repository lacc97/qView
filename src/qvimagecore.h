#ifndef QVIMAGECORE_H
#define QVIMAGECORE_H

#include <QObject>
#include <QImageReader>
#include <QPixmap>
#include <QMovie>
#include <QFileInfo>

class QVImageCore : public QObject
{
    Q_OBJECT

public:
    enum class scaleMode
    {
       normal,
       width,
       height
    };
    Q_ENUM(scaleMode)

    struct QVFileDetails
    {
        QFileInfo fileInfo;
        bool isPixmapLoaded;
        bool isMovieLoaded;
        QFileInfoList folder;
        int folderIndex;
    };

    explicit QVImageCore(QObject *parent = nullptr);

    QString loadFile(const QString &fileName);
    void updateFolderInfo();

    void loadSettings();

    void jumpToNextFrame();
    void setPaused(bool desiredState);
    void setSpeed(int desiredSpeed);

    const QPixmap scaleExpensively(const int desiredWidth, const int desiredHeight, const scaleMode mode = scaleMode::normal);
    const QPixmap scaleExpensively(const QSize desiredSize, const scaleMode mode = scaleMode::normal);

    //returned const reference is read-only
    const QPixmap& getLoadedPixmap() const {return loadedPixmap; }
    const QMovie& getLoadedMovie() const {return loadedMovie; }
    const QVFileDetails& getCurrentFileDetails() const {return currentFileDetails; }

signals:
    void animatedFrameChanged(QRect rect);

public slots:

private:
    const QStringList filterList = (QStringList() << "*.bmp" << "*.cur" << "*.gif" << "*.icns" << "*.ico" << "*.jp2" << "*.jpeg" << "*.jpe" << "*.jpg" << "*.mng" << "*.pbm" << "*.pgm" << "*.png" << "*.ppm" << "*.svg" << "*.svgz" << "*.tif" << "*.tiff" << "*.wbmp" << "*.webp" << "*.xbm" << "*.xpm");

    QImage loadedImage;
    QPixmap loadedPixmap;
    QMovie loadedMovie;
    QImageReader imageReader;

    QVFileDetails currentFileDetails;
};

#endif // QVIMAGECORE_H