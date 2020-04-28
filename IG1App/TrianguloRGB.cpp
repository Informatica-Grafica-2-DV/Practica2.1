#include "TrianguloRGB.h"

TrianguloRGB::TrianguloRGB(GLdouble rd_) : rd(rd_){
	mMesh = Mesh::generaTrianguloRGB(rd);
}

TrianguloRGB::~TrianguloRGB() {
	delete mMesh; mMesh = nullptr;
}

void TrianguloRGB::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		//Para que no se rellene la parte trasera del triángulo.
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();

		//Reseteamos aributos
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}