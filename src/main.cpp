i32 main()
{
	ZLog_Init(ZLOG_LEVEL_INFO);

	i32 user_count = 15;

	ZLOG_INFO("Application started with %d users online.", user_count);

	ZLOG_WARN("Good morning, Crono");
	ZLOG_DEBUG("DEBUG");
    ZLOG_WARN("WARN: TEST");
    ZLOG_INFO("good morning, Crono");
    ZLOG_ERROR("ERROR: Test");
    ZLOG_CRIT("CRIT: Test");

	return 0;
}
