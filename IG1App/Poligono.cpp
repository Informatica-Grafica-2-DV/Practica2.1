#include "Poligono.h"

Poligono::Poligono(GLuint numL_, GLdouble rd_) : numL(numL_), rd(rd_){
	mMesh = Mesh::generaPoligono(numL, rd);
}

Poligono::~Poligono() {
	delete mMesh; mMesh = nullptr;
}
void Poligono::render(glm::dmat4 const& modelViewMat) const{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		mMesh->render();

		//Reseteamos aributos
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}