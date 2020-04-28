#pragma once

#include "Entity.h"

class TrianguloRGB : public Abs_Entity
{
private:
	GLdouble rd = 1;
public:
	TrianguloRGB(GLdouble rd_);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

