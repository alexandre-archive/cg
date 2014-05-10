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

bool selectionMode = false,
     isSelectFromSelectionMode = false;

PUniverse universe;

bool isMouseDown = false;

void resize(int width, int height)
{

}

void drawMode()
{
    DrawText(ortho2D_minX + 4, ortho2D_minY + 4, (char*)(selectionMode ? "Selecao (Tab)" : "Edicao (Tab)"));
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
    int action = 0;

    switch (key)
    {
        case KEY_ESC:
            exit(0);
        break;
        case KEY_TAB:
            selectionMode = !selectionMode;
            glutPostRedisplay();
        break;
        case KEY_DEL:
            // Deleta o ponto ou poligono se for seleção.
            // Limpa a tela se for edição.
            /*if (selectionMode)
            {
                if (currentObj && currentVertexIndex != -1)
                {
                    currentObj->Points.erase(currentObj->Points.begin() + currentVertexIndex);
                    currentObj->SetSelectedVertex(-1);

                    int size = currentObj->Points.size();

                    if (size <= 1)
                    {
                        universe->Objects.erase(universe->Objects.begin() + currentObjIndex);
                    }

                    Reset();
                }
                else if (currentObj)
                {
                    universe->Objects.erase(universe->Objects.begin() + currentObjIndex);

                    Reset();
                }
            }
            else
            {
                Reset();
                universe->Objects.clear();
            }*/
            glutPostRedisplay();
        break;
        case KEY_SPACE:
            g = universe->GetSelectedObj();
            if (g)
            {
                g->ChangePrimitive();
                glutPostRedisplay();
            }
        break;
        case 'P':
        case 'p':
            // Seleciona um poligono.
            if (selectionMode && universe->ObjCount() > 0)
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
                        g->ChangeRColor();
                    break;
                    case CHANGE_COLOR_G:
                        g->ChangeGColor();
                    break;
                    case CHANGE_COLOR_B:
                        g->ChangeBColor();
                    break;
                    case CHANGE_LINE_WIDTH:
                        if (g->LineWidth < 6.0f)
                        {
                            g->LineWidth += 1.0f;
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
                        g->ChangeRColor();
                    break;
                    case CHANGE_COLOR_G:
                        g->ChangeGColor();
                    break;
                    case CHANGE_COLOR_B:
                        g->ChangeBColor();
                    break;
                    case CHANGE_LINE_WIDTH:
                        if (g->LineWidth > 1.0f)
                        {
                            g->LineWidth -= 1.0f;
                        }
                    break;
                }

                glutPostRedisplay();
            }
        break;
        default:
            cout << key << "\n";
        break;
    }
}

void mouseMove(int x, int y)
{
    if (!isMouseDown || !universe->HasSelectedObj()) return;

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
    int px = convertXSpace(x, width);
    int py = convertYSpace(y, height);

    if (selectionMode)
    {
        if (state == GLUT_DOWN)
        {
            isMouseDown = true;

            PGraf g = universe->GetSelectedObj();
/*
            if (!(g && g->HasSelectedVertex()/* && g->GetSelectedVertex() == g->GetSelectedVertex(px, py)* /))
            {
                universe->SelectNone();

                for (size_t i = 0; i < universe->Objects.size(); ++i)
                {
                    int point = universe->Objects[i]->GetSelectedVertexIndex(px, py);

                    if (point != -1)
                    {
                        universe->SetSelectedObj(i);
                        universe->Objects[i]->SetSelectedVertex(point);
                    }
                    else
                    {
                        // TODO: Aplicar funçaõ map para desabilitar todos os selecionados.
                        universe->Objects[i]->SetSelectedVertex(-1);
                    }
                }
            }
*/
            if (g && !g->HasSelectedVertex())
            {
                for (size_t i = 0; i < universe->Objects.size(); ++i)
                {
                    auto g = universe->Objects[i];

                    if (g->IsMouseInside(px, py))
                    {
                        g->SetSelected(true);
                        universe->SetSelectedObj(i);
                    }
                    else
                    {
                        // TODO: Aplicar funçaõ map para desabilitar todos os selecionados.
                        g->SetSelected(false);
                    }
                }
            }
        }
        else
        {
            isMouseDown = false;
        }
    }
    else
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            if (state == GLUT_DOWN)
            {
                isMouseDown = true;

                Point ps;
                ps.x = px;
                ps.y = py;

                if (isSelectFromSelectionMode)
                {
                    
                }
                else
                {
                    // É um novo
                    if (!universe->HasSelectedObj())
                    {
                        universe->Objects.push_back(new GraphicObject());
                        universe->SetSelectedObj(universe->Objects.size() - 1);
                        // O 1o ponto duplica-se, para desenha o rastro.
                        universe->GetSelectedObj()->Points.push_back(ps);
                    }

                    universe->GetSelectedObj()->Points.push_back(ps);
                    universe->GetSelectedObj()->CalculateBBox();
                }
            }
            else if (state == GLUT_UP)
            {
                isMouseDown = false;

                if (isSelectFromSelectionMode)
                {
                   
                }
                else
                {
                    if (universe->HasSelectedObj())
                    {
                        Point& pe = universe->GetSelectedObj()->Points.back();

                        pe.x = px;
                        pe.y = py;

                        universe->GetSelectedObj()->CalculateBBox();
                    }
                }
            }
        }
        else
        {
            universe->SetSelectedObj(-1);
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