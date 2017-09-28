#include <QUrl>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTemporaryFile>
#include <QXmlStreamReader>
#include "xmlparser.h"
#include "trackviewmodel.h"
#include "trackdata.h"

XMLParser &XMLParser::Instance()
{
    static XMLParser instance;
    return instance;
}
int XMLParser::tracksLoaded() const
{
    return m_tracksLoaded;
}
void XMLParser::setTracksLoaded(int trueOrFalse)
{
    if (trueOrFalse != m_tracksLoaded)
    {
        m_tracksLoaded = trueOrFalse;
        emit tracksLoadedChanged();
    }
}
void XMLParser::getXMLFile()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    QNetworkRequest request;
    request.setUrl(QUrl("http://itunes.apple.com/us/rss/topsongs/limit=100/xml"));
    manager->get(request);
}
void XMLParser::readXML()
{
    if (!m_file.open())
    {
        qDebug () << "Error opening file";
    }
    else
    {
        qDebug () << "File opened";
        QXmlStreamReader reader(m_file.readAll());
        m_file.close();
        TrackData trackData;
        bool firstElementFound = false;
        while(!reader.atEnd())
        {
            reader.readNext();
            if (reader.hasError())
            {
                qDebug () << "Error: ";
            }
            if (reader.isStartElement())
            {
                if (reader.name() == "title")
                {
                    QString title;
                    QString artist;
                    title.append(reader.readElementText());
                    artist = title;
                    title.chop(title.size() - title.lastIndexOf('-'));
                    title = title.trimmed();
                    artist.append(reader.readElementText());
                    artist.remove(0, artist.indexOf('-')+1);
                    artist = artist.trimmed();
                    trackData.setTitle(title);
                    trackData.setArtist(artist);
                }
                if (reader.name() == "link")
                {
                    bool isValidLink = false;
                    //get attributes
                    foreach(const QXmlStreamAttribute &attr, reader.attributes())
                    {
                        if (attr.name().toString() == QString("title"))
                        {
                            if (attr.value().toString().compare("Preview", Qt::CaseInsensitive) == 0)
                            {
                                isValidLink = true;
                            }
                        }
                        if (attr.name().toString() == QString("href") && isValidLink == true)
                        {
                            trackData.setAudioURL(attr.value().toString());
                            //qDebug () << trackData.getAudioURL();
                        }
                    }
                }
                if (reader.name() == "price")
                {
                    trackData.setPrice(reader.readElementText());
                }
                if (reader.name() == "image")
                {
                    firstElementFound = true;
                    //get attributes
                    foreach(const QXmlStreamAttribute &attr, reader.attributes())
                    {
                        if (attr.name().toString() == QString("height"))
                        {
                            if (attr.value().toString().compare("170", Qt::CaseInsensitive) == 0)
                            {
                                trackData.setImageURL(reader.readElementText());
                            }
                        }
                    }
                }
                if (reader.name() == "rights" && firstElementFound == true)
                {
                    trackData.setRights(reader.readElementText());
                }
                if (!trackData.getArtist().isEmpty() && !trackData.getTitle().isEmpty()
                        && !trackData.getPrice().isEmpty() && !trackData.getImageURL().isEmpty()
                        && !trackData.getAudioURL().isEmpty() && !trackData.getRights().isEmpty())
                {
                    TrackViewModel::Instance().appendTrack(trackData);
                    trackData.clearTrackData();
                }
            }
        }
        TrackViewModel::Instance().refresh();
    }
}
void XMLParser::replyFinished(QNetworkReply *reply)
{
    qDebug () << "CALL";
    if (m_file.open())
    {
        QByteArray text = reply->readAll();
        if (text.isEmpty())
        {
            qDebug () << "Empty";
            setTracksLoaded(2);
        }
        else
        {
            setTracksLoaded(1);
        }
        m_file.write(text);
    }
    m_file.close();

//    if (m_file.open())
//    {
//        while (!m_file.atEnd()) {
//            QByteArray line = m_file.readLine();
//            qDebug () << line;
//        }
//    }
//    m_file.close();
    if (tracksLoaded() == 1)
    {
        readXML();
    }
}
XMLParser::XMLParser()
{
    setTracksLoaded(0);
}
