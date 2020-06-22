#include "NumberRenderer.h"
#include "Game.h"

NumberRenderer* NumberRenderer::s_Instance;

void NumberRenderer::init()
{
	g_AssetManager->loadTexture("Resources/Textures/numbers.png");

	m_0Rect = { 26, 0, 203, 256 };
	m_1Rect = { (256) + 69, 0, 117, 256 };
	m_2Rect = { (256 * 2) + 39, 0, 177, 256 };
	m_3Rect = { (256 * 3) + 39, 0, 177, 256 };
	m_4Rect = { (256 * 4) + 24, 0, 207, 256 };
	m_5Rect = { (256 * 5) + 38, 0, 178, 256 };
	m_6Rect = { (256 * 6) + 32, 0, 191, 256 };
	m_7Rect = { (256 * 7) + 35, 0, 186, 256 };
	m_8Rect = { (256 * 8) + 29, 0, 198, 256 };
	m_9Rect = { (256 * 9) + 32, 0, 191, 256 };
}

void NumberRenderer::render(int num, float destX, float destY, float scale, SDL_Color color)
{
	std::string number = std::to_string(num);
	int numDigits = 0;
	int lastNumWidth = 0;

	SDL_SetTextureColorMod(g_AssetManager->getTexture("Resources/Textures/numbers.png"), color.r, color.g, color.b);

	for (const auto& digit : number)
	{
		switch (digit)
		{

		case '0':
			g_AssetManager->render("Resources/Textures/numbers.png", destX + lastNumWidth, destY, (int) (m_0Rect.w * scale), (int) (m_0Rect.h * scale), m_0Rect.x, m_0Rect.y, m_0Rect.w, m_0Rect.h);
			lastNumWidth += (int) (m_0Rect.w * scale);
			break;

		case '1':
			g_AssetManager->render("Resources/Textures/numbers.png", destX + lastNumWidth, destY, (int) (m_1Rect.w * scale), (int) (m_1Rect.h * scale), m_1Rect.x, m_1Rect.y, m_1Rect.w, m_1Rect.h);
			numDigits++;
			lastNumWidth += (int) (m_1Rect.w * scale);
			break;

		case '2':
			g_AssetManager->render("Resources/Textures/numbers.png", destX + lastNumWidth, destY, (int) (m_2Rect.w * scale), (int) (m_2Rect.h * scale), m_2Rect.x, m_2Rect.y, m_2Rect.w, m_2Rect.h);
			numDigits++;
			lastNumWidth += (int) (m_2Rect.w * scale);
			break;

		case '3':
			g_AssetManager->render("Resources/Textures/numbers.png", destX + lastNumWidth, destY, (int) (m_3Rect.w * scale), (int) (m_3Rect.h * scale), m_3Rect.x, m_3Rect.y, m_3Rect.w, m_3Rect.h);
			numDigits++;
			lastNumWidth += (int) (m_3Rect.w * scale);
			break;

		case '4':
			g_AssetManager->render("Resources/Textures/numbers.png", destX + lastNumWidth, destY, (int) (m_4Rect.w * scale), (int) (m_4Rect.h * scale), m_4Rect.x, m_4Rect.y, m_4Rect.w, m_4Rect.h);
			numDigits++;
			lastNumWidth += (int) (m_4Rect.w * scale);
			break;

		case '5':
			g_AssetManager->render("Resources/Textures/numbers.png", destX + lastNumWidth, destY, (int) (m_5Rect.w * scale), (int) (m_5Rect.h * scale), m_5Rect.x, m_5Rect.y, m_5Rect.w, m_5Rect.h);
			numDigits++;
			lastNumWidth += (int) (m_5Rect.w * scale);
			break;

		case '6':
			g_AssetManager->render("Resources/Textures/numbers.png", destX + lastNumWidth, destY, (int) (m_6Rect.w * scale), (int) (m_6Rect.h * scale), m_6Rect.x, m_6Rect.y, m_6Rect.w, m_6Rect.h);
			numDigits++;
			lastNumWidth += (int) (m_6Rect.w * scale);
			break;

		case '7':
			g_AssetManager->render("Resources/Textures/numbers.png", destX + lastNumWidth, destY, (int) (m_7Rect.w * scale), (int) (m_7Rect.h * scale), m_7Rect.x, m_7Rect.y, m_7Rect.w, m_7Rect.h);
			numDigits++;
			lastNumWidth += (int) (m_7Rect.w * scale);
			break;

		case '8':
			g_AssetManager->render("Resources/Textures/numbers.png", destX + lastNumWidth, destY, (int) (m_8Rect.w * scale), (int) (m_8Rect.h * scale), m_8Rect.x, m_8Rect.y, m_8Rect.w, m_8Rect.h);
			numDigits++;
			lastNumWidth += (int) (m_8Rect.w * scale);
			break;

		case '9':
			g_AssetManager->render("Resources/Textures/numbers.png", destX + lastNumWidth, destY, (int) (m_9Rect.w * scale), (int) (m_9Rect.h * scale), m_9Rect.x, m_9Rect.y, m_9Rect.w, m_9Rect.h);
			numDigits++;
			lastNumWidth += (int) (m_9Rect.w * scale);
			break;
		}
	}
}

int NumberRenderer::getNumWidth(int num, float scale)
{
	std::string numString = std::to_string(num);
	int numWidth = 0;

	for (const auto& digit : numString)
	{
		switch (digit)
		{

		case '0':
			numWidth += (int) (m_0Rect.w * scale);
			break;

		case '1':
			numWidth += (int) (m_1Rect.w * scale);
			break;

		case '2':
			numWidth += (int) (m_2Rect.w * scale);
			break;

		case '3':
			numWidth += (int) (m_3Rect.w * scale);
			break;

		case '4':
			numWidth += (int) (m_4Rect.w * scale);
			break;

		case '5':
			numWidth += (int) (m_5Rect.w * scale);
			break;

		case '6':
			numWidth += (int) (m_6Rect.w * scale);
			break;

		case '7':
			numWidth += (int) (m_7Rect.w * scale);
			break;

		case '8':
			numWidth += (int) (m_8Rect.w * scale);
			break;

		case '9':
			numWidth += (int) (m_9Rect.w * scale);
			break;
		}
	}

	return numWidth;
}
