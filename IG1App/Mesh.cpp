#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 

    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }
    if (vTexCoords.size() > 0) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}
//-------------------------------------------------------------------------

#pragma region Implementación1.0
//Genera polígonos
Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd) {
    GLdouble angulo = 90;
    Mesh* poligono = new Mesh();
    poligono->mPrimitive = GL_LINE_LOOP;

    poligono->mNumVertices = numL;
    poligono->vVertices.reserve(poligono->mNumVertices);
    for (int i = 0; i < numL; i++) {
        poligono->vVertices.emplace_back(rd * cos(radians(angulo)), rd * sin(radians(angulo)), 0.0);
        angulo += 360 / numL;
    }

    return poligono;
}

//Genera triángulos de Sierpinski
Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP) {
    Mesh* triangulo = generaPoligono(3, rd); //Genera triángulo exterior
    Mesh* sierpinski = new Mesh(); //Mesh para los puntos dentro del triángulo
    sierpinski->mPrimitive = GL_POINTS;//Utilizamos la primitiva de puntos

    sierpinski->mNumVertices = numP;
    sierpinski->vVertices.reserve(sierpinski->mNumVertices);
    for (int i = 0; i < 3; i++) {
        sierpinski->vVertices.emplace_back(triangulo->vVertices.at(i));
    }

    dvec3 ultimoV = sierpinski->vVertices.back(); //El último vértice del vector de sierpinski
    for (int i = 0; i < numP - 3; i++) {
        dvec3 rndPunto = triangulo->vVertices[rand() % 3]; //Punto aleatorio del triángulo auxiliar
        ultimoV = (ultimoV + rndPunto) / 2.0; //Punto medio entre el último punto de sierpinski y el triángulo auxiliar
        sierpinski->vVertices.emplace_back(ultimoV);
    }
    delete triangulo; triangulo = nullptr;

    return sierpinski;
}

Mesh* Mesh::generaTrianguloRGB(GLdouble rd) {
    Mesh* triangulo = generaPoligono(3, rd); //Generamos el triángulo
    triangulo->mPrimitive = GL_TRIANGLES;

    //Añade el vector de colores
    triangulo->vColors.reserve(triangulo->mNumVertices);
    // X axis color: red  (Alpha = 1 : fully opaque)
    triangulo->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    // Y axis color: green
    triangulo->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    // Z axis color: blue
    triangulo->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    return triangulo;
}

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h) {
    Mesh* rectangulo = new Mesh();
    rectangulo->mNumVertices = 4;
    rectangulo->mPrimitive = GL_TRIANGLE_STRIP;
    rectangulo->vVertices.reserve(rectangulo->mNumVertices);
    rectangulo->vVertices.emplace_back(-w, h, 0.0);
    rectangulo->vVertices.emplace_back(-w, -h, 0.0);
    rectangulo->vVertices.emplace_back(w, h, 0.0);
    rectangulo->vVertices.emplace_back(w, -h, 0.0);
    return rectangulo;
}

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h) {
    Mesh* rectangulo = generaRectangulo(w,h);
    rectangulo->mPrimitive = GL_TRIANGLE_STRIP;

    //Añade el vector de colores
    rectangulo->vColors.reserve(rectangulo->mNumVertices);
    // X axis color: red  (Alpha = 1 : fully opaque)
    rectangulo->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    // Y axis color: green
    rectangulo->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    // Z axis color: blue
    rectangulo->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    return rectangulo;
}
#pragma endregion

#pragma region Implementación1.1
Mesh* Mesh::generaEstrella3D(GLdouble re, GLuint np, GLdouble h) {
    GLdouble ri = re / 2; //ri = radio interior; re = radio exterior
    GLdouble angulo = 90;
    
    Mesh* estrella = new Mesh();
    estrella->mPrimitive = GL_TRIANGLE_FAN;
    estrella->mNumVertices = 2 * np + 2;
    
    //Verticas
    estrella->vVertices.reserve(estrella->mNumVertices);
    estrella->vVertices.emplace_back(0.0, 0.0, 0.0);

    //Texturas
    estrella->vTexCoords.reserve(estrella->mNumVertices);
    estrella->vTexCoords.emplace_back(0.5, 0.5);

    for (int i = 0; i < np; i++) {
        estrella->vVertices.emplace_back(re * cos(radians(angulo)), re * sin(radians(angulo)), h); //Puntos del radio exterior
        estrella->vTexCoords.emplace_back(0.5 + 0.5 * cos(radians(angulo)), 0.5 + 0.5*(sin(radians(angulo)))); //Textura en los vértices exteriores
        angulo += 360.0 / (np* 2);

        estrella->vVertices.emplace_back(ri * cos(radians(angulo)), ri * sin(radians(angulo)), h); //Puntos del radio interior
        estrella->vTexCoords.emplace_back(0.5 + 0.25 * cos(radians(angulo)), 0.5 + 0.25 * (sin(radians(angulo)))); //Textura en los vértices exteriores
        angulo += 360.0 / (np * 2) ;
    }
    estrella->vVertices.emplace_back(estrella->vVertices[1]);
    estrella->vTexCoords.emplace_back(estrella->vTexCoords[1]);
    return estrella;
}

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
    Mesh* suelo = generaRectangulo(w, h);
    suelo->vTexCoords.reserve(suelo->mNumVertices);
    suelo->vTexCoords.emplace_back(vec2(0, rh));
    suelo->vTexCoords.emplace_back(vec2(0, 0));
    suelo->vTexCoords.emplace_back(vec2(rw, rh));
    suelo->vTexCoords.emplace_back(vec2(rw, 0));
    return suelo;
}

Mesh* Mesh::generaContCubo(GLdouble ld) {
    Mesh* cubo = new Mesh();

    cubo->mPrimitive = GL_TRIANGLE_STRIP;
    cubo->mNumVertices = 10;

    //Vértices
    cubo->vVertices.reserve(cubo->mNumVertices);
    GLdouble halfLd = ld / 2;


    cubo->vVertices.emplace_back(-halfLd , halfLd , halfLd);//v[0]
    cubo->vVertices.emplace_back(-halfLd, -halfLd, halfLd);//v[1]
    cubo->vVertices.emplace_back(halfLd, halfLd, halfLd);//v[2]
    cubo->vVertices.emplace_back(halfLd, -halfLd, halfLd);//v[3]
    cubo->vVertices.emplace_back(halfLd, halfLd, -halfLd);//v[4]
    cubo->vVertices.emplace_back(halfLd, -halfLd, -halfLd);//v[5]
    cubo->vVertices.emplace_back(-halfLd, halfLd, -halfLd);//v[6]
    cubo->vVertices.emplace_back(-halfLd, -halfLd, -halfLd);//v[7]
    cubo->vVertices.emplace_back(cubo->vVertices[0]);//v[6] cierre con v[0]
    cubo->vVertices.emplace_back(cubo->vVertices[1]);//v[7] cierre con v[1]

    return cubo;
}

Mesh* Mesh::generaCajaTexCor(GLdouble nl) {
    //Textura
    Mesh* cajaTex = generaContCubo(nl);
    cajaTex->vTexCoords.reserve(16);

    int j = 0;
    for (int i = 0; i < 4; i++) {
        cajaTex->vTexCoords.emplace_back(vec2(0, 1));
        cajaTex->vTexCoords.emplace_back(vec2(0, 0));
        cajaTex->vTexCoords.emplace_back(vec2(1, 1));
        cajaTex->vTexCoords.emplace_back(vec2(1, 0));
    }

    return cajaTex;
}

Mesh* Mesh::generaCajaRectangulo(GLdouble w, GLdouble h) {
    Mesh* caja = new Mesh();

    caja->mPrimitive = GL_TRIANGLE_STRIP;
    caja->mNumVertices = 10;

    //Vértices
    caja->vVertices.reserve(caja->mNumVertices);
    GLdouble halfW = w / 2;
    GLdouble halfH = h / 2;

   caja->vVertices.emplace_back(-halfW, halfH, halfW);//v[0]
   caja->vVertices.emplace_back(-halfW, -halfH, halfW);//v[1]
   caja->vVertices.emplace_back(halfW, halfH, halfW);//v[2]
   caja->vVertices.emplace_back(halfW, -halfH, halfW);//v[3]
   caja->vVertices.emplace_back(halfW, halfH, -halfW);//v[4]
   caja->vVertices.emplace_back(halfW, -halfH, -halfW);//v[5]
   caja->vVertices.emplace_back(-halfW, halfH, -halfW);//v[6]
   caja->vVertices.emplace_back(-halfW, -halfH, -halfW);//v[7]
   caja->vVertices.emplace_back(caja->vVertices[0]);//v[6] cierre con v[0]
   caja->vVertices.emplace_back(caja->vVertices[1]);//v[7] cierre con v[1]

   //Texturas
   caja->vTexCoords.reserve(16);

   int j = 0;
   for (int i = 0; i < 4; i++) {
       caja->vTexCoords.emplace_back(vec2(0, 1));
       caja->vTexCoords.emplace_back(vec2(0, 0));
       caja->vTexCoords.emplace_back(vec2(1, 1));
       caja->vTexCoords.emplace_back(vec2(1, 0));
   }

    return caja;
}

Mesh* Mesh::generaFoto(GLdouble w, GLdouble h) {
    Mesh* suelo = generaRectangulo(w, h);
    suelo->vTexCoords.reserve(suelo->mNumVertices);
    suelo->vTexCoords.emplace_back(vec2(0, 1));
    suelo->vTexCoords.emplace_back(vec2(0, 0));
    suelo->vTexCoords.emplace_back(vec2(1, 1));
    suelo->vTexCoords.emplace_back(vec2(1, 0));
    return suelo;
}
#pragma endregion
