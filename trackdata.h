#ifndef TRACKDATA_H
#define TRACKDATA_H

#include <QString>

class TrackData
{
public:
    TrackData()=default;
    TrackData(QString title, QString artist, QString rights, QString price,
              QString audioURL, QString imageURL);

    QString getTitle()const;
    void setTitle(QString title);
    QString getArtist()const;
    void setArtist(QString artist);
    QString getRights()const;
    void setRights(QString rights);
    QString getPrice()const;
    void setPrice(QString price);
    QString getAudioURL()const;
    void setAudioURL(QString audioURL);
    QString getImageURL()const;
    void setImageURL(QString imageURL);
    void clearTrackData();

private:
    QString m_title;
    QString m_artist;
    QString m_rights;
    QString m_price;
    QString m_audioURL;
    QString m_imageURL;

};

#endif // TRACKDATA_H
