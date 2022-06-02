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
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent (QMouseEvent *event);
    virtual void creaBuffers ();
    virtual void carregaShaders ();
    virtual void modelTransform ();
    
    void calculCapsaContenidora ();
    void calculAtributsEscena (float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);
    void ini_camera ();
    void modelTransformTerra ();
    void viewTransform ();
    void projectTransform ();
    
    // uniform locations
    GLuint viewLoc;
    GLuint projLoc;
    
    //ViewMatrix
    glm::vec3 OBS;
    glm::vec3 VRP;
    glm::vec3 UP;
    float angx = 0.0f;
    float angy = 0.0f;
    float xClick = 0.0f;
    float yClick = 0.0f;
    
    //ProjectMatrix
    float anglew;
    float FOV;
    float ra;
    float znear;
    float zfar;
    float l, r, b, t;
    
    //VAO i VBO names
    GLuint VAO_Patricio;
    GLuint VAO_Terra;
    
    //Modelo
    Model m;
    
    // Internal vars
    float ry = 0;
    glm::vec3 centreEscena;
    float radi, d;
    float xmini, ymini, zmini, xmaxi, ymaxi, zmaxi;
    glm::vec3 centreBaseModel;
    bool ortho = false;
};
