#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersQuadrat();
  creaBuffersTriangle();
}

void MyGLWidget::modelTransformMuntanya () {
    
    glm::mat4 TG (1.0);
    TG = glm::translate (TG, glm::vec3 (-0.2, -1.0, 0));
    TG = glm::scale (TG, glm::vec3 (1.6, 1.8, 1));
    TG = glm::translate (TG, glm::vec3 (-0.5, 0, 0));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
    colObj = glm::vec3 (0.5, 0.3, 0.1);
    glUniform3fv (colorLoc, 1, &colObj[0]);
}

void MyGLWidget::pintaMuntanya ()  // Caldrà modificar aquest mètode per pintar la muntanya
{
  // pintem un triangle
  glBindVertexArray(VAOTriangle);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyGLWidget::modelTransformBaseGronxador () {
    
    glm::mat4 TG (1.0);
    TG = glm::translate (TG, glm::vec3 (0, -1.0, 0));
    TG = glm::scale (TG, glm::vec3 (0.2, 0.3, 1));
    TG = glm::translate (TG, glm::vec3 (-0.5, 0, 0));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
    colObj = glm::vec3 (0.7, 0, 0);
    glUniform3fv (colorLoc, 1, &colObj[0]);
}

void MyGLWidget::pintaBaseGronxador ()  // Caldrà modificar aquest mètode per pintar la muntanya
{
  // pintem un triangle
  glBindVertexArray(VAOTriangle);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyGLWidget::modelTransformNeu () {
    
    glm::mat4 TG (1.0);
    TG = glm::translate (TG, glm::vec3 (-0.2, 0.4, 0));
    TG = glm::scale (TG, glm::vec3 (0.4, 0.4, 1));
    TG = glm::translate (TG, glm::vec3 (-0.5, 0, 0));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
    colObj = glm::vec3 (1, 1, 1);
    glUniform3fv (colorLoc, 1, &colObj[0]);
}

void MyGLWidget::pintaNeu ()  // Caldrà modificar aquest mètode per pintar la muntanya
{
  // pintem un triangle
  glBindVertexArray(VAOTriangle);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}


void MyGLWidget::modelTransformBarraGronxador () {
    
    glm::mat4 TG (1.0);
    TG = glm::translate (TG, glm::vec3 (0, -0.7, 0));
    TG = TG * GirGronxador;
    TG = glm::scale (TG, glm::vec3 (1.4/0.5, 0.2/0.5, 1));
    TG = glm::translate (TG, glm::vec3 (0.25, 0.5, 0));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
    colObj = glm::vec3 (0.2, 0.7, 0.2);
    glUniform3fv (colorLoc, 1, &colObj[0]);
}

void MyGLWidget::modelTransformSeient(glm::vec3 posBase) {
    
    glm::mat4 TG (1.0);
    TG = glm::translate (TG, glm::vec3 (0, -0.7, 0));
    TG = TG * GirGronxador;
    TG = glm::translate (TG, glm::vec3 (posBase.x, 0.2, 0));
    TG = glm::scale (TG, glm::vec3 (0.2/0.5, 0.1/0.5, 1));
    TG = glm::translate (TG, glm::vec3 (0.25, 0.5, 0));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
    colObj = glm::vec3 (0.4, 0.4, 0.4);
    glUniform3fv (colorLoc, 1, &colObj[0]);
}

void MyGLWidget::transformGirGronxador ()
{
    GirGronxador = glm::mat4(1.0);
    GirGronxador = glm::rotate (GirGronxador, angleGir, glm::vec3 (0,0,1)); 
}

void MyGLWidget::pintaGronxador ()  
{ // Caldrà modificar aquest mètode per pintar el gronxador sencer, la barra i els dos seients
  // pintem un quadrat 
  glBindVertexArray(VAOQuadrat);
  modelTransformBarraGronxador();
  glDrawArrays(GL_TRIANGLES, 0, 6);
  modelTransformSeient(glm::vec3 (-0.6, -0.5, 0));
  glDrawArrays(GL_TRIANGLES, 0, 6);
  modelTransformSeient(glm::vec3 (0.6, -0.5, 0));
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void MyGLWidget::paintGL ()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  // Pintem muntanya
  modelTransformMuntanya();
  pintaMuntanya();
  
  //Pintem base gronxador
  modelTransformBaseGronxador();
  pintaBaseGronxador();
  
  
  // Pintem gronxador
  transformGirGronxador();
  pintaGronxador();
  
  //Pintem neu
  modelTransformNeu();
  pintaNeu();
  
  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_Left:
            if (angleGir <= M_PI/7.2) angleGir += M_PI/36;
            break;
    case Qt::Key_Right:
            if (angleGir >= -M_PI/7.2) angleGir -= M_PI/36;
            break;
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::creaBuffersQuadrat ()
{
  glm::vec3 Vertices[6];  // vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3(-0.5, -0.5, 0);
  Vertices[1] = glm::vec3( 0, -0.5, 0);
  Vertices[2] = glm::vec3(-0.5, 0, 0);
  Vertices[3] = glm::vec3( 0, -0.5, 0);
  Vertices[4] = glm::vec3( 0, 0, 0);
  Vertices[5] = glm::vec3( -0.5, 0, 0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar el tronc
  glGenVertexArrays(1, &VAOQuadrat);
  glBindVertexArray(VAOQuadrat);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::creaBuffersTriangle ()
{
  glm::vec3 Vertices[3];  // Quatre vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3( 0, 0, 0);
  Vertices[1] = glm::vec3( 1, 0, 0);
  Vertices[2] = glm::vec3( 0.5, 1, 0);

  // Creació del Vertex Array Object (VAO) que usarem per pintar el tronc
  glGenVertexArrays(1, &VAOTriangle);
  glBindVertexArray(VAOTriangle);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");

  // Obtenim els identificadors dels uniforms
  transLoc = glGetUniformLocation (program->programId(), "TG");
  colorLoc = glGetUniformLocation (program->programId(), "color");
}
