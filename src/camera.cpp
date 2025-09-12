i32 virtualWidth;
i32 virtualHeight;

f32 targetX = 0.0f;
f32 targetY = 0.0f;
f32 camX = 0.0f;
f32 camY = 0.0f;
i32 camScreenW = 320;
i32 camScreenH = 180;
f32 camProj[16];

void ortho(f32 left, f32 right, f32 bottom, f32 top, f32* mat) 
{
    for (int i = 0; i < 16; i++) mat[i] = 0.0f;
    mat[0] = 2.0f / (right - left);
    mat[5] = 2.0f / (top - bottom);
    mat[10] = -1.0f;
    mat[12] = -(right + left) / (right - left);
    mat[13] = -(top + bottom) / (top - bottom);
    mat[15] = 1.0f;
}

void Camera_Init(i32 vWidth, i32 vHeight)
{
	virtualWidth = vWidth;
    virtualHeight = vHeight;
    camX = 0.0f; 
    camY = 0.0f;
}

void Camera_SetPosition(f32 x, f32 y) 
{
    camX = x;
    camY = y;
}

void Camera_Move(f32 dx, f32 dy)
{
    camX += dx;
    camY += dy;
}

void Camera_Follow(f32 targetX, f32 targetY, f32 width, f32 height) 
{
    camX = targetX + width / 2.0f - virtualWidth / 2.0f;
    camY = targetY + height / 2.0f - virtualHeight / 2.0f;
}

void Camera_FollowSmooth(f32 x, f32 y, f32 w, f32 h, f32 speed, f32 deltaTime) 
{
	targetX = x + w / 2.0f - virtualWidth / 2.0f;
    targetY = y + h / 2.0f - virtualHeight / 2.0f;

    camX += (targetX - camX) * speed * deltaTime;
    camY += (targetY - camY) * speed * deltaTime;
}

void Camera_UpdateProjection(void) 
{
    ortho(camX, camX + virtualWidth, camY + virtualHeight, camY, camProj);
}

ZINLINE f32* Camera_GetProjection(void) 
{
    return camProj;
}

void Camera_SetViewport(SDL_Window* window) 
{
    int windowW, windowH;
    SDL_GetWindowSize(window, &windowW, &windowH);

    // Figure out the largest integer scale that still fits:
    int scaleX = windowW / virtualWidth;
    int scaleY = windowH / virtualHeight;
    int pixelScale = scaleX < scaleY ? scaleX : scaleY;
    if (pixelScale < 1) pixelScale = 1;

    // Compute the actual “screen” size we’ll render into:
    camScreenW = virtualWidth  * pixelScale;
    camScreenH = virtualHeight * pixelScale;

    // Center it in the real window for letterbox/pillarbox bars:
    int vpX = (windowW  - camScreenW) / 2;
    int vpY = (windowH - camScreenH) / 2;

    glViewport(vpX, vpY, camScreenW, camScreenH);
}