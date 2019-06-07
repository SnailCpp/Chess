#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include <QString>

class GameSettings
{
public:
    GameSettings();
    ~GameSettings();
    void LoadSettings();
    void SaveSettings();

    int GetGameType() const;
    void SetGameType(int value);

    int GetCompetitorSide() const;
    void SetCompetitorSide(int value);

    int GetAhead() const;
    void SetAhead(int value);

    int GetStepTime() const;
    void SetStepTime(int value);

    void CreateSettingsFile(const QString &file);

private:
    int gameType;
    int competitorSide;
    int ahead;
    int stepTime;

};

extern GameSettings g_gameSettings;

#endif // GAMESETTINGS_H
