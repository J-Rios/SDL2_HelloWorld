// Librerias
#include <SDL.h>
#include <stdio.h>
/***********************************************************************************/
// Tamano de la ventana
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
/***********************************************************************************/
// Funciones
bool init(); // Inicializa SDL y crea la ventana
bool loadMedia(); // Carga recursos
void close(); // Libera los recursos y cierra SDL
/***********************************************************************************/
// Elementos SDL
SDL_Window* window = NULL; // Ventana a renderizar
SDL_Surface* screenSurface = NULL; // Superficie contenida por la ventana
SDL_Surface* img_HelloWorld = NULL; // Imagen a cargar y mostrar en pantalla
/***********************************************************************************/
int main(int argc, char* args[])
{
    // Inicializa SDL y crea la ventana
    if(!init())
        printf("No se ha podido inicializar SDL\n" );
    else
    {
        // Carga de recursos
        if(!loadMedia())
            printf("No se han podido cargar los recursos\n" );
        else
        {
            // FLAG de cerrar aplicacion
            bool quit = false;

            // Evento
            SDL_Event e;

            //While application is running
            while(!quit)
            {
                while(SDL_PollEvent(&e) != 0) // Manejar eventos en cola
                {
                    if(e.type == SDL_QUIT) // Peticion de salir de aplicacion (presionada x de la ventana)
                        quit = true;
                }
                // Aplicamos la imagen a la superficie de la ventana
                SDL_BlitSurface(img_HelloWorld, NULL, screenSurface, NULL);

                // Actualizamos la superficie en la ventana
                SDL_UpdateWindowSurface(window);
            }
        }
    }

    // Libera los recursos y cierra SDL
    close();

    return 0;
}
/***********************************************************************************/
bool init()
{
    bool success = true; // FLAG de exito

    // Inicializacion de SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error al inicializar SDL. SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Creacion de la ventana
        window = SDL_CreateWindow( "Titulo de la ventana", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            printf("Error en la creacion de la ventana. SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Obtencion de la superficie de la ventana
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true; // FLAG de exito

    // Carga de la imagen
    img_HelloWorld = SDL_LoadBMP("recursos/hello_world.bmp");
    if(img_HelloWorld == NULL)
    {
        printf("Error al cargar la imagen %s. SDL Error: %s\n", "recursos/hello_world.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

void close()
{
    // Liberamos las superficies
    SDL_FreeSurface(img_HelloWorld);
    img_HelloWorld = NULL;

    // Destruimos la ventana
    SDL_DestroyWindow(window);
    window = NULL;

    // Salir del subsistema SDL
    SDL_Quit();
}
/***********************************************************************************/
