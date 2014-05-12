#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif

#include "graphicobject.cpp"
#include "universe.cpp"

#define KEY_TAB 9
#define KEY_ESC 27
#define KEY_DEL 127
#define KEY_SPACE 32
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
     isSelectFromSelectionMode = false;

PUniverse universe;

bool isMouseDown = false;
int action = 0;

void resize(int width, int height)
{

}

void drawMode()
{
    DrawText(ortho2D_minX + 4, ortho2D_minY + 4, (char*)(isSelectionMode ? "Selecao (Tab)" : "Edicao (Tab)"));
}

void display()
{
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
                    if (g->HasSelectedVertex())
                    {
                        g->DeleteSelectedVertex();

                        int size = g->Points.size();

                        if (size <= 1)
                        {
                            universe->DeleteSelectedObject();
                        }
                    }
                    else
                    {
                        universe->DeleteSelectedObject();
                    }
                }
            }
            else
            {
                universe->SelectNone();
                universe->Objects.clear();
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
        case 'P':
        case 'p':
            action = 0;
            // Seleciona um poligono.
            if (isSelectionMode && universe->ObjCount() > 0)
            {
                universe->SelectNextObj();
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
        default:
            action = 0;
            cout << key << "\n";
        break;
    }
}

void mouseMove(int x, int y)
{
    if (!isMouseDown || !universe->HasSelectedObj() || universe->GetSelectedObj()->IsSelected()) return;

    int px = convertXSpace(x, width);
    int py = convertYSpace(y, height);

    PGraf g = universe->GetSelectedObj();

    if (g->HasSelectedVertex())
    {
        Point& pe = g->GetSelectedVertex();
        pe.x = px;
        pe.y = py;
    }
    else
    {
        Point& pe = g->Points.back();
        pe.x = px;
        pe.y = py;
    }

    g->CalculateBBox();

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
        //universe->SetSelectedObj(-1);
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

                // Verifica se selecionou um ponto (vértice).
                for (size_t i = 0; i < universe->ObjCount(); ++i)
                {
                    PGraf g = universe->Objects[i];

                    int point = g->GetSelectedVertexIndex(px, py);

                    if (point != -1)
                    {
                        universe->SetSelectedObj(i);
                        g->SetSelectedVertex(point);
                    }
                    else
                    {
                        g->SetSelectedVertex(-1);
                    }
                }

                // Não selecionou nenhum ponto, verifica se selecionou um objeto então.
                if (!universe->HasSelectedObj())
                {
                    // Verifica se está dentro de um poligono. (Selecionou um com o mouse).
                    for (size_t i = 0; i < universe->ObjCount(); ++i)
                    {
                        PGraf g = universe->Objects[i];

                        if (g->IsMouseInside(px, py))
                        {
                            g->SetSelected(true);
                            universe->SetSelectedObj(i);
                        }
                        else
                        {
                            g->SetSelected(false);
                        }
                    }
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

                PGraf g = universe->GetSelectedObj();

                // Não está desenhando nenhum, então é um novo gráfico.
                if (!g)
                {
                    g = new GraphicObject();
                    universe->Objects.push_back(g);
                    universe->SetSelectedObj(universe->ObjCount() - 1);
                    // O 1o ponto duplica-se, para desenha o rastro.
                    g->Points.push_back(ps);
                }

                g->Points.push_back(ps);
                g->CalculateBBox();

            }
            // Término de inserção de um ponto, caso tenha algum poligono.
            else if (universe->HasSelectedObj())
            {
                PGraf g = universe->GetSelectedObj();
                Point& pe = g->Points.back();

                pe.x = px;
                pe.y = py;

                g->CalculateBBox();
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