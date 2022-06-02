#include <QSlider>

class MyQSlider: public QSlider {
    
    Q_OBJECT
    
    public:
        MyQSlider (QWidget *parent);
        
    public slots:
        void tractaZoom();
        
    signals:
        void valueChanged (int);
}
