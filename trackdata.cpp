#include "trackdata.h"

TrackData::TrackData(QString title, QString artist, QString rights, QString price, QString audioURL, QString imageURL)
{
    m_title = title;
    m_artist = artist;
    m_rights = rights;
    m_price = price;
    m_audioURL = audioURL;
    m_imageURL = imageURL;
}
QString TrackData::getTitle() const
{
    return m_title;
}
void TrackData::setTitle(QString title)
{
    m_title = title;
}
QString TrackData::getArtist() const
{
    return m_artist;
}
void TrackData::setArtist(QString artist)
{
    m_artist = artist;
}
QString TrackData::getRights() const
{
    return m_rights;
}
void TrackData::setRights(QString rights)
{
    m_rights = rights;
}
QString TrackData::getPrice() const
{
    return m_price;
}
void TrackData::setPrice(QString price)
{
    m_price = price;
}
QString TrackData::getAudioURL() const
{
    return m_audioURL;
}
void TrackData::setAudioURL(QString audioURL)
{
    m_audioURL = audioURL;
}
QString TrackData::getImageURL() const
{
    return m_imageURL;
}
void TrackData::setImageURL(QString imageURL)
{
    m_imageURL = imageURL;
}
void TrackData::clearTrackData()
{
    m_title.clear();
    m_artist.clear();
    m_rights.clear();
    m_price.clear();
    m_audioURL.clear();
    m_imageURL.clear();
}
