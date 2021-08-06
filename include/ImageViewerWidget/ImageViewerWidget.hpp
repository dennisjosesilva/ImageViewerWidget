#pragma once 

#include <QWidget>
#include <QPoint>

class QLabel;
class QScrollArea;
class QImage;
class QScrollBar;
class QMouseEvent;


namespace ImageViewerWidget
{
  class ImageViewerWidget : public QWidget
  {
    Q_OBJECT
  public:
    ImageViewerWidget(QWidget *parent=nullptr);

    inline QImage& image() { return image_; };
    inline const QImage& image() const { return image_; }

    bool saveImage(const QString &fileName);
    bool loadImage(const QString &fileName);

    void setImage(const QImage &newImage);

    void fitToWidget(); 
    void unfitToWidget();    

    void normalSize();    
    void zoomIn();
    void zoomOut();   
    void scaleImage(double factor); 

    inline double scaleFactor() const { return scaleFactor_; }

  protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;

  public:
  signals:
    void imageMousePress(const QPoint &p);
    void imageMouseRelease(const QPoint &p);
    void imageMouseDoubleClick(const QPoint &p);

  private:
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

  private:
    QImage image_;
    QLabel *imageLabel_;
    QScrollArea *scrollArea_;
    double scaleFactor_;
  };
}