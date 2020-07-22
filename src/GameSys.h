//
// Created by 蔡元涵 on 2020/6/2.
//

#ifndef SEMI_DEMO_GAMESYS_H
#define SEMI_DEMO_GAMESYS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <json.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <ext/vector_int2.hpp>

class GameSys
{
public:
    GameSys();

    bool InitGame();

    void RunLoop();

    void Shutdown();

    void AddObject(class Object *object);

    void RemoveObject(class Object *object);

    class Texture *GetTexture(const std::string &fileName);

    class Font *GetFont(const std::string &fileName);

    void AddSprite(class SpriteComponent *sprite);

    void RemoveSprite(class SpriteComponent *sprite);

    void BeginGame();

    const Json::Value &GetInitObjRoot() const;

    const glm::ivec2 &getInitPos() const
    {
        return mInitPos;
    }

    void setInitPos(const glm::ivec2 &mInitPos)
    {
        GameSys::mInitPos = mInitPos;
    }

    const glm::ivec2 &getMousePos() const
    {
        return mMousePos;
    }

    void AddItemToSys(class Item *item);

    void AddDocToSys(class Document *document);

private:
    void ProcessInput();

    void UpdateGame();

    void GenerateOutput();

    bool LoadShaders();

    void CreateSpriteVerts();

    void LoadData();

    void LoadStartUI();

    void UnloadAllData();

    SDL_Window *mWindow;
    SDL_GLContext mContext;
    bool mIsRunning;
    bool mIsUpdatingObjects;
    Uint32 mTicks;


    float mDeltaTime;

    class UIObject *mStartUI;

    class Maps *mMaps;

    class Player *mPlayer;

    glm::ivec2 mInitPos;

    //游戏中的actor
    std::vector<class Object *> mObjects;
    //游戏中等待加入的actor
    std::vector<class Object *> mPendingObjects;

    //sprite着色器
    class Shader *mSpritesShader;

    //VAO
    class VertexArray *mSpriteVerts;

    //储存加载的贴图、字体
    std::unordered_map<std::string, class Texture *> mTextures;
    std::unordered_map<std::string, class Font *> mFonts;

    //精灵组件要画的图
    std::vector<class SpriteComponent *> mSprites;

    //InitObj.json对象
    Json::Value mInitObjRoot;

    glm::ivec2 mMousePos;

    std::vector<class Item *> mItems;
    std::vector<class Document *> mDocuments;

};


#endif //SEMI_DEMO_GAMESYS_H
