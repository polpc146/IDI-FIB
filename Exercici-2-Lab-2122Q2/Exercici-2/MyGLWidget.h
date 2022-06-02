#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();

  private:
    int printOglError(const char file[], int line, const char func[]);
    
    void calculAtributsEscena (float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);
    virtual void iniEscena();
    virtual void iniCamera();
    virtual void paintGL ();
    virtual void patrTransform ();
    void cubTransform (int i);
    virtual void projectTransform ();
    virtual void viewTransform ();
    virtual void resizeGL (int width, int height);
    virtual void rebotaParets ();
    virtual void tractamentGol();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);
    
    // Internal vars
    float angx;
    float angy;
    float d;
    float movPatr;
    bool pintaPilota = true;
    float anglew;
    float l, r, b, t;
    bool ortho;
};
