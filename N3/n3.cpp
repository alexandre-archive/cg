#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif

#include "graphicobject.cpp"
#include "universe.cpp"

#define KEY_TAB 9
#define KEY_ESC 27
#define KEY_SPACE 32
#define KEY_DEL 127

#define CHANGE_COLOR_R 1
#define CHANGE_COLOR_G 2
#define CHANGE_COLOR_B 3

#define CHANGE_LINE_WIDTH 4

GLint width  = 400,
      height = 400;

GLfloat ortho2D_minX = -400.0f,
        ortho2D_maxX =  400.0f,
        ortho2D_minY = -400.0f,
        ortho2D_maxY =  400.0f;

bool isSelectionMode = false,
     isMouseDown = false;

PUniverse universe;

PGraf currentObj;

int action = 0;

void resize(int nwidth, int nheight)
{
    width = nwidth;
    height = nheight;

    ortho2D_minX = width * -1;
    ortho2D_maxX = width;
    ortho2D_minY = height * -1;
    ortho2D_maxY = height;
}

void drawMode()
{
    DrawText(ortho2D_minX + 4, ortho2D_minY + 4, (char*)(isSelectionMode ? "Selecao (Tab)" : "Edicao (Tab)"));
}

void display()
{
    glViewport(0.0, 0.0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(ortho2D_minX, ortho2D_maxX, ortho2D_minY, ortho2D_maxY);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawMode();

    universe->Draw();

    glutSwapBuffers();
}

/**
    Captura eventos do teclado.
**/
void keyPress(unsigned char key, int x, int y)
{
    PGraf g = NULL;
    Transform matrixTranslate, matrixTranslateInverse, matrixScale, matrixRotate, matrixGlobal;
    double angGlobal = 0;
    static double RAS_DEG_TO_RAD = 0.017453292519943295769236907684886;

    switch (key)
    {
        case KEY_ESC:
            exit(0);
        break;
        case KEY_TAB:
            action = 0;
            isSelectionMode = !isSelectionMode;
            glutPostRedisplay();
        break;
        case KEY_DEL:
            action = 0;
            // Deleta o ponto ou poligono se for seleção.
            // Limpa a tela se for edição.
            if (isSelectionMode)
            {
                PGraf g = universe->GetSelectedObj();

                if (g)
                {
                    universe->DeleteSelectedObj();
                }

                g = universe->GetObjSelectedPoint();

                if (g)
                {
                    g->DeleteSelectedPoint();

                    int size = g->PointCount();

                    if (size <= 1)
                    {
                        universe->DeleteSelectedObj();
                    }
                }
            }
            else
            {
                universe->SelectNone();
                universe->Clear();
            }
            glutPostRedisplay();
        break;
        case KEY_SPACE:
            action = 0;
            g = universe->GetSelectedObj();
            if (g)
            {
                g->ChangePrimitive();
                glutPostRedisplay();
            }
        break;
        case 'R':
        case 'r':
            action = CHANGE_COLOR_R;
        break;
        case 'G':
        case 'g':
            action = CHANGE_COLOR_G;
        break;
        case 'B':
        case 'b':
            action = CHANGE_COLOR_B;
        break;
        case 'L':
        case 'l':
            action = CHANGE_LINE_WIDTH;
        break;
        case '+':
            g = universe->GetSelectedObj();
            if (g)
            {
                switch (action)
                {
                    case CHANGE_COLOR_R:
                        g->BackColor.r += 0.1;
                    break;
                    case CHANGE_COLOR_G:
                        g->BackColor.g += 0.1;
                    break;
                    case CHANGE_COLOR_B:
                        g->BackColor.b += 0.1;
                    break;
                    case CHANGE_LINE_WIDTH:
                        if (g->LineWidth < 6.0f)
                        {
                            g->LineWidth += 0.5f;
                        }
                    break;
                }

                glutPostRedisplay();
            }
        break;
        case '-':
            g = universe->GetSelectedObj();
            if (g)
            {
                switch (action)
                {
                    case CHANGE_COLOR_R:
                        g->BackColor.r -= 0.1;
                    break;
                    case CHANGE_COLOR_G:
                        g->BackColor.g -= 0.1;
                    break;
                    case CHANGE_COLOR_B:
                        g->BackColor.b -= 0.1;
                    break;
                    case CHANGE_LINE_WIDTH:
                        if (g->LineWidth > 1.0f)
                        {
                            g->LineWidth -= 0.5f;
                        }
                    break;
                }

                glutPostRedisplay();
            }
        break;
        /*Mostra o vetor de pontos do Objeto*/
        case '1':
            g = universe->GetSelectedObj();
            if (g)
            {
                g->dumpPoint();
                glutPostRedisplay();
            }
        break;
        //Mostra a matriz de transformação do objeto
        case '2':
            g = universe->GetSelectedObj();
            if (g)
            {
                g->transform.dumpMatriz();
                glutPostRedisplay();
            }
        break;
        //Restaura a matriz de Transformacao
        case '3':
            g = universe->GetSelectedObj();
            if (g)
            {
                g->transform.MakeIdentity();
                glutPostRedisplay();
            }
        break;
        //Translação para a Direita
        case 'd':
        case 'D':
            g = universe->GetSelectedObj();
            if (g)
            {
                Point point;
                point.x = 2.0;
                point.y = g->transform.GetPoint().y;
                matrixTranslate.MakeTranslation(point);
                g->transform = g->transform.transformMatrix(matrixTranslate);
                glutPostRedisplay();
            }
        break;
        //Translação para a Esquerda
        case 'a':
        case 'A':
            g = universe->GetSelectedObj();
            if (g)
            {
                Point point;
                point.x = -2.0;
                point.y = g->transform.GetPoint().y;
                matrixTranslate.MakeTranslation(point);
                g->transform = g->transform.transformMatrix(matrixTranslate);
                glutPostRedisplay();
            }
        break;
        //Translação para cima
        case 'w':
        case 'W':
            g = universe->GetSelectedObj();
            if (g)
            {
                Point point;
                point.y = 2.0;
                point.x = g->transform.GetPoint().x;
                matrixTranslate.MakeTranslation(point);
                g->transform = g->transform.transformMatrix(matrixTranslate);
                glutPostRedisplay();
            }
        break;
        //Translação para baixo
        case 's':
        case 'S':
            g = universe->GetSelectedObj();
            if (g)
            {
                Point point;
                point.y = -2.0;
                point.x = g->transform.GetPoint().x;
                matrixTranslate.MakeTranslation(point);
                g->transform = g->transform.transformMatrix(matrixTranslate);
                glutPostRedisplay();
            }
        break;
        //Escala + em relação a origem
        case '4':
            g = universe->GetSelectedObj();
            if (g)
            {
                // x   y   z
                matrixScale.MakeScale(2.0,2.0,1.0);
                g->transform = g->transform.transformMatrix(matrixScale);
                glutPostRedisplay();
            }
        break;
        //Escala - em relação a origem
        case '5':
            g = universe->GetSelectedObj();
            if (g)
            {
                // x   y   z
                matrixScale.MakeScale(0.5,0.5,1.0);
                g->transform = g->transform.transformMatrix(matrixScale);
                glutPostRedisplay();
            }
        break;
        //Rotação em +10º em relaçao a origem
        case '6':
            g = universe->GetSelectedObj();
            if (g)
            {
                angGlobal += 10.0; // rotacao em 10 graus
                matrixRotate.MakeZRotation(RAS_DEG_TO_RAD * angGlobal);
                g->transform = g->transform.transformMatrix(matrixRotate);
                glutPostRedisplay();
            }
        break;
        //Rotação em -10° em relaçao a origem
        case '7':
            g = universe->GetSelectedObj();
            if (g)
            {
                angGlobal -= 10.0; // rotacao em 10 graus
                matrixRotate.MakeZRotation(RAS_DEG_TO_RAD * angGlobal);
                g->transform = g->transform.transformMatrix(matrixRotate);
                glutPostRedisplay();
            }
        break;
        //Rotação em +10º em um ponto qualquer.
        case '8':
            g = universe->GetSelectedObj();
            if (g)
            {
                Point point;
                //Translação para a origem do objeto(cento da BBOX)
                point.x  = - (g->bbox.maxX / 2);
                point.y  = -(g->bbox.maxY / 2);
                matrixTranslate.MakeTranslation(point);

                //Rotaciona o objeto em relação a sua origem
                matrixRotate.MakeZRotation(RAS_DEG_TO_RAD * 10);

                //Translação inversa, voltando a posicao original do objeto
                point.x  = (g->bbox.maxX / 2); 
                point.y  = (g->bbox.maxY / 2);
                matrixTranslateInverse.MakeTranslation(point);

                matrixGlobal = matrixGlobal.transformMatrix(matrixTranslateInverse);
                matrixGlobal = matrixGlobal.transformMatrix(matrixRotate);
                matrixGlobal = matrixGlobal.transformMatrix(matrixTranslate);

                g->transform =  g->transform.transformMatrix(matrixGlobal);
                glutPostRedisplay();
            }
        break;
        //Rotação em -10º em um ponto qualquer.
        case '9':
            g = universe->GetSelectedObj();
            if (g)
            {
                Point point;
                //Translação para a origem do objeto(cento da BBOX)
                point.x  = - (g->bbox.maxX / 2);
                point.y  = -(g->bbox.maxY / 2);
                matrixTranslate.MakeTranslation(point);

                //Rotaciona o objeto em relação a sua origem
                matrixRotate.MakeZRotation(RAS_DEG_TO_RAD * -10);

                //Translação inversa, voltando a posicao original do objeto
                point.x  = (g->bbox.maxX / 2); 
                point.y  = (g->bbox.maxY / 2);
                matrixTranslateInverse.MakeTranslation(point);

                matrixGlobal = matrixGlobal.transformMatrix(matrixTranslateInverse);
                matrixGlobal = matrixGlobal.transformMatrix(matrixRotate);
                matrixGlobal = matrixGlobal.transformMatrix(matrixTranslate);

                g->transform =  g->transform.transformMatrix(matrixGlobal);
                glutPostRedisplay();
            }
        break;
        //Escala - em um ponto qualquer.
        case 'Z':   
        case 'z':
            g = universe->GetSelectedObj();
            if (g)
            {
                Point point;
                //Translação para a origem do objeto(cento da BBOX)
                point.x  = - (g->bbox.maxX / 2);
                point.y  = -(g->bbox.maxY / 2);
                matrixTranslate.MakeTranslation(point);

                //Escala reduzindo objeto pela metade em relacao a origem
                matrixScale.MakeScale(0.5, 0.5, 1.0);

                //Translação inversa, voltando a posicao original do objeto
                point.x  = (g->bbox.maxX / 2); 
                point.y  = (g->bbox.maxY / 2);
                matrixTranslateInverse.MakeTranslation(point);

                matrixGlobal = matrixGlobal.transformMatrix(matrixTranslateInverse);
                matrixGlobal = matrixGlobal.transformMatrix(matrixScale);
                matrixGlobal = matrixGlobal.transformMatrix(matrixTranslate);

                g->transform =  g->transform.transformMatrix(matrixGlobal);
                glutPostRedisplay();
            }
        break;
        //Escala + em um ponto qualquer.
        case 'X':
        case 'x':
            g = universe->GetSelectedObj();
            if (g)
            {
                Point point;
                //Translação para a origem do objeto(cento da BBOX)
                point.x  = - (g->bbox.maxX / 2);
                point.y  = -(g->bbox.maxY / 2);
                matrixTranslate.MakeTranslation(point);

                //Escala aumentando objeto pela metade em relacao a origem
                matrixScale.MakeScale(2.0, 2.0, 1.0);

                //Translação inversa, voltando a posicao original do objeto
                point.x  = (g->bbox.maxX / 2); 
                point.y  = (g->bbox.maxY / 2);
                matrixTranslateInverse.MakeTranslation(point);

                matrixGlobal = matrixGlobal.transformMatrix(matrixTranslateInverse);
                matrixGlobal = matrixGlobal.transformMatrix(matrixScale);
                matrixGlobal = matrixGlobal.transformMatrix(matrixTranslate);

                g->transform =  g->transform.transformMatrix(matrixGlobal);
                glutPostRedisplay();
            }
        break;
        default:
            action = 0;
            cout << key << "\n";
        break;
    }
}

void mouseMove(int x, int y)
{
    if (!isMouseDown) return;

    int px = convertXSpace(x, width);
    int py = convertYSpace(y, height);

    if (isSelectionMode)
    {
        if (universe->HasSelectedPoint())
        {
            PPoint pe = universe->GetSelectedPoint();
            pe->x = px;
            pe->y = py;
        }
    }
    else
    {
        if (currentObj)
        {
            PPoint pe = currentObj->GetLastPoint();
            pe->x = px;
            pe->y = py;
        }
    }

    glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y)
{
    // button GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON
    // state  GLUT_UP or GLUT_DOWN
    isMouseDown = state == GLUT_DOWN;

    // Click com o botão direito deseleciona tudo.
    if (button == GLUT_RIGHT_BUTTON)
    {
        universe->SelectNone();
        currentObj = NULL;
    }
    else if (button == GLUT_LEFT_BUTTON)
    {
        int px = convertXSpace(x, width);
        int py = convertYSpace(y, height);

        if (isSelectionMode)
        {
            if (isMouseDown)
            {
                universe->SelectNone();
                currentObj = NULL;

                bool hasPoint = false;

                // Verifica se selecionou um ponto (vértice).
                for (size_t i = 0; i < universe->ObjCount(); ++i)
                {
                    hasPoint = universe->GetObj(i)->IsPointSelectable(px, py);

                    if (hasPoint)
                    {
                        break;
                    }
                }

                // Não selecionou nenhum ponto, verifica se selecionou um objeto então.
                if (!hasPoint)
                {
                    universe->SelectObj(px, py);
                }
            }
        }
        else
        {
            // Inserção de um ponto.
            if (isMouseDown)
            {
                Point ps;
                ps.x = px;
                ps.y = py;
                ps.z = 0;
                ps.is_selected = false;

                PGraf parent = universe->GetSelectedObj();

                // Não está desenhando nenhum, então é um novo gráfico.
                if (!currentObj)
                {
                    currentObj = new GraphicObject();
                    // O 1o ponto duplica-se, para desenha o rastro.
                    currentObj->AddPoint(ps);

                    if (parent)
                    {
                        parent->AddObj(currentObj);
                    }
                    else
                    {
                        universe->AddObj(currentObj);
                    }
                }
                currentObj->AddPoint(ps);
            }
        }
    }

    glutPostRedisplay();
}

void init(void)
{
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_LIGHTING);

    glClearColor(0.8f, 0.8f, 1.0f, 1.0f);

    universe = new Universe();
}

int main(int argc, const char * argv[])
{
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(300, 250);
    glutInitWindowSize(height, width);

    glutCreateWindow("N3");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);

    init();

    glutMainLoop();

    return 0;
}