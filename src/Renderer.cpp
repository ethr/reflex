#include <vector>
#include <sstream>
#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "Renderer.hpp"
#include "ScoreArea.hpp"
#include "Utils.hpp"

#include <stdexcept>

using namespace std;

namespace reflexgame {

  enum textquality {solid, shaded, blended};

  static TTF_Font* loadfont(char* file, int ptsize) {
    TTF_Font* tmpfont;
    tmpfont = TTF_OpenFont(file, ptsize);
    if (tmpfont == NULL){
	  char dst[1024];
      sprintf_s(dst, "Unable to load font: %s %s \n", file, TTF_GetError());
	  throw exception(dst);
      // Handle the error here.
    }
    return tmpfont;
  }

  static SDL_Surface* drawtext(TTF_Font *fonttodraw, unsigned char fgR, unsigned char fgG,
      unsigned char fgB, unsigned char fgA, unsigned char bgR, unsigned char bgG, unsigned char bgB, unsigned char bgA,
      const std::string& text) {
    SDL_Color tmpfontcolor = {fgR,fgG,fgB,fgA};
    SDL_Color tmpfontbgcolor = {bgR, bgG, bgB, bgA};
    SDL_Surface* resulting_text;
	textquality quality = blended;

	const char* text_arr = text.c_str();

    if (quality == solid) resulting_text = TTF_RenderText_Solid(fonttodraw,
        text.c_str(), tmpfontcolor);
    else if (quality == shaded) resulting_text = TTF_RenderText_Shaded(
        fonttodraw, text_arr, tmpfontcolor, tmpfontbgcolor);
    else if (quality == blended) resulting_text = TTF_RenderText_Blended(
        fonttodraw, text_arr, tmpfontcolor);
 
    return resulting_text;
  }

  static void drawScoreAreas(SDL_Surface* surface_, const vector<ScoreArea*>& scoreAreas) {
    for (vector<ScoreArea*>::const_reverse_iterator it =
        scoreAreas.rbegin();
        it != scoreAreas.rend(); it++) {
      ScoreArea* sa = *it;
      int x = sa->getX();
      int y = sa->getY();
      Uint32 age = SDL_GetTicks() - sa->getCreationTime();
      int r = util::ageToRadius(age);
      if (r > 0) {
        filledCircleColor(surface_, x, y, r, 0xff00ffA0);
        filledCircleColor(surface_, x, y, (3*r)/4, 0xA0A000A0);
        filledCircleColor(surface_, x, y, r/2, 0xff0000A0);
        filledCircleColor(surface_, x, y, r/4, 0xA00000A0);
      }
    }
  }

  ///usr/share/fonts/truetype/freefont/FreeSans.ttf
  Renderer::Renderer(SDL_Surface* surface) : surface_(surface),
    font_(loadfont("Squared_Display.ttf", 12)),
    crosshair_(IMG_Load("images/crosshair.png")) {}

  Renderer::~Renderer() {
    // TODO free font?
    SDL_FreeSurface(crosshair_);
  }

  void Renderer::draw(const GameState& gameState) {
    SDL_FillRect(surface_, NULL, 0x000000FF); 
    SDL_LockSurface(surface_);
    drawScoreAreas(surface_, gameState.getScoreAreasRef());
    SDL_UnlockSurface(surface_);

    stringstream os;
    os << "Round: " << gameState.getRoundNumber();
    stringstream time;
    time << "Time: " << floor(static_cast<float>(
        (SDL_GetTicks() - gameState.getStartTime()))/100.0)/10.0;
	  stringstream score;
	  score << "Score: " << gameState.getScore();

    // Text
    SDL_Surface* text_surface = drawtext(font_, 255, 255, 255, 255, 255, 255, 255, 255,
      os.str());
    SDL_Surface* time_surface = drawtext(font_, 255, 255, 0, 255, 255,
      255, 255, 255, time.str().c_str());
	  SDL_Surface* score_surface = drawtext(font_, 255, 255, 0, 255, 255,
      255, 255, 255, score.str().c_str());

    SDL_Rect rect = { 0, 0, text_surface->w, text_surface->h };
    SDL_BlitSurface(text_surface, NULL, surface_, &rect);

	  rect.x = 0;
	  rect.y = text_surface->h + 3;
	  rect.w = time_surface->w;
	  rect.h = time_surface->h;
    SDL_BlitSurface(time_surface, NULL, surface_, &rect);

	  rect.x = 0;
	  rect.y += time_surface->h + 3;
	  rect.w = score_surface->w;
	  rect.h = score_surface->h;
    SDL_BlitSurface(score_surface, NULL, surface_, &rect);

    int mx, my;
    SDL_GetMouseState(&mx, &my);
	  rect.x = mx;
	  rect.y = my;
	  rect.w = crosshair_->w;
	  rect.h = crosshair_->h;
    SDL_BlitSurface(crosshair_, NULL, surface_, &rect);

    SDL_FreeSurface(text_surface);
    SDL_FreeSurface(time_surface);
  }

  void Renderer::drawEndGame(const GameState& gameState) {
    const Uint32 midX = surface_->w / 2;
    const Uint32 midY = surface_->h / 2;
    const Uint32 scoreBoardWidth = 500;
    const Uint32 scoreBoardHeight = 500;
    const Uint32 dx = midX - scoreBoardWidth/2;
    const Uint32 dy = midY - scoreBoardHeight/2;
    SDL_FillRect(surface_, NULL, 0x000000FF);
    aalineRGBA(surface_, dx, dy, dx + scoreBoardWidth, dy, 0xFF, 0xFF, 0xFF, 0xFF);
  }
}

