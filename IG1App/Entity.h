//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity(): mModelMat(1.0), mColor(1) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };
	
#pragma region Implementación Enunciado
	void setMColor(dvec4 newColor) { mColor = newColor; }; //Aplica color a la malla
	virtual void update() = 0;

#pragma endregion 1.0

#pragma region Implementación Enunciado 1.1
	void setTexture(Texture* tex) { mTexture = tex; };
#pragma endregion

protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 

#pragma region Implementación Enunciado
	dvec4 mColor;
	glm::dmat4 transform;
	Texture* mTexture = nullptr;
#pragma endregion
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
};

#pragma region Implementación 1.0
class Poligono : public Abs_Entity
{
private:
	GLuint numL = 1;
	GLdouble rd = 1;
public:
	explicit Poligono(GLuint numL_, GLdouble rd_);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
};

class Sierpinski : public Abs_Entity
{
private:
	GLuint numP = 1;
	GLdouble rd = 1;
public:
	Sierpinski(GLdouble rd_, GLuint numP_);
	~Sierpinski();
	virtual void render(glm::dmat4 const& modelViewMat) const;	
	virtual void update() {};

};

class TrianguloRGB : public Abs_Entity
{
private:
	GLdouble rd = 1;
	//Parametros para el movimiento
	dvec3 posOriginal{ (0.0, 0.0, 0.0) };
	dvec3 posCfc{ (0.0,0.0,0.0) };
	GLdouble angulo = 1.0f;
	
public:
	TrianguloRGB(GLdouble rd_);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};

class RectanguloRGB : public Abs_Entity {
private:
	GLdouble width = 0;
	GLdouble height = 0;
public:
	RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
};
#pragma endregion

#pragma region Implementación1.1
#pragma region Estrella3D
class Estrella3D : public Abs_Entity
{
private:
	GLdouble re_;
	GLuint np_;
	GLdouble h_;
	GLdouble angulo = 1.0f;

public:
	Estrella3D(GLdouble re, GLuint np, GLdouble h);
	~Estrella3D();

	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};
#pragma endregion
#pragma region Suelo
class Suelo :public Abs_Entity {
private:
	GLdouble w_, h_, rw_, rh_;
public:
	Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
};
#pragma endregion
#pragma region Caja
class Caja : public Abs_Entity {
private:
	Texture* mTextureInt = nullptr;

public:
	Caja() {};
	Caja(GLdouble ld);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};

	void setTextureInt(Texture* tex) { mTextureInt = tex; };
};
#pragma endregion

#pragma region Foto
class Foto : public Abs_Entity {
private:
	GLdouble w_, h_;
public:
	Foto(GLdouble w, GLdouble h);
	~Foto();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
};
#pragma endregion
class Cristal : public Abs_Entity {
private:
	GLdouble w_ = 0;
	GLdouble h_ = 0;

public:
	Cristal(GLdouble w, GLdouble h);
	~Cristal();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {}
};
#pragma endregion

#pragma region Implementacion2.1
class QuadricEntity : public Abs_Entity {
public:
	~QuadricEntity() { gluDeleteQuadric(q); };
	virtual void render(glm::dmat4 const& modelViewMat) const = 0;
	virtual void update() = 0;
	virtual void setColor(glm::fvec3 newColor) { color = newColor; }
protected:
	QuadricEntity() { q = gluNewQuadric(); };
	glm::fvec3 color = glm::fvec3(-1, -1, -1);	//Permite dibujar con un color determinado
	GLUquadricObj* q = nullptr;
};

class Sphere : public QuadricEntity {
public:
	Sphere(GLdouble radius, GLint slices, GLint stacks) : 
		QuadricEntity(), radius_(radius), slices_(slices), stacks_(stacks){};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();

private:
	GLdouble radius_ = 0;
	GLint slices_ = 0;
	GLint stacks_ = 0;
};

class Cylinder : public QuadricEntity {
public:
	Cylinder(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks) :
		QuadricEntity(), baseRadius(baseRadius), topRadius(topRadius), height(height), slices(slices), stacks(stacks){};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
private:
	GLdouble baseRadius = 0;
	GLdouble topRadius = 0;
	GLdouble height = 0;
	GLint slices = 0;
	GLint stacks = 0;
};

class Disk : public QuadricEntity {
public:
	Disk(GLdouble inneRadius, GLdouble outerRadius, GLint slices, GLint loops) :
		QuadricEntity(), inneRadius(inneRadius), outerRadius(outerRadius), slices(slices), loops(loops) {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
private:
	GLdouble inneRadius = 0;
	GLdouble outerRadius = 0;
	GLint slices = 0;
	GLint loops = 0;
}; 

class PartialDisk : public QuadricEntity {
public:
	PartialDisk(GLdouble inneRadius, GLdouble outerRadius, GLint slices, GLint loops, GLdouble startAngle, GLdouble sweepAngle) :
		QuadricEntity(), inneRadius(inneRadius), outerRadius(outerRadius), slices(slices), loops(loops), startAngle(startAngle), sweepAngle(sweepAngle) {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update();
private:
	GLdouble inneRadius = 0;
	GLdouble outerRadius = 0;
	GLint slices = 0; 
	GLint loops = 0;
	GLdouble startAngle = 0;
	GLdouble sweepAngle = 0;
};
#pragma endregion
#endif //_H_Entities_H_