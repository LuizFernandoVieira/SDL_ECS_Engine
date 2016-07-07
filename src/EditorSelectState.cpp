#include "../include/EditorSelectState.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Resources.hpp"
#include "../include/Game.hpp"
#include "../include/LevelEditorState.hpp"
#include "../include/TileMap.hpp"
#include "../include/CollisionMap.hpp"

#include <sstream>


EditorSelectState::EditorSelectState() :
	bg_("../img/bgEditor.png"),
	mode(INIT),
	btnNewMap("../img/interface/editor/btn.png"),
	btnNewMapPos(300, 250, 200, 100),
	btnNewMapText("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Novo mapa", Colors::purple),
	btnEditMap("../img/interface/editor/btn.png"),
	btnEditMapPos(600, 250, 200, 100),
	btnEditMapText("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Editar mapa", Colors::purple),
	btnAccept("../img/interface/editor/btn.png"),
	btnAcceptPos(900, 500, 100, 60),
	btnAcceptText("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Proximo", Colors::purple),
	btnReturn("../img/interface/editor/btn.png"),
	btnReturnPos(750, 500, 100, 60),
	btnReturnText("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Voltar", Colors::purple),
	textLabels(),
	textAreas(),
	selectedTextArea(0)
{
	btnNewMapText.setPos(400, 300);
	btnEditMapText.setPos(700, 300);

	btnAcceptText.setPos(950, 515);
	btnReturnText.setPos(800, 515);

	btnNewMap.setScaleX(200 / btnNewMap.getWidth());
	btnNewMap.setScaleY(100 / btnNewMap.getHeight());
	btnEditMap.setScaleX(200 / btnEditMap.getWidth());
	btnEditMap.setScaleY(100 / btnEditMap.getHeight());

	btnAccept.setScaleX(100 / btnAccept.getWidth());
	btnAccept.setScaleY(60 / btnAccept.getHeight());
	btnReturn.setScaleX(100 / btnReturn.getWidth());
	btnReturn.setScaleY(60 / btnReturn.getHeight());
}

EditorSelectState::~EditorSelectState()
{
	textLabels.clear();
	textAreas.clear();
}


void EditorSelectState::update(float dt)
{
	InputHandler& input = InputHandler::getInstance();
	input.update();

	if (mode == INIT)
	{
		if (input.mousePress(LEFT_MOUSE_BUTTON))
		{
			if (btnNewMapPos.isInside(input.getMouse()))
			{
				mode = NEW_MAP;
				selectedTextArea = 0;
				textAreas.clear();
				textLabels.clear();

				textLabels.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Nome:", Colors::white));
				textLabels[0]->setPos(200, 150, false, false);
				textAreas.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Fase", Colors::gray));
				textAreas[0]->setPos(400, 150, false, false);

				textLabels.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Imagem tile set:", Colors::white));
				textLabels[1]->setPos(200, 250, false, false);
				textAreas.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "../img/maps/test/tile_set.png", Colors::white));
				textAreas[1]->setPos(400, 250, false, false);

				textLabels.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Largura:", Colors::white));
				textLabels[2]->setPos(200, 350, false, false);
				textAreas.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "50", Colors::white));
				textAreas[2]->setPos(400, 350, false, false);

				textLabels.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Altura:", Colors::white));
				textLabels[3]->setPos(200, 450, false, false);
				textAreas.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "30", Colors::white));
				textAreas[3]->setPos(400, 450, false, false);
			}
			else if (btnEditMapPos.isInside(input.getMouse()))
			{
				mode = EDIT_MAP;
				selectedTextArea = 0;
				textAreas.clear();
				textLabels.clear();

				textLabels.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Imagem tile set:", Colors::white));
				textLabels[0]->setPos(200, 150, false, false);
				textAreas.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "../img/maps/tilesetcidade1.png", Colors::gray));
				textAreas[0]->setPos(400, 150, false, false);

				textLabels.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Tile map:", Colors::white));
				textLabels[1]->setPos(200, 250, false, false);
				textAreas.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "../map/FaseUm_tilemap.txt", Colors::white));
				textAreas[1]->setPos(400, 250, false, false);

				textLabels.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Collision map:", Colors::white));
				textLabels[2]->setPos(200, 350, false, false);
				textAreas.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "../map/FaseUm_colmap.txt", Colors::white));
				textAreas[2]->setPos(400, 350, false, false);

				textLabels.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Object map:", Colors::white));
				textLabels[3]->setPos(200, 450, false, false);
				textAreas.emplace_back(new Text("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "../map/FaseUm.xml", Colors::white));
				textAreas[3]->setPos(400, 450, false, false);

			}
			else if (btnReturnPos.isInside(input.getMouse()))
			{
				pop_ = true;
			}
		}
	}
	else
	{
		if (input.mousePress(LEFT_MOUSE_BUTTON))
		{
			if (btnAcceptPos.isInside(input.getMouse()))
			{
				accept();
			}
			else if (btnReturnPos.isInside(input.getMouse()))
			{
				mode = INIT;
			}
			else
			{
				for (int i = 0; i < (int)textAreas.size(); i++)
				{
					if (textAreas[i]->getPos().isInside(input.getMouse()))
					{
						textAreas[selectedTextArea]->setColor(Colors::white);
						textAreas[i]->setColor(Colors::gray);
						selectedTextArea = i;
						break;
					}
				}
			}
		}

		if (input.textInput())
			textAreas[selectedTextArea]->setText( textAreas[selectedTextArea]->getText() + input.getText() );
		if (input.keyPress(BACKSPACE))
		{
			std::string newText = textAreas[selectedTextArea]->getText();
			newText.pop_back();
			textAreas[selectedTextArea]->setText( newText );
		}

	}

	if (input.quitRequested()) {
		quit_ = true;
	}
}


void EditorSelectState::render()
{
	bg_.render(0,0);

	if (mode == INIT)
	{
		// NEW MAP BTN
		btnNewMap.render(btnNewMapPos.x(), btnNewMapPos.y());
		btnNewMapText.render();

		// EDIT MAP BTN
		btnEditMap.render(btnEditMapPos.x(), btnEditMapPos.y());
		btnEditMapText.render();
	}
	else
	{
		for (int i = 0; i < (int)textLabels.size(); i++)
		{
			textLabels[i]->render();
			textAreas[i]->render();
		}

		btnAccept.render(btnAcceptPos.x(), btnAcceptPos.y());
		btnAcceptText.render();
	}

	btnReturn.render(btnReturnPos.x(), btnReturnPos.y());
	btnReturnText.render();
}


void EditorSelectState::accept()
{
	if (mode == NEW_MAP)
	{
		Resources::TILE_SET_IMG = textAreas[1]->getText();
		Resources::TILE_MAP_TXT = "../map/" + textAreas[0]->getText() + "_tilemap.txt";
		Resources::COLLISION_MAP_TXT = "../map/" + textAreas[0]->getText() + "_colmap.txt";
		Resources::OBJECT_MAP_XML = "../map/" + textAreas[0]->getText() + "_objmap.xml";

		// criar novos mapas
		int tempW, tempH;
		std::istringstream(textAreas[2]->getText()) >> tempW;
		std::istringstream(textAreas[3]->getText()) >> tempH;
		TileMap tileMap(Resources::TILE_MAP_TXT.c_str(), tempW, tempH);
		CollisionMap collisionMap(Resources::COLLISION_MAP_TXT.c_str(), tempW, tempH);

		pop_ = true;
		Game::getInstance().push(new LevelEditorState());
	}
	else if (mode == EDIT_MAP)
	{
		Resources::TILE_SET_IMG = textAreas[0]->getText();
		Resources::TILE_MAP_TXT = textAreas[1]->getText();
		Resources::COLLISION_MAP_TXT = textAreas[2]->getText();
		Resources::OBJECT_MAP_XML = textAreas[3]->getText();

		pop_ = true;
		Game::getInstance().push(new LevelEditorState());
	}
}



void EditorSelectState::pause()
{

}

void EditorSelectState::resume()
{

}
