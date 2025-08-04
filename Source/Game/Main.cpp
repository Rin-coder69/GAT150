#include "Math/Math.h"
#include "Math/Vector3.h"
#include "Render/Renderer.h"
#include "core/random.h"
#include "core/Time.h"
#include "Core/File.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Math/Vector2.h"
#include "Framework/Actor.h"
#include "Math/Transform.h"
#include "Render/Model.h"
#include "Framework/Scene.h"
#include "GAMIGN/Player.h"
#include "Engine.h"
#include "GAMIGN/SpaceGame.h"
#include "Render/Font.h"
#include <SDL3/SDL.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <fmod.hpp>
#include <memory>

int main(int argc, char* argv[]) {
	//gaia::file::SetCurrentDirectory("Assets");

	 // Test getInt() variants
	std::cout << "Integer Functions:\n";
	std::cout << "getInt(): " << gaia::random::getInt() << "\n";
	std::cout << "getInt(): " << gaia::random::getInt() << "\n";
	std::cout << "getInt(10): " << gaia::random::getInt(10) << "\n";
	std::cout << "getInt(10): " << gaia::random::getInt(10) << "\n";
	std::cout << "getInt(5, 15): " << gaia::random::getInt(5, 15) << "\n";
	std::cout << "getInt(5, 15): " << gaia::random::getInt(5, 15) << "\n";
	std::cout << "getInt(-10, 10): " << gaia::random::getInt(-10, 10) << "\n\n";

	// Test getReal() variants with float
	std::cout << "Float Functions:\n";
	std::cout << std::fixed << std::setprecision(6);
	std::cout << "getReal<float>(): " << gaia::random::getReal<float>() << "\n";
	std::cout << "getReal<float>(): " << gaia::random::getReal<float>() << "\n";
	std::cout << "getReal<float>(5.0f): " << gaia::random::getReal<float>(5.0f) << "\n";
	std::cout << "getReal<float>(2.5f, 7.5f): " << gaia::random::getReal<float>(2.5f, 7.5f) << "\n";
	std::cout << "getReal<float>(-1.0f, 1.0f): " << gaia::random::getReal<float>(-1.0f, 1.0f) << "\n\n";

	// Test getReal() variants with double
	std::cout << "Double Functions:\n";
	std::cout << std::setprecision(10);
	std::cout << "getReal<double>(): " << gaia::random::getReal<double>() << "\n";
	std::cout << "getReal<double>(100.0): " << gaia::random::getReal<double>(100.0) << "\n";
	std::cout << "getReal<double>(0.0, 2.0): " << gaia::random::getReal<double>(0.0, 2.0) << "\n\n";

	// Test getBool()
	std::cout << "Boolean Functions:\n";
	for (int i = 0; i < 10; ++i) {
		std::cout << "getBool(): " << std::boolalpha << gaia::random::getBool() << "\n";
	}
	std::cout << "\n";

	std::cout << "Gaia Engine - Space Game\n";
	/*
	// Get current directory path
	std::cout << "Directory Operations:\n";
	std::cout << "Current directory: " << gaia::file::GetCurrentDirectory() << "\n";

	// Set current directory path (current path + "Assets")
	std::cout << "Setting directory to 'Assets'...\n";
	gaia::file::SetCurrentDirectory("Assets");
	std::cout << "New directory: " << gaia::file::GetCurrentDirectory() << "\n\n";

	// Get filenames in the current directory
	std::cout << "Files in Directory:\n";
	auto filenames = gaia::file::GetFilesInDirectory(gaia::file::GetCurrentDirectory());
	for (const auto& filename : filenames) {
		std::cout << filename << "\n";
	}
	std::cout << "\n";

	// Get filename (filename.extension) only
	if (!filenames.empty()) {
		std::cout << "Path Analysis:\n";
		std::string filename = gaia::file::GetFilename(filenames[0]);
		std::cout << "Filename only: " << filename << "\n";

		// Get extension only
		std::string ext = gaia::file::GetExtension(filenames[0]);
		std::cout << "Extension: " << ext << "\n\n";
	}

	// Read and display text file
	std::cout << "Text File Reading:\n";
	std::string str;
	bool success = gaia::file::ReadTextFile("test.txt", str);
	if (success) {
		std::cout << "Contents of test.txt:\n";
		std::cout << str << "\n";
	}
	else {
		std::cout << "Failed to read test.txt\n";
	}
	*/
	gaia::file::SetCurrentDirectory("Assets");

	gaia::GetEngine().Initialize();
	/*gaia::Font* font = new gaia::Font();
	font->Load("ArcadeClassic.ttf", 20);*/

	
	//text->Create(gaia::GetEngine().GetRenderer(), "Hello Gaia Engine!", gaia::vec3{ 1.0f, 1.0f, 1.0f });



	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initialize();

	SDL_Event e;
	bool quit = false;

	//create stars
	std::vector<gaia::vec2> stars;
	for (int i = 0; i < 100; i++) {
		stars.push_back(gaia::vec2{ gaia::random::getReal() * 1200, gaia::random::getReal() * 1024 });
	};

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}

		}

		gaia::GetEngine().Update();
		game->Update(gaia::GetEngine().GetTime().GetDeltaTime());
		//scene.update(gaia::GetEngine().GetTime().GetDeltaTime());

		if (gaia::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

		//draw
		float f = 5;
		gaia::vec3 color{ 0,0,0 };

		gaia::GetEngine().GetRenderer().SetColor(color.x, color.y, color.z);
		gaia::GetEngine().GetRenderer().Clear();

		//draw game
		game->Draw(gaia::GetEngine().GetRenderer());

		// stars
		gaia::vec2 speed{ -40.0f,0 };
		float length = speed.length();
		for (auto& star : stars) {
			star += speed * gaia::GetEngine().GetTime().GetDeltaTime();

			if (star[0] > 1280) star[0] = 0;
			if (star[0] < 0) star[0] = 1280;
			gaia::GetEngine().GetRenderer().SetColor(gaia::random::getReal(256.0f), gaia::random::getReal(256.0f), gaia::random::getReal(256.0f));
			gaia::GetEngine().GetRenderer().DrawPoint(star.x, star.y);
		}

		gaia::GetEngine().GetRenderer().Present();
	}

	game->ShutDown();
	game.release();
	gaia::GetEngine().ShutDown();

	return 0;
}

