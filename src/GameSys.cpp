//
// Created by 蔡元涵 on 2020/6/2.
//

#include <glew.h>
#include <glm.hpp>
#include <algorithm>
#include "GameSys.h"
#include "Tools.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Font.h"
#include "SpriteComponent.h"
#include "Object.h"
#include "Player.h"
#include "Maps.h"
#include "House.h"
#include "UIObject.h"
#include "Button.h"
#include "Item.h"
#include "Document.h"
#include "Gear.h"
#include "ItemSys.h"
#include "NPCSys.h"
#include "NPChara.h"

GameSys::GameSys() : mWindow(nullptr), mContext(nullptr), mIsRunning(true), mIsUpdatingObjects(
        false), mMousePos(0, 0)
{

}

bool GameSys::InitGame()
{
    //初始化sdl和OpenGL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("fail to init SDL: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() != 0)
    {
        SDL_Log("Failed to initialize SDL_ttf");
        return false;
    }

    //设定OpenGL属性
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    mWindow = SDL_CreateWindow("Semi_Demo", 100, 100,
                               1024, 768, SDL_WINDOW_OPENGL);

    if (!mWindow)
    {
        SDL_Log("fail to create window: %s", SDL_GetError());
    }

    //初始化glew
    mContext = SDL_GL_CreateContext(mWindow);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_Log("fail to init GLEW");
        return false;
    }
    glGetError();

    if (!LoadShaders())
    {
        SDL_Log("Failed to load shaders.");

        return false;
    }

    //创建纹理贴图并load actor
    CreateSpriteVerts();

    mInitObjRoot = GetJsonRoot("../Configs/InitObj.json");

    //LoadData();
    LoadStartUI();

    mTicks = SDL_GetTicks();

    return true;
}

void GameSys::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void GameSys::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mMousePos = {event.button.x - 512, 384 - event.button.y};

                mIsUpdatingObjects = true;
                for (auto object : mObjects)
                {
                    mMousePos = {event.button.x - 512, 384 - event.button.y};
                    object->UIInput({static_cast<float>(mMousePos.x),
                                     static_cast<float>(mMousePos.y)});
                }
                mIsUpdatingObjects = false;
            default:
                break;
        }
    }

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }

    mIsUpdatingObjects = true;
    for (auto object : mObjects)
    {
        object->ProcessInput(keyState);
    }
    mIsUpdatingObjects = false;
}

void GameSys::UpdateGame()
{
    //强制锁定60帧
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicks + 16));

    mDeltaTime = (SDL_GetTicks() - mTicks) / 1000.0f;
    if (mDeltaTime > 0.05f)
    {
        mDeltaTime = 0.05f;
    }
    mTicks = SDL_GetTicks();

    //更新、移动所有actor
    mIsUpdatingObjects = true;
    for (auto object : mObjects)
    {
        object->Update(mDeltaTime);
    }
    mIsUpdatingObjects = false;

    // Move any pending actors to mObjects
    for (auto pending : mPendingObjects)
    {
        pending->ComputeWorldTransform();
        mObjects.emplace_back(pending);
    }
    mPendingObjects.clear();

    // Add any dead actors to a temp vector
    std::vector<Object *> deadObjects;
    for (auto object : mObjects)
    {
        if (object->getState() == Object::Dead)
        {
            deadObjects.emplace_back(object);
        }
    }

    // Delete dead actors (which removes them from mObjects)
    for (auto object : deadObjects)
    {
        delete object;
    }
}

void GameSys::GenerateOutput()
{
    //背景颜色
    glClearColor(0.3f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //绘制所有精灵组件
    mSpritesShader->SetActive();
    mSpriteVerts->SetActive();
    for (auto sprite : mSprites)
    {
        if (sprite->getIsVisible())
        {
            sprite->Draw(mSpritesShader);
        }
    }

    SDL_GL_SwapWindow(mWindow);
}

void GameSys::Shutdown()
{
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
    TTF_Quit();
    SDL_Quit();
}

void GameSys::LoadData()
{
    //创建游戏actor
    mPlayer = new Player(this);

    //创建地图
    mMaps = new Maps(this, mPlayer);

    new House(this, mPlayer);

    Json::Value NPCInitInfo = mInitObjRoot["NPCharas"];

    mNPCSys = new NPCSys(mPlayer, NPCInitInfo);

    Json::Value itemsInfo = mInitObjRoot["Items"];

    for (int i = 0; i < itemsInfo.size(); ++i)
    {
        new Item(this, mPlayer, itemsInfo[i]);
    }

    Json::Value docsInfo = mInitObjRoot["Docs"];

    for (int i = 0; i < docsInfo.size(); ++i)
    {
        new Document(this, mPlayer, docsInfo[i]);
    }

    Json::Value gearsInfo = mInitObjRoot["Gears"];

    for (int i = 0; i < gearsInfo.size(); ++i)
    {
        new Gear(this, mPlayer, gearsInfo[i]);
    }

    mItemSys = new ItemSys(this);

    mMainUI = new UIObject(this, mInitObjRoot["UIObjects"]["MainUI"]["UITexPath"].asString());
    Json::Value buttonInfo;
    for (int i = 0; i < mInitObjRoot["UIObjects"]["MainUI"]["Button"].size(); ++i)
    {
        buttonInfo = mInitObjRoot["UIObjects"]["MainUI"]["Button"][i];
        mMainUI->CreateButton(this, mMainUI, buttonInfo["TexPath"].asString(),
                              buttonInfo["Type"].asInt(), buttonInfo["Text"].asString(),
                              {buttonInfo["Position"][0].asFloat(),
                               buttonInfo["Position"][1].asFloat()},
                              buttonInfo["Function"].asInt(), buttonInfo["Size"].asInt());
    }
}

void GameSys::LoadStartUI()
{
    Json::Value startUI = mInitObjRoot["UIObjects"]["StartUI"];
    Json::Value buttonInfo;

    mStartUI = new UIObject(this, startUI["UITexPath"].asString());

    for (int i = 0; i < startUI["Button"].size(); ++i)
    {
        buttonInfo = startUI["Button"][i];
        mStartUI->CreateButton(this, mStartUI, buttonInfo["TexPath"].asString(),
                               buttonInfo["Type"].asInt(), buttonInfo["Text"].asString(),
                               {buttonInfo["Position"][0].asFloat(),
                                buttonInfo["Position"][1].asFloat()},
                               buttonInfo["Function"].asInt(), buttonInfo["Size"].asInt());
    }
}

void GameSys::UnloadAllData()
{
    while (!mObjects.empty())
    {
        delete mObjects.back();
    }

    for (auto i:mTextures)
    {
        i.second->Unload();
        delete i.second;
    }
    mTextures.clear();
}

void GameSys::AddObject(struct Object *object)
{
    if (mIsUpdatingObjects)
    {
        mPendingObjects.emplace_back(object);
    } else
    {
        mObjects.emplace_back(object);
    }
}

void GameSys::RemoveObject(struct Object *object)
{
    auto iter = std::find(mPendingObjects.begin(), mPendingObjects.end(), object);
    if (iter != mPendingObjects.end())
    {
        std::iter_swap(iter, mPendingObjects.end() - 1);
        mPendingObjects.pop_back();
    }

    iter = std::find(mObjects.begin(), mObjects.end(), object);
    if (iter != mObjects.end())
    {
        std::iter_swap(iter, mObjects.end() - 1);
        mObjects.pop_back();
    }
}

bool GameSys::LoadShaders()
{
    mSpritesShader = new Shader();
    if (!mSpritesShader->Load("../Shaders/Sprite.vert", "../Shaders/Sprite.frag"))
    {
        return false;
    }

    mSpritesShader->SetActive();

    glm::mat4 viewProj = glm::mat4(1.0f);
    //此处做视野转换
    viewProj[0][0] *= 2.0f / 1024.0f;
    viewProj[1][1] *= 2.0f / 768.0f;
    mSpritesShader->SetMatrixUniform("uViewProj", viewProj);

    return true;
}

void GameSys::CreateSpriteVerts()
{
    float vertices[] = {
            -0.5f, 0.5f, 0.f, 0.f, 0.f, // top left
            0.5f, 0.5f, 0.f, 1.f, 0.f, // top right
            0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
            -0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

Texture *GameSys::GetTexture(const std::string &fileName)
{
    Texture *tex = nullptr;
    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end())
    {
        tex = iter->second;
    } else
    {
        tex = new Texture();
        if (tex->Load(fileName))
        {
            mTextures.emplace(fileName, tex);
        } else
        {
            delete tex;
            tex = nullptr;
        }
    }

    return tex;
}

class Font *GameSys::GetFont(const std::string &fileName)
{
    auto iter = mFonts.find(fileName);
    if (iter != mFonts.end())
    {
        return iter->second;
    } else
    {
        Font *font = new Font(this);
        if (font->Load(fileName))
        {
            mFonts.emplace(fileName, font);
        } else
        {
            font->Unload();
            delete font;
            font = nullptr;
        }

        return font;
    }
}

void GameSys::AddSprite(SpriteComponent *sprite)
{
    int myDrawOrder = sprite->getDrawOrder();
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); iter++)
    {
        if (myDrawOrder < (*iter)->getDrawOrder())
        {
            break;
        }
    }

    mSprites.insert(iter, sprite);
}

void GameSys::RemoveSprite(SpriteComponent *sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

const Json::Value &GameSys::GetInitObjRoot() const
{
    return mInitObjRoot;
}

void GameSys::BeginGame()
{
    LoadData();
}

void GameSys::AddItemToSys(class Item *item)
{
    mItems.emplace_back(item);
}

void GameSys::AddDocToSys(class Document *document)
{
    mDocuments.emplace_back(document);
}

void GameSys::AddGearToSys(class Gear *gear)
{
    mGears.emplace_back(gear);
}

void GameSys::AddNPCToSys(class NPChara *npChara)
{
    mNPCharas.emplace_back(npChara);
}

void GameSys::UseItemInUI(int itemID)
{
    mItemSys->ItemEvent(itemID);
}

const std::vector<class Item *> &GameSys::getItemsInInventory()
{
    return mPlayer->getInventory()->getItems();
}

const std::vector<class Document *> &GameSys::getDocsInInventory()
{
    return mPlayer->getInventory()->getDocuments();
}

class NPCSys GameSys::getNPCsysDONOTUSETHIS()
{
    return *mNPCSys;
}
