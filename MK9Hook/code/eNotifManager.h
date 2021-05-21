#pragma once


class eNotificationManager {
public:
	char szMessageBuffer[2048] = {};
	bool m_bIsNotificationActive;
	int  m_nNotificationTime;
	unsigned int m_tTimer;


	void Init();

	void Update();
	void Draw();
	void SetNotificationTime(int time);
	void PushNotification(const char* format, ...);
};

extern eNotificationManager* Notifications;