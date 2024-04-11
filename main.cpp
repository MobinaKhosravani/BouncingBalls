#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <sstream>
#include <vector>

#ifdef TA_LINUX_BUILD
#include <SDL2/SDL2_gfxPrimitives.h>
#else

#include <SDL2/SDL2_gfx.h>

#endif

#include <iostream>
#include <string>
#include <cmath>
#include <SDL2/SDL_mixer.h>

using namespace std;

SDL_Window *m_window;
SDL_Renderer *m_renderer;
int vpayin = 8;
double r = 20, v = 7, paiin = 0;
int score = 0;
int brkhdv = 0;
int brkhdvc = 0;
struct point {
    double x = 0, y = 0;
};
//struct colors {
//   // int r = 0, g = 0, b = 0;
//};
int color_set[6] = {0, 1, 2, 3, 4, 5};
struct toop {
    point center, hamsaye_center[6];
    int hamsaye[6] = {-1, -1, -1, -1, -1, -1};
    bool hazf = false, locked = false;
    bool connected = false;
    int rang_toop = -1, hamsaye_colour[6];
    bool time_effect = false;
};


class image {
private:
    SDL_Renderer *ren;
    SDL_Rect img_rect;
public:
    string path;
    SDL_Texture *img;
    int img_w, img_h;
    int x;
    int y;
    float sc_x;
    float sc_y;

    void run() {
        img = IMG_LoadTexture(ren, path.c_str());
        SDL_QueryTexture(img, NULL, NULL, &img_w, &img_h);
    }

    void load() {
        //const char* cpath = path.c_str();


        img_rect.x = x;
        img_rect.y = y;
        img_rect.w = img_w * sc_x;
        img_rect.h = img_h * sc_y;
        SDL_RenderCopy(ren, img, NULL, &img_rect);
        //delete cpath;
    }

    image(string Path, int X, int Y, float SC, SDL_Renderer *Ren) {
        x = X;
        y = Y;
        path = Path;
        sc_x = SC;
        sc_y = SC;
        ren = Ren;
        run();
        load();
    }

    void setCenter(int X, int Y) {
        x = X - img_w * sc_x / 2;
        y = Y - img_h * sc_y / 2;
        load();
    }

    void render() {
        SDL_RenderCopy(ren, img, NULL, &img_rect);
    }

    ~image() {
        SDL_DestroyTexture(img);
    }
};

//string music[2] = {"m1", "m2"};
string username = "", password = "";
int shomarekarbari, timed = 200, abstime = 0;

/* -------------------------------------functions--------------------------------*/
string image_toop(int color);

void oftadan(toop *toops, int ball, SDL_Texture *redball, SDL_Texture *blueball, SDL_Texture *purpleball,
             SDL_Texture *yellowball, SDL_Texture *sangball, SDL_Texture *greenball, image *bg1, image *bg2, int theme);

bool barkhord(toop *toops, toop partabi1);

void window_color(SDL_Renderer *Renderer, int R, int G, int B);

void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian);

int weighted_random(int choices, int *weights);

double distance(point pain, point ahhh);

void khatchin(SDL_Renderer *Renderer, point avl, point dvm, toop *toops, double r);

int random_partabi_color(toop *toops, int smax);

void angleimage(SDL_Texture *text, int x, int y, int w, int h, double alfa);

void hazf_check(toop *toops, int smax, int s, int &vpyin);

void sang_random(int k, toop *toops, int max);

void toop_rang(int tedad, toop *toops);

void betterText(SDL_Renderer *renderer, string S, int x, int y, int size, string Font);

//string TextBox(SDL_Renderer *Renderer, int x_position, int y_position);

string TextBox(SDL_Renderer *Renderer, int x_position, int y_position, int theme, image *bg_menu, image *bg_menu2,
               SDL_Texture *backbtn, SDL_Texture *textbox);

int mode6check(toop *toops, int mode);

int readNthValue(const string &filePath, int n);

string readNthValuestr(const string &filePath, int n);

bool searchStringInCSV(const string &filename, const string &target);

int findIndexInCSV(const string &filePath, const string &targetString);

void replaceNthStringInCSV(const string &filePath, int n, const string &replacement);

void balabar(toop *toops, int smax);

void lock_render(toop *toops, SDL_Texture *lock);

bool okrang(int a, int b);

void toops_reset(toop *toops);

void fall(toop *toops, int i, SDL_Texture *redball, SDL_Texture *blueball, SDL_Texture *purpleball,
          SDL_Texture *yellowball, SDL_Texture *sangball, SDL_Texture *greenball, SDL_Texture *greenpurple,
          SDL_Texture *purpleblue, SDL_Texture *yellowred, image *bg1, image *bg2,
          int theme);

double faselekhat(point avl, point akhr, toop *toops, int i);

void anbomb(int xm2, int ym2, int rm2);

void toopbekhor(int xm2, int ym2, int rm2, int R, int G, int B);

void clock_render(toop *toops, SDL_Texture *clock);

void clock_random(toop *toops, int max);

int main(int argc, char *argv[]) {
    bool sabttime = false;
    int t0 = 0;
    bool bord = false;
    bool laser = false;
    bool laserkey = false;
    Mix_Fading Mix_FadingMusic(Mix_Chunk *pChunk);
    int theme = 0;
    int w = 1000;
    int h = 800;
    int smax = 1200;
    srand(time(NULL));
    string inputText = "";
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s",
                     SDL_GetError());
        return 3;
    }

    m_window = SDL_CreateWindow("pain", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 800,
                                SDL_WINDOW_SHOWN);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    assert(m_window != NULL);
    assert(m_renderer != NULL);
/*---------ttf---------*/
    TTF_Init();

    TTF_Font *font = TTF_OpenFont("Modak-Regular.ttf", 60);


    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_renderer);


    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3 || Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        return 1;
    }/*-------------------------------Ax ha---------------------------- */
    image *bg1 = new image("pics/bg1.png", 0, 0, 0.5, m_renderer);
    image *bg2 = new image("pics/bg2.png", 0, 0, 0.5, m_renderer);
    image *bg_menu = new image("pics/bg_menu.png", 0, 0, 1.2, m_renderer);
    image *bg_menu2 = new image("pics/bg_menu2.png", 0, 0, 0.5, m_renderer);
    SDL_Texture *redball = IMG_LoadTexture(m_renderer, "pics/red.png");
    SDL_Texture *blueball = IMG_LoadTexture(m_renderer, "pics/blue.png");
    SDL_Texture *yellowball = IMG_LoadTexture(m_renderer, "pics/yellow.png");
    SDL_Texture *greenball = IMG_LoadTexture(m_renderer, "pics/green.png");
    SDL_Texture *purpleball = IMG_LoadTexture(m_renderer, "pics/purple.png");
    SDL_Texture *sangball = IMG_LoadTexture(m_renderer, "pics/sang.png");
    SDL_Texture *pin_cannon = IMG_LoadTexture(m_renderer, "pics/pingu_cannon.png");
    SDL_Texture *pin_cannon2 = IMG_LoadTexture(m_renderer, "pics/cannon2.png");
    SDL_Texture *textbox = IMG_LoadTexture(m_renderer, "pics/TextboxIce.png");
    SDL_Texture *textboxinfmode = IMG_LoadTexture(m_renderer, "pics/TextboxIceInfgamemode.png");
    SDL_Texture *textboxinfmode2 = IMG_LoadTexture(m_renderer, "pics/candybuttoninfmode.png");
    SDL_Texture *textboxnoramlmode = IMG_LoadTexture(m_renderer, "pics/TextboxIceNormalgamemode.png");
    SDL_Texture *textboxnoramlmode2 = IMG_LoadTexture(m_renderer, "pics/candybuttonnormalmode.png");
    SDL_Texture *textboxtimemode = IMG_LoadTexture(m_renderer, "pics/TextboxIceTimedgamemode.png");
    SDL_Texture *textboxtimemode2 = IMG_LoadTexture(m_renderer, "pics/candybuttontimedmode.png");
    SDL_Texture *textboxlogin = IMG_LoadTexture(m_renderer, "pics/TextboxIceLogin.png");
    SDL_Texture *textboxlogin2 = IMG_LoadTexture(m_renderer, "pics/candybuttonlogin.png");
    SDL_Texture *textboxsignup = IMG_LoadTexture(m_renderer, "pics/TextboxIceSignup.png");
    SDL_Texture *textboxsignup2 = IMG_LoadTexture(m_renderer, "pics/candybuttonsignup.png");
    SDL_Texture *textboxstart = IMG_LoadTexture(m_renderer, "pics/TextboxIceStart.png");
    SDL_Texture *textboxstart2 = IMG_LoadTexture(m_renderer, "pics/candybuttonstart.png");
    SDL_Texture *textboxleaderboard = IMG_LoadTexture(m_renderer, "pics/TextboxIceLeaderBoard.png");
    SDL_Texture *textboxleaderboard2 = IMG_LoadTexture(m_renderer, "pics/candybuttonleaderboard.png");
    SDL_Texture *setting = IMG_LoadTexture(m_renderer, "pics/icesetting.png");
    SDL_Texture *setting2 = IMG_LoadTexture(m_renderer, "pics/candysetting.png");
    SDL_Texture *backbtn = IMG_LoadTexture(m_renderer, "pics/backbtn.png");
    SDL_Texture *playbtn = IMG_LoadTexture(m_renderer, "pics/play.png");
    SDL_Texture *nextbtn = IMG_LoadTexture(m_renderer, "pics/nextbtn.png");
    SDL_Texture *upbtn = IMG_LoadTexture(m_renderer, "pics/volumnup.png");
    SDL_Texture *downbtn = IMG_LoadTexture(m_renderer, "pics/volumndown.png");
    SDL_Texture *iceicon = IMG_LoadTexture(m_renderer, "pics/iceicon.png");
    SDL_Texture *candyicon = IMG_LoadTexture(m_renderer, "pics/candyicon.png");
    SDL_Texture *m1cover = IMG_LoadTexture(m_renderer, "pics/m1.png");
    SDL_Texture *m2cover = IMG_LoadTexture(m_renderer, "pics/m2.png");
    SDL_Texture *m3cover = IMG_LoadTexture(m_renderer, "pics/m3.png");
    SDL_Texture *m4cover = IMG_LoadTexture(m_renderer, "pics/m4.png");
    SDL_Texture *m5cover = IMG_LoadTexture(m_renderer, "pics/m5.png");
    SDL_Texture *exitbtn = IMG_LoadTexture(m_renderer, "pics/exit.png");
    SDL_Texture *happyice = IMG_LoadTexture(m_renderer, "pics/happyice.png");
    SDL_Texture *happycandy = IMG_LoadTexture(m_renderer, "pics/happycandy.png");
    SDL_Texture *gameover = IMG_LoadTexture(m_renderer, "pics/gameover.png");
    SDL_Texture *purpleblue = IMG_LoadTexture(m_renderer, "pics/purple-blue.png");
    SDL_Texture *yellowred = IMG_LoadTexture(m_renderer, "pics/yellow-red.png");
    SDL_Texture *greenpurple = IMG_LoadTexture(m_renderer, "pics/green-purple.png");
    SDL_Texture *lock = IMG_LoadTexture(m_renderer, "pics/lock.png");
    SDL_Texture *clock = IMG_LoadTexture(m_renderer, "pics/clock.png");
    SDL_Texture *bomb = IMG_LoadTexture(m_renderer, "pics/bomb.png");
    SDL_Texture *navarpower = IMG_LoadTexture(m_renderer, "pics/navarpower.png");
    SDL_Texture *rangi = IMG_LoadTexture(m_renderer, "pics/rangi.png");
/*------------------------------------------ahng-----------------------------------------------*/

    Mix_Music *m1 = Mix_LoadMUS("music/m1.mp3");
    Mix_Music *m2 = Mix_LoadMUS("music/m2.mp3");
    Mix_Music *m3 = Mix_LoadMUS("music/m3.mp3");
    Mix_Music *m4 = Mix_LoadMUS("music/m4.mp3");
    Mix_Music *m5 = Mix_LoadMUS("music/m5.mp3");
    Mix_Chunk *shootingsound = Mix_LoadWAV("music/shootingsound.wav");
    Mix_Chunk *btnsound = Mix_LoadWAV("music/btnsound.wav");
//    if (btnsound == NULL) {
//        return 0;
//    }

//    if (music == NULL) {
//        cout<<ahng;
//    }



    /*-----------------------------------------------------------------------*/

    toop partabi1, partabi2;

    partabi1.center.x = 500 - r;
    partabi1.center.y = 750 - r;
//    partabi2.center.x = 500;
//    partabi2.center.y = 800;

    /* -----------------------------taiin markaz-------------------------*/
    toop toops[1200];
    toop lank;
    int time = 0;
    for (int i = 0; i < 1200; ++i) {
        toops[i] = lank;
    }
    int q = 0;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (i % 2 == 0) {
                toops[q] = {{260 + r * (2 * j + 1), r * (1 + i * sqrt(3)) - 300 + paiin}};
            } else {
                toops[q] = {{260 + 2 * r * (1 + j), r * (1 + sqrt(3) * (1 + (i - 1))) - 300 + paiin}};
            }
            toops[q].hamsaye_center[0] = {toops[q].center.x + r, toops[q].center.y - sqrt(3) * r};
            toops[q].hamsaye_center[1] = {toops[q].center.x + 2 * r, toops[q].center.y};
            toops[q].hamsaye_center[2] = {toops[q].center.x + r, toops[q].center.y + r * sqrt(3)};
            toops[q].hamsaye_center[3] = {toops[q].center.x - r, toops[q].center.y + sqrt(3) * r};
            toops[q].hamsaye_center[4] = {toops[q].center.x - 2 * r, toops[q].center.y};
            toops[q].hamsaye_center[5] = {toops[q].center.x - r, toops[q].center.y - r * sqrt(3)};
            q++;
        }
    }

    /* -----------------------------rang tup hye avalie  ------------------------ */
    toop_rang(144, toops);//asd


    SDL_Event *e = new SDL_Event();
    bool quit = false, signup, play = false;
    int xmouse, ymouse;
    bool partab = false;
    int xmouse0, ymouse0, ahng = 0;
    bool firstpress = false;
    bool barkhord_first = false;
    point xymouse;
    point vasat = {500.0, 750.0};
    int mode = 0; //debug
    int moder = 0;//debug
//    bool event =event;
//    Mix_PlayMusic(music, -1);
    int play_stop = 0;
    int volumn = 60;
    bool reset = true;
    while (!quit) {
        if (mode >= 20)
            abstime++;

        SDL_GetMouseState(&xmouse, &ymouse);
        xymouse = {double(xmouse), double(ymouse)};
        bool event = SDL_PollEvent(e);
        if (!play && ahng % 5 == 0) {
            Mix_PlayMusic(m1, -1);
            play = true;
        }
        if (!play && ahng % 5 == 1) {
            Mix_PlayMusic(m2, -1);
            play = true;
        }
        if (!play && ahng % 5 == 2) {
            Mix_PlayMusic(m3, -1);
            play = true;
        }
        if (!play && ahng % 5 == 3) {
            Mix_PlayMusic(m4, -1);
            play = true;
        }
        if (!play && ahng % 5 == 4) {
            Mix_PlayMusic(m5, -1);
            play = true;
        }
        Mix_VolumeMusic(volumn);
        if (mode == 0) {


            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
            if (theme == 0) {
                bg_menu->render();
//                angleimage(texttexture, 10, 10, 100, 100, 0);
                angleimage(textboxsignup, 350, 200, 300, 175, 0);
                angleimage(textboxlogin, 350, 380, 300, 175, 0);
            }
            if (theme == 1) {
                bg_menu2->render();
                angleimage(textboxsignup2, 350, 200, 300, 175, 0);
                angleimage(textboxlogin2, 350, 380, 300, 175, 0);
            }
            SDL_RenderPresent(m_renderer);
            if (event) {

//                if (e->type == SDL_QUIT) {
//                    quit = true;
//                    Mix_FreeMusic(m1);
//                    Mix_CloseAudio();
//                    Mix_Quit();

//                } else
                if (e->type == SDL_MOUSEBUTTONDOWN) {
                    SDL_GetMouseState(&xmouse, &ymouse);
                    xymouse = {double(xmouse), double(ymouse)};
                    if (xymouse.x > 350 && xymouse.x < 650) {
                        if (xymouse.y > 200 && xymouse.y < 320) {
                            mode = 1;
                            signup = true;
                        } else if (xymouse.y > 380 && xymouse.y < 500) {
                            mode = 1;
                            signup = false;
                        }
                    }

                }
            }
        } else if (mode == 1) {
            ofstream scorenormal("scorenormal.txt", ios::app);
            ofstream scoretimed("scoretimed.txt", ios::app);
            ofstream scoreinf("scoreinf.txt", ios::app);
            ofstream power("powercount.txt", ios::app);


//            SDL_RenderClear(m_renderer);
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
            if (theme == 0) {
                bg_menu->render();
                // boxRGBA(m_renderer, 880, 40, 940, 100, 255, 255, 0, 255);
                angleimage(backbtn, 880, 40, 60, 60, 0);
                angleimage(textbox, 350, 200, 300, 175, 0);
                angleimage(textbox, 350, 380, 300, 175, 0);
            }
            if (theme == 1) {
                bg_menu2->render();
                angleimage(backbtn, 880, 40, 60, 60, 0);
                angleimage(textbox, 350, 200, 300, 175, 0);
                angleimage(textbox, 350, 380, 300, 175, 0);
            }

            if (event) {

//                if (e->type == SDL_QUIT) {
//                    quit = true;
//                } else
                if (e->type == SDL_MOUSEBUTTONDOWN) {
                    SDL_GetMouseState(&xmouse, &ymouse);
                    xymouse = {double(xmouse), double(ymouse)};
                    if (xymouse.x > 350 && xymouse.x < 650) {
                        if (xymouse.y > 200 && xymouse.y < 320) {
                            username = TextBox(m_renderer, 355, 230, theme, bg_menu, bg_menu2, backbtn, textbox);

                        } else if (xymouse.y > 380 && xymouse.y < 500) {
                            password = TextBox(m_renderer, 355, 410, theme, bg_menu, bg_menu2, backbtn, textbox);

                        }
                    }

                } else if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_SPACE) {

                    if (signup) {
                        ofstream user("user.txt", ios::app);
//                        ofstream pass("pass.txt", ios::app);
                        if (searchStringInCSV("user.txt", username)) {
                            username = "";
                            betterText(m_renderer, "username already existent", 355, 500, 60, "");
                        }
                        if (username != "") {
                            user << username << ",";
//                            if (password != "") {
//                                pass << password << ",";
                            scorenormal << "0,";
                            scoretimed << "0,";
                            scoreinf << "0,";
                            power << "3,";
                            scorenormal.close();
                            scoreinf.close();
                            scoretimed.close();
                            power.close();
//                            }
                        }
                        signup = false;
                        user.close();
//                        pass.close();
                        mode = 2;
                        reset = true;
                        bord = false;
                        score = 0;
                    } else {
                        ifstream user("user.txt", ios::in);
//                        ifstream pass("pass.txt", ios::in);
                        if (findIndexInCSV("user.txt", username) != -1) {
                            user.close();
//                            pass.close();
                            mode = 2;
                            reset = true;
                            bord = false;
                            score = 0;
                        }
//                        else {
//                            username = "";
//                            password = "";
//                        }


                    }
                    shomarekarbari = findIndexInCSV("user.txt", username);
                    cout << shomarekarbari << "\n";
                    cout << readNthValue("scorenormal.txt", shomarekarbari);
                }
            }
            betterText(m_renderer, password, 355, 410, 50, "");
            betterText(m_renderer, username, 355, 230, 50, "");
            SDL_RenderPresent(m_renderer);
        } else if (mode == 2) {
            if (reset) {
                toops_reset(toops);
                bord = false;
            }
            reset = false;
            double charkh = 0;
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
            if (theme == 0) {
                bg_menu->render();
                angleimage(backbtn, 880, 40, 60, 60, 0);
                angleimage(textboxstart, 350, 200, 300, 175, 0);
                angleimage(textboxleaderboard, 350, 380, 300, 175, 0);
                angleimage(setting, 50, 100, 175, 175, charkh);
            }
            if (theme == 1) {
                bg_menu2->render();
                angleimage(backbtn, 880, 40, 60, 60, 0);
                angleimage(textboxstart2, 350, 200, 300, 175, 0);
                angleimage(textboxleaderboard2, 350, 380, 300, 175, 0);
                angleimage(setting2, 50, 100, 175, 175, charkh);
            }

            SDL_RenderPresent(m_renderer);
            if (event) {

//                if (e->type == SDL_QUIT) {
//                    quit = true;
//                } else
                if (e->type == SDL_MOUSEBUTTONDOWN) {
                    SDL_GetMouseState(&xmouse, &ymouse);
                    xymouse = {double(xmouse), double(ymouse)};
                    if (xymouse.x > 350 && xymouse.x < 650) {
                        if (xymouse.y > 200 && xymouse.y < 320) {
                            mode = 3;

                        } else if (xymouse.y > 380 && xymouse.y < 500) {
                            mode = 4;

                        }
                    } else if (xymouse.y > 100 && xymouse.y < 275 && xymouse.x > 50 && xymouse.x < 225) {
                        mode = 5;

                    }
                }
            }
            charkh += 10;
        } else if (mode == 3) {
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
            if (theme == 0) {
                bg_menu->render();
                angleimage(backbtn, 880, 40, 60, 60, 0);
                angleimage(textboxnoramlmode, 350, 100, 300, 175, 0);
                angleimage(textboxtimemode, 350, 280, 300, 175, 0);
                angleimage(textboxinfmode, 350, 460, 300, 175, 0);
            }
            if (theme == 1) {
                bg_menu2->render();
                angleimage(backbtn, 880, 40, 60, 60, 0);
                angleimage(textboxnoramlmode2, 350, 100, 300, 175, 0);
                angleimage(textboxtimemode2, 350, 280, 300, 175, 0);
                angleimage(textboxinfmode2, 350, 460, 300, 175, 0);
            }
//            toop_rang(144, toops);

            SDL_RenderPresent(m_renderer);
            if (event) {

//                if (e->type == SDL_QUIT) {
//                    quit = true;
//                } else
                if (e->type == SDL_MOUSEBUTTONDOWN) {
                    SDL_GetMouseState(&xmouse, &ymouse);
                    xymouse = {double(xmouse), double(ymouse)};
                    if (xymouse.x > 350 && xymouse.x < 650) {
                        if (xymouse.y > 100 && xymouse.y < 220) {
                            mode = 20;
                        } else if (xymouse.y > 280 && xymouse.y < 400) {
                            mode = 21;
                        } else if (xymouse.y > 360 && xymouse.y < 580) {
                            mode = 22;
                        }
                    }

                }
            }
        } else if (mode == 4) {
            SDL_RenderClear(m_renderer);
            if (theme == 0) {
                bg2->render();
                angleimage(backbtn, 880, 40, 60, 60, 0);

            }
            if (theme == 1) {
                bg1->render();
                angleimage(backbtn, 880, 40, 60, 60, 0);

            }
            betterText(m_renderer, username + ":    " + "normal score" + "-timed score" + "-inf score", 300, 20, 30,
                       "");
            int hajm = 0;
            while (readNthValue("powercount.txt", hajm) != -1)
                hajm++;
            for (int i = 0; i < hajm; ++i) {
                string ldrbrd = readNthValuestr("user.txt", i) + ":    " +
                                to_string(readNthValue("scorenormal.txt", i)) + "-" +
                                to_string(readNthValue("scoretimed.txt", i)) + "-" +
                                to_string(readNthValue("scoreinf.txt", i));
                betterText(m_renderer, ldrbrd, 300, 700 / hajm * i + 100, 36, "");


            }
            SDL_RenderPresent(m_renderer);
            //leader board
//            mode = 0;
        } else if (mode == 5) {
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
            if (theme == 0)
                bg_menu->render();
            if (theme == 1)
                bg_menu2->render();
//            boxRGBA(m_renderer, w / 3, h / 16, 2 * w / 3, 7 * h / 16, 0, 255, 255, 255); //cover ahng
            if (ahng % 5 == 0)
                angleimage(m1cover, w / 3, h / 16, w / 3, 3 * h / 8, 0);
            if (ahng % 5 == 1)
                angleimage(m2cover, w / 3, h / 16, w / 3, 3 * h / 8, 0);
            if (ahng % 5 == 2)
                angleimage(m3cover, w / 3, h / 16, w / 3, 3 * h / 8, 0);
            if (ahng % 5 == 3)
                angleimage(m4cover, w / 3, h / 16, w / 3, 3 * h / 8, 0);
            if (ahng % 5 == 4)
                angleimage(m5cover, w / 3, h / 16, w / 3, 3 * h / 8, 0);
            angleimage(playbtn, 370, 370, 70, 70, 0);
            angleimage(nextbtn, 553, 370, 70, 70, 0);
            angleimage(upbtn, 700, 70, 70, 70, 0);
            angleimage(downbtn, 700, 200, 70, 70, 0);
            angleimage(iceicon, 300, 600, 200, 180, 0);
            angleimage(candyicon, 550, 600, 200, 180, 0);
            angleimage(backbtn, 880, 40, 60, 60, 0);


            SDL_RenderPresent(m_renderer);
        } else if (mode == 6) {
            if (!bord) {
                string emtiys = to_string(readNthValue("powercount.txt", shomarekarbari) + 1);
                replaceNthStringInCSV("powercount.txt", shomarekarbari, emtiys);
            }
            bord = true;
            SDL_RenderClear(m_renderer);
            if ((score) > readNthValue("scorenormal.txt", shomarekarbari))
                replaceNthStringInCSV("scorenormal.txt", shomarekarbari, to_string(score));
            if (theme == 0) {
                bg2->render();
                angleimage(happyice, w / 2 - 300, h / 2 - 300, 600, 600, 0);
                betterText(m_renderer, username, w / 2 - 110, h / 2 - 137, 45, "");
                betterText(m_renderer, to_string(score), w / 2 - 95, h / 2 - 5, 45, "");
            }
            if (theme == 1) {
                bg1->render();
                angleimage(happycandy, w / 2 - 300, h / 2 - 300, 600, 600, 0);
                betterText(m_renderer, username, w / 2 - 110, h / 2 - 210, 45, "");
                betterText(m_renderer, to_string(score), w / 2 - 95, h / 2 - 5, 45, "");
            }

            SDL_RenderPresent(m_renderer);
        } else if (mode == 7) { //back tu bazi
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
            if (theme == 0)
                bg_menu->render();
            if (theme == 1)
                bg_menu2->render();
            angleimage(playbtn, 370, 370, 70, 70, 0);
            angleimage(nextbtn, 553, 370, 70, 70, 0);
            angleimage(upbtn, 700, 70, 70, 70, 0);
            angleimage(downbtn, 700, 200, 70, 70, 0);
            angleimage(iceicon, 300, 600, 200, 180, 0);
            angleimage(candyicon, 550, 600, 200, 180, 0);
            angleimage(backbtn, 880, 40, 60, 60, 0);
            angleimage(exitbtn, w / 3 + 60, h / 16 + 50, 200, 200, 0);
            SDL_RenderPresent(m_renderer);

        } else if (mode == 8) {
            if (score != 0) {
                if (moder == 20) {
                    if ((score) > readNthValue("scorenormal.txt", shomarekarbari))
                        replaceNthStringInCSV("scorenormal.txt", shomarekarbari, to_string(score));
                }
                if (moder == 21) {
//                                replaceNthStringInCSV("scoretimed.txt", shomarekarbari,
//                                                      to_string(score)
//                    );
                    if ((score) > readNthValue("scoretimed.txt", shomarekarbari))
                        replaceNthStringInCSV("scoretimed.txt", shomarekarbari, to_string(score));
                }
                if (moder == 22) {
//                                replaceNthStringInCSV("scoreinf.txt", shomarekarbari,
//                                                      to_string(score)
//                                );
                    if ((score) > readNthValue("scoreinf.txt", shomarekarbari))
                        replaceNthStringInCSV("scoreinf.txt", shomarekarbari, to_string(score));
                }
                score = 0;
            }
            score = 0;
            SDL_RenderClear(m_renderer);
            if (theme == 0) {
                bg2->render();
            }
            if (theme == 1) {
                bg1->render();
            }
            angleimage(gameover, w / 2 - 250, h / 2 - 250, 500, 500, 0);
            SDL_RenderPresent(m_renderer);

        } else if (mode == 20) { //game
            cout << "s" << abstime;
//            int toopnamorde = 0 ;
            moder = 20;
            SDL_RenderClear(m_renderer);
            if (theme == 0) {
                bg2->

                        render();

                SDL_SetRenderDrawColor(m_renderer,
                                       90, 90, 100, 255);
                SDL_RenderDrawLine(m_renderer,
                                   260, 0, 260, 800);
                SDL_RenderDrawLine(m_renderer,
                                   760, 0, 760, 800);
            }
            if (theme == 1) {
                bg1->

                        render();

                SDL_SetRenderDrawColor(m_renderer,
                                       220, 220, 140, 255);
                SDL_RenderDrawLine(m_renderer,
                                   260, 0, 260, 800);
                SDL_RenderDrawLine(m_renderer,
                                   760, 0, 760, 800);
            }
            angleimage(navarpower, 30, 450, 60, 300, 0);
            betterText(m_renderer, to_string(readNthValue("powercount.txt", shomarekarbari)), 48, 445, 40, "");
/*------------------------------hadaf giri-----------------------------------*/

            if (
                    mode6check(toops, mode
                    ) == 0) {
                mode = 6;
                replaceNthStringInCSV("scorenormal.txt", shomarekarbari,
                                      to_string(score)
                );
            }

            SDL_GetMouseState(&xmouse, &ymouse
            );
            xymouse = {double(xmouse), double(ymouse)};
//SDL_SetRenderDrawColor(m_renderer, 100, 10, 80, 255);
            khatchin(m_renderer, vasat, xymouse, toops, r
            );


//            laser = false;
//            laserkey = false;
/* ---------------------------------partab tup-------------------------------- */
            if (partabi1.rang_toop == -1 && !laser)
                partabi1.
                        rang_toop = random_partabi_color(toops, smax);

            if (partabi1.rang_toop == 0) {
                angleimage(redball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            }
            if (partabi1.rang_toop == 1)
                angleimage(blueball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == 2)
                angleimage(yellowball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == 3)
                angleimage(greenball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == 4)
                angleimage(purpleball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == -10)
                angleimage(bomb,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == -20)
                angleimage(rangi,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi2.rang_toop == -1)
                partabi2.
                        rang_toop = random_partabi_color(toops, smax);
            if (partabi2.rang_toop == 0) {
                angleimage(redball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            }
            if (partabi2.rang_toop == 1)
                angleimage(blueball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            if (partabi2.rang_toop == 2)
                angleimage(yellowball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            if (partabi2.rang_toop == 3)
                angleimage(greenball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            if (partabi2.rang_toop == 4)
                angleimage(purpleball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);


            if (
                    partab && firstpress
                    ) {
                int speedx = v * (xmouse0 - 500) /
                             sqrt((750 - ymouse0) * (750 - ymouse0) +
                                  (xmouse0 - 500) * (xmouse0 - 500));
                partabi1.center.
                        y = 750 - v * (750 - ymouse0) * time /
                                  sqrt((750 - ymouse0) * (750 - ymouse0) +
                                       (xmouse0 - 500) * (xmouse0 - 500));
                if (partabi1.center.x < 260 + r) {
                    brkhdv = 1;
                    partabi1.center.
                            x = 260 + r + 5;
                    brkhdvc++;

                }
                if (partabi1.center.x > 720 + r) {
                    brkhdv = 2;

                    partabi1.center.
                            x = 720 + r - 5;
                    brkhdvc++;
                }
                if (brkhdv == 0) {

                    partabi1.center.
                            x = 500 + v * (xmouse0 - 500) * time /
                                      sqrt((750 - ymouse0) * (750 - ymouse0) +
                                           (xmouse0 - 500) * (xmouse0 - 500));
                }
                if (brkhdv == 2) {
                    speedx *= -1;
                    if (brkhdvc % 2 == 1)
                        speedx *= -1;
                    partabi1.center.x +=
                            speedx;
                }
                if (brkhdv == 1) {
                    speedx *= -1;
                    if (brkhdvc % 2 == 1)
                        speedx *= -1;
                    partabi1.center.x +=
                            speedx;
                }
                if (laser) {
                    partabi1.rang_toop = -1;
                    partabi2.rang_toop = -1;
                }
                if (partabi1.rang_toop == 0) {
                    angleimage(redball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                }
                if (partabi1.rang_toop == 1)
                    angleimage(blueball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == 2)
                    angleimage(yellowball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == 3)
                    angleimage(greenball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == 4)
                    angleimage(purpleball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == -10)
                    angleimage(bomb,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == -20)
                    angleimage(rangi,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                time += 1;
            }


            for (
                    int i = 0;
                    i < 1200; i++) {

                if (
                        int(toops[i]
                                    .center.y - r) >= -2 * r) {
                    if (toops[i].rang_toop == 0) {
                        angleimage(redball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    }
                    if (toops[i].rang_toop == 1)
                        angleimage(blueball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 2)
                        angleimage(yellowball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 3)
                        angleimage(greenball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 4)
                        angleimage(purpleball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                }
// -2 nmide tabamun
                if (toops[i].rang_toop == -2)
                    angleimage(sangball,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
                if (toops[i].rang_toop == 6)
                    angleimage(greenpurple,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
                if (toops[i].rang_toop == 7)
                    angleimage(purpleblue,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
                if (toops[i].rang_toop == 8)
                    angleimage(yellowred,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
            }
            int smax = -1;
            for (
                    int i = 0;
                    i < 1200; i++) {
                if (toops[i].rang_toop != -1 && i > smax) {
                    smax = i;
                }
            }
            int s = 0;
            if (
                    barkhord(toops, partabi1
                    ) || partabi1.center.y <= toops[0].center.y) {
                toop select = toops[0];
                barkhord_first = true;
                partab = false;
                for (
                        int i = 0;
                        i < 1200; i++) {
                    if (
                            distance(toops[i]
                                             .center, partabi1.center) <
                            distance(select
                                             .center, partabi1.center) &&
                            toops[i].rang_toop == -1) {
                        select = toops[i];
                        s = i;
                    }

                }
                if (laser)
                    toops[s].rang_toop = -1;
                toops[s].locked = false;
                toops[s].
                        rang_toop = partabi1.rang_toop;
                toops[s].
                        hazf = true;

                int teddhazf = 0;
                for (
                        int i = 0;
                        i < 1200; i++) {
                    if (toops[i].rang_toop != -1 && i > smax) {
                        smax = i;
                    }
                }

                if (toops[s].rang_toop == -10) {
                    anbomb(toops[s].center.x, toops[s].center.y, 4 * r + 5);
                    toops[s].rang_toop = -1;
                    toops[s].locked = false;
                    for (int i = 0; i < smax; ++i) {
                        if (distance(toops[s].center, toops[i].center) < 4 * r + 5) {
                            toops[i].rang_toop = -1;
                            toops[i].locked = false;
                        }
                    }
                }
                if (toops[s].rang_toop == -20) {
                    toops[s].rang_toop = -1;
                    toops[s].locked = false;
                    for (int i = 0; i < smax; ++i) {
                        if (distance(toops[s].center, toops[i].center) < 4 * r + 5) {
                            toops[i].rang_toop = -1;
                            toops[i].locked = false;
                        }
                    }
                }
                hazf_check(toops, smax
                                  + 1, s, vpayin);

                for (
                        int i = 0;
                        i <=
                        smax;
                        i++) {
                    if (toops[i].hazf) {
                        teddhazf++;
//                        cout << "a" << i << "a";
//                        return 0;
                    }
                }
                if (teddhazf > 2) {
                    score += (
                                     log(teddhazf)
                                     / log(3) * 50) *
                             sqrt(timed);
                    cout << score <<
                         endl;
                    cout << teddhazf << "s";
                    for (
                            int i = smax;
                            i >= 0; i--) {
                        if (toops[i].hazf) {
                            toops[i].
                                    rang_toop = -1;
                            toops[i].locked = false;
                            toopbekhor(toops[i].center.x, toops[i].center.y, r, 109, 243, 255);
                            toops[i].
                                    hazf = false;
                        }
                    }

                } else {
                    for (
                            int i = 0;
                            i <=
                            smax;
                            ++i) {

                        toops[i].
                                hazf = false;
                    }
                }
                if (abstime % 40 == 0) {
                    timed--;
                }
                partabi1.
                        rang_toop = partabi2.rang_toop;
                partabi2.
                        rang_toop = -1;
                time = 0;
                firstpress = false;
                partab = false;
                barkhord_first = false;
                partabi1.
                        center = {500 - r, 750 - r};
//                cout << "plpp";
                brkhdv = 0;
            }

            for (
                    int i = 0;
                    i < 12; ++i) {
                if (toops[i].rang_toop > -1)
                    toops[i].
                            connected = true;
                else
                    toops[i].
                            connected = false;
            }
//            toops[s].connected = true;
            for (
                    int i = 12;
                    i <=
                    smax;
                    ++i) {
                bool vasl = false;
                for (
                        int j = 0;
                        j < i;
                        ++j) {

//                    if (i == s) {
//                        cout << i << ":" << j << toops[j].connected << ' ' << distance(toops[i].center, toops[j].center)
//                             << ' '
//                             << toops[i].rang_toop << '\n';
//                    }
                    if ((toops[j].rang_toop != -1 && toops[j].
                            connected &&
                         distance(toops[i].center, toops[j].center)
                         <= 2 * r + 1) || i == s) {
                        vasl = true;
//                        cout << 2;
                    }
                    if (
                            vasl && toops[i]
                                            .rang_toop != -1) {
                        toops[i].
                                connected = true;
//                        cout << 3;
                    }
                }
//                cout << "\n";
            }
            for (
                    int i = smax;
                    i >= 0; --i) {
                bool vasl = false;
                for (
                        int j = smax;
                        j >
                        i;
                        --j) {

//                    if (i == s) {
//                        cout << i << ":" << j << toops[j].connected << ' ' << distance(toops[i].center, toops[j].center)
//                             << ' '
//                             << toops[i].rang_toop << '\n';
//                    }
                    if ((toops[j].rang_toop != -1 && toops[j].
                            connected &&
                         distance(toops[i].center, toops[j].center)
                         <= 2 * r + 1) || i == s) {
                        vasl = true;
//                        cout << 2;
                    }
                    if (
                            vasl && toops[i]
                                            .rang_toop != -1) {
                        toops[i].
                                connected = true;
//                        cout << 3;
                    }
                }
//                cout << "\n";
            }
            for (
                    int i = 12;
                    i <=
                    smax;
                    ++i) {
                bool vasl = false;
                for (
                        int j = 0;
                        j < i;
                        ++j) {

//                    if (i == s) {
//                        cout << i << ":" << j << toops[j].connected << ' ' << distance(toops[i].center, toops[j].center)
//                             << ' '
//                             << toops[i].rang_toop << '\n';
//                    }
                    if ((toops[j].rang_toop != -1 && toops[j].
                            connected &&
                         distance(toops[i].center, toops[j].center)
                         <= 2 * r + 1) || i == s) {
                        vasl = true;
//                        cout << 2;
                    }
                    if (
                            vasl && toops[i]
                                            .rang_toop != -1) {
                        toops[i].
                                connected = true;
//                        cout << 3;
                    }
                }
//                cout << "\n";
            }
            for (
                    int i = 1199;
                    i >= 0; --i) {
                if (!toops[i].
                        connected && toops[i]
                                             .rang_toop != -1) {
                    fall(toops, i, redball, blueball, purpleball,
                         yellowball, sangball, greenball, greenpurple, purpleblue, yellowred, bg1, bg2,
                         theme);
                    toops[i].
                            locked = false;
                    toops[i].time_effect = false;

                }
            }
            for (
                    int i = 0;
                    i < 1200; ++i) {
                toops[i].
                        connected = false;

            }

            if (event) {

//                if (e->type == SDL_QUIT) {
//                    quit = true;
//                } else
                if (e->type == SDL_MOUSEBUTTONDOWN && !firstpress) {


                    xmouse0 = xmouse, ymouse0 = ymouse;
                    partab = true;
                    firstpress = true;

                }
            }
/*--------paiin oomadan---------*/
            if (vpayin == 100 && !sabttime) {
                t0 = abstime;
                sabttime = true;
            }
            if (abstime == t0 + 300 && sabttime) {
                vpayin = 8;
                sabttime = false;
            }

            for (
                    int i = 0;
                    i < 1200; ++i) {
                if (toops[smax].center.y <= 690 &&
                    int(paiin)
                    % vpayin == 1)
                    toops[i].center.y += 1;
            }
            if (toops[smax].center.y > 690) {
                mode = 8;
                cout << "jhuh";
            }
            if (theme == 0)
                angleimage(pin_cannon,
                           400, 650,
                           200,
                           200, 45 * -1 *
                                atan2(xymouse
                                              .x - 500, xymouse.y - 800) / atan(1) + 115);
            else
                angleimage(pin_cannon2,
                           400, 650,
                           200,
                           200, 45 * -1 *
                                atan2(xymouse
                                              .x - 500, xymouse.y - 800) / atan(1) + 115);
            betterText(m_renderer, to_string(score),
                       10, 10, 30, "");
            lock_render(toops, lock
            );
            clock_render(toops, clock
            );
            bool plybrkh = false;
            for (int i = 0; i < 1200; i++) {
                if (toops[i].rang_toop != -1) {
                    if (distance(partabi1.center, toops[i].center) <= 2 * r + 5) {
                        plybrkh = true;
                    }
                }
            }
            if (plybrkh)
                int channel = Mix_PlayChannel(-1, shootingsound, 0);
            SDL_RenderPresent(m_renderer);
            SDL_Delay(10);
            paiin += 1;


        } else if (mode == 21) { //game
//            int toopnamorde = 0 ;
            moder = 21;
            if (abstime % 40 == 0)
                timed--;

            if (
                    mode6check(toops, mode
                    ) == 0) {
                mode = 6;
                replaceNthStringInCSV("scoretimed.txt", shomarekarbari,
                                      to_string(score)
                );

            }
            SDL_RenderClear(m_renderer);
            if (theme == 0) {
                bg2->

                        render();

                SDL_SetRenderDrawColor(m_renderer,
                                       90, 90, 100, 255);
                SDL_RenderDrawLine(m_renderer,
                                   260, 0, 260, 800);
                SDL_RenderDrawLine(m_renderer,
                                   760, 0, 760, 800);
            }
            if (theme == 1) {
                bg1->

                        render();

                SDL_SetRenderDrawColor(m_renderer,
                                       220, 220, 140, 255);
                SDL_RenderDrawLine(m_renderer,
                                   260, 0, 260, 800);
                SDL_RenderDrawLine(m_renderer,
                                   760, 0, 760, 800);
            }

/*------------------------------hadaf giri-----------------------------------*/


            SDL_GetMouseState(&xmouse, &ymouse
            );
            xymouse = {double(xmouse), double(ymouse)};
//SDL_SetRenderDrawColor(m_renderer, 100, 10, 80, 255);
            khatchin(m_renderer, vasat, xymouse, toops, r
            );
/* ---------------------------------partab tup-------------------------------- */
            if (partabi1.rang_toop == -1)
                partabi1.
                        rang_toop = random_partabi_color(toops, smax);
            if (partabi1.rang_toop == 0) {
                angleimage(redball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            }
            if (partabi1.rang_toop == 1)
                angleimage(blueball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == 2)
                angleimage(yellowball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == 3)
                angleimage(greenball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == 4)
                angleimage(purpleball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == -10)
                angleimage(bomb,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == -20)
                angleimage(rangi,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi2.rang_toop == -1)
                partabi2.
                        rang_toop = random_partabi_color(toops, smax);
            if (partabi2.rang_toop == 0) {
                angleimage(redball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            }
            if (partabi2.rang_toop == 1)
                angleimage(blueball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            if (partabi2.rang_toop == 2)
                angleimage(yellowball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            if (partabi2.rang_toop == 3)
                angleimage(greenball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            if (partabi2.rang_toop == 4)
                angleimage(purpleball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);


            if (
                    partab && firstpress
                    ) {
                int speedx = v * (xmouse0 - 500) /
                             sqrt((750 - ymouse0) * (750 - ymouse0) +
                                  (xmouse0 - 500) * (xmouse0 - 500));
                partabi1.center.
                        y = 750 - v * (750 - ymouse0) * time /
                                  sqrt((750 - ymouse0) * (750 - ymouse0) +
                                       (xmouse0 - 500) * (xmouse0 - 500));
                if (partabi1.center.x < 260 + r) {
                    brkhdv = 1;
                    partabi1.center.
                            x = 260 + r + 5;
                    brkhdvc++;

                }
                if (partabi1.center.x > 720 + r) {
                    brkhdv = 2;

                    partabi1.center.
                            x = 720 + r - 5;
                    brkhdvc++;
                }
                if (brkhdv == 0) {

                    partabi1.center.
                            x = 500 + v * (xmouse0 - 500) * time /
                                      sqrt((750 - ymouse0) * (750 - ymouse0) +
                                           (xmouse0 - 500) * (xmouse0 - 500));
                }
                if (brkhdv == 2) {
                    speedx *= -1;
                    if (brkhdvc % 2 == 1)
                        speedx *= -1;
                    partabi1.center.x +=
                            speedx;
                }
                if (brkhdv == 1) {
                    speedx *= -1;
                    if (brkhdvc % 2 == 1)
                        speedx *= -1;
                    partabi1.center.x +=
                            speedx;
                }

                if (partabi1.rang_toop == 0) {
                    angleimage(redball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                }
                if (partabi1.rang_toop == 1)
                    angleimage(blueball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == 2)
                    angleimage(yellowball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == 3)
                    angleimage(greenball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == 4)
                    angleimage(purpleball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == -10)
                    angleimage(bomb,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == -20)
                    angleimage(rangi,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                time += 1;
            }


            for (
                    int i = 0;
                    i < 1200; i++) {
                if (
                        int(toops[i]
                                    .center.y - r) >= -2 * r) {
                    if (toops[i].rang_toop == 0) {
                        angleimage(redball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    }
                    if (toops[i].rang_toop == 1)
                        angleimage(blueball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 2)
                        angleimage(yellowball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 3)
                        angleimage(greenball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 4)
                        angleimage(purpleball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                }
// -2 nmide tabamun
                if (toops[i].rang_toop == -2)
                    angleimage(sangball,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
                if (toops[i].rang_toop == 6)
                    angleimage(greenpurple,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
                if (toops[i].rang_toop == 7)
                    angleimage(purpleblue,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
                if (toops[i].rang_toop == 8)
                    angleimage(yellowred,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
            }
            int smax = -1;
            for (
                    int i = 0;
                    i < 1200; i++) {
                if (toops[i].rang_toop != -1 && i > smax) {
                    smax = i;
                }
            }
            int s = 0;
            if (
                    barkhord(toops, partabi1
                    ) || partabi1.center.y <= toops[0].center.y) {
                toop select = toops[0];
                barkhord_first = true;
                partab = false;
                for (
                        int i = 0;
                        i < 1200; i++) {
                    if (
                            distance(toops[i]
                                             .center, partabi1.center) <
                            distance(select
                                             .center, partabi1.center) &&
                            toops[i].rang_toop == -1) {
                        select = toops[i];
                        s = i;
                    }

                }
                toops[s].
                        rang_toop = partabi1.rang_toop;
                toops[s].
                        hazf = true;

                int teddhazf = 0;
                for (
                        int i = 0;
                        i < 1200; i++) {
                    if (toops[i].rang_toop != -1 && i > smax) {
                        smax = i;
                    }
                }

                if (toops[s].rang_toop == -10) {
                    anbomb(toops[s].center.x, toops[s].center.y, 4 * r + 5);
                    toops[s].rang_toop = -1;
                    toops[s].locked = false;
                    for (int i = 0; i < smax; ++i) {
                        if (distance(toops[s].center, toops[i].center) < 4 * r + 5) {
                            toops[i].rang_toop = -1;
                            toops[i].locked = false;
                        }
                    }
                }
                if (toops[s].rang_toop == -20) {
                    toops[s].rang_toop = -1;
                    for (int i = 0; i < smax; ++i) {
                        if (distance(toops[s].center, toops[i].center) < 4 * r + 5) {
                            toops[i].rang_toop = -1;
                            toops[i].locked = false;
                        }
                    }
                }
                hazf_check(toops, smax
                                  + 1, s, vpayin);
                for (
                        int i = 0;
                        i <=
                        smax;
                        i++) {
                    if (toops[i].hazf) {
                        teddhazf++;
//                        cout << "a" << i << "a";
//                        return 0;
                    }
                }
                if (teddhazf > 2) {
                    score += (
                                     log(teddhazf)
                                     / log(3) * 50) *
                             sqrt(timed);
                    cout << score <<
                         endl;
//                    cout << teddhazf << "s";
                    for (
                            int i = smax;
                            i >= 0; i--) {
                        if (toops[i].hazf) {
                            toops[i].
                                    rang_toop = -1;
                            toops[i].locked = false;
                            toopbekhor(toops[i].center.x, toops[i].center.y, r, 109, 243, 255);
                            toops[i].
                                    hazf = false;
                        }
                    }

                } else {
                    for (
                            int i = 0;
                            i <=
                            smax;
                            ++i) {

                        toops[i].
                                hazf = false;
                    }
                }
                partabi1.
                        rang_toop = partabi2.rang_toop;
                partabi2.
                        rang_toop = -1;
                time = 0;
                firstpress = false;
                partab = false;
                barkhord_first = false;
                partabi1.
                        center = {500 - r, 750 - r};
//                cout << "plpp";
                brkhdv = 0;
            }

            for (
                    int i = 0;
                    i < 12; ++i) {
                if (toops[i].rang_toop > -1)
                    toops[i].
                            connected = true;
                else
                    toops[i].
                            connected = false;
            }
//            toops[s].connected = true;
            for (
                    int i = 12;
                    i <=
                    smax;
                    ++i) {
                bool vasl = false;
                for (
                        int j = 0;
                        j < i;
                        ++j) {

//                    if (i == s) {
//                        cout << i << ":" << j << toops[j].connected << ' ' << distance(toops[i].center, toops[j].center)
//                             << ' '
//                             << toops[i].rang_toop << '\n';
//                    }
                    if ((toops[j].rang_toop != -1 && toops[j].
                            connected &&
                         distance(toops[i].center, toops[j].center)
                         <= 2 * r + 1) || i == s) {
                        vasl = true;
//                        cout << 2;
                    }
                    if (
                            vasl && toops[i]
                                            .rang_toop != -1) {
                        toops[i].
                                connected = true;
//                        cout << 3;
                    }
                }
//                cout << "\n";
            }
            for (
                    int i = smax;
                    i >= 0; --i) {
                bool vasl = false;
                for (
                        int j = smax;
                        j >
                        i;
                        --j) {

//                    if (i == s) {
//                        cout << i << ":" << j << toops[j].connected << ' ' << distance(toops[i].center, toops[j].center)
//                             << ' '
//                             << toops[i].rang_toop << '\n';
//                    }
                    if ((toops[j].rang_toop != -1 && toops[j].
                            connected &&
                         distance(toops[i].center, toops[j].center)
                         <= 2 * r + 1) || i == s) {
                        vasl = true;
//                        cout << 2;
                    }
                    if (
                            vasl && toops[i]
                                            .rang_toop != -1) {
                        toops[i].
                                connected = true;
//                        cout << 3;
                    }
                }
//                cout << "\n";
            }
            for (
                    int i = 12;
                    i <=
                    smax;
                    ++i) {
                bool vasl = false;
                for (
                        int j = 0;
                        j < i;
                        ++j) {

//                    if (i == s) {
//                        cout << i << ":" << j << toops[j].connected << ' ' << distance(toops[i].center, toops[j].center)
//                             << ' '
//                             << toops[i].rang_toop << '\n';
//                    }
                    if ((toops[j].rang_toop != -1 && toops[j].
                            connected &&
                         distance(toops[i].center, toops[j].center)
                         <= 2 * r + 1) || i == s) {
                        vasl = true;
//                        cout << 2;
                    }
                    if (
                            vasl && toops[i]
                                            .rang_toop != -1) {
                        toops[i].
                                connected = true;
//                        cout << 3;
                    }
                }
//                cout << "\n";
            }
            for (
                    int i = 0;
                    i < 1200; ++i) {
                if (!toops[i].
                        connected && toops[i]
                                             .rang_toop != -1) {
                    toops[i].
                            rang_toop = -1;
                    toops[i].locked = false;
                    cout << ' ' << i << ' ' << toops[i].hazf << ' ' << toops[i].connected << ' ';
                }
            }
            for (
                    int i = 0;
                    i < 1200; ++i) {
                toops[i].
                        connected = false;

            }

            if (event) {

//                if (e->type == SDL_QUIT) {
//                    quit = true;
//                } else
                if (e->type == SDL_MOUSEBUTTONDOWN && !firstpress) {


                    xmouse0 = xmouse, ymouse0 = ymouse;
                    partab = true;
                    firstpress = true;

                }
            }
/*--------paiin oomadan---------*/
            if (vpayin == 100 && !sabttime) {
                t0 = abstime;
                sabttime = true;
            }
            if (abstime == t0 + 300 && sabttime) {
                vpayin = 8;
                sabttime = false;
            }
            if (vpayin == 100) {
                t0 = abstime;
            }
            if (abstime > (t0 + 200))
                vpayin = 8;

            for (
                    int i = 0;
                    i < 1200; ++i) {
                if (toops[smax].center.y <= 690 &&
                    int(paiin)
                    % vpayin == 1)
                    toops[i].center.y += 1;
            }
            if (toops[smax].center.y > 690 || timed == 0) {
                mode = 8;
            }
            if (theme == 0)
                angleimage(pin_cannon,
                           400, 650,
                           200,
                           200, 45 * -1 *
                                atan2(xymouse
                                              .x - 500, xymouse.y - 800) / atan(1) + 115);
            else
                angleimage(pin_cannon2,
                           400, 650,
                           200,
                           200, 45 * -1 *
                                atan2(xymouse
                                              .x - 500, xymouse.y - 800) / atan(1) + 115);
            betterText(m_renderer, to_string(score),
                       10, 10, 30, "");
            betterText(m_renderer, to_string(timed),
                       800, 10, 60, "");
            lock_render(toops, lock
            );
            clock_render(toops, clock
            );
            SDL_RenderPresent(m_renderer);
            SDL_Delay(10);
            paiin += 1;

        } else if (mode == 22) { //game
//            int toopnamorde = 0 ;
            moder = 22;
            if (abstime % 40 == 0)
                timed--;

            if (
                    mode6check(toops, mode
                    ) == 0) {
                mode = 6;
                replaceNthStringInCSV("scoreinf.txt", shomarekarbari,
                                      to_string(score)
                );

            }
            SDL_RenderClear(m_renderer);
            if (theme == 0) {
                bg2->

                        render();

                SDL_SetRenderDrawColor(m_renderer,
                                       90, 90, 100, 255);
                SDL_RenderDrawLine(m_renderer,
                                   260, 0, 260, 800);
                SDL_RenderDrawLine(m_renderer,
                                   760, 0, 760, 800);
            }
            if (theme == 1) {
                bg1->

                        render();

                SDL_SetRenderDrawColor(m_renderer,
                                       220, 220, 140, 255);
                SDL_RenderDrawLine(m_renderer,
                                   260, 0, 260, 800);
                SDL_RenderDrawLine(m_renderer,
                                   760, 0, 760, 800);
            }

/*------------------------------hadaf giri-----------------------------------*/


            SDL_GetMouseState(&xmouse, &ymouse
            );
            xymouse = {double(xmouse), double(ymouse)};
//SDL_SetRenderDrawColor(m_renderer, 100, 10, 80, 255);
            khatchin(m_renderer, vasat, xymouse, toops, r
            );

/* ---------------------------------partab tup-------------------------------- */
            if (partabi1.rang_toop == -1)
                partabi1.
                        rang_toop = random_partabi_color(toops, smax);
            if (partabi1.rang_toop == 0) {
                angleimage(redball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            }
            if (partabi1.rang_toop == 1)
                angleimage(blueball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == 2)
                angleimage(yellowball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == 3)
                angleimage(greenball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == 4)
                angleimage(purpleball,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == -10)
                angleimage(bomb,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == -20)
                angleimage(rangi,
                           int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi2.rang_toop == -1)
                partabi2.
                        rang_toop = random_partabi_color(toops, smax);
            if (partabi2.rang_toop == 0) {
                angleimage(redball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            }
            if (partabi2.rang_toop == 1)
                angleimage(blueball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            if (partabi2.rang_toop == 2)
                angleimage(yellowball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            if (partabi2.rang_toop == 3)
                angleimage(greenball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            if (partabi2.rang_toop == 4)
                angleimage(purpleball,
                           int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);


            if (
                    partab && firstpress
                    ) {
                int speedx = v * (xmouse0 - 500) /
                             sqrt((750 - ymouse0) * (750 - ymouse0) +
                                  (xmouse0 - 500) * (xmouse0 - 500));
                partabi1.center.
                        y = 750 - v * (750 - ymouse0) * time /
                                  sqrt((750 - ymouse0) * (750 - ymouse0) +
                                       (xmouse0 - 500) * (xmouse0 - 500));
                if (partabi1.center.x < 260 + r) {
                    brkhdv = 1;
                    partabi1.center.
                            x = 260 + r + 5;
                    brkhdvc++;

                }
                if (partabi1.center.x > 720 + r) {
                    brkhdv = 2;

                    partabi1.center.
                            x = 720 + r - 5;
                    brkhdvc++;
                }
                if (brkhdv == 0) {

                    partabi1.center.
                            x = 500 + v * (xmouse0 - 500) * time /
                                      sqrt((750 - ymouse0) * (750 - ymouse0) +
                                           (xmouse0 - 500) * (xmouse0 - 500));
                }
                if (brkhdv == 2) {
                    speedx *= -1;
                    if (brkhdvc % 2 == 1)
                        speedx *= -1;
                    partabi1.center.x +=
                            speedx;
                }
                if (brkhdv == 1) {
                    speedx *= -1;
                    if (brkhdvc % 2 == 1)
                        speedx *= -1;
                    partabi1.center.x +=
                            speedx;
                }

                if (partabi1.rang_toop == 0) {
                    angleimage(redball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                }
                if (partabi1.rang_toop == 1)
                    angleimage(blueball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == 2)
                    angleimage(yellowball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == 3)
                    angleimage(greenball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == 4)
                    angleimage(purpleball,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == -10)
                    angleimage(bomb,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == -20)
                    angleimage(rangi,
                               int(partabi1
                                           .center.x - r),
                               int(partabi1
                                           .center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                time += 1;
            }


            for (
                    int i = 0;
                    i < 1200; i++) {
                if (
                        int(toops[i]
                                    .center.y - r) >= -2 * r) {
                    if (toops[i].rang_toop == 0) {
                        angleimage(redball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    }
                    if (toops[i].rang_toop == 1)
                        angleimage(blueball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 2)
                        angleimage(yellowball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 3)
                        angleimage(greenball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 4)
                        angleimage(purpleball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                }
// -2 nmide tabamun
                if (toops[i].rang_toop == -2)
                    angleimage(sangball,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
                if (toops[i].rang_toop == 6)
                    angleimage(greenpurple,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
                if (toops[i].rang_toop == 7)
                    angleimage(purpleblue,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
                if (toops[i].rang_toop == 8)
                    angleimage(yellowred,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
            }
            int smax = -1;
            for (
                    int i = 0;
                    i < 1200; i++) {
                if (toops[i].rang_toop != -1 && i > smax) {
                    smax = i;
                }
            }
            int s = 0;
            if (
                    barkhord(toops, partabi1
                    ) || partabi1.center.y <= toops[0].center.y) {
                toop select = toops[0];
                barkhord_first = true;
                partab = false;
                for (
                        int i = 0;
                        i < 1200; i++) {
                    if (
                            distance(toops[i]
                                             .center, partabi1.center) <
                            distance(select
                                             .center, partabi1.center) &&
                            toops[i].rang_toop == -1) {
                        select = toops[i];
                        s = i;
                    }

                }

                toops[s].
                        rang_toop = partabi1.rang_toop;
                toops[s].
                        hazf = true;

                int teddhazf = 0;
                for (
                        int i = 0;
                        i < 1200; i++) {
                    if (toops[i].rang_toop != -1 && i > smax) {
                        smax = i;
                    }
                }

                if (toops[s].rang_toop == -10) {
                    anbomb(toops[s].center.x, toops[s].center.y, 4 * r + 5);
                    toops[s].rang_toop = -1;
                    toops[s].locked = false;
                    for (int i = 0; i < smax; ++i) {
                        if (distance(toops[s].center, toops[i].center) < 4 * r + 5) {
                            toops[i].rang_toop = -1;
                            toops[i].locked = false;
                        }
                    }
                }
                if (toops[s].rang_toop == -20) {
                    toops[s].rang_toop = -1;
                    toops[s].locked = false;
                    for (int i = 0; i < smax; ++i) {
                        if (distance(toops[s].center, toops[i].center) < 4 * r + 5) {
                            toops[i].rang_toop = -1;
                            toops[i].locked = false;

                        }
                    }
                }
                hazf_check(toops, smax
                                  + 1, s, vpayin);
                for (
                        int i = 0;
                        i <=
                        smax;
                        i++) {
                    if (toops[i].hazf) {
                        teddhazf++;
//                        cout << "a" << i << "a";
//                        return 0;
                    }
                }
                if (teddhazf > 2) {
                    score +=
                            log(teddhazf)
                            / log(3) * 50;
                    cout << score <<
                         endl;
//                    cout << teddhazf << "s";
                    for (
                            int i = smax;
                            i >= 0; i--) {
                        if (toops[i].hazf) {
                            toops[i].
                                    rang_toop = -1;
                            toops[i].locked = false;
                            toopbekhor(toops[i].center.x, toops[i].center.y, r, 109, 243, 255);
                            toops[i].
                                    hazf = false;
                        }
                    }

                } else {
                    for (
                            int i = 0;
                            i <=
                            smax;
                            ++i) {

                        toops[i].
                                hazf = false;
                    }
                }
                partabi1.
                        rang_toop = partabi2.rang_toop;
                partabi2.
                        rang_toop = -1;
                time = 0;
                firstpress = false;
                partab = false;
                barkhord_first = false;
                partabi1.
                        center = {500 - r, 750 - r};
//                cout << "plpp";
                brkhdv = 0;
            }

            for (
                    int i = 0;
                    i < 12; ++i) {
                if (toops[i].rang_toop > -1)
                    toops[i].
                            connected = true;
                else
                    toops[i].
                            connected = false;
            }
//            toops[s].connected = true;
            for (
                    int i = 12;
                    i <=
                    smax;
                    ++i) {
                bool vasl = false;
                for (
                        int j = 0;
                        j < i;
                        ++j) {

//                    if (i == s) {
//                        cout << i << ":" << j << toops[j].connected << ' ' << distance(toops[i].center, toops[j].center)
//                             << ' '
//                             << toops[i].rang_toop << '\n';
//                    }
                    if ((toops[j].rang_toop != -1 && toops[j].
                            connected &&
                         distance(toops[i].center, toops[j].center)
                         <= 2 * r + 1) || i == s) {
                        vasl = true;
//                        cout << 2;
                    }
                    if (
                            vasl && toops[i]
                                            .rang_toop != -1) {
                        toops[i].
                                connected = true;
//                        cout << 3;
                    }
                }
//                cout << "\n";
            }
            for (
                    int i = smax;
                    i >= 0; --i) {
                bool vasl = false;
                for (
                        int j = smax;
                        j >
                        i;
                        --j) {

//                    if (i == s) {
//                        cout << i << ":" << j << toops[j].connected << ' ' << distance(toops[i].center, toops[j].center)
//                             << ' '
//                             << toops[i].rang_toop << '\n';
//                    }
                    if ((toops[j].rang_toop != -1 && toops[j].
                            connected &&
                         distance(toops[i].center, toops[j].center)
                         <= 2 * r + 1) || i == s) {
                        vasl = true;
//                        cout << 2;
                    }
                    if (
                            vasl && toops[i]
                                            .rang_toop != -1) {
                        toops[i].
                                connected = true;
//                        cout << 3;
                    }
                }
//                cout << "\n";
            }
            for (
                    int i = 12;
                    i <=
                    smax;
                    ++i) {
                bool vasl = false;
                for (
                        int j = 0;
                        j < i;
                        ++j) {

//                    if (i == s) {
//                        cout << i << ":" << j << toops[j].connected << ' ' << distance(toops[i].center, toops[j].center)
//                             << ' '
//                             << toops[i].rang_toop << '\n';
//                    }
                    if ((toops[j].rang_toop != -1 && toops[j].
                            connected &&
                         distance(toops[i].center, toops[j].center)
                         <= 2 * r + 1) || i == s) {
                        vasl = true;
//                        cout << 2;
                    }
                    if (
                            vasl && toops[i]
                                            .rang_toop != -1) {
                        toops[i].
                                connected = true;
//                        cout << 3;
                    }
                }
//                cout << "\n";
            }
            for (
                    int i = 0;
                    i < 1200; ++i) {
                if (!toops[i].
                        connected && toops[i]
                                             .rang_toop != -1) {
                    toops[i].
                            rang_toop = -1;
                    toops[i].locked = false;
                    cout << ' ' << i << ' ' << toops[i].hazf << ' ' << toops[i].connected << ' ';
                }
            }
            for (
                    int i = 0;
                    i < 1200; ++i) {
                toops[i].
                        connected = false;

            }

            if (event) {

//                if (e->type == SDL_QUIT) {
//                    quit = true;
//                } else
                if (e->type == SDL_MOUSEBUTTONDOWN && !firstpress) {


                    xmouse0 = xmouse, ymouse0 = ymouse;
                    partab = true;
                    firstpress = true;

                }
            }
/*--------paiin oomadan---------*/
            if (vpayin == 100 && !sabttime) {
                t0 = abstime;
                sabttime = true;
            }
            if (abstime == t0 + 300 && sabttime) {
                vpayin = 8;
                sabttime = false;
            }
            if (vpayin == 100) {
                t0 = abstime;
            }
            if (abstime > (t0 + 200))
                vpayin = 8;
            for (
                    int i = 0;
                    i < 1200; ++i) {
                if (toops[smax].center.y <= 690 &&
                    int(paiin)
                    % vpayin == 1)
                    toops[i].center.y += 1;
            }
            if (toops[smax].center.y > 690) {
                mode = 8;
            }
            if (toops[0].center.y >= 0) {
                balabar(toops, smax
                );
                cout << "mobinaa";
            }
            if (theme == 0)
                angleimage(pin_cannon,
                           400, 650,
                           200,
                           200, 45 * -1 *
                                atan2(xymouse
                                              .x - 500, xymouse.y - 800) / atan(1) + 115);
            else
                angleimage(pin_cannon2,
                           400, 650,
                           200,
                           200, 45 * -1 *
                                atan2(xymouse
                                              .x - 500, xymouse.y - 800) / atan(1) + 115);
            betterText(m_renderer, to_string(score),
                       10, 10, 30, "");
//            betterText(m_renderer, to_string(timed), 800, 10, 60, "");
            lock_render(toops, lock
            );
            clock_render(toops, clock
            );
            SDL_RenderPresent(m_renderer);
            SDL_Delay(10);
            paiin += 1;

        }

//        cout << distance(toops[155].center, toops[143].center) << ' ';
        SDL_RenderClear(m_renderer);
        if (event) {
            switch (e->type) {
                case SDL_KEYDOWN:

// Handle key press
                    if (e->key.keysym.sym == SDLK_w) {

                        int channel = Mix_PlayChannel(-1, btnsound, 0);
                        play = false;
                        ahng++;
                        cout <<
                             ahng;
                        play = false;
                        Mix_FreeMusic(m1);
                        Mix_FreeMusic(m2);
                        Mix_FreeMusic(m3);
                        Mix_FreeMusic(m4);
                        Mix_FreeMusic(m5);

                        m1 = Mix_LoadMUS("music/m1.mp3");
                        m2 = Mix_LoadMUS("music/m2.mp3");
                        m3 = Mix_LoadMUS("music/m3.mp3");
                        m4 = Mix_LoadMUS("music/m4.mp3");
                        m5 = Mix_LoadMUS("music/m5.mp3");

                    }
                    if (e->key.keysym.sym == SDLK_a) {

                        partabi2.rang_toop = partabi1.rang_toop;
                        if (readNthValue("powercount.txt", shomarekarbari) > 0) {
                            partabi1.rang_toop = -20;
                            replaceNthStringInCSV("powercount.txt", shomarekarbari,
                                                  to_string(readNthValue("powercount.txt", shomarekarbari) - 1));
                        }
                    }
                    if (e->key.keysym.sym == SDLK_s) {
                        partabi2.rang_toop = partabi1.rang_toop;
                        if (readNthValue("powercount.txt", shomarekarbari) > 0) {
                            partabi1.rang_toop = -10;
                            replaceNthStringInCSV("powercount.txt", shomarekarbari,
                                                  to_string(readNthValue("powercount.txt", shomarekarbari) - 1));
                        }
                    }
                    if (e->key.keysym.sym == SDLK_d) {
                        if (readNthValue("powercount.txt", shomarekarbari) > 0) {
                            laser = true;
                            replaceNthStringInCSV("powercount.txt", shomarekarbari,
                                                  to_string(readNthValue("powercount.txt", shomarekarbari) - 1));
                        }
                        cout << "s";
//                        partabi1.rang_toop = -1;
//                        partabi1.rang_toop = -1;
                    }

                    if (e->key.keysym.sym ==
                        SDLK_ESCAPE && (mode
                                        == 20 || mode == 21 || mode == 22 || mode == 8)) {

                        int channel = Mix_PlayChannel(-1, btnsound, 0);

                        mode = 7;
//                        SDL_RenderClear(m_renderer);
                    }
                    if (e->key.keysym.sym == SDLK_SPACE && !partab) {

                        int channel = Mix_PlayChannel(-1, btnsound, 0);

                        toop happy;
                        happy.
                                rang_toop = partabi1.rang_toop;
                        partabi1.
                                rang_toop = partabi2.rang_toop;
                        partabi2.
                                rang_toop = happy.rang_toop;

                    }
                    break;

                case SDL_QUIT :
                    quit = true;
                    if (score != 0) {
                        if (moder == 20) {
                            if ((score) > readNthValue("scorenormal.txt", shomarekarbari))
                                replaceNthStringInCSV("scorenormal.txt", shomarekarbari, to_string(score));
                        }
                        if (moder == 21) {
//                                replaceNthStringInCSV("scoretimed.txt", shomarekarbari,
//                                                      to_string(score)
//                            );
                            if ((score) > readNthValue("scoretimed.txt", shomarekarbari))
                                replaceNthStringInCSV("scoretimed.txt", shomarekarbari, to_string(score));
                        }
                        if (moder == 22) {
//                                replaceNthStringInCSV("scoreinf.txt", shomarekarbari,
//                                                      to_string(score)
//                                );
                            if ((score) > readNthValue("scoreinf.txt", shomarekarbari))
                                replaceNthStringInCSV("scoreinf.txt", shomarekarbari, to_string(score));
                        }
                        score = 0;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (laser) {
                        laserkey = true;
                        partabi1.rang_toop = -1;
                        cout << "k";
                        if (laser && laserkey) {

//                            SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
//                            SDL_RenderDrawLine(m_renderer, 500 - r, 750 - r, xymouse.x, xymouse.y);
                            //SDL_RenderPresent(m_renderer);
                            for (int i = 0; i < 1200; i++) {
                                if (faselekhat({500 - r, 750 - r}, xymouse, toops, i) <= r + 5) {
                                    toops[i].rang_toop = -1;
                                    toops[i].locked = false;
                                    toops[i].time_effect = false;
                                    score += 1;

                                }
                            }
                        }

                        laser = false;
                        laserkey = false;

                    }
                    if (mode < 20)
                        int channel = Mix_PlayChannel(-1, btnsound, 0);


                    if (xymouse.x > 880 && xymouse.x < 940 && xymouse.y > 40 &&
                        xymouse.y < 100) {
                        switch (mode) {
                            case 1:
                                mode = 0;
                                break;
                            case 2:
                                mode = 1;
                                break;
                            case 3:
                                mode = 2;
                                reset = true;
//                                replaceNthStringInCSV("scorenormal.txt", shomarekarbari, to_string(score));
                                score = 0;
                                break;
                            case 4:
                                mode = 2;
                                reset = true;
//                                replaceNthStringInCSV("scorenormal.txt", shomarekarbari, to_string(score));
                                score = 0;
                                break;
                            case 5:
                                mode = 2;
                                reset = true;
//                                replaceNthStringInCSV("scorenormal.txt", shomarekarbari, to_string(score));
                                score = 0;
                                break;
                            case 7:
                                mode = moder;
                        }
                    }
                    if (xymouse.x > 0 && xymouse.x < w && xymouse.y < h &&
                        xymouse.y > 0 && mode == 6) {
                        mode = 2;
                        reset = true;
//                        replaceNthStringInCSV("scorenormal.txt", shomarekarbari, to_string(score));
                        if (score != 0) {
                            if (moder == 20) {
                                if ((score) > readNthValue("scorenormal.txt", shomarekarbari))
                                    replaceNthStringInCSV("scorenormal.txt", shomarekarbari, to_string(score));
                            }
                            if (moder == 21) {
//                                replaceNthStringInCSV("scoretimed.txt", shomarekarbari,
//                                                      to_string(score)
//                                );
                                if ((score) > readNthValue("scoretimed.txt", shomarekarbari))
                                    replaceNthStringInCSV("scoretimed.txt", shomarekarbari, to_string(score));
                            }
                            if (moder == 22) {
//                                replaceNthStringInCSV("scoreinf.txt", shomarekarbari,
//                                                      to_string(score)
//                                );
                                if ((score) > readNthValue("scoreinf.txt", shomarekarbari))
                                    replaceNthStringInCSV("scoreinf.txt", shomarekarbari, to_string(score));
                            }
                            score = 0;
                        }
                    }
                    if (mode == 5 || mode == 7) {
                        if (xymouse.x > 370 && xymouse.x < 440 && xymouse.y > 370 &&
                            xymouse.y < 440) {
                            play_stop++;
                            if (play_stop % 2 == 1) {
                                Mix_PauseMusic();

                            }
                            if (play_stop % 2 == 0) {
                                Mix_ResumeMusic();

                            }
                        }
                        if (xymouse.x > 553 && xymouse.x < 623 && xymouse.y > 370 &&
                            xymouse.y < 440) {
                            ahng++;
                            play = false;
                            Mix_FreeMusic(m1);
                            Mix_FreeMusic(m2);
                            Mix_FreeMusic(m3);
                            Mix_FreeMusic(m4);
                            Mix_FreeMusic(m5);
// Load your music again before playing
                            m1 = Mix_LoadMUS("music/m1.mp3");
                            m2 = Mix_LoadMUS("music/m2.mp3");
                            m3 = Mix_LoadMUS("music/m3.mp3");
                            m4 = Mix_LoadMUS("music/m4.mp3");
                            m5 = Mix_LoadMUS("music/m5.mp3");
                        }

                        if (xymouse.x > 700 && xymouse.x < 770 && xymouse.y > 70 &&
                            xymouse.y < 140) {
                            if (volumn < 118)
                                volumn += 10;

                        }
                        if (xymouse.x > 700 && xymouse.x < 770 && xymouse.y > 200 &&
                            xymouse.y < 270) {
                            if (volumn > 10)
                                volumn -= 10;

                        }
                        if (xymouse.x > 300 && xymouse.x < 500 && xymouse.y > 600 &&
                            xymouse.y < 780) {
                            theme = 0;
                        }
                        if (xymouse.x > 550 && xymouse.x < 750 && xymouse.y > 600 &&
                            xymouse.y < 780) {
                            theme = 1;
                        }

                    }
                    if (mode == 7) {
                        if (xymouse.x > (w / 3 + 70) && xymouse.
                                x<(w / 3 + 270) && xymouse.y>(h
                                                              / 16 + 50) &&
                            xymouse.y < (h / 16 + 250))
                            mode = 2;
                        reset = true;
                        if (score != 0) {
                            if (moder == 20) {
                                if (((score)) > (readNthValue("scorenormal.txt", shomarekarbari)))
                                    replaceNthStringInCSV("scorenormal.txt", shomarekarbari, to_string(score));
                            }
                            if (moder == 21) {
//                                replaceNthStringInCSV("scoretimed.txt", shomarekarbari,
//                                                      to_string(score)
//                                );
                                if ((score) > readNthValue("scoretimed.txt", shomarekarbari))
                                    replaceNthStringInCSV("scoretimed.txt", shomarekarbari, to_string(score));
                            }
                            if (moder == 22) {
//                                replaceNthStringInCSV("scoreinf.txt", shomarekarbari,
//                                                      to_string(score)
//                                );
                                if ((score) > readNthValue("scoreinf.txt", shomarekarbari))
                                    replaceNthStringInCSV("scoreinf.txt", shomarekarbari, to_string(score));
                            }
                            score = 0;
                        }
                        score = 0;
                    }
            }
        }

    }
// angleimage(backbtn, 880, 40, 60, 60, 0);
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);

    SDL_Quit();

    return 0;
}

void window_color(SDL_Renderer *Renderer, int R, int G, int B) {
    SDL_SetRenderDrawColor(Renderer, R, G, B, 255);
    SDL_RenderClear(Renderer);

}

void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian) {
    if (fill_boolian == 1)
        filledEllipseRGBA(Renderer, x, y, Radius1, Radius2, R, G, B, 255);
    if (fill_boolian == 0)
        ellipseRGBA(Renderer, x, y, Radius1, Radius2, R, G, B, 255);
}

int weighted_random(int choices, int *weights) {
    int total_weight = 0;
    for (int i = 0; i < choices; i++) {
        total_weight += weights[i];
    }

    int random_number = rand() % total_weight;

    int i = 0;
    while (i < choices) {
        if (random_number < weights[i]) {
            return i;
        }

        random_number -= weights[i];
        i++;
    }

    return rand() % choices;
}

double distance(point pain, point ahhh) {
    double d;
    d = sqrt((pain.x - ahhh.x) * (pain.x - ahhh.x) + (pain.y - ahhh.y) * (pain.y - ahhh.y));
    return d;
}

bool barkhord(toop *toops, toop partabi1) {
    for (int i = 0; i < 1200; i++) {
        if (toops[i].rang_toop != -1) {
            if (distance(partabi1.center, toops[i].center) <= 2 * r) {
                toops[i].locked = false;
                if (toops[i].time_effect) {
                    for (int t = 0; t < 600; t++) {
                        vpayin = 100;
                    }
                    toops[i].time_effect = false;
                    vpayin = 8;
                }

                return true;
            }
        }
    }
    return false;
}

void khatchin(SDL_Renderer *Renderer, point avl, point dvm, toop *toops, double r) {
    bool barkhord = false;
    point khatchin = avl;
    double t = 0;
    while (!barkhord && t < 600) {

        t += 8;
        for (int i = 0; i < 1200; i++) {
            if (toops[i].rang_toop != -1) {
                if (distance(khatchin, toops[i].center) <= r) {
                    barkhord = true;

                }
            }
        }
        khatchin.y = avl.y - 3 * (avl.y - dvm.y) * t /
                             sqrt((avl.y - dvm.y) * (avl.y - dvm.y) + (dvm.x - avl.x) * (dvm.x - avl.x));
        khatchin.x = avl.x + 3 * (dvm.x - avl.x) * t /
                             sqrt((avl.y - dvm.y) * (avl.y - dvm.y) + (dvm.x - avl.x) * (dvm.x - avl.x));
        while (khatchin.x > 760 || khatchin.x < 260) {
            if (khatchin.x > 760) {
                khatchin.x = 2 * 760 - khatchin.x;
            }
            if (khatchin.x < 260) {
                khatchin.x = 2 * 260 - khatchin.x;
            }
        }
        ellipse(Renderer, int(khatchin.x), int(khatchin.y), 2, 2, 255, 255, 255, 1);

    }
}


string image_toop(int color) {
    if (color == -2)
        return "sangball";
    else if (color == 1)
        return "blueball";
    else if (color == 2)
        return "redball";
    else if (color == 3)
        return "purpleball";
    else if (color == 4)
        return "greenball";
    else if (color == 5)
        return "yellowball";
    return "";

}

void angleimage(SDL_Texture *text, int x, int y, int w, int h, double alfa) {
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopyEx(m_renderer, text, NULL, &rect, alfa, NULL, SDL_FLIP_NONE);
}

int random_partabi_color(toop *toops, int smax) {
    int color_weight[6] = {0, 0, 0, 0, 0, 0};
    if (smax == 1200) {
        for (int i = 0; i <= smax; i++) {
            if (toops[i].rang_toop != -1)
                color_weight[toops[i].rang_toop]++;
        }
//        return -10;//bomb check
//        return -20;//chand rang check
    } else {
        for (int i = smax - 100; i <= smax; i++) {
            if (toops[i].rang_toop != -1)
                color_weight[toops[i].rang_toop]++;
        }
    }
    int ted0 = 0;
    for (int i = 0; i < 6; ++i) {
        if (color_weight[i] == 0)
            ted0++;
    }
    if (ted0 == 6)
        return 0;
    return weighted_random(5, color_weight);
}

bool okrang(int a, int b) {
    if ((a == b || (a == 6 && (b == 3 || b == 4)) || (a == 7 && (b == 4 || b == 1)) ||
         (a == 8 && (b == 0 || b == 2))) ||
        (a == b || (b == 6 && (a == 3 || a == 4)) || (b == 7 && (a == 4 || a == 1)) ||
         (b == 8 && (a == 0 || a == 2))) || a == -20 || b == -20) {
        cout << endl << a << " " << b;
        return true;
    }
    return false;
}

void hazf_check(toop *toops, int smax, int s, int &vpyin) {
    for (int i = 0; i < 1200; ++i) {
        if (toops[i].locked) {
            toops[i].hazf = false;
        }
    }
    for (int i = smax; i >= 0; --i) {
        for (int j = smax; j >= 0; --j) {

            if (toops[i].rang_toop != -1 && toops[i].rang_toop != -2/*na sangi bashe na -1*/ &&
                distance(toops[i].center, toops[j].center) <= 2 * r + 1 && toops[i].hazf &&
                ((okrang(toops[i].rang_toop, toops[j].rang_toop) && !toops[j].locked) /*toop sangi bashe*/)) {
                toops[j].hazf = true;
                if (toops[j].time_effect) {
                    vpyin = 100;
                }
//                cout << j << " fwfw3fw3f" << endl;
            }
        }
    }


    for (int i = 0; i <= smax + 1; ++i) {
        for (int j = 0; j <= smax + 1; ++j) {

            if (toops[i].rang_toop != -1 && toops[i].rang_toop != -2/*na sangi bashe na -1*/ &&
                distance(toops[i].center, toops[j].center) <= 2 * r + 1 && toops[i].hazf &&
                ((okrang(toops[i].rang_toop, toops[j].rang_toop) && !toops[j].locked) /*toop sangi bashe*/) &&
                (i != j)) {
                toops[j].hazf = true;
                if (toops[j].time_effect) {
                    vpyin = 100;
                }
//                cout << j << " hauhuiwgwg" << endl;
            }
        }
    }
    for (int i = smax; i >= 0; --i) {
        for (int j = smax; j >= 0; --j) {

            if (toops[i].rang_toop != -1 && toops[i].rang_toop != -2/*na sangi bashe na -1*/ &&
                distance(toops[i].center, toops[j].center) <= 2 * r + 1 && toops[i].hazf &&
                ((okrang(toops[i].rang_toop, toops[j].rang_toop) && !toops[j].locked) /*toop sangi bashe*/)) {
                toops[j].hazf = true;
                if (toops[j].time_effect) {
                    vpyin = 100;
                }
//                cout << j << " fwfw3fw3f" << endl;
            }
        }
    }
}

void sang_random(int k, toop *toops, int max) {
    for (int i = 0; i < k; ++i) {
        int r = (rand()) % (max - 11) + 11;
        toops[r].rang_toop = -2;

    }
    for (int i = 0; i < 4; ++i) {
        int r = (rand()) % (max - 11) + 11;
        toops[r].locked = true;
    }
//    if (abstime % 10 == 0) {
//        for (int j = 0; j < 1200; j++) {
//            toops[j].time_effect =
//                    false;
//        }
//        for (int i = 0; i < 5; ++i) {
//            int h = (rand()) % (max - 11) + 11;
//            toops[h].time_effect = true;
//        }
//    }
    for (int i = 0; i < 5; ++i) {
        int r = (rand()) % (max);
        toops[r].rang_toop = 6;
    }
    for (int i = 0; i < rand() % 5; ++i) {
        int r = (rand()) % (max);
        toops[r].rang_toop = 7;
    }
    for (int i = 0; i < rand() % 5; ++i) {
        int r = (rand()) % (max);
        toops[r].rang_toop = 8;
    }

}

void toop_rang(int tedad, toop *toops) {
    toops[0].rang_toop = rand() % 5;
    for (int i = 1; i < tedad; i++) {
        if (i / 12 % 2 == 0) {
            if (i > 12) {
                toops[i].hamsaye_colour[0] = toops[i - 12].rang_toop;
                toops[i].hamsaye_colour[5] = toops[i - 13].rang_toop;
            }
            if (i < 216 - 12) {
                toops[i].hamsaye_colour[2] = toops[i + 12].rang_toop;
                toops[i].hamsaye_colour[3] = toops[i + 11].rang_toop;
            }
            if (i % 12 < 11)
                toops[i].hamsaye_colour[1] = toops[i + 1].rang_toop;
            if (i % 12 > 1)
                toops[i].hamsaye_colour[4] = toops[i - 1].rang_toop;
            int weight[6] = {1, 1, 1, 1, 1, 1};
            for (int j = 0; j < 6; ++j) {
                weight[toops[i].hamsaye_colour[j]]++;
            }
            toops[i].rang_toop = weighted_random(5, weight);
        }
        if (i / 12 % 2 == 1) {
            if (i > 12) {
                toops[i].hamsaye_colour[5] = toops[i - 12].rang_toop;
                toops[i].hamsaye_colour[0] = toops[i - 11].rang_toop;
            }
            if (i < 216 - 12) {
                toops[i].hamsaye_colour[2] = toops[i + 12].rang_toop;
                toops[i].hamsaye_colour[3] = toops[i + 13].rang_toop;
            }
            if (i % 12 < 11)
                toops[i].hamsaye_colour[1] = toops[i + 1].rang_toop;
            if (i % 12 > 0)
                toops[i].hamsaye_colour[4] = toops[i - 1].rang_toop;
            int weight[6] = {1, 1, 1, 1, 1, 1};
            for (int j = 0; j < 6; ++j) {
                weight[toops[i].hamsaye_colour[j]]++;
            }
            toops[i].rang_toop = weighted_random(5, weight);
        }
    }
    sang_random(6, toops, 144);
//    clock_random(toops, 144);
}

string TextBox(SDL_Renderer *Renderer, int x_position, int y_position, int theme, image *bg_menu, image *bg_menu2,
               SDL_Texture *backbtn, SDL_Texture *textbox) {
    bool caps_lock = false;
    int A = 0.5;
    int W = 1000;
    int H = 800;
    bool q = false;
    char ch = 0;
    SDL_Event *e1 = new SDL_Event();
    string name = "";
    char lastkey;
    name = name.substr(0, name.length() - 1);
    while (!q) {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);
        if (theme == 0) {
            bg_menu->render();
            // boxRGBA(m_renderer, 880, 40, 940, 100, 255, 255, 0, 255);
            angleimage(backbtn, 880, 40, 60, 60, 0);
            angleimage(textbox, 350, 200, 300, 175, 0);
            angleimage(textbox, 350, 380, 300, 175, 0);
        }
        if (theme == 1) {
            bg_menu2->render();
            angleimage(backbtn, 880, 40, 60, 60, 0);
            angleimage(textbox, 350, 200, 300, 175, 0);
            angleimage(textbox, 350, 380, 300, 175, 0);
        }
//        SDL_RenderPresent(m_renderer);
//        SDL_Delay(10);
//        SDL_RenderClear(m_renderer);
        ch = 0;
        if (SDL_PollEvent(e1) && (e1->type == SDL_KEYUP || e1->type == SDL_MOUSEBUTTONDOWN)) {
            if (e1->type == SDL_MOUSEBUTTONDOWN)
                q = true;
            switch (e1->key.keysym.sym) {
                case SDLK_SPACE:
                    //quit = true;
                    ch = ' ';
                    break;
                case SDLK_RETURN:
                    q = true;
                    break;
                case SDLK_KP_ENTER:
                    q = true;
                    break;
                case SDLK_TAB:
                    q = true;
                    break;
                case SDLK_CAPSLOCK:
                    ch = 0;
                    caps_lock = !caps_lock;
                    break;
                case SDLK_BACKSPACE:
                    ch = 0;
                    if (name.length() != 0) {
                        betterText(Renderer, name.c_str(), x_position, y_position, 50, "calibrib");

                        name.pop_back();
                    }
                    break;
                default :
                    if (e1->key.keysym.sym != SDLK_UP && e1->key.keysym.sym != SDLK_DOWN &&
                        e1->key.keysym.sym != SDLK_LEFT && e1->key.keysym.sym != SDLK_RIGHT)
                        ch = e1->key.keysym.sym;
                    break;
            }
            if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == ' ') ||
                (ch >= '0' && ch <= '9') && name.length() < 25 && !q && ch != 0) {
                if (caps_lock == 1 && ch != ' ' && (ch < '0' || ch > '9'))
                    name += ch + 'A' - 'a';
                else
                    name += ch;
            }
            if (name != "" && !q)
                betterText(Renderer, name.c_str(), x_position, y_position, 50, "calibrib");
        }
        betterText(Renderer, name.c_str(), x_position, y_position, 50, "calibrib");
//        betterText(m_renderer, username, 335, 230, 60, "");
//        betterText(m_renderer, password, 335, 410, 60, "");
        SDL_RenderPresent(Renderer);
        lastkey = e1->key.keysym.sym;
    }
//    betterText(m_renderer, username, 335, 230, 60, "");
//    betterText(m_renderer, password, 335, 410, 60, "");
    string output;
    if (lastkey == name[name.length() - 1])
        output = name.substr(0, name.length() - 1);
    else
        output = name;

    return output;
}

void betterText(SDL_Renderer *renderer, string S, int x, int y, int size, string Font) {

    if (!TTF_WasInit())
        TTF_Init();
    string fontDir = "Modak-Regular.ttf"; // should have fonts as .ttf files in ./fonts folder from project path
    TTF_Font *font = TTF_OpenFont(fontDir.c_str(), size);
    SDL_Color color = {0, 0, 0, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, S.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect;
    int h, w;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    rect.h = h;
    rect.w = w;
    rect.x = x;
    rect.y = y;
    //cout << h << " " << w << endl;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    // free resources
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

}

int mode6check(toop *toops, int mode) {
    int toopnamorde = 0;
    for (int i = 0; i < 1200; ++i) {
        if (toops[i].rang_toop != -1)
            toopnamorde++;
    }
    return toopnamorde;

}

int readNthValue(const string &filepath, int n) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filepath << endl;
        return -1;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<string> tokens;

        while (getline(ss, value, ',')) {
            tokens.push_back(value);
        }

        if (n >= 0 && n < tokens.size()) {
            file.close();
            return stoi(tokens[n]);
        }
    }

    file.close();
    return -1;
}

string readNthValuestr(const string &filepath, int n) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filepath << endl;
        return "";
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<string> tokens;

        while (getline(ss, value, ',')) {
            tokens.push_back(value);
        }

        if (n >= 0 && n < tokens.size()) {
            file.close();
            return (tokens[n]);
        }
    }

    file.close();
    return "";
}

bool searchStringInCSV(const string &filename, const string &target) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string cell;

        while (getline(iss, cell, ',')) {
            if (cell == target) {
                file.close();
                return true;
            }
        }
    }

    file.close();
    return false;
}

int findIndexInCSV(const string &filePath, const string &targetString) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return -1; // Return -1 to indicate an error
    }

    string line;
    getline(file, line); // Read the header line

    istringstream headerStream(line);
    string column;
    int index = 0;

    while (getline(headerStream, column, ',')) {
        if (column == targetString) {
            file.close(); // Close the file after finding the index
            return index;
        }
        ++index;
    }

    file.close(); // Close the file if the target string is not found
    return -1; // Return -1 to indicate that the target string is not in the CSV
}


void replaceNthStringInCSV(const string &filePath, int n, const string &replacement) {
    fstream file(filePath, ios::in | ios::out);
    n++;
    if (file.is_open()) {
        vector<string> tokens;
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string token;

            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() >= n) {
                tokens[n - 1] = replacement;  // Assuming 1-based index
                file.seekp(0, ios::cur);  // Move the write pointer to the current position
                file.seekg(0, ios::beg);  // Move the read pointer to the beginning

                for (const auto &t: tokens) {
                    file << t;
                    file << ',';

                }
                break;  // Stop after processing the first line
            }
            tokens.clear();
        }

        file.close();

    } else {
        cerr << "Error opening the file.\n";
    }
}

void balabar(toop *toops, int smax) {

    for (int i = 0; i <= 1200; ++i) {
        toops[i].center.y -= (2 * r * sqrt(3));
    }
    for (int i = 1176; i >= 0; i--) {
        toops[i + 24].rang_toop = toops[i].rang_toop;
    }

//    toop_rang(12, toops);
    toops[0].rang_toop = rand() % 5;
    for (int i = 1; i < 24; i++) {
        if (i / 12 % 2 == 0) {
            if (i > 12) {
                toops[i].hamsaye_colour[0] = toops[i - 12].rang_toop;
                toops[i].hamsaye_colour[5] = toops[i - 13].rang_toop;
            }
            if (i < 216 - 12) {
                toops[i].hamsaye_colour[2] = toops[i + 12].rang_toop;
                toops[i].hamsaye_colour[3] = toops[i + 11].rang_toop;
            }
            if (i % 12 < 11)
                toops[i].hamsaye_colour[1] = toops[i + 1].rang_toop;
            if (i % 12 > 1)
                toops[i].hamsaye_colour[4] = toops[i - 1].rang_toop;
            int weight[6] = {1, 1, 1, 1, 1, 1};
            for (int j = 0; j < 6; ++j) {
                weight[toops[i].hamsaye_colour[j]]++;
            }
            toops[i].rang_toop = weighted_random(5, weight);
        }
        if (i / 12 % 2 == 1) {
            if (i > 12) {
                toops[i].hamsaye_colour[5] = toops[i - 12].rang_toop;
                toops[i].hamsaye_colour[0] = toops[i - 11].rang_toop;
            }
            if (i < 216 - 12) {
                toops[i].hamsaye_colour[2] = toops[i + 12].rang_toop;
                toops[i].hamsaye_colour[3] = toops[i + 13].rang_toop;
            }
            if (i % 12 < 11)
                toops[i].hamsaye_colour[1] = toops[i + 1].rang_toop;
            if (i % 12 > 0)
                toops[i].hamsaye_colour[4] = toops[i - 1].rang_toop;
            int weight[6] = {1, 1, 1, 1, 1, 1};
            for (int j = 0; j < 6; ++j) {
                weight[toops[i].hamsaye_colour[j]]++;
            }
            toops[i].rang_toop = weighted_random(5, weight);
        }
    }
}

void lock_render(toop *toops, SDL_Texture *lock) {
    for (int i = 0; i < 1200; ++i) {
        if (toops[i].locked && toops[i].rang_toop != -1) {
            angleimage(lock, int(toops[i].center.x - r), int(toops[i].center.y - r),
                       int(2 * r),
                       int(2 * r), 0);
        }
    }
}

void clock_render(toop *toops, SDL_Texture *clock) {
    clock_random(toops, 144);
    for (int i = 0; i < 1200; ++i) {
        if (toops[i].time_effect && toops[i].rang_toop != -1) {
            angleimage(clock, int(toops[i].center.x - r), int(toops[i].center.y - r),
                       int(2 * r),
                       int(2 * r), 0);
        }
    }
}

void oftadan(toop *toops, int ball, SDL_Texture *redball, SDL_Texture *blueball, SDL_Texture *purpleball,
             SDL_Texture *yellowball, SDL_Texture *sangball, SDL_Texture *greenball, image *bg1, image *bg2,
             int theme) {
    toop hero;
    hero = toops[ball];
    toops[ball].rang_toop = -1;


    for (int i = 0; i < 800; ++i) {
        SDL_RenderClear(m_renderer);
        if (theme == 0) {
            bg2->render();
        }
        if (theme == 1) {
            bg1->render();
        }
        SDL_Delay(5);
        hero.center.y -= 1;
        if (hero.rang_toop == 0) {
            angleimage(redball, int(toops[i].center.x - r), int(toops[i].center.y - r),
                       int(2 * r),
                       int(2 * r), 0);
        }
        if (hero.rang_toop == 1)
            angleimage(blueball, int(toops[i].center.x - r), int(toops[i].center.y - r),
                       int(2 * r),
                       int(2 * r), 0);
        if (hero.rang_toop == 2)
            angleimage(yellowball, int(toops[i].center.x - r), int(toops[i].center.y - r),
                       int(2 * r),
                       int(2 * r), 0);
        if (hero.rang_toop == 3)
            angleimage(greenball, int(toops[i].center.x - r), int(toops[i].center.y - r),
                       int(2 * r),
                       int(2 * r), 0);
        if (hero.rang_toop == 4)
            angleimage(purpleball, int(toops[i].center.x - r), int(toops[i].center.y - r),
                       int(2 * r),
                       int(2 * r), 0);
        if (hero.rang_toop == -2)
            angleimage(sangball, int(toops[i].center.x - r), int(toops[i].center.y - r),
                       int(2 * r),
                       int(2 * r), 0);
        SDL_RenderPresent(m_renderer);
    }

}

void toops_reset(toop *toops) {
    int q = 0;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (i % 2 == 0) {
                toops[q] = {{260 + r * (2 * j + 1), r * (1 + i * sqrt(3)) - 300}};
            } else {
                toops[q] = {{260 + 2 * r * (1 + j), r * (1 + sqrt(3) * (1 + (i - 1))) - 300}};
            }
            q++;
        }
    }
    toop_rang(144, toops);
}


double faselekhat(point avl, point akhr, toop *toops, int i) {

    double a;

    double b;
    a = (akhr.x - avl.x) / (akhr.y - avl.y);
    b = (akhr.y * avl.x - avl.y * akhr.x) / (akhr.y - avl.y);

    return fabs(toops[i].center.x - a * toops[i].center.y - b) / sqrt(1 + a * a);

}

void fall(toop *toops, int i, SDL_Texture *redball, SDL_Texture *blueball, SDL_Texture *purpleball,
          SDL_Texture *yellowball, SDL_Texture *sangball, SDL_Texture *greenball, SDL_Texture *greenpurple,
          SDL_Texture *purpleblue, SDL_Texture *yellowred, image *bg1, image *bg2,
          int theme) {
    toop fall;
    if (!toops[i].connected) {
        fall = toops[i];
        toops[i].rang_toop = -1;
        toops[i].locked = false;
        while (fall.center.y < 750 - r) {
            SDL_RenderClear(m_renderer);
            if (theme == 0) {
                bg2->render();
            }
            if (theme == 1) {
                bg1->render();
            }
            fall.center.y += (1200 / i) * (1200 / i);


            if (fall.rang_toop == 0) {
                angleimage(redball,
                           int(fall
                                       .center.x - r),
                           int(fall
                                       .center.y - r),
                           int(2 * r),
                           int(2 * r), 0);
            }
            if (fall.rang_toop == 1)
                angleimage(blueball,
                           int(fall
                                       .center.x - r),
                           int(fall
                                       .center.y - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (fall.rang_toop == 2)
                angleimage(yellowball,
                           int(fall
                                       .center.x - r),
                           int(fall
                                       .center.y - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (fall.rang_toop == 3)
                angleimage(greenball,
                           int(fall
                                       .center.x - r),
                           int(fall
                                       .center.y - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (fall.rang_toop == 4)
                angleimage(purpleball,
                           int(fall
                                       .center.x - r),
                           int(fall
                                       .center.y - r),
                           int(2 * r),
                           int(2 * r), 0);

// -2 nmide tabamun
            if (fall.rang_toop == -2)
                angleimage(sangball,
                           int(fall
                                       .center.x - r),
                           int(fall
                                       .center.y - r), int(2 * r),
                           int(2 * r),
                           0);
            if (fall.rang_toop == 6)
                angleimage(greenpurple,
                           int(fall
                                       .center.x - r),
                           int(fall
                                       .center.y - r), int(2 * r),
                           int(2 * r),
                           0);
            if (fall.rang_toop == 7)
                angleimage(purpleblue,
                           int(fall
                                       .center.x - r),
                           int(fall
                                       .center.y - r), int(2 * r),
                           int(2 * r),
                           0);
            if (fall.rang_toop == 8)
                angleimage(yellowred,
                           int(fall
                                       .center.x - r),
                           int(fall
                                       .center.y - r), int(2 * r),
                           int(2 * r),
                           0);
            for (
                    int i = 0;
                    i < 1200; i++) {
                if (
                        int(toops[i]
                                    .center.y - r) >= -2 * r) {
                    if (toops[i].rang_toop == 0) {
                        angleimage(redball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    }
                    if (toops[i].rang_toop == 1)
                        angleimage(blueball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 2)
                        angleimage(yellowball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 3)
                        angleimage(greenball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 4)
                        angleimage(purpleball,
                                   int(toops[i]
                                               .center.x - r),
                                   int(toops[i]
                                               .center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                }
// -2 nmide tabamun
                if (toops[i].rang_toop == -2)
                    angleimage(sangball,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
                if (toops[i].rang_toop == 6)
                    angleimage(greenpurple,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
                if (toops[i].rang_toop == 7)
                    angleimage(purpleblue,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
                if (toops[i].rang_toop == 8)
                    angleimage(yellowred,
                               int(toops[i]
                                           .center.x - r),
                               int(toops[i]
                                           .center.y - r), int(2 * r),
                               int(2 * r),
                               0);
            }
            SDL_Delay(5);
            SDL_RenderPresent(m_renderer);
        }
    }

}

void anbomb(int xm2, int ym2, int rm2) {
    double z;

    for (int i = 1; i <= 2 * rm2; i++) {

        z = 1.0 * i / (2 * rm2);
        if (z >= 0.9) {
            filledCircleRGBA(m_renderer, xm2, ym2, i / 2, 100, 0, 0, 3);
            SDL_Delay(2);

        }
        aacircleRGBA(m_renderer, xm2, ym2, i / 2, 255 - z * z * 150, 220 - (z) * 220,
                     200 - sqrt(z) * 200,
                     255 - z * 50);
        //SDL_Delay(1);
        if (i % 15 == 0) {
            filledCircleRGBA(m_renderer, xm2, ym2, i / 2, 255, 200, 200, 10);
        }
        if (i % 5 == 0) {
            SDL_Delay(z * 10);
            SDL_RenderPresent(m_renderer);
        }
    }


}

void toopbekhor(int xm2, int ym2, int rm2, int R, int G, int B) {
    double z;
    for (int i = 0; i < 2 * rm2; i++) {
        z = 1.0 * i / (2 * rm2);
        aacircleRGBA(m_renderer, xm2, ym2, 1.0 * rm2 * (1 - z), R, G, B, 255);

        if (i % 15 == 0)
            SDL_RenderPresent(m_renderer);
    }

}

void clock_random(toop *toops, int max) {
    if (abstime % 700 == 350) {
        for (int i = 0; i < 1200; i++) {
            toops[i].time_effect = false;
        }
    }
    if (abstime % 700 == 0) {
        for (int i = 0; i < 10; ++i) {
            int h = (rand()) % (max - 11) + 11;
            toops[h].time_effect = true;
        }
    }
}


