//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include <vector>
using namespace glm;

//-------------------------------------------------------------------------

class Mesh 
{
public:

	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh
	
	Mesh() {};
	virtual ~Mesh() {};

	Mesh(const Mesh & m) = delete;  // no copy constructor
	Mesh & operator=(const Mesh & m) = delete;  // no copy assignment
			
	virtual void render() const;
	
	GLuint size() const { return mNumVertices; };   // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };

		
#pragma region Implementación1.0
	static Mesh* generaPoligono(GLuint numL, GLdouble rd);
	static Mesh* generaSierpinski(GLdouble rd, GLuint numP);
	static Mesh* generaTrianguloRGB(GLdouble rd);
	static Mesh* generaRectangulo(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h);
#pragma endregion

#pragma region Implementación1.1
	static Mesh* generaEstrella3D(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	static Mesh* generaContCubo(GLdouble ld);
	static Mesh* generaCajaTexCor(GLdouble nl);
	static Mesh* generaCajaRectangulo(GLdouble w, GLdouble h);
	static Mesh* generaFoto(GLdouble w, GLdouble h);
#pragma endregion

protected:
#pragma region Implementación1.1
	std::vector<glm::dvec2> vTexCoords;  // vertex array

#pragma endregion


	GLuint mPrimitive = GL_TRIANGLES;   // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0;  // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices;  // vertex array
	std::vector<glm::dvec4> vColors;    // color array

	virtual void draw() const;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_