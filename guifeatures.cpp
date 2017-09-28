#include <QDebug>
#include <QUrl>
#include "guifeatures.h"
#include "trackviewmodel.h"

GUIFeatures &GUIFeatures::Instance()
{
    static GUIFeatures instance;
    return instance;
}
QString GUIFeatures::currentTrackImageURL() const
{
    return m_currentTrackImageURL;
}
void GUIFeatures::setCurrentTrackImageURL(QString URL)
{
    if (URL != m_currentTrackImageURL)
    {
        m_currentTrackImageURL = URL;
        emit currentTrackImageURLChanged();
    }
}
QString GUIFeatures::currentTrackAudioURL() const
{
    return m_currentTrackAudioURL;
}
void GUIFeatures::setCurrentTrackAudioURL(QString URL)
{
    if (URL != m_currentTrackAudioURL)
    {
        m_currentTrackAudioURL = URL;
        emit currentTrackAudioURLChanged();
    }
}
void GUIFeatures::changeImageURL(int row)
{
    setCurrentTrackImageURL(TrackViewModel::Instance().getTracks().at(row).getImageURL());
}
void GUIFeatures::changeAudioURL(int row)
{
    setCurrentTrackAudioURL(TrackViewModel::Instance().getTracks().at(row).getAudioURL());
}
GUIFeatures::GUIFeatures()
{
    setCurrentTrackImageURL("Images/select_song.jpg");
}
