#pragma once

#include "Entity.h"

class Sierpinski : public Abs_Entity
{
private:
	GLuint numP = 1;
	GLdouble rd = 1;
public:
	Sierpinski(GLdouble rd_, GLuint numP_);
	~Sierpinski();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

