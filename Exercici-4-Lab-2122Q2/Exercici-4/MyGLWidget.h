// MyGLWidget.h
#include "LL4GLWidget.h"

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT
  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();
  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void carregaShaders();
    virtual void initializeGL();
  private:
    int printOglError(const char file[], int line, const char func[]);
    
    GLuint posFocusEscLoc, posFocusCamLoc, posFocusModLoc;
    glm::vec3 posFocusEsc;
    glm::vec3 posFocusCam;
    glm::vec3 posFocusMod;
};
