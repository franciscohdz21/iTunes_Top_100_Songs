#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTemporaryFile>

class XMLParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int tracksLoaded READ tracksLoaded WRITE setTracksLoaded NOTIFY tracksLoadedChanged)
public:
    ~XMLParser()=default;
    static XMLParser &Instance();

    int tracksLoaded()const;
    void setTracksLoaded(int trueOrFalse);
    Q_INVOKABLE void getXMLFile();
    Q_INVOKABLE void readXML();

signals:
    void finished(QNetworkReply* reply);
    void tracksLoadedChanged();

public slots:
    void replyFinished(QNetworkReply* reply);

private:
    XMLParser();
    XMLParser(XMLParser const&)=delete;
    void operator = (XMLParser const&)=delete;

    QByteArray m_text;
    QTemporaryFile m_file;
    int m_tracksLoaded; // 0 = start state, 1 = success state, 2 = failure state
};

#endif // XMLPARSER_H
