/**
 * \file renderer.c
 * \brief File for every in game render.
 * \author Ayaden Hugo
 * \version 1.0
 * \date 31/03/2026
 * 
 */

#include "../lib/renderer.h"

void buttons_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH,
                    int img_stretchedW_game_res)
{
    int buttonW = 60;
    int buttonH = 60;
    int spacing = img_stretchedW_game_res / spacing_amount;
    int buttonWcamera = 860;
    int buttonHcamera = 60;
    int spacingcamera = 500;

    SDL_Rect btnCameras = {spacingcamera, windowH - 50, buttonWcamera, buttonHcamera};

    SDL_Rect btnPorteGauche = {spacing + camera_offset_x, windowH / 2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereGauche = {spacing + camera_offset_x, windowH / 2 + 10, buttonW, buttonH};
    SDL_Rect btnLumiereGeneral = {spacing + camera_offset_x, windowH / 2 + 160, buttonW, buttonH};
    SDL_Rect btnPorteDroite = {img_stretchedW_game_res - spacing - buttonW + camera_offset_x, windowH / 2 - buttonH - 10, buttonW, buttonH};
    SDL_Rect btnLumiereDroite = {img_stretchedW_game_res - spacing - buttonW + camera_offset_x, windowH / 2 + 10, buttonW, buttonH};

    drawButton(renderer, font, btnPorteGauche, porteGaucheActive, "DOOR");
    drawButton(renderer, font, btnPorteDroite, porteDroiteActive, "DOOR");
    drawButton(renderer, font, btnLumiereGauche, lumiereGaucheActive, "LIGHT");
    drawButton(renderer, font, btnLumiereDroite, lumiereDroiteActive, "LIGHT");
    drawButton(renderer, font, btnLumiereGeneral, boutonLumieres, "LIGHT_G");
    drawButton(renderer, font, btnCameras, moniteurCameras, "CAMERAS");
}

void camera_buttons_render(SDL_Renderer *renderer,
                           TTF_Font *font,
                           int windowW,
                           int windowH)
{

    int buttonW = 44;
    int buttonH = 27;

    /* PLACEMENT DES BOUTTONS DES CAMERAS (fastidieux) */

    //camera 1
    int buttonX1 = windowW-154+buttonW;
    int buttonY1 = windowH/2-54;

    //camera 2
    int buttonX2 = windowW-154+buttonW;
    int buttonY2 = windowH/2+55;

    //camera 3
    int buttonX3 = windowW-276+buttonW;
    int buttonY3 = windowH/2 + 1;

    //camera 4
    int buttonX4 = windowW-341+buttonW;
    int buttonY4 = windowH/2+10;

    //camera 5
    int buttonX5 = windowW-472+buttonW;
    int buttonY5 = windowH/2+55;

    //camera 6
    int buttonX6 = windowW-472+buttonW;
    int buttonY6 = windowH/2-54;

    //camera 7
    int buttonX7 = windowW-278+buttonW;
    int buttonY7= windowH/2-177;

    //camera 8
    int buttonX8 = windowW-452+buttonW;
    int buttonY8 = windowH/2-177;

    //camera 9
    int buttonX9 = windowW-341+buttonW;
    int buttonY9 = windowH/2+144;

    // toggle camera
    int buttonWcamera = 860;
    int buttonHcamera = 60;
    int spacingcamera = 500;


    SDL_Rect btnCameras = {spacingcamera, windowH -50, buttonWcamera, buttonHcamera};
    SDL_Rect btnCamera1 = {buttonX1, buttonY1, buttonW, buttonH};
    SDL_Rect btnCamera2 = {buttonX2, buttonY2, buttonW, buttonH};
    SDL_Rect btnCamera3 = {buttonX3, buttonY3, buttonW, buttonH};
    SDL_Rect btnCamera4 = {buttonX4, buttonY4, buttonW, buttonH};
    SDL_Rect btnCamera5 = {buttonX5, buttonY5, buttonW, buttonH};
    SDL_Rect btnCamera6 = {buttonX6, buttonY6, buttonW, buttonH};
    SDL_Rect btnCamera7 = {buttonX7, buttonY7, buttonW, buttonH};
    SDL_Rect btnCamera8 = {buttonX8, buttonY8, buttonW, buttonH};
    SDL_Rect btnCamera9 = {buttonX9, buttonY9, buttonW, buttonH};

    drawButton(renderer, font, btnCamera1, camera1on, " ");
    drawButton(renderer, font, btnCamera2, camera2on, " ");
    drawButton(renderer, font, btnCamera3, camera3on, " ");
    drawButton(renderer, font, btnCamera4, camera4on, " ");
    drawButton(renderer, font, btnCamera5, camera5on, " ");
    drawButton(renderer, font, btnCamera6, camera6on, " ");
    drawButton(renderer, font, btnCamera7, camera7on, " ");
    drawButton(renderer, font, btnCamera8, camera8on, " ");
    drawButton(renderer, font, btnCamera9, camera9on, " ");
    drawButton(renderer, font, btnCameras, moniteurCameras, "CAMERAS");
}

void renderCameraMap(SDL_Renderer *renderer)
{
    int buttonWcamera = 860;
    int buttonHcamera = 60;
    int spacingcamera = 500;

    SDL_Rect mapCamera = {spacingcamera, windowH / 2, buttonWcamera, buttonHcamera};

    drawCamera(renderer, mapCamera);
}

void battery_render(SDL_Renderer *renderer,
                    TTF_Font *font,
                    int windowW,
                    int windowH)
{
    const int batteryWidth = 150;
    const int batteryHeight = 40;
    const int capWidth = 10;
    const int margin = 20;

    int x = margin;
    int y = windowH - batteryHeight - margin;

    SDL_Rect batteryOutline = {x, y, batteryWidth, batteryHeight};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &batteryOutline);

    SDL_Rect batteryCap = {x + batteryWidth,
                           y + batteryHeight / 4,
                           capWidth,
                           batteryHeight / 2};
    SDL_RenderFillRect(renderer, &batteryCap);

    SDL_Rect batteryBar = {x, y,
                           (int)(batteryWidth * (battery / 100.0f)),
                           batteryHeight};

    SDL_Color batteryColor;

    if (battery > 50)
    {
        batteryColor.r = 0;
        batteryColor.g = 255;
        batteryColor.b = 0;
    }
    else
    {
        float ratio = battery / 50.0f;
        batteryColor.r = (Uint8)(255 * (1.0f - ratio));
        batteryColor.g = (Uint8)(255 * ratio);
        batteryColor.b = 0;
    }

    SDL_SetRenderDrawColor(renderer,
                           batteryColor.r,
                           batteryColor.g,
                           batteryColor.b,
                           255);

    SDL_RenderFillRect(renderer, &batteryBar);

    char text[20];
    sprintf(text, "%.0f%%", battery);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, white);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect textRect = {
        x + batteryWidth / 2 - surface->w / 2,
        y - surface->h - 5,
        surface->w,
        surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void render_game(SDL_Renderer *renderer,
                 TTF_Font *fontBattery,
                 TTF_Font *fontButtons,
                 SDL_Window *window,
                int img_stretchedW_game_res){

    SDL_GetWindowSize(window, &windowW, &windowH);

    battery_render(renderer, fontBattery, windowW, windowH);
    if (moniteurCameras == 0)
        buttons_render(renderer, fontButtons, windowW, windowH,img_stretchedW_game_res);
    else
    {
        camera_buttons_render(renderer, fontButtons, windowW, windowH);
        renderCameraMap(renderer);
    }
}

void affichage(camera_type *camera_type){
    if (moniteurCameras == 0)
    {
        *camera_type = GAME;
        if (battery <= 0)
        {
            background = BLACKOUT;
            change = FAUX;
            porteDroiteActive = FAUX;
            porteGaucheActive = FAUX;
            lumiereDroiteActive = FAUX;
            lumiereGaucheActive = FAUX;
            ouverture_porte_gauche(map, joueur);
            ouverture_porte_droite(map, joueur);
        }
        else if (battery > 0 && boutonLumieres)
        {
            background = BLACKOUT;
            change = FAUX;
            porteDroiteActive = FAUX;
            porteGaucheActive = FAUX;
            lumiereDroiteActive = FAUX;
            lumiereGaucheActive = FAUX;
            ouverture_porte_gauche(map, joueur);
            ouverture_porte_droite(map, joueur);
        }
        //LIGHT LEFT
        else if(!porteDroiteActive && !lumiereDroiteActive && !porteGaucheActive && lumiereGaucheActive){
            if(monster->num_camera == PORTE_BAS){
                background = R_D_OFF_LI_OFF_L_D_OFF_LI_ON_M;
            }
            else if(monster->num_camera == PORTE_BAS-1){
                background = R_D_OFF_LI_OFF_L_D_OFF_LI_ON_M_W;
            }
            else
            background = R_D_OFF_LI_OFF_L_D_OFF_LI_ON;
        }
         //DOOR RIGHT
        else if(porteDroiteActive && !lumiereDroiteActive && !porteGaucheActive && !lumiereGaucheActive){
            background = R_D_ON_LI_OFF_L_D_OFF_LI_OFF;
        }
        //DOOR LEFT
        else if(!porteDroiteActive && !lumiereDroiteActive && porteGaucheActive && !lumiereGaucheActive){
            background = R_D_OFF_LI_OFF_L_D_ON_LI_OFF;
        }
        //EVERYTHING
        else if(porteDroiteActive && lumiereDroiteActive && porteGaucheActive && lumiereGaucheActive){
            if(monster->num_camera == PORTE_HAUT-1){
               background = R_D_ON_LI_ON_L_D_ON_LI_ON_M_W_D;
            }
             else if(monster->num_camera == PORTE_BAS-1){
                background = R_D_ON_LI_ON_L_D_ON_LI_ON_M_W;
            }
            else 
                background = R_D_ON_LI_ON_L_D_ON_LI_ON;
        }
        //LIGHT RIGHT
        else if(!porteDroiteActive && lumiereDroiteActive && !porteGaucheActive && !lumiereGaucheActive){
            if(monster->num_camera == PORTE_HAUT){
                background = R_D_OFF_LI_ON_L_D_OFF_LI_OFF_M;
            }
            else if(monster->num_camera == PORTE_HAUT-1){
                background = R_D_OFF_LI_ON_L_D_OFF_LI_OFF_M_W;
            }
            else
               background = R_D_OFF_LI_ON_L_D_OFF_LI_OFF;
        }
        //LIGHT RIGHT LIGHT LEFT
         else if(!porteDroiteActive && lumiereDroiteActive && !porteGaucheActive && lumiereGaucheActive){
            if(monster->num_camera == PORTE_BAS-1){
                background = R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_W;
            }
            else if(monster->num_camera == PORTE_BAS){
                background = R_D_OFF_LI_ON_L_D_OFF_LI_ON_M;
            }
            else if(monster->num_camera == PORTE_HAUT-1){
                background = R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_W_D;
            }
            else if(monster->num_camera == PORTE_HAUT){
                background = R_D_OFF_LI_ON_L_D_OFF_LI_ON_M_D;
            }
            else 
                background = R_D_OFF_LI_ON_L_D_OFF_LI_ON;
        }
        //LIGHT LEFT DOOR LEFT
         else if(!porteDroiteActive && !lumiereDroiteActive && porteGaucheActive && lumiereGaucheActive){
            if(monster->num_camera == PORTE_BAS-1){
                background = R_D_OFF_LI_OFF_L_D_ON_LI_ON_M_W;
            }
            else
                background = R_D_OFF_LI_OFF_L_D_ON_LI_ON;
        }
        //LIGHT LEFT DOOR RIGHT
         else if(porteDroiteActive && !lumiereDroiteActive && !porteGaucheActive && lumiereGaucheActive){
             if(monster->num_camera == PORTE_BAS-1){
                background = R_D_ON_LI_OFF_L_D_OFF_LI_ON_M_W;
            }
            else if(monster->num_camera == PORTE_BAS){
                background = R_D_ON_LI_OFF_L_D_OFF_LI_ON_M;
            }
            else 
                background = R_D_ON_LI_OFF_L_D_OFF_LI_ON;
        }
        //LIGHT RIGHT DOOR LEFT
        else if(!porteDroiteActive && lumiereDroiteActive && porteGaucheActive && !lumiereGaucheActive){
            if(monster->num_camera == PORTE_HAUT){
                background = R_D_OFF_LI_ON_L_D_ON_LI_OFF_M;
            }
            else if(monster->num_camera == PORTE_HAUT-1){
                background = R_D_OFF_LI_ON_L_D_ON_LI_OFF_M_W_D;
            }
            else 
                background = R_D_OFF_LI_ON_L_D_ON_LI_OFF;
        }
        
        //LIGHT RIGHT LIGHT LEFT DOOR LEFT
         else if(!porteDroiteActive && lumiereDroiteActive && porteGaucheActive && lumiereGaucheActive){
            if(monster->num_camera == PORTE_HAUT){
                background = R_D_OFF_LI_ON_L_D_ON_LI_ON_M;
            }
            else if(monster->num_camera == PORTE_HAUT-1){
                background = R_D_OFF_LI_ON_L_D_ON_LI_ON_M_W_D;
            }
             else if(monster->num_camera == PORTE_BAS-1){
                background = R_D_OFF_LI_ON_L_D_ON_LI_ON_M_W;
            }
            else 
                background = R_D_OFF_LI_ON_L_D_ON_LI_ON;
        }
        
        //LIGHT RIGHT LIGHT LEFT DOOR RIGHT
         else if(porteDroiteActive && lumiereDroiteActive && !porteGaucheActive && lumiereGaucheActive){
            if(monster->num_camera == PORTE_HAUT-1){
                background = R_D_ON_LI_ON_L_D_OFF_LI_ON_M_W_D;
            }
            else if(monster->num_camera == PORTE_BAS){
                background = R_D_ON_LI_ON_L_D_OFF_LI_ON_M;
            }
             else if(monster->num_camera == PORTE_BAS-1){
                background = R_D_ON_LI_ON_L_D_OFF_LI_ON_M_W;
            }
            else 
                background = R_D_ON_LI_ON_L_D_OFF_LI_ON;
        }
        //LIGHT LEFT DOOR LEFT DOOR RIGHT
         else if(porteDroiteActive && !lumiereDroiteActive && porteGaucheActive && lumiereGaucheActive){
             if(monster->num_camera == PORTE_BAS-1){
                background = R_D_ON_LI_OFF_L_D_ON_LI_ON_M_W;
            }
            else 
                background = R_D_ON_LI_OFF_L_D_ON_LI_ON;
        }
        
        //DOOR RIGHT LIGHT RIGHT DOOR LEFT
        else if(porteDroiteActive && lumiereDroiteActive && porteGaucheActive && !lumiereGaucheActive){
            if(monster->num_camera == PORTE_HAUT-1){
                background = R_D_ON_LI_ON_L_D_ON_LI_OFF_M_W_D;
            }
            else background = R_D_ON_LI_ON_L_D_ON_LI_OFF;
        }
        
        //DOOR RIGHT LIGHT RIGHT
        else if(porteDroiteActive && lumiereDroiteActive && !porteGaucheActive && !lumiereGaucheActive){
            if(monster->num_camera == PORTE_HAUT-1){
                background = R_D_ON_LI_ON_L_D_OFF_LI_OFF_M_W_D;
            }
            else background = R_D_ON_LI_ON_L_D_OFF_LI_OFF;
        }
        //DOOR LEFT DOOR RIGHT
        else if(porteDroiteActive && !lumiereDroiteActive && porteGaucheActive && !lumiereGaucheActive){
            background = R_D_ON_LI_OFF_L_D_ON_LI_OFF;
        }
        else{
            background = R_D_OFF_LI_OFF_L_D_OFF_LI_OFF;
        }
    }
    //If the monitor is on we display the camera backgrounds
    else{
        change_camera(camera, monster, camera_type);
    }
}
