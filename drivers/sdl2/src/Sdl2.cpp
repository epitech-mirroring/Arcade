/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Sdl2.hpp"

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
        throw SDL2Exception(error);
    }
    if (TTF_Init() < 0) {
        error = "TTF_Init Error: " + std::string(TTF_GetError());
        SDL_Quit();
        throw SDL2Exception(error);
    }
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        error = "IMG_Init Error: " + std::string(IMG_GetError());
        TTF_Quit();
        SDL_Quit();
        throw SDL2Exception(error);
    }
    this->_window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(SDL_CreateWindow("Arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN), SDL_DestroyWindow);
    if (this->_window == nullptr) {
        error = "SDL_CreateWindow Error: " + std::string(SDL_GetError());
        SDL_Quit();
        throw SDL2Exception(error);
    }
    this->_renderer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>(SDL_CreateRenderer(this->_window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
    if (this->_renderer == nullptr) {
        SDL_DestroyWindow(this->_window.get());
        error = "SDL_CreateRenderer Error: " + std::string(SDL_GetError());
        SDL_Quit();
        throw SDL2Exception(error);
    }
    SDL_SetRenderDrawColor(this->_renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(this->_renderer.get());
    SDL_RenderPresent(this->_renderer.get());
    this->_keyMap = {
        {SDL_KeyCode::SDLK_a, _KEY_A},
        {SDL_KeyCode::SDLK_b, _KEY_B},
        {SDL_KeyCode::SDLK_c, _KEY_C},
        {SDL_KeyCode::SDLK_d, _KEY_D},
        {SDL_KeyCode::SDLK_e, _KEY_E},
        {SDL_KeyCode::SDLK_f, _KEY_F},
        {SDL_KeyCode::SDLK_g, _KEY_G},
        {SDL_KeyCode::SDLK_h, _KEY_H},
        {SDL_KeyCode::SDLK_i, _KEY_I},
        {SDL_KeyCode::SDLK_j, _KEY_J},
        {SDL_KeyCode::SDLK_k, _KEY_K},
        {SDL_KeyCode::SDLK_l, _KEY_L},
        {SDL_KeyCode::SDLK_m, _KEY_M},
        {SDL_KeyCode::SDLK_n, _KEY_N},
        {SDL_KeyCode::SDLK_o, _KEY_O},
        {SDL_KeyCode::SDLK_p, _KEY_P},
        {SDL_KeyCode::SDLK_q, _KEY_Q},
        {SDL_KeyCode::SDLK_r, _KEY_R},
        {SDL_KeyCode::SDLK_s, _KEY_S},
        {SDL_KeyCode::SDLK_t, _KEY_T},
        {SDL_KeyCode::SDLK_u, _KEY_U},
        {SDL_KeyCode::SDLK_v, _KEY_V},
        {SDL_KeyCode::SDLK_w, _KEY_W},
        {SDL_KeyCode::SDLK_x, _KEY_X},
        {SDL_KeyCode::SDLK_y, _KEY_Y},
        {SDL_KeyCode::SDLK_z, _KEY_Z},
        {SDL_KeyCode::SDLK_0, _KEY_DIGIT_0},
        {SDL_KeyCode::SDLK_KP_0, _KEY_DIGIT_0},
        {SDL_KeyCode::SDLK_1, _KEY_DIGIT_1},
        {SDL_KeyCode::SDLK_KP_1, _KEY_DIGIT_1},
        {SDL_KeyCode::SDLK_2, _KEY_DIGIT_2},
        {SDL_KeyCode::SDLK_KP_2, _KEY_DIGIT_2},
        {SDL_KeyCode::SDLK_3, _KEY_DIGIT_3},
        {SDL_KeyCode::SDLK_KP_3, _KEY_DIGIT_3},
        {SDL_KeyCode::SDLK_4, _KEY_DIGIT_4},
        {SDL_KeyCode::SDLK_KP_4, _KEY_DIGIT_4},
        {SDL_KeyCode::SDLK_5, _KEY_DIGIT_5},
        {SDL_KeyCode::SDLK_KP_5, _KEY_DIGIT_5},
        {SDL_KeyCode::SDLK_6, _KEY_DIGIT_6},
        {SDL_KeyCode::SDLK_KP_6, _KEY_DIGIT_6},
        {SDL_KeyCode::SDLK_7, _KEY_DIGIT_7},
        {SDL_KeyCode::SDLK_KP_7, _KEY_DIGIT_7},
        {SDL_KeyCode::SDLK_8, _KEY_DIGIT_8},
        {SDL_KeyCode::SDLK_KP_8, _KEY_DIGIT_8},
        {SDL_KeyCode::SDLK_9, _KEY_DIGIT_9},
        {SDL_KeyCode::SDLK_KP_9, _KEY_DIGIT_9},
        {SDL_KeyCode::SDLK_ESCAPE, _KEY_ESCAPE},
        {SDL_KeyCode::SDLK_LCTRL, _KEY_CTRL},
        {SDL_KeyCode::SDLK_RCTRL, _KEY_CTRL},
        {SDL_KeyCode::SDLK_LSHIFT, _KEY_SHIFT},
        {SDL_KeyCode::SDLK_RSHIFT, _KEY_SHIFT},
        {SDL_KeyCode::SDLK_TAB, _KEY_TAB},
        {SDL_KeyCode::SDLK_SPACE, _KEY_SPACE},
        {SDL_KeyCode::SDLK_RETURN, _KEY_ENTER},
        {SDL_KeyCode::SDLK_BACKSPACE, _KEY_BACKSPACE},
        {SDL_KeyCode::SDLK_UP, _KEY_UP},
        {SDL_KeyCode::SDLK_DOWN, _KEY_DOWN},
        {SDL_KeyCode::SDLK_LEFT, _KEY_LEFT},
        {SDL_KeyCode::SDLK_RIGHT, _KEY_RIGHT},
        {SDL_KeyCode::SDLK_F1, _KEY_F1},
        {SDL_KeyCode::SDLK_F2, _KEY_F2},
        {SDL_KeyCode::SDLK_F3, _KEY_F3},
        {SDL_KeyCode::SDLK_F4, _KEY_F4},
        {SDL_KeyCode::SDLK_F5, _KEY_F5},
        {SDL_KeyCode::SDLK_F6, _KEY_F6},
        {SDL_KeyCode::SDLK_F7, _KEY_F7},
        {SDL_KeyCode::SDLK_F8, _KEY_F8},
        {SDL_KeyCode::SDLK_F9, _KEY_F9},
        {SDL_KeyCode::SDLK_F10, _KEY_F10},
        {SDL_KeyCode::SDLK_F11, _KEY_F11},
        {SDL_KeyCode::SDLK_F12, _KEY_F12},
    };
}

SDL2::~SDL2()
{
    for (auto &font : this->_fonts) {
        TTF_CloseFont(font.second);
    }
    for (auto &image : this->_images) {
        SDL_FreeSurface(image.second.surface);
        SDL_DestroyTexture(image.second.texture);
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
        throw SDL2Exception("Error while setting color");
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

void SDL2::handleMouseEvents(SDL_Event event)
{
    IEvent::EventType type;
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        type = IEvent::EventType::_MOUSE_DOWN;
    } else if (event.type == SDL_MOUSEBUTTONUP) {
        type = IEvent::EventType::_MOUSE_UP;
    } else {
        type = IEvent::EventType::_MOUSE_MOVE;
    }
    EventKey key;
    if (type == IEvent::EventType::_MOUSE_MOVE) {
        key = _MOUSE_MOVE;
    } else if (event.button.button == SDL_BUTTON_LEFT) {
        key = _MOUSE_LEFT_CLICK;
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
        key = _MOUSE_RIGHT_CLICK;
    } else if (event.button.button == SDL_BUTTON_MIDDLE) {
        key = _MOUSE_MIDDLE_CLICK;
    }
    int x = event.button.x;
    int y = event.button.y;

    EventCallback callback = this->_events[std::make_pair(type, key)];
    if (callback) {
        callback(Event(type, key, x, y));
    }
}

void SDL2::handleEvents()
{
    if (this->_event.type == SDL_QUIT) {
        EventCallback callback = this->_events[std::make_pair(IEvent::EventType::_KEY_DOWN, _KEY_ESCAPE)];
        if (callback) {
            callback(Event(IEvent::EventType::_KEY_DOWN, _KEY_ESCAPE));
        }
    }
    if (this->_event.type == SDL_KEYDOWN) {
        this->handleKeyDownEvents(this->_event);
    }
    this->handleKeyPressedEvents();
    if (this->_event.type == SDL_KEYUP) {
        this->handleKeyUpEvents(this->_event);
    }
    if (this->_event.type == SDL_MOUSEBUTTONDOWN || this->_event.type == SDL_MOUSEBUTTONUP || this->_event.type == SDL_MOUSEMOTION) {
        this->handleMouseEvents(this->_event);
    }
}

void SDL2::handleKeyDownEvents(SDL_Event event)
{
    EventCallback callback = this->_events[std::make_pair(IEvent::EventType::_KEY_DOWN, this->_keyMap[event.key.keysym.sym])];
    if (callback) {
        callback(Event(IEvent::EventType::_KEY_DOWN, this->_keyMap[event.key.keysym.sym]));
    }
    this->_pressedKeys.push_back(event.key.keysym.sym);
}

void SDL2::handleKeyUpEvents(SDL_Event event)
{
    EventCallback callback = this->_events[std::make_pair(IEvent::EventType::_KEY_UP, this->_keyMap[event.key.keysym.sym])];
    if (callback) {
        callback(Event(IEvent::EventType::_KEY_UP, this->_keyMap[event.key.keysym.sym]));
    }
    this->_pressedKeys.erase(std::remove(this->_pressedKeys.begin(), this->_pressedKeys.end(), event.key.keysym.sym), this->_pressedKeys.end());
}

void SDL2::handleKeyPressedEvents()
{
    for (auto key : this->_pressedKeys) {
        EventCallback callback = this->_events[std::make_pair(IEvent::EventType::_KEY_PRESS, this->_keyMap[key])];
        if (callback) {
            callback(Event(IEvent::EventType::_KEY_PRESS, this->_keyMap[key]));
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
    } else if (IS_INSTANCE_OF(const ILine, primitive)) {
        this->displayLine(dynamic_cast<const ILine &>(primitive));
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
            throw SDL2Exception("Error while loading font");
        }
    }
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface(TTF_RenderText_Solid(this->_fonts[fontKey], text.getText().c_str(), color), SDL_FreeSurface);
    if (surface == nullptr) {
        throw SDL2Exception("Error while rendering text");
    }
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture(SDL_CreateTextureFromSurface(this->_renderer.get(), surface.get()), SDL_DestroyTexture);
    if (texture == nullptr) {
        throw SDL2Exception("Error while rendering text");
    }
    SDL_Rect rect = {text.getPosition().getX(), text.getPosition().getY(), surface->w, surface->h};

    if (IS_INSTANCE_OF(const ICanRotate, text)) {
        if (SDL_RenderCopyEx(this->_renderer.get(), texture.get(), nullptr, &rect, TRANSFORM_TO(const ICanRotate, text)->getRotation(), nullptr, SDL_FLIP_NONE) != 0) {
            throw SDL2Exception("Error while rendering text");
        }
    } else {
        if (SDL_RenderCopy(this->_renderer.get(), texture.get(), nullptr, &rect) != 0) {
            throw SDL2Exception("Error while rendering text");
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
        throw SDL2Exception("Error while setting color");
    }

    if (square.isFilled()) {
        std::pair<std::vector<SDL_Vertex>, std::vector<SDL_Vertex>> triangles = getSquareVertexes(
                posX, posY, sizeX, sizeY, angle, color);
        if (SDL_RenderGeometry(this->_renderer.get(), nullptr,
                               triangles.first.data(), triangles.first.size(),
                               nullptr, 0) != 0) {
            throw SDL2Exception("Error while rendering square");
        }
        if (SDL_RenderGeometry(this->_renderer.get(), nullptr,
                               triangles.second.data(), triangles.second.size(),
                               nullptr, 0) != 0) {
            throw SDL2Exception("Error while rendering square");
        }
    } else {
        // Draw 4 lines
        SDL_FPoint points[5] = {
            {posX, posY},
            {posX + sizeX, posY},
            {posX + sizeX, posY + sizeY},
            {posX, posY + sizeY},
            {posX, posY},
        };
        for (int i = 0; i < 4; i++) {
            SDL_FPoint point1 = points[i];
            SDL_FPoint point2 = points[i + 1];
            SDL_FPoint newPoint1 = {posX + cos(angle) * (point1.x - posX) - sin(angle) * (point1.y - posY), posY + sin(angle) * (point1.x - posX) + cos(angle) * (point1.y - posY)};
            SDL_FPoint newPoint2 = {posX + cos(angle) * (point2.x - posX) - sin(angle) * (point2.y - posY), posY + sin(angle) * (point2.x - posX) + cos(angle) * (point2.y - posY)};
            if (SDL_RenderDrawLine(this->_renderer.get(), (int) newPoint1.x, (int) newPoint1.y, (int) newPoint2.x, (int) newPoint2.y) != 0) {
                throw SDL2Exception("Error while rendering square");
            }
        }
    }
}

void SDL2::displayLine(const ILine &line)
{
    SDL_Color color = convertColor(line.getColor());
    int posX = line.getPosition().getX();
    int posY = line.getPosition().getY();
    int endX = line.getEnd().getX();
    int endY = line.getEnd().getY();

    if (SDL_SetRenderDrawColor(this->_renderer.get(), color.r, color.g, color.b, color.a) != 0) {
        throw SDL2Exception("Error while setting color");
    }
    if (SDL_RenderDrawLine(this->_renderer.get(), posX, posY, endX, endY) != 0) {
        throw SDL2Exception("Error while rendering line");
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
        throw SDL2Exception("Error while setting color");
    }
    for (int i = posX; i < posX + radius * 2; i++) {
        for (int j = posY; j < posY + radius * 2; j++) {
            int dx = i - cX;
            int dy = j - cY;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                if (SDL_RenderDrawPoint(this->_renderer.get(), i, j) != 0) {
                    throw SDL2Exception("Error while rendering circle");
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
    DrawRect drawRect = entity.getSprite().getDrawRect();
    float w = drawRect.width * scale;
    float h = drawRect.height * scale;
    SDL_Rect drawRectSDL = {static_cast<int>(drawRect.x), static_cast<int>(drawRect.y), static_cast<int>(drawRect.width), static_cast<int>(drawRect.height)};
    SDL_Rect rect = {entity.getPosition().getX(), entity.getPosition().getY(), (int)w, (int)h};

    if (this->_images.find(path) == this->_images.end()) {
        this->_images[path] = {nullptr, nullptr};
        this->_images[path].surface = IMG_Load(path.c_str());
        if (this->_images[path].surface == nullptr) {
            throw SDL2Exception("Error while loading image");
        }
        this->_images[path].texture = SDL_CreateTextureFromSurface(this->_renderer.get(), this->_images[path].surface);
        if (this->_images[path].texture == nullptr) {
            throw SDL2Exception("Error while rendering image");
        }
    }
    if (IS_INSTANCE_OF(const ICanRotate, entity)) {
        angle = TRANSFORM_TO(const ICanRotate, entity)->getRotation();
    }
    if (SDL_RenderCopyEx(this->_renderer.get(), this->_images[path].texture, &drawRectSDL, &rect, angle, nullptr, SDL_FLIP_NONE) != 0) {
        throw SDL2Exception("Error while rendering image");
    }
}

void SDL2::unbindAll()
{
    this->_events.clear();
}

SDL_Color SDL2::convertColor(const IColor &color)
{
    if (color.getA() > 255 || color.getR() > 255 || color.getG() > 255 || color.getB() > 255) {
        throw SDL2Exception("Invalid color");
    }
    return {static_cast<Uint8>(color.getR()), static_cast<Uint8>(color.getG()), static_cast<Uint8>(color.getB()), static_cast<Uint8>(color.getA())};
}
