#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "glm/gtx/component_wise.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace glm;

struct Vertex
{
    vec3 posicao; //v
    vec2 textura; //vt
    vec3 normal; //vn
};

struct VertRef //f
{
    VertRef(int v, int vt, int vn)
        : v(v), vt(vt), vn(vn)
    { }
    int v, vt, vn;
};

vector< Vertex > LoadOBJ(istream& in)
{
    vector< Vertex > verts;

    vector< vec4 > posicoes(1, vec4(0, 0, 0, 0)); //x, y, z, w (posicao normalizada)
    vector< vec3 > texturas(1, vec3(0, 0, 0));
    vector< vec3 > normais(1, vec3(0, 0, 0));
    string lineStr;
    while (getline(in, lineStr))
    {
        istringstream lineSS(lineStr);
        string lineType;
        lineSS >> lineType;

        // vertice - posicao
        if (lineType == "v")
        {
            float x = 0, y = 0, z = 0, w = 1;
            lineSS >> x >> y >> z >> w;
            posicoes.push_back(vec4(x, y, z, w));
        }

        // textura - coordenada da textura png
        if (lineType == "vt")
        {
            float u = 0, v = 0, w = 0;
            lineSS >> u >> v >> w;
            texturas.push_back(vec3(u, v, w));
        }

        // normal - mapa de normais
        if (lineType == "vn")
        {
            float i = 0, j = 0, k = 0;
            lineSS >> i >> j >> k;
            normais.push_back(normalize(vec3(i, j, k)));
        }

        // faces - poligonos
        if (lineType == "f")
        {
            vector< VertRef > refs;
            string refStr;
            while (lineSS >> refStr)
            {
                istringstream ref(refStr);
                string vStr, vtStr, vnStr;
                getline(ref, vStr, '/');
                getline(ref, vtStr, '/');
                getline(ref, vnStr, '/');
                int v = atoi(vStr.c_str());
                int vt = atoi(vtStr.c_str());
                int vn = atoi(vnStr.c_str());
                v = (v >= 0 ? v : posicoes.size() + v);
                vt = (vt >= 0 ? vt : texturas.size() + vt);
                vn = (vn >= 0 ? vn : normais.size() + vn);
                refs.push_back(VertRef(v, vt, vn));
            }

            if (refs.size() < 3)
            {
                // ignorar linhas abreviadas
                continue;
            }

            // calculo da normal
            // assume que é convexo e coplanar
            VertRef* p[3] = { &refs[0], NULL, NULL };
            for (size_t i = 1; i + 1 < refs.size(); ++i)
            {
                p[1] = &refs[i + 0];
                p[2] = &refs[i + 1];

                // referência http://www.opengl.org/wiki/Calculating_a_Surface_Normal
                vec3 U(posicoes[p[1]->v] - posicoes[p[0]->v]);
                vec3 V(posicoes[p[2]->v] - posicoes[p[0]->v]);
                vec3 faceNormal = normalize(cross(U, V));

                for (size_t j = 0; j < 3; ++j)
                {
                    Vertex vert;
                    vert.posicao = vec3(posicoes[p[j]->v]);
                    vert.textura = vec2(texturas[p[j]->vt]);
                    vert.normal = (p[j]->vn != 0 ? normais[p[j]->vn] : faceNormal);
                    verts.push_back(vert);
                }
            }
        }
    }

    return verts;
}

// Entrada do teclado
bool luz = true;

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: //Esc
        exit(0);
        break;
    };
}

void keyboardOnRelease(unsigned char key, int x, int y) {
    switch (key) {
    case 108: //letra l
        luz = luz ? false : true;
        break;
    };
}

// Movimento do Mouse
int btn;
ivec2 startMouse;
ivec2 startRot, curRot;
ivec2 startTrans, curTrans;
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        btn = button;
        startMouse = ivec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
        startRot = curRot;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        btn = button;
        startMouse = ivec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
        startTrans = curTrans;
    }
}

void motion(int x, int y)
{
    ivec2 curMouse(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
    if (btn == GLUT_LEFT_BUTTON)
    {
        curRot = startRot + (curMouse - startMouse);
    }
    else if (btn == GLUT_RIGHT_BUTTON)
    {
        curTrans = startTrans + (curMouse - startMouse);
    }
    glutPostRedisplay();
}

// Renderizar
vector< Vertex > modelo;
void display()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double w = glutGet(GLUT_WINDOW_WIDTH);
    double h = glutGet(GLUT_WINDOW_HEIGHT);
    double ar = w / h;
    glTranslatef(curTrans.x / w * 2, curTrans.y / h * 2, 0);
    gluPerspective(60, ar, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -10);

    glPushMatrix();
    {
        // Mouse
        glRotatef(curRot.x % 360, 0, 1, 0);
        glRotatef(-curRot.y % 360, 1, 0, 0);
        
        // Teclado


        // Modelo - .obj
        glColor3ub(255, 0, 0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &modelo[0].posicao);
        glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &modelo[0].textura);
        glNormalPointer(GL_FLOAT, sizeof(Vertex), &modelo[0].normal);
        glDrawArrays(GL_TRIANGLES, 0, modelo.size());
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);

        // Iluminação
        if (luz) {
            glEnable(GL_LIGHTING);
        }
        else {
            glDisable(GL_LIGHTING);
        }
        
    }
    glPopMatrix();

    glutSwapBuffers();
}

// Retorna os pontos minimos e máximos
template< typename Vec >
pair< Vec, Vec > GetPontas(const Vec* pts, size_t stride, size_t count)
{
    unsigned char* base = (unsigned char*)pts;
    Vec pmin(*(Vec*)base);
    Vec pmax(*(Vec*)base);
    for (size_t i = 0; i < count; ++i, base += stride)
    {
        const Vec& pt = *(Vec*)base;
        pmin = glm::min(pmin, pt);
        pmax = glm::max(pmax, pt);
    }

    return make_pair(pmin, pmax);
}

// Centraliza geometria no ponto de origem
template< typename Vec >
void Centralizar(Vec* pts, size_t stride, size_t count, const typename Vec::value_type& size)
{
    typedef typename Vec::value_type Scalar;

    // obter extremidades máximas e minimas
    pair< Vec, Vec > exts = GetPontas(pts, stride, count);

    // centralizar e colocar em escala
    const Vec center = (exts.first * Scalar(0.5)) + (exts.second * Scalar(0.5f));

    const Scalar factor = size / glm::compMax(exts.second - exts.first);
    unsigned char* base = (unsigned char*)pts;
    for (size_t i = 0; i < count; ++i, base += stride)
    {
        Vec& pt = *(Vec*)base;
        pt = ((pt - center) * factor);
    }
}

int main(int argc, char** argv)
{
    // Ler arquivo
    ifstream ifile("data/radar.obj");
    modelo = LoadOBJ(ifile);
    Centralizar(&modelo[0].posicao, sizeof(Vertex), modelo.size(), 7);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Janela");
    glutDisplayFunc(display);
    //Entrada - Mouse
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    //Entrada - Teclado
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardOnRelease);

    glEnable(GL_DEPTH_TEST);

    // Configurações de iluminação
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat posicao[] = { 0, 0, 1, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, posicao);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glutMainLoop();
    return 0;
}