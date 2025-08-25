enum GameStateID
{
	GAME_STATE_MAIN_MENU,
	GAME_STATE_IN_LEVEL,
};

struct GameState
{
	GameStateID state;
	f32 updateTimer;
	bool initialized = false;
};