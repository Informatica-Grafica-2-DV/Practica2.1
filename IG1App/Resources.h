#pragma once

#include <string>
#include <vector>

using namespace std;

class Resources {
public:
	enum TextureId : int
	{
		//images
		BaldosaC,
		BaldosaF,
		BaldosaP,
		Container,
		Grass,
		PapelC,
		PapelE,
		WindowC,
		WindowV,
		Zelda,

		//no borrar Size
		Size
	};

	struct ImageInfo {
		TextureId id;
		string fileName;
	};

	static vector<ImageInfo> images_; // initialized in .cpp

	static int textureSize() { return Size; }
};