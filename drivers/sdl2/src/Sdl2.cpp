/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Sdl2.hpp"
#include <memory>
#include <string>
#include <iostream>

extern "C" {
    __attribute__((constructor))
    void load_lib()
    {
        std::cout << "Loading SDL2 driver" << std::endl;
    }

    __attribute__((destructor))
    void unload_lib()
    {
        std::cout << "Unloading SDL2 driver" << std::endl;
    }

    std::unique_ptr<IDriver> create_driver()
    {
        std::unique_ptr<IDriver> driver = std::make_unique<SDL2>();
        return driver;
    }

    const std::string &get_name()
    {
        static const std::string driver_name = "SDL2";
        return driver_name;
    }
}

SDL2::SDL2()
{
    std::string error;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        error = "SDL_Init Error: " + std::string(SDL_GetError());
        throw SDL2Exception(error, *this);
    }
    if (TTF_Init() < 0) {
        error = "TTF_Init Error: " + std::string(TTF_GetError());
        SDL_Quit();
        throw SDL2Exception(error, *this);
    }
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        error = "IMG_Init Error: " + std::string(IMG_GetError());
        TTF_Quit();
        SDL_Quit();
        throw SDL2Exception(error, *this);
    }
    this->_window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(SDL_CreateWindow("Arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN), SDL_DestroyWindow);
    if (this->_window == nullptr) {
        error = "SDL_CreateWindow Error: " + std::string(SDL_GetError());
        SDL_Quit();
        throw SDL2Exception(error, *this);
    }
    this->_renderer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>(SDL_CreateRenderer(this->_window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
    if (this->_renderer == nullptr) {
        SDL_DestroyWindow(this->_window.get());
        error = "SDL_CreateRenderer Error: " + std::string(SDL_GetError());
        SDL_Quit();
        throw SDL2Exception(error, *this);
    }
    SDL_SetRenderDrawColor(this->_renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(this->_renderer.get());
    SDL_RenderPresent(this->_renderer.get());
    this->_keyMap = {
        {SDL_KeyCode::SDLK_a, KEY_A},
        {SDL_KeyCode::SDLK_b, KEY_B},
        {SDL_KeyCode::SDLK_c, KEY_C},
        {SDL_KeyCode::SDLK_d, KEY_D},
        {SDL_KeyCode::SDLK_e, KEY_E},
        {SDL_KeyCode::SDLK_f, KEY_F},
        {SDL_KeyCode::SDLK_g, KEY_G},
        {SDL_KeyCode::SDLK_h, KEY_H},
        {SDL_KeyCode::SDLK_i, KEY_I},
        {SDL_KeyCode::SDLK_j, KEY_J},
        {SDL_KeyCode::SDLK_k, KEY_K},
        {SDL_KeyCode::SDLK_l, KEY_L},
        {SDL_KeyCode::SDLK_m, KEY_M},
        {SDL_KeyCode::SDLK_n, KEY_N},
        {SDL_KeyCode::SDLK_o, KEY_O},
        {SDL_KeyCode::SDLK_p, KEY_P},
        {SDL_KeyCode::SDLK_q, KEY_Q},
        {SDL_KeyCode::SDLK_r, KEY_R},
        {SDL_KeyCode::SDLK_s, KEY_S},
        {SDL_KeyCode::SDLK_t, KEY_T},
        {SDL_KeyCode::SDLK_u, KEY_U},
        {SDL_KeyCode::SDLK_v, KEY_V},
        {SDL_KeyCode::SDLK_w, KEY_W},
        {SDL_KeyCode::SDLK_x, KEY_X},
        {SDL_KeyCode::SDLK_y, KEY_Y},
        {SDL_KeyCode::SDLK_z, KEY_Z},
        {SDL_KeyCode::SDLK_0, KEY_DIGIT_0},
        {SDL_KeyCode::SDLK_KP_0, KEY_DIGIT_0},
        {SDL_KeyCode::SDLK_1, KEY_DIGIT_1},
        {SDL_KeyCode::SDLK_KP_1, KEY_DIGIT_1},
        {SDL_KeyCode::SDLK_2, KEY_DIGIT_2},
        {SDL_KeyCode::SDLK_KP_2, KEY_DIGIT_2},
        {SDL_KeyCode::SDLK_3, KEY_DIGIT_3},
        {SDL_KeyCode::SDLK_KP_3, KEY_DIGIT_3},
        {SDL_KeyCode::SDLK_4, KEY_DIGIT_4},
        {SDL_KeyCode::SDLK_KP_4, KEY_DIGIT_4},
        {SDL_KeyCode::SDLK_5, KEY_DIGIT_5},
        {SDL_KeyCode::SDLK_KP_5, KEY_DIGIT_5},
        {SDL_KeyCode::SDLK_6, KEY_DIGIT_6},
        {SDL_KeyCode::SDLK_KP_6, KEY_DIGIT_6},
        {SDL_KeyCode::SDLK_7, KEY_DIGIT_7},
        {SDL_KeyCode::SDLK_KP_7, KEY_DIGIT_7},
        {SDL_KeyCode::SDLK_8, KEY_DIGIT_8},
        {SDL_KeyCode::SDLK_KP_8, KEY_DIGIT_8},
        {SDL_KeyCode::SDLK_9, KEY_DIGIT_9},
        {SDL_KeyCode::SDLK_KP_9, KEY_DIGIT_9},
        {SDL_KeyCode::SDLK_ESCAPE, KEY_ESCAPE},
        {SDL_KeyCode::SDLK_LCTRL, KEY_CTRL},
        {SDL_KeyCode::SDLK_RCTRL, KEY_CTRL},
        {SDL_KeyCode::SDLK_LSHIFT, KEY_SHIFT},
        {SDL_KeyCode::SDLK_RSHIFT, KEY_SHIFT},
        {SDL_KeyCode::SDLK_TAB, KEY_TAB},
        {SDL_KeyCode::SDLK_SPACE, KEY_SPACE},
        {SDL_KeyCode::SDLK_RETURN, KEY_ENTER},
        {SDL_KeyCode::SDLK_BACKSPACE, KEY_BACKSPACE},
        {SDL_KeyCode::SDLK_UP, KEY_UP},
        {SDL_KeyCode::SDLK_DOWN, KEY_DOWN},
        {SDL_KeyCode::SDLK_LEFT, KEY_LEFT},
        {SDL_KeyCode::SDLK_RIGHT, KEY_RIGHT},
        {SDL_KeyCode::SDLK_F1, KEY_F1},
        {SDL_KeyCode::SDLK_F2, KEY_F2},
        {SDL_KeyCode::SDLK_F3, KEY_F3},
        {SDL_KeyCode::SDLK_F4, KEY_F4},
        {SDL_KeyCode::SDLK_F5, KEY_F5},
        {SDL_KeyCode::SDLK_F6, KEY_F6},
        {SDL_KeyCode::SDLK_F7, KEY_F7},
        {SDL_KeyCode::SDLK_F8, KEY_F8},
        {SDL_KeyCode::SDLK_F9, KEY_F9},
        {SDL_KeyCode::SDLK_F10, KEY_F10},
        {SDL_KeyCode::SDLK_F11, KEY_F11},
        {SDL_KeyCode::SDLK_F12, KEY_F12},
    };
}

SDL2::~SDL2()
{
    for (auto &font : this->_fonts) {
        TTF_CloseFont(font.second);
    }
    for (auto &image : this->_images) {
        SDL_FreeSurface(image.second);
    }
    this->_renderer.reset();
    this->_window.reset();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void SDL2::flipFrame()
{
    SDL_RenderPresent(this->_renderer.get());
    if (SDL_SetRenderDrawColor(this->_renderer.get(), 0, 0, 0, 255) != 0) {
        throw SDL2Exception("Error while setting color", *this);
    }
    SDL_RenderClear(this->_renderer.get());
    if (SDL_PollEvent(&this->_event)) {
        this->handleEvents();
    }
}

void SDL2::setPreferredSize(std::size_t width, std::size_t height)
{
    this->_width = width;
    this->_height = height;
    SDL_SetWindowSize(this->_window.get(), width, height);
}

void SDL2::bindEvent(IEvent::EventType type, EventKey key, EventCallback callback)
{
    this->_events[std::make_pair(type, key)] = callback;
}

void SDL2::handleEvents()
{
    if (this->_event.type == SDL_QUIT) {
        EventCallback callback = this->_events[std::make_pair(IEvent::EventType::KEY_DOWN, KEY_ESCAPE)];
        if (callback) {
            callback(Event(IEvent::EventType::KEY_DOWN, KEY_ESCAPE));
        }
    }
    if (this->_event.type == SDL_KEYDOWN) {
        this->handleKeyDownEvents(this->_event);
    }
    this->handleKeyPressedEvents();
    if (this->_event.type == SDL_KEYUP) {
        this->handleKeyUpEvents(this->_event);
    }
}

void SDL2::handleKeyDownEvents(SDL_Event event)
{
    EventCallback callback = this->_events[std::make_pair(IEvent::EventType::KEY_DOWN, this->_keyMap[event.key.keysym.sym])];
    if (callback) {
        callback(Event(IEvent::EventType::KEY_DOWN, this->_keyMap[event.key.keysym.sym]));
    }
    this->_pressedKeys.push_back(event.key.keysym.sym);
}

void SDL2::handleKeyUpEvents(SDL_Event event)
{
    EventCallback callback = this->_events[std::make_pair(IEvent::EventType::KEY_UP, this->_keyMap[event.key.keysym.sym])];
    if (callback) {
        callback(Event(IEvent::EventType::KEY_UP, this->_keyMap[event.key.keysym.sym]));
    }
    this->_pressedKeys.erase(std::remove(this->_pressedKeys.begin(), this->_pressedKeys.end(), event.key.keysym.sym), this->_pressedKeys.end());
}

void SDL2::handleKeyPressedEvents()
{
    for (auto key : this->_pressedKeys) {
        EventCallback callback = this->_events[std::make_pair(IEvent::EventType::KEY_PRESS, this->_keyMap[key])];
        if (callback) {
            callback(Event(IEvent::EventType::KEY_PRESS, this->_keyMap[key]));
        }
    }
}

void SDL2::display(const IDisplayable &displayable)
{
    if (IS_INSTANCE_OF(const IPrimitive, displayable)) {
        this->displayPrimitive(dynamic_cast<const IPrimitive &>(displayable));
    } else if (IS_INSTANCE_OF(const IEntity, displayable)) {
        this->displayEntity(dynamic_cast<const IEntity &>(displayable));
    }
}

void SDL2::displayPrimitive(const IPrimitive &primitive)
{
    if (IS_INSTANCE_OF(const IText, primitive)) {
        this->displayText(dynamic_cast<const IText &>(primitive));
    } else if (IS_INSTANCE_OF(const ISquare, primitive)) {
        this->displaySquare(dynamic_cast<const ISquare &>(primitive));
    } else if (IS_INSTANCE_OF(const ICircle, primitive)) {
        this->displayCircle(dynamic_cast<const ICircle &>(primitive));
    }
}

void SDL2::displayText(const IText &text)
{
    if (text.getFontPath().empty() || text.getText().empty()) {
        return;
    }
    
    std::string path = text.getFontPath();
    std::size_t fontSize = text.getSize();
    std::pair<std::string, std::size_t> fontKey = std::make_pair(path, fontSize);
    SDL_Color color = convertColor(text.getColor());
    if (this->_fonts.find(fontKey) == this->_fonts.end()) {
        this->_fonts[fontKey] = TTF_OpenFont(path.c_str(), text.getSize());
        if (this->_fonts[fontKey] == nullptr) {
            throw SDL2Exception("Error while loading font", *this);
        }
    }
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface(TTF_RenderText_Solid(this->_fonts[fontKey], text.getText().c_str(), color), SDL_FreeSurface);
    if (surface == nullptr) {
        throw SDL2Exception("Error while rendering text", *this);
    }
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture(SDL_CreateTextureFromSurface(this->_renderer.get(), surface.get()), SDL_DestroyTexture);
    if (texture == nullptr) {
        throw SDL2Exception("Error while rendering text", *this);
    }
    SDL_Rect rect = {text.getPosition().getX(), text.getPosition().getY(), surface->w, surface->h};

    if (IS_INSTANCE_OF(const ICanRotate, text)) {
        if (SDL_RenderCopyEx(this->_renderer.get(), texture.get(), nullptr, &rect, TRANSFORM_TO(const ICanRotate, text)->getRotation(), nullptr, SDL_FLIP_NONE) != 0) {
            throw SDL2Exception("Error while rendering text", *this);
        }
    } else {
        if (SDL_RenderCopy(this->_renderer.get(), texture.get(), nullptr, &rect) != 0) {
            throw SDL2Exception("Error while rendering text", *this);
        }
    }
}

static std::pair<std::vector<SDL_Vertex>, std::vector<SDL_Vertex>> getSquareVertexes(float posX, float posY, float sizeX, float sizeY, float angle, SDL_Color color)
{
    float angleRad = angle * M_PI / 180;
    float c = cos(angleRad);
    float s = sin(angleRad);
    SDL_FPoint vertexes[4] = {
        {posX, posY},
        {posX + sizeX, posY},
        {posX + sizeX, posY + sizeY},
        {posX, posY + sizeY},
    };
    SDL_Vertex newVertexes[4];
    for (int i = 0; i < 4; i++) {
        SDL_FPoint vertex = vertexes[i];
        newVertexes[i] = {SDL_FPoint{posX + c * (vertex.x - posX) - s * (vertex.y - posY), posY + s * (vertex.x - posX) + c * (vertex.y - posY)}, color, SDL_FPoint{0, 0}};
    }
    std::vector<SDL_Vertex> triangle1 = {newVertexes[0], newVertexes[1], newVertexes[2]};
    std::vector<SDL_Vertex> triangle2 = {newVertexes[0], newVertexes[2], newVertexes[3]};
    return std::make_pair(triangle1, triangle2);
}

void SDL2::displaySquare(const ISquare &square)
{
    SDL_Color color = convertColor(square.getColor());
    float posX = square.getPosition().getX();
    float posY = square.getPosition().getY();
    float sizeX = square.getWidth() * square.getSize();
    float sizeY = square.getHeight() * square.getSize();
    float angle = 0;

    if (IS_INSTANCE_OF(const ICanRotate, square)) {
        angle = TRANSFORM_TO(const ICanRotate, square)->getRotation();
    }
    if (SDL_SetRenderDrawColor(this->_renderer.get(), color.r, color.g, color.b, color.a) != 0) {
        throw SDL2Exception("Error while setting color", *this);
    }
    std::pair<std::vector<SDL_Vertex>, std::vector<SDL_Vertex>> triangles = getSquareVertexes(posX, posY, sizeX, sizeY, angle, color);
    if (SDL_RenderGeometry(this->_renderer.get(), nullptr, triangles.first.data(), triangles.first.size(), nullptr, 0) != 0) {
        throw SDL2Exception("Error while rendering square", *this);
    }
    if (SDL_RenderGeometry(this->_renderer.get(), nullptr, triangles.second.data(), triangles.second.size(), nullptr, 0) != 0) {
        throw SDL2Exception("Error while rendering square", *this);
    }
}

void SDL2::displayCircle(const ICircle &circle)
{
    SDL_Color color = convertColor(circle.getColor());
    int radius = (int)circle.getRadius() * circle.getSize();
    int posX = circle.getPosition().getX();
    int posY = circle.getPosition().getY();
    int cX = posX + radius;
    int cY = posY + radius;

    if (SDL_SetRenderDrawColor(this->_renderer.get(), color.r, color.g, color.b, color.a) != 0) {
        throw SDL2Exception("Error while setting color", *this);
    }
    for (int i = posX; i < posX + radius * 2; i++) {
        for (int j = posY; j < posY + radius * 2; j++) {
            int dx = i - cX;
            int dy = j - cY;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                if (SDL_RenderDrawPoint(this->_renderer.get(), i, j) != 0) {
                    throw SDL2Exception("Error while rendering circle", *this);
                }
            }
        }
    }
}

void SDL2::displayEntity(const IEntity &entity)
{
    std::string path = entity.getSprite().getPicture().getPath();
    int angle = 0;
    float scale = entity.getSize();
    float w = entity.getSprite().getPicture().getWidth() * scale;
    float h = entity.getSprite().getPicture().getHeight() * scale;
    SDL_Rect rect = {entity.getPosition().getX(), entity.getPosition().getY(), (int)w, (int)h};

    if (this->_images.find(path) == this->_images.end()) {
        this->_images[path] = IMG_Load(path.c_str());
        if (this->_images[path] == nullptr) {
            throw SDL2Exception("Error while loading image", *this);
        }
    }
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture(SDL_CreateTextureFromSurface(this->_renderer.get(), this->_images[path]), SDL_DestroyTexture);
    if (texture == nullptr) {
        throw SDL2Exception("Error while rendering image", *this);
    }
    if (IS_INSTANCE_OF(const ICanRotate, entity)) {
        angle = TRANSFORM_TO(const ICanRotate, entity)->getRotation();
    }
    if (SDL_RenderCopyEx(this->_renderer.get(), texture.get(), nullptr, &rect, angle, nullptr, SDL_FLIP_NONE) != 0) {
        throw SDL2Exception("Error while rendering image", *this);
    }
}

void SDL2::unbindAll()
{
    this->_events.clear();
}

SDL_Color SDL2::convertColor(const IColor &color)
{
    if (color.getA() > 255 || color.getR() > 255 || color.getG() > 255 || color.getB() > 255) {
        throw SDL2Exception("Invalid color", *this);
    }
    return {static_cast<Uint8>(color.getR()), static_cast<Uint8>(color.getG()), static_cast<Uint8>(color.getB()), static_cast<Uint8>(color.getA())};
}
