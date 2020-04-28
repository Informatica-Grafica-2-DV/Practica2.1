#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_access.hpp>

using namespace glm;

//-------------------------------------------------------------------------

Camera::Camera(Viewport* vp): mViewPort(vp), mViewMat(1.0), mProjMat(1.0),  
							  xRight(vp->width() / 2.0), xLeft(-xRight),
							  yTop(vp->height() / 2.0), yBot(-yTop)
{
    setPM();
}
//-------------------------------------------------------------------------

void Camera::setAxes()
{
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2);
}

void Camera::uploadVM() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(mViewMat)); // transfers view matrix to the GPU 
}
//-------------------------------------------------------------------------

void Camera::moveLR(GLdouble cs)
{
	setVM();
	mEye += mRight * cs;
	mLook += mRight * cs;
}

void Camera::moveFB(GLdouble cs)
{
	setVM();
	mEye += mFront * cs;
	mLook += mFront * cs;
}

void Camera::moveUD(GLdouble cs)
{
	setVM();
	mEye += mUpward * cs;
	mLook += mUpward * cs;
}

void Camera::setVM()
{
	mViewMat = lookAt(mEye, mLook, mUp);  // glm::lookAt defines the view matrix 
	setAxes(); //Inicializa los ejes (Izquierda/Derecha, Arriba/Abajo, Delante/Detrás)
}
void Camera::orbit(GLdouble incAng, GLdouble incY) {
	setVM();
	mAng += incAng;
	mEye.z = mLook.x + cos(radians(mAng)) * mRadio;
	mEye.x = mLook.z - sin(radians(mAng)) * mRadio;
	mEye.y -= incY;
}
void Camera::changePrj()
{
	bOrto = !bOrto;
	setPM();
}
void Camera::setCenital()
{
	mLook = dvec3(0, 0, 0);
	mEye = dvec3(0, mRadio, 0);
	mAng = 90;
	mUp = dvec3(0, 0, 1);
	setVM();
}
//-------------------------------------------------------------------------

void Camera::set2D() 
{
	mLook = dvec3(0, 0, 0);
	mEye = dvec3(0, 0, mRadio);
	mAng = 0;
	mUp = dvec3(0, 1, 0);
	setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
	mLook = dvec3(0, 10, 0);   
	mEye = dvec3(mRadio, mRadio, mRadio);
	mAng = 315; //Eje Z y EjeX positivos
	mUp = dvec3(0, 1, 0);
	setVM();
}
//-------------------------------------------------------------------------

//void Camera::pitch(GLdouble a) 
//{  
//	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(1.0, 0, 0));
//	// glm::rotate returns mViewMat * rotationMatrix
//}
////-------------------------------------------------------------------------
//
//void Camera::yaw(GLdouble a) 
//{
//	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 1.0, 0));
//	// glm::rotate returns mViewMat * rotationMatrix
//}
////-------------------------------------------------------------------------
//
//void Camera::roll(GLdouble a) 
//{
//	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 0, 1.0));
//	// glm::rotate returns mViewMat * rotationMatrix
//}
////-------------------------------------------------------------------------

void Camera::setSize(GLdouble xw, GLdouble yh) 
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setScale(GLdouble s)
{
	if (bOrto) { //Solo escala en ortogonal
		setPM();
		mScaleFact -= s;
		if (mScaleFact < 0) mScaleFact = 0.01;
	}
}
//-------------------------------------------------------------------------

void Camera::setPM() 
{
	if (bOrto) { //  if orthogonal projection
		mProjMat = ortho(xLeft*mScaleFact, xRight*mScaleFact, yBot*mScaleFact, yTop*mScaleFact, mNearVal, mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}
	else {
		//Se supone un fovy = 90 grados por lo que Near = yTop
		mProjMat = frustum(xLeft * mScaleFact, xRight * mScaleFact, yBot * mScaleFact, yTop * mScaleFact, yTop, mFarVal);
	}
}
//-------------------------------------------------------------------------

void Camera::uploadPM() const 
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(mProjMat)); // transfers projection matrix to the GPU
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------


