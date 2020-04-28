#pragma once

#include "Entity.h"

class Poligono : public Abs_Entity
{
private:
	GLuint numL = 1;
	GLdouble rd = 1;
public:
	Poligono(GLuint numL_, GLdouble rd_);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

