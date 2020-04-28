#include "Sierpinski.h"
#include <gtc/matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

Sierpinski::Sierpinski(GLdouble rd_, GLuint numP_) : numP(numP_), rd(rd_) {
	mMesh = Mesh::generaSierpinski(rd,numP);
}

Sierpinski::~Sierpinski() { 
	delete mMesh; mMesh = nullptr; 
}

void Sierpinski::render(glm::dmat4 const& modelViewMat) const {
	
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		glPointSize(2);
		mMesh->render();
		//Reseteamos aributos
		glPointSize(1);
		glColor4dv(value_ptr(glm::dvec4(1.0, 1.0, 1.0, 1.0)));
	}
}