#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>
#include <SDL2/SDL_ttf.h>

#ifdef TA_LINUX_BUILD
#include <SDL2/SDL2_gfxPrimitives.h>
#else

#include <SDL2/SDL2_gfx.h>

#endif

#include <iostream>
#include <string>
#include <cmath>
//#include <SDL2/SDL_mixer.h>

using namespace std;

SDL_Window *m_window;
SDL_Renderer *m_renderer;

double r = 20, v = 7, paiin = 0;
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
    bool hazf = false;
    bool connected = false;
    int rang_toop = -1, hamsaye_colour[6];
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


/* -------------------------------------functions--------------------------------*/
string image_toop(int color);

bool barkhord(toop *toops, toop partabi1);

void window_color(SDL_Renderer *Renderer, int R, int G, int B);

void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian);

int weighted_random(int choices, int *weights);

double distance(point pain, point ahhh);

void khatchin(SDL_Renderer *Renderer, point avl, point dvm, toop *toops, double r);

int random_partabi_color(toop *toops);

void angleimage(SDL_Texture *text, int x, int y, int w, int h, double alfa);

void hazf_check(toop *toops, int smax, int s);


int main(int argc, char *argv[]) {
    srand(time(NULL));

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

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
    /*-------------------------------Ax ha---------------------------- */
    image *bg = new image("pics/GameBG.png", 0, 0, 1.0, m_renderer);
    image *bg2 = new image("pics/bg2.png", 0, 0, 1.0, m_renderer);
    SDL_Texture *redball = IMG_LoadTexture(m_renderer, "pics/red.png");
    SDL_Texture *blueball = IMG_LoadTexture(m_renderer, "pics/blue.png");
    SDL_Texture *yellowball = IMG_LoadTexture(m_renderer, "pics/yellow.png");
    SDL_Texture *greenball = IMG_LoadTexture(m_renderer, "pics/green.png");
    SDL_Texture *sangball = IMG_LoadTexture(m_renderer, "pics/sang.png");
    SDL_Texture *purpleball = IMG_LoadTexture(m_renderer, "pics/purple.png");
    /*-----------------------------------------------------------------------*/

    toop partabi1, partabi2;

//    partabi1.center.x = 500;
//    partabi1.center.y =750;
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
    toops[0].rang_toop = rand() % 5;
    for (int i = 1; i < 216; i++) {
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


    SDL_Event *e = new SDL_Event();
    bool quit = false;
    int xmouse, ymouse;
    bool partab = false;
    int xmouse0, ymouse0;
    bool firstpress = false;
    bool barkhord_first = false;
    point xymouse;
    point vasat = {500.0, 750.0};
    int mode = 20;
    while (!quit) {

        if (mode == 20) { //game

            SDL_RenderClear(m_renderer);
            bg2->render();


            /*------------------------------hadaf giri-----------------------------------*/


            SDL_GetMouseState(&xmouse, &ymouse);
            xymouse = {double(xmouse), double(ymouse)};
            //SDL_SetRenderDrawColor(m_renderer, 100, 10, 80, 255);
            khatchin(m_renderer, vasat, xymouse, toops, r);

            /* ---------------------------------partab tup-------------------------------- */
            if (partabi1.rang_toop == -1)
                partabi1.rang_toop = random_partabi_color(toops);
            if (partabi1.rang_toop == 0) {
                angleimage(redball, int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            }
            if (partabi1.rang_toop == 1)
                angleimage(blueball, int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == 2)
                angleimage(yellowball, int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == 3)
                angleimage(greenball, int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi1.rang_toop == 4)
                angleimage(purpleball, int(500 - r), int(750 - r),
                           int(2 * r),
                           int(2 * r), 0);
            if (partabi2.rang_toop == -1)
                partabi2.rang_toop = random_partabi_color(toops);
            if (partabi2.rang_toop == 0) {
                angleimage(redball, int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            }
            if (partabi2.rang_toop == 1)
                angleimage(blueball, int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            if (partabi2.rang_toop == 2)
                angleimage(yellowball, int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            if (partabi2.rang_toop == 3)
                angleimage(greenball, int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);
            if (partabi2.rang_toop == 4)
                angleimage(purpleball, int(450 - r), int(780 - r),
                           int(3.0 / 2 * r),
                           int(3.0 / 2 * r), 0);


            if (partab && firstpress) {
                int speedx = v * (xmouse0 - 500) /
                             sqrt((750 - ymouse0) * (750 - ymouse0) +
                                  (xmouse0 - 500) * (xmouse0 - 500));
                partabi1.center.y = 750 - v * (750 - ymouse0) * time /
                                          sqrt((750 - ymouse0) * (750 - ymouse0) +
                                               (xmouse0 - 500) * (xmouse0 - 500));
                if (partabi1.center.x < 260 + r) {
                    brkhdv = 1;
                    partabi1.center.x = 260 + r + 5;
                    brkhdvc++;

                }
                if (partabi1.center.x > 720 + r) {
                    brkhdv = 2;

                    partabi1.center.x = 720 + r - 5;
                    brkhdvc++;
                }
                if (brkhdv == 0) {

                    partabi1.center.x = 500 + v * (xmouse0 - 500) * time /
                                              sqrt((750 - ymouse0) * (750 - ymouse0) +
                                                   (xmouse0 - 500) * (xmouse0 - 500));
                }
                if (brkhdv == 2) {
                    speedx *= -1;
                    if (brkhdvc % 2 == 1)
                        speedx *= -1;
                    partabi1.center.x += speedx;
                }
                if (brkhdv == 1) {
                    speedx *= -1;
                    if (brkhdvc % 2 == 1)
                        speedx *= -1;
                    partabi1.center.x += speedx;
                }

                if (partabi1.rang_toop == 0) {
                    angleimage(redball, int(partabi1.center.x - r), int(partabi1.center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                }
                if (partabi1.rang_toop == 1)
                    angleimage(blueball, int(partabi1.center.x - r), int(partabi1.center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == 2)
                    angleimage(yellowball, int(partabi1.center.x - r), int(partabi1.center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == 3)
                    angleimage(greenball, int(partabi1.center.x - r), int(partabi1.center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                if (partabi1.rang_toop == 4)
                    angleimage(purpleball, int(partabi1.center.x - r), int(partabi1.center.y - r),
                               int(2 * r),
                               int(2 * r), 0);
                time += 1;
            }


            for (int i = 0; i < 1200; i++) {
                if (int(toops[i].center.y - r) >= -2 * r) {
                    if (toops[i].rang_toop == 0) {
                        angleimage(redball, int(toops[i].center.x - r), int(toops[i].center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    }
                    if (toops[i].rang_toop == 1)
                        angleimage(blueball, int(toops[i].center.x - r), int(toops[i].center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 2)
                        angleimage(yellowball, int(toops[i].center.x - r), int(toops[i].center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 3)
                        angleimage(greenball, int(toops[i].center.x - r), int(toops[i].center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                    if (toops[i].rang_toop == 4)
                        angleimage(purpleball, int(toops[i].center.x - r), int(toops[i].center.y - r),
                                   int(2 * r),
                                   int(2 * r), 0);
                }
                // -2 nmide tabamun
                //            if (toops[i].rang_toop == -2)
                //                image_render(sangball, int(toops[i].center.x - r), int(toops[i].center.y - r), int(2 * r), int(2 * r),
                //                             0);
            }
            int smax = 0;
            for (int i = 0; i < 1200; i++) {
                if (toops[i].rang_toop != -1 && i > smax) {
                    smax = i;
                }
            }
            if (barkhord(toops, partabi1) || partabi1.center.y <= r) {
                toop select = toops[0];
                barkhord_first = true;
                int s = 0;
                partab = false;
                for (int i = 0; i < 1200; i++) {
                    if (distance(toops[i].center, partabi1.center) < distance(select.center, partabi1.center) &&
                        toops[i].rang_toop == -1) {
                        select = toops[i];
                        s = i;
                    }

                }
                toops[s].rang_toop = partabi1.rang_toop;
                toops[s].hazf = true;
                s = 0;

                int teddhazf = 0;
                for (int i = 0; i < 1200; i++) {
                    if (toops[i].rang_toop != -1 && i > smax) {
                        smax = i;
                    }
                }
                hazf_check(toops, smax + 1, s);
                for (int i = 0; i <= smax; i++) {
                    if (toops[i].hazf) {
                        teddhazf++;
//                        cout << "a" << i << "a";
//                        return 0;
                    }
                }
                if (teddhazf > 2) {
//                    cout << teddhazf << "s";
                    for (int i = smax; i >= 0; i--) {
                        if (toops[i].hazf) {
                            toops[i].rang_toop = -1;
                            toops[i].hazf = false;
                        }
                    }

                } else {
                    for (int i = 0; i <= smax; ++i) {

                        toops[i].hazf = false;
                    }
                }
                partabi1.rang_toop = partabi2.rang_toop;
                partabi2.rang_toop = -1;
                time = 0;
                firstpress = false;
                partab = false;
                barkhord_first = false;
                partabi1.center = {500 - r, 750 - r};
//                cout << "plpp";
                brkhdv = 0;
            }
            for (int i = 0; i < 12; ++i) {
                if (toops[i].rang_toop > -1)
                    toops[i].connected = true;
                else
                    toops[i].connected = false;
            }
            for (int i = 12; i < 1200; ++i) {
                bool vasl = false;
                for (int j = 0; j < i; ++j) {

                    if (toops[j].rang_toop != -1 && toops[j].connected &&
                        distance(toops[i].center, toops[j].center) <= 2 * r + 1) {
                        vasl = true;
//                        cout << 2;
                    }
                    if (vasl && toops[i].rang_toop != -1) {
                        toops[i].connected = true;
//                        cout << 3;
                    }
                }

            }
            for (int k = 1; k < 60; ++k) {
                for (int i = (k + 1) * 12 - 1; i >= k * 12; --i) {
                    bool vasl = false;
                    for (int j = 0; j <= i; ++j) {


                        if (toops[j].connected && distance(toops[i].center, toops[j].center) <= 2 * r + 1) {
                            vasl = true;
                        }
                        if (vasl && toops[i].rang_toop != -1)
                            toops[i].connected = true;
                    }

                }
            }

            for (int i = 0; i < 1200; ++i) {
                if (!toops[i].connected && toops[i].rang_toop != -1) {
                    toops[i].rang_toop = -1;
                    cout << ' ' << i << ' ';
                }
            }
            for (int i = 0; i < 1200; ++i) {
                toops[i].connected = false;

            }

            if (SDL_PollEvent(e)) {

                if (e->type == SDL_QUIT) {
                    quit = true;
                } else if (e->type == SDL_MOUSEBUTTONDOWN && !firstpress) {


                    xmouse0 = xmouse, ymouse0 = ymouse;
                    partab = true;
                    firstpress = true;

                }
            }
            /*--------paiin oomadan---------*/
            for (int i = 0; i < 1200; ++i) {
                if (toops[smax].center.y <= 690 && int(paiin) % 2 == 1)
                    toops[i].center.y += 1;
            }

            SDL_RenderPresent(m_renderer);
            SDL_Delay(10);
            SDL_RenderClear(m_renderer);
            paiin += 1;
        }
    }
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
    while (!barkhord && t < 320) {

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

int random_partabi_color(toop *toops) {
    int color_weight[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 1200; i++) {
        if (toops[i].rang_toop != -1)
            color_weight[toops[i].rang_toop]++;
    }
    return weighted_random(5, color_weight);
}

void hazf_check(toop *toops, int smax, int s) {
    for (int i = smax; i >= 0; --i) {
        for (int j = smax; j >= 0; --j) {

            if (toops[i].rang_toop >= 0/*na sangi bashe na -1*/ &&
                distance(toops[i].center, toops[j].center) <= 2 * r + 1 && toops[i].hazf &&
                ((toops[i].rang_toop == toops[j].rang_toop) /*toop sangi bashe*/)) {
                toops[j].hazf = true;
//                cout << j << " fwfw3fw3f" << endl;
            }
        }
    }


    for (int i = 0; i <= smax + 1; ++i) {
        for (int j = 0; j <= smax + 1; ++j) {

            if (toops[i].rang_toop >= 0/*na sangi bashe na -1*/ &&
                distance(toops[i].center, toops[j].center) <= 2 * r + 1 && toops[i].hazf &&
                ((toops[i].rang_toop == toops[j].rang_toop) /*toop sangi bashe*/) && (i != j)) {
                toops[j].hazf = true;
//                cout << j << " hauhuiwgwg" << endl;
            }
        }
    }
}


