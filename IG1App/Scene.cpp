#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

#pragma region includesImplementación
#include "Resources.h"
#pragma endregion


using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settingsu
	gObjects.push_back(new EjesRGB(400.0)); //Ejes RGB
	switch (mId)
	{
	case 0:
		initScene0();
		break;
	case 1:
		initScene1();
		break;
	case 2:
		initScene2();
		break;
	default:
		break;
	}


	// allocate memory and load resources
    // Lights
    // Textures
    // Graphics objects (entities) of the scene


}

void Scene::chargeTextures() {

	for (auto& image : Resources::images_) {
		Texture* currTexture = new Texture();
		currTexture->load(image.fileName);
		gTextures.push_back(currTexture);
	}
}

void Scene::initScene1() {
	glEnable(GL_DEPTH_TEST);
	//Cargamos texturas
	chargeTextures();
	
	//Caja transparente
	gObjects.push_back(new Cristal(600, 350));
	gObjects.back()->setModelMat(translate(dmat4(1), dvec3(0.0, 175.0, 0.0)));
	gTextures[Resources::WindowV]->load(Resources::images_[Resources::WindowV].fileName, 100);
	gObjects.back()->setTexture(gTextures[Resources::WindowV]);

	//Estrella
	gObjects.push_back(new Estrella3D(50, 4, 75));
	gObjects.back()->setTexture(gTextures[Resources::BaldosaP]);

	
	//Suelo
	gObjects.push_back(new Suelo(300, 300, 5, 5));
	gObjects.back()->setTexture(gTextures[Resources::BaldosaC]);
	
	//Caja
	gObjects.push_back(new Caja(50));
	gObjects.back()->setTexture(gTextures[Resources::Container]);
	dynamic_cast<Caja*>(gObjects.back())->setTextureInt(gTextures[Resources::PapelE]);
	gObjects.back()->setModelMat(translate(dmat4(1), dvec3(-50.0, 25.0, -50)));

	//Foto
	Texture* fotoTex = new Texture();
	fotoTex->loadColorBuffer();
	gTextures.push_back(fotoTex);
	gObjects.push_back(new Foto(50, 75));
	gObjects.back()->setTexture(fotoTex);

}

void Scene::initScene0() {
#pragma region Ejercicio1
	gObjects.push_back(new Poligono(3, 300)); //Triángulo
	gObjects.back()->setMColor({ 255.0, 255.0, 0.0, 1.0 }); //Asignamos amarillo al triángulo
	gObjects.push_back(new Poligono(360, 300)); //Circunferencia
	gObjects.back()->setMColor({ 255.0, 0.0, 255.0, 1.0 }); //Asignamos magenta al triángulo
#pragma endregion
#pragma region Ejercicio2
	gObjects.push_back(new Sierpinski(300, 10000));
	gObjects.back()->setMColor(dvec4(1.0, 1.0, 0.0, 1.0)); //Asignamos magenta a Sierpinski
#pragma endregion
#pragma region Ejercicio3
	gObjects.push_back(new TrianguloRGB(60));
#pragma endregion
#pragma region Ejercicio4
	gObjects.push_back(new RectanguloRGB(800, 600));

#pragma endregion
}

void Scene::initScene2() {
	setGL2();
	//Cabeza
	Sphere* head = new Sphere(200, 100, 100); 
	head->setColor(glm::fvec3(1.0, 0.6, 0));	//Naranja
	gObjects.push_back(head);
	//Ojo Derecho
	Cylinder* rightEye = new Cylinder(50, 0, 50, 50, 50);
	rightEye->setColor(glm::fvec3(0, 0, 1));	//Azul
	glm::dmat4 mAux = rightEye->modelMat();
	mAux = translate(mAux, dvec3(170, 70, 50));
	mAux = rotate(mAux, radians(70.0), dvec3(0, 1.0, 0));
	mAux = rotate(mAux, radians(-20.0), dvec3(1.0, 0, 0));
	rightEye->setModelMat(mAux);
	gObjects.push_back(rightEye);
	//Ojo Izquierdo
	Cylinder* leftEye = new Cylinder(50, 0, 50, 50, 50);
	leftEye->setColor(glm::fvec3(0, 0.8, 1));	//Cyan
	mAux = leftEye->modelMat();
	mAux = translate(mAux, dvec3(50, 70, 170));
	mAux = rotate(mAux, radians(20.0), dvec3(0, 1.0, 0));
	mAux = rotate(mAux, radians(-20.0), dvec3(1.0, 0, 0));
	leftEye->setModelMat(mAux);
	gObjects.push_back(leftEye);
	//Aureola
	Disk* halo = new Disk(100, 200, 100, 100);
	halo->setColor(glm::fvec3(1, 0, 0));	//Rojo
	mAux = halo->modelMat();
	mAux = translate(mAux, dvec3(0, 150, 0)); 
	mAux = rotate(mAux, radians(90.0), dvec3(1.0, 0, 0));
	halo->setModelMat(mAux);
	gObjects.push_back(halo);
	//Boca
	PartialDisk* mouth = new PartialDisk(100, 170, 100, 100, 0, 180);
	mouth->setColor(glm::fvec3(0.2, 1, 0));	//Verde
	mAux = mouth->modelMat();
	mAux = translate(mAux, dvec3(100, 10, 100));
	mAux = rotate(mAux, radians(90.0), dvec3(1.0, 0.0, 0));
	mAux = rotate(mAux, radians(45.0), dvec3(0, 0, 1.0));
	mAux = rotate(mAux, radians(-90.0), dvec3(0, 1.0, 0));
	mouth->setModelMat(mAux);
	gObjects.push_back(mouth);
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	gObjects.clear();
	for (int i = 0; i < gTextures.size(); ++i) {
		delete gTextures.at(i);
		gTextures[i] = nullptr;
	}
	gTextures.clear();
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test
	glEnable(GL_TEXTURE_2D);
}

void Scene::setGL2()
{
	// OpenGL basic setting
	glClearColor(0.7, 0.8, 0.9, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test
	glEnable(GL_TEXTURE_2D);
}

//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);  // disable Depth test 	
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	if (mId == 2) {
		sceneDirLight(cam);
	}
	cam.upload();
	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
}
//-------------------------------------------------------------------------

#pragma region Implementación1
void Scene::update() {
	for (Abs_Entity* el : gObjects) {
		el->update();
	}
}

void Scene::setState(int id_) {
	mId = id_;
}
#pragma endregion

#pragma region Implementacion2.1
void Scene::sceneDirLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
}
#pragma endregion