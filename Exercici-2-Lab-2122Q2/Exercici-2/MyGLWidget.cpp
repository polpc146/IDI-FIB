#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[])  {
    
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

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::calculAtributsEscena (float xmin, float ymin, float zmin, float xmax, float ymax, float zmax) {
    
    centreEscena = glm::vec3((xmax+xmin)/2.0f, (ymax+ymin)/2.0f, (zmax+zmin)/2.0f);
    radiEscena = glm::distance(glm::vec3(xmin,ymin,zmin),glm::vec3(xmax,ymax,zmax))/2.0f;
}

void MyGLWidget::iniEscena() {
    
    calculAtributsEscena (-10, 0, -7, 10, 4, 7);
    
    altPorter = 4;
    posPorter = glm::vec3(9.0, 0.0, 0.0);  // posició inicial del porter
    posPilota = glm::vec3(7.0, 0.0, 0.0);  // posició inicial de la pilota
    dirInicialPilota();    // direcció inicial de la pilota
    movPatr = 0;
}

void MyGLWidget::iniCamera () {
    
    ortho = false;
    angx = float(M_PI)/4.0f;
    angy = 0;
    vrp = centreEscena;
    d = 2 * radiEscena;
    obs = vrp + d * glm::vec3(0,1,0);
    up = glm::vec3(-1,0,0);
    viewTransform();
    
    anglew = asin(radiEscena/d);
    fov = 2 * anglew;
    ra = 1.0f;
    znear = d - radiEscena;
    zfar = d + radiEscena;
    l = -radiEscena;
    r = radiEscena;
    b = -radiEscena;
    t = radiEscena;
    LL2GLWidget::projectTransform();
}

void MyGLWidget::paintGL () {
    
    // descomentar per canviar paràmetres
    // glViewport (0, 0, ample, alt);

    // Esborrem el frame-buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Patricio
    glBindVertexArray (VAO_Patr);
    patrTransform();
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);

    // Pilota
    if (pintaPilota) {
        
        glBindVertexArray (VAO_Pil);
        pilTransform();
        glDrawArrays(GL_TRIANGLES, 0, pil.faces().size()*3);
    }

    // Cub
    glBindVertexArray (VAO_Cub);
    for (int i=0; i<3; ++i) {
        
        cubTransform (i);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // Terra
    glBindVertexArray (VAO_Terra);
    identTransform();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray (0);
}

void MyGLWidget::patrTransform () {
    
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(0,0,movPatr));
    TG = glm::translate(TG, posPorter);
    TG = glm::rotate(TG, float(-M_PI/2.0f), glm::vec3(0,1,0));
    TG = glm::scale(TG, glm::vec3(altPorter,altPorter,altPorter));
    TG = glm::scale(TG, glm::vec3(escalaPatr,escalaPatr,escalaPatr));
    TG = glm::translate(TG, -centreBasePatr);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::cubTransform (int i) {
    
    glm::mat4 TG(1.0f);
    switch (i) {
        case 0: 
            TG = glm::translate(TG, glm::vec3(0,0,-6.9));
            TG = glm::scale(TG, glm::vec3(20,2,0.2f));
            break;
        case 1: 
            TG = glm::translate(TG, glm::vec3(0,0,6.9f));
            TG = glm::scale(TG, glm::vec3(20,2,0.2f));
            break;
        case 2:
            TG = glm::translate(TG, glm::vec3(-9.9,0,0));
            TG = glm::scale(TG, glm::vec3(0.2,2,14));
            break;
        default: break;
  }
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform () {
    
    glm::mat4 Proj;
    if (not ortho) Proj = glm::perspective (fov, ra, znear, zfar);
    else {
        if (ra >= 1.0f) { 
        
        l = -radiEscena * ra;
        r = radiEscena * ra;
        b = -radiEscena;
        t = radiEscena;
    }
    else { 
        
        l = -radiEscena;
        r = radiEscena;
        b = -radiEscena/ra;
        t = radiEscena/ra;
    }
        Proj = glm::ortho (l, r, b, t, znear, zfar);
    }
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform () {
    
    // Matriu de posició i orientació de l'observador
    glm::mat4 View(1.0f);
    if (not ortho) {
        
        View = glm::translate(View, glm::vec3(0,0,-d));
        View = glm::rotate(View, angx, glm::vec3(1,0,0));
        View = glm::rotate(View, -angy, glm::vec3(0,1,0));
    }
    else View = glm::lookAt (obs, vrp, up);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::resizeGL (int width, int height) {
    
    // Aquest codi és necessari únicament per a MACs amb pantalla retina.
    #ifdef __APPLE__
    GLint vp[4];
    glGetIntegerv (GL_VIEWPORT, vp);
    ample = vp[2];
    alt = vp[3];
    #else
    ample = width;
    alt = height;
    #endif
    ra = float(ample)/float(alt);
    factorAngleY = M_PI / ample;
    factorAngleX = M_PI / alt;
    if (ra >= 1.0f) fov = 2 * anglew;
    else fov = 2 * atan(tan(anglew)/ra);
    projectTransform();
}

void MyGLWidget::rebotaParets () {
    
    if (posPilota[0] <= -9.2 && dirPilota[0]< 0) dirPilota[0] = -dirPilota[0];
    if ((posPilota[2] <= -6.2 && dirPilota[2] < 0) || (posPilota[2] >= 6.2f && dirPilota[2] > 0)) dirPilota[2] = -dirPilota[2];
}

void MyGLWidget::tractamentGol() {
    
    pintaPilota = false;
    timer.stop();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
    
    makeCurrent();
    switch (event->key()) {
        
        case Qt::Key_Up: { // moviment de la pilota
        
            if (posPilota[0] == 7.0) mourePilota ();
            break;
        }
        case Qt::Key_I: { // reinicia posició pilota
        
            pintaPilota = true;
            iniciPilota ();
            break;
        }
        case Qt::Key_Left: {
            
            float limit = 7 - (altPorter/2);
            if (movPatr < limit) movPatr += 0.5;
            break;
        }
        case Qt::Key_Right: {
            
            float limit = 7 - (altPorter/2);
            if (movPatr > -limit) movPatr -= 0.5;
            break;
        }
        case Qt::Key_C: {
            
            if(not ortho) ortho = true;
            else ortho = false;
            viewTransform();
            projectTransform();
            break;
        }
        case Qt::Key_W: {
            
            if (altPorter < 6) ++altPorter;
            break;
        }
        case Qt::Key_S: {
            
            if (altPorter > 2) --altPorter;
            break;
        }
        case Qt::Key_R: {
            
            iniEscena();
            iniCamera();
            pintaPilota = true;
            iniciPilota ();
            break;
        }
        default: event->ignore(); break;
    }
    update();
}

void MyGLWidget::mousePressEvent(QMouseEvent* event) {
    
    makeCurrent();
    xClick = event->x();
    yClick = event->y();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent* event) {
    
    makeCurrent();
    if (not ortho && event->buttons() == Qt::LeftButton && !(event->modifiers() & (Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier))) {
        
        float factorAngleX2 = event->x() - xClick;
        float factorAngleY2 = event->y() - yClick;
        angy += factorAngleX * factorAngleX2;
        angx += factorAngleY * factorAngleY2;
    }
    viewTransform();
    update();
    
    xClick = event->x();
    yClick = event->y();
}
