void gameLoop()
{
    running = 1;

    Uint32 lastTime = SDL_GetTicks();

    while (running)
    {
        Uint32 currentTime = SDL_GetTicks();
        float dt = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        processInput();
        updateGame(dt);
        renderGame();
    }
}

void processInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = 0;
        }
    }

    handleInput(&player);
}

void updateGame(float dt)
{
    if (gameState == STATE_EXIT)
    {
        running = 0;
        return;
    }

    updatePlayer(&player, dt);

    updateEnemies(enemies, enemyCount, dt, &player);

    resolveCollisions();

    resolveCombat();

    updateLevel(dt);
}

void resolveCollisions()
{
    for (int i = 0; i < enemyCount; i++)
    {
        resolveBodyCollision(&player, &enemies[i]);
    }
}

void resolveCombat()
{
    for (int i = 0; i < enemyCount; i++)
    {
        resolvePlayerVsEnemy(&player, &enemies[i]);
    }
}

void updateLevel(float dt)
{
    if (enemyCount == 0)
    {
        levelTransitionTimer += dt;

        if (levelTransitionTimer > 2.0f)
        {
            loadNextLevel();
            levelTransitionTimer = 0;
        }
    }
}

void renderGame()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    renderBackground();

    renderPlayer(&player);

    renderEnemies(enemies, enemyCount);

    SDL_RenderPresent(renderer);
}

void renderEnemies(Enemy enemies[], int count)
{
    for (int i = 0; i < count; i++)
    {
        renderEnemy(&enemies[i]);
    }
}

void renderBackground()
{
    SDL_RenderCopy(renderer, background, NULL, NULL);
}

