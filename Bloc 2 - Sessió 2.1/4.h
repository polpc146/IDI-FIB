// MyGLWidget.h
#include "BL2GLWidget.h"
#include "model.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

  private:
    int printOglError(const char file[], int line, const char func[]);
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    virtual void creaBuffers ();
    virtual void carregaShaders ();
    void ini_camera();
    void viewTransform ();
    void projectTransform ();
    
    // uniform locations
    GLuint viewLoc;
    GLuint projLoc;
    
    //ViewMatrix
    glm::vec3 OBS;
    glm::vec3 VRP;
    glm::vec3 UP;
    
    //ProjectMatrix
    float FOV;
    float ra;
    float znear;
    float zfar;
    
    GLuint VAO_Homer;
    
    Model m;
};
