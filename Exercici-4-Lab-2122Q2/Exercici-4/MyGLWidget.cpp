// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_F: {
      // ...
    break;
	}
  case Qt::Key_Right: {
      // ...
    break;
	}
  case Qt::Key_Left: {
      // ...
    break;
	}
  default: LL4GLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::initializeGL() {
    
    LL4GLWidget::initializeGL();
    
    posFocusEsc = glm::vec3(10.0, 3.0, 5.0);
    glUniform3fv(posFocusEscLoc, 1, &posFocusEsc[0]);
    
    posFocusCam = glm::vec3(0.0, 0.0, 0.0);
    glUniform3fv(posFocusCamLoc, 1, &posFocusCam[0]);
    
    posFocusMod = glm::vec3(centreBasePatr[0], maxYPat, centreBasePatr[2]);
    glUniform3fv(posFocusModLoc, 1, &posFocusMod[0]);
}

void MyGLWidget::carregaShaders() {
    
    LL4GLWidget::carregaShaders();

    posFocusEscLoc = glGetUniformLocation(program->programId(), "posFocusEsc");
    posFocusCamLoc = glGetUniformLocation(program->programId(), "posFocusCam");
    posFocusModLoc = glGetUniformLocation(program->programId(), "posFocusMod");
}
