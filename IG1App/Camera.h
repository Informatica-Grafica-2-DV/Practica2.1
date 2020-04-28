//#pragma once
#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Viewport.h"
#include <gtc/matrix_access.hpp> 
//-------------------------------------------------------------------------

class Camera {
public:
	explicit Camera(Viewport* vp);
	~Camera() {};

	// viewPort
	Viewport const& viewPort() const { return *mViewPort; };

	// view matrix 
	glm::dmat4 const& viewMat() const { return mViewMat; };
	
	void set2D();
	void set3D();
	
	//void pitch(GLdouble a); // rotates a degrees on the X axis
	//void yaw(GLdouble a);   // rotates a degrees on the Y axis
	//void roll(GLdouble a);  // rotates a degrees on the Z axis

	// projection matrix
	glm::dmat4 const& projMat() const { return mProjMat; };
	
	// sets scene visible area size 
	void setSize(GLdouble xw, GLdouble yh);
	// updates the scale factor 
	void setScale(GLdouble s);

	// transfers its viewport, the view matrix and projection matrix to the GPU
	void upload() const { mViewPort->upload();  uploadVM(); uploadPM(); }; 

	#pragma region Implementación 1.2
	void moveLR(GLdouble cs);					//Left / Right
	void moveFB(GLdouble cs);					//Forward / Backward
	void moveUD(GLdouble cs);					//Up / Down
	void setVM();								//Inicializa el viewMat
	void orbit(GLdouble incAng, GLdouble incY); //Método para orbitar la cámara
	void changePrj();							//Cambia entre ortogonal y perspectiva
	void setCenital();							//Pone la cámara en vista cenital
	#pragma endregion

protected:
	#pragma region Implementación1.2
	glm::dvec3 mRight;		//Modificadores de la vista en el eje X
	glm::dvec3 mUpward;		//Modificadores de la vista en el eje Y
	glm::dvec3 mFront;		//Modificadores de la vista en el eje Z

	GLdouble mAng = 0;		//Ángulo para orbitar
	GLdouble mRadio = 1000; //Radio de la circunferencia para orbitar
	void setAxes();			//Inicializa mRight, mUpward y mFront
	#pragma endregion

	glm::dvec3 mEye = { 0.0, 0.0, 500.0 };  // camera's position
	glm::dvec3 mLook = { 0.0, 0.0, 0.0 };   // target's position
	glm::dvec3 mUp = { 0.0, 1.0, 0.0 };     // the up vector 

	glm::dmat4 mViewMat;    // view matrix = inverse of modeling matrix 
	void uploadVM() const;  // transfers viewMat to the GPU

	glm::dmat4 mProjMat;     // projection matrix
	void uploadPM() const;   // transfers projMat to the GPU

	GLdouble xRight, xLeft, yTop, yBot;      // size of scene visible area
	GLdouble mNearVal = 1, mFarVal = 10000;  // view volume
	GLdouble mScaleFact = 1;   // scale factor
	bool bOrto = true;   // orthogonal or perspective projection

	Viewport* mViewPort;   // the viewport

	void setPM();
};
//-------------------------------------------------------------------------

#endif //_H_Camera_H_