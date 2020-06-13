//
// Created by 蔡元涵 on 2020/6/2.
//

#ifndef SEMI_DEMO_GAMESYS_H
#define SEMI_DEMO_GAMESYS_H

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

class GameSys
{
public:
    GameSys();

    bool InitGame();

    void RunLoop();

    void Shutdown();

    void AddActor(class Actor *actor);

    void RemoveActor(class Actor *actor);

    class Texture *GetTexture(const std::string &fileName);

    void AddSprite(class SpriteComponent *sprite);

    void RemoveSprite(class SpriteComponent *sprite);

private:
    void ProcessInput();

    void UpdateGame();

    void GenerateOutput();

    bool LoadShaders();

    void CreateSpriteVerts();

    void LoadData();

    void UnloadData();

    SDL_Window *mWindow;
    SDL_GLContext mContext;
    bool mIsRunning;
    bool mIsUpdatingActors;
    Uint32 mTicks;


    float mDeltaTime;

    class Player *mPlayer;

    //游戏中的actor
    std::vector<class Actor *> mActors;
    //游戏中等待加入的actor
    std::vector<class Actor *> mPendingActors;

    //sprite着色器
    class Shader *mSpritesShader;

    //VAO
    class VertexArray *mSpriteVerts;

    //储存加载的贴图
    std::unordered_map<std::string, class Texture *> mTextures;

    //精灵组件要画的图
    std::vector<class SpriteComponent *> mSprites;
};


#endif //SEMI_DEMO_GAMESYS_H
