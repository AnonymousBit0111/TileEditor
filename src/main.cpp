// #include <bgfx/bgfx.h>
// #include <bgfx/platform.h>
// #include <bx/math.h>

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_syswm.h>
// #include <string>

// #include "imgui.h"
// #include "imgui_impl_bgfx.h"
// #include "imgui_impl_sdl2.h"

// #include <fstream>
// #include <iostream>

// struct context_t {
//   SDL_Window *window = nullptr;

//   float cam_pitch = 0.0f;
//   float cam_yaw = 0.0f;
//   float rot_scale = 0.01f;

//   int prev_mouse_x = 0;
//   int prev_mouse_y = 0;

//   int width = 0;
//   int height = 0;

//   bool quit = false;
// };

// void main_loop(void *data) {

//   auto context = static_cast<context_t *>(data);

//   for (SDL_Event currentEvent; SDL_PollEvent(&currentEvent) != 0;) {
//     ImGui_ImplSDL2_ProcessEvent(&currentEvent);
//     if (currentEvent.type == SDL_QUIT) {
//       context->quit = true;
//       break;
//     }
//   }
//   bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
//   0x6495EDFF, 1.0f,
//                      0);
//   ImGui_Implbgfx_NewFrame();
//   ImGui_ImplSDL2_NewFrame();

//   ImGui::NewFrame();
//   ImGui::ShowDemoWindow(); // your drawing here
//   ImGui::Render();
//   ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());

//   if (!ImGui::GetIO().WantCaptureMouse) {
//     // simple input code for orbit camera
//     int mouse_x, mouse_y;
//     const int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
//     if ((buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0) {
//       int delta_x = mouse_x - context->prev_mouse_x;
//       int delta_y = mouse_y - context->prev_mouse_y;
//       context->cam_yaw += float(-delta_x) * context->rot_scale;
//       context->cam_pitch += float(-delta_y) * context->rot_scale;
//     }
//     context->prev_mouse_x = mouse_x;
//     context->prev_mouse_y = mouse_y;
//   }

//   bgfx::touch(0);
//   bgfx::frame();

// #if BX_PLATFORM_EMSCRIPTEN
//   if (context->quit) {
//     emscripten_cancel_main_loop();
//   }
// #endif
// }

// int main(int argc, char **argv) {
//   if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
//     printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
//     return 1;
//   }

//   const int width = 800;
//   const int height = 600;
//   SDL_Window *window = SDL_CreateWindow(argv[0], SDL_WINDOWPOS_UNDEFINED,
//                                         SDL_WINDOWPOS_UNDEFINED, width,
//                                         height, SDL_WINDOW_SHOWN);

//   if (window == nullptr) {
//     printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
//     return 1;
//   }

// #if !BX_PLATFORM_EMSCRIPTEN
//   SDL_SysWMinfo wmi;
//   SDL_VERSION(&wmi.version);
//   if (!SDL_GetWindowWMInfo(window, &wmi)) {
//     printf("SDL_SysWMinfo could not be retrieved. SDL_Error: %s\n",
//            SDL_GetError());
//     return 1;
//   }
//   bgfx::renderFrame(); // single threaded mode
// #endif                 // !BX_PLATFORM_EMSCRIPTEN

//   bgfx::PlatformData pd{};
// #if BX_PLATFORM_WINDOWS
//   pd.nwh = wmi.info.win.window;
// #elif BX_PLATFORM_OSX
//   pd.nwh = wmi.info.cocoa.window;
// #elif BX_PLATFORM_LINUX
//   pd.ndt = wmi.info.x11.display;
//   pd.nwh = (void *)(uintptr_t)wmi.info.x11.window;
// #elif BX_PLATFORM_EMSCRIPTEN
//   pd.nwh = (void *)"#canvas";
// #endif // BX_PLATFORM_WINDOWS ? BX_PLATFORM_OSX ? BX_PLATFORM_LINUX ?
//        // BX_PLATFORM_EMSCRIPTEN

//   bgfx::Init bgfx_init;
//   bgfx_init.type = bgfx::RendererType::Count; // auto choose renderer
//   bgfx_init.resolution.width = width;
//   bgfx_init.resolution.height = height;
//   bgfx_init.resolution.reset = BGFX_RESET_VSYNC;
//   bgfx_init.platformData = pd;
//   bgfx::init(bgfx_init);

//   bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
//   0x6495EDFF, 1.0f,
//                      0);
//   bgfx::setViewRect(0, 0, 0, width, height);

//   ImGui::CreateContext();
//   ImGuiIO &io = ImGui::GetIO();

//   ImGui_Implbgfx_Init(255);
// #if BX_PLATFORM_WINDOWS
//   ImGui_ImplSDL2_InitForD3D(window);
// #elif BX_PLATFORM_OSX
//   ImGui_ImplSDL2_InitForMetal(window);
// #elif BX_PLATFORM_LINUX || BX_PLATFORM_EMSCRIPTEN
//   ImGui_ImplSDL2_InitForOpenGL(window, nullptr);
// #endif // BX_PLATFORM_WINDOWS ? BX_PLATFORM_OSX ? BX_PLATFORM_LINUX ?
//        // BX_PLATFORM_EMSCRIPTEN

//   context_t context;
//   context.width = width;
//   context.height = height;
//   context.window = window;

// #if BX_PLATFORM_EMSCRIPTEN
//   emscripten_set_main_loop_arg(main_loop, &context, -1, 1);
// #else
//   while (!context.quit) {
//     main_loop(&context);
//   }
// #endif // BX_PLATFORM_EMSCRIPTEN

//   ImGui_ImplSDL2_Shutdown();
//   ImGui_Implbgfx_Shutdown();

//   ImGui::DestroyContext();
//   bgfx::shutdown();

//   SDL_DestroyWindow(window);
//   SDL_Quit();

//   return 0;
// }

#include "Nexus/Box.h"
#include "Nexus/Engine.h"
#include "Nexus/Physics.h"
#include "Nexus/PhysicsObject.h"
#include "Nexus/Rect.h"
#include "Nexus/Ref.h"
#include "Nexus/Renderer.h"
#include "Nexus/Scene.h"
#include "Nexus/Sprite.h"
#include "Nexus/TextureAtlas.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Vulkan.hpp"
#include "box2d/b2_body.h"
#include "box2d/b2_math.h"
#include "box2d/b2_types.h"
#include "box2d/b2_world.h"
#include "box2d/box2d.h"
#include "imgui.h"
#include <iostream>
#include <vector>
using namespace Nexus;

class MainScene : public Scene {
private:
  sf::Texture texture;
  sf::Texture texture2;
  uint32 rgba;

  float red[4];
  Ref<Rect> r;
  TextureAtlas atl;

  int addedboxes = 0;

public:
  MainScene() {
    srand(ImGui::GetTime());
    world = make_Ref<b2World>(b2Vec2(0, -100));
    texture.loadFromFile("res/tree.png");
    atl.loadTexFromFile("res/texture.png");
    atl.loadRectsFromFile("res/texture.json");
    std::cout << "\n";

    r = make_Ref<Rect>(sf::Vector2f{100, 100}, sf::Vector2f{100, 500},
                       sf::Color{255, 255, 255},
                       atl.getRect("tree.png"));

    texture2 = atl.getTexture();
    Renderer::setTexture(&texture2);
    // Renderer::setTexture(texture);
  }
  float top, left, width, height;
  void update() override {

    world->Step(1.0f / 120, 6, 2);
    ImGui::Begin("Info");
    auto rect = r->getRect();
    ImGui::Text("rect.top:%f\nrect.left:%f\nrect.width:%f\nrect.height:%f\n",
                rect.top, rect.left, rect.width, rect.height);
    ImGui::InputFloat4("rect", &top);

    if (ImGui::Button("update")) {
      sf::FloatRect texRect(top,left,width,height);
      r->setRect(texRect);
    }
    ImGui::End();

    // b.setPosition({MetersToPixels(body->GetPosition().x),
    //                Engine::getWindow().getSize().y -
    //                    MetersToPixels(body->GetPosition().y)});
  }
  void render() override {

    // sf::RenderStates states;
    // states.texture = &texture;
    // Engine::getWindow().draw(arr, states);

    Renderer::begin();

    Renderer::addQuad(*r);
    Renderer::render();
  }
};

int main() {

  Engine::init(800, 600, "Mirage Sandbox");
  Engine::addScene("main", make_Ref<MainScene>());
  Engine::mainLoop("main");
  Engine::cleanup();
}
