#include "gamesettings.h"
#include "chessbase.h"
#include "chesslog.h"
#include <QSettings>
#include <QFile>

GameSettings g_gameSettings;
GameSettings::GameSettings()
{
    LoadSettings();
}

GameSettings::~GameSettings()
{

}

void GameSettings::LoadSettings()
{
    QSettings settings(SETTINGS_FILE, QSettings::IniFormat);
    settings.beginGroup("Game");
    gameType = settings.value("GameType", 0).toInt();
    competitorSide = settings.value("CompetitorSide", 0).toInt();
    ahead = settings.value("Ahead", 0).toInt();
    stepTime = settings.value("StepTime", 30000).toInt();
    settings.endGroup();
}

void GameSettings::SaveSettings()
{
    CreateSettingsFile(QString(SETTINGS_FILE));

    QSettings settings(SETTINGS_FILE, QSettings::IniFormat);
    settings.beginGroup("Game");
    settings.setValue("GameType", gameType);
    settings.setValue("CompetitorSide", competitorSide);
    settings.setValue("Ahead", ahead);
    settings.setValue("StepTime", stepTime);
    settings.endGroup();
}
int GameSettings::GetGameType() const
{
    return gameType;
}

void GameSettings::SetGameType(int value)
{
    gameType = value;
}
int GameSettings::GetCompetitorSide() const
{
    return competitorSide;
}

void GameSettings::SetCompetitorSide(int value)
{
    competitorSide = value;
}
int GameSettings::GetAhead() const
{
    return ahead;
}

void GameSettings::SetAhead(int value)
{
    ahead = value;
}

int GameSettings::GetStepTime() const
{
    return stepTime;
}

void GameSettings::SetStepTime(int value)
{
    stepTime = value;
}

void GameSettings::CreateSettingsFile(const QString &filePath)
{
    if (!QFile::exists(filePath))
    {
        QFile file(filePath);
        file.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate);
        file.close();
    }
}
