#ifndef GUIFEATURES_H
#define GUIFEATURES_H

#include <QObject>

class GUIFeatures : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentTrackImageURL READ currentTrackImageURL WRITE setCurrentTrackImageURL NOTIFY currentTrackImageURLChanged)
    Q_PROPERTY(QString currentTrackAudioURL READ currentTrackAudioURL WRITE setCurrentTrackAudioURL NOTIFY currentTrackAudioURLChanged)
public:
    ~GUIFeatures()=default;
    static GUIFeatures &Instance();

    QString currentTrackImageURL()const;
    void setCurrentTrackImageURL(QString URL);
    QString currentTrackAudioURL()const;
    void setCurrentTrackAudioURL(QString URL);
    Q_INVOKABLE void changeImageURL(int row);
    Q_INVOKABLE void changeAudioURL(int row);

signals:
    void currentTrackImageURLChanged();
    void currentTrackAudioURLChanged();

private:
    GUIFeatures();
    GUIFeatures(GUIFeatures const&)=delete;
    void operator = (GUIFeatures const&)=delete;

    QString m_currentTrackImageURL;
    QString m_currentTrackAudioURL;
};

#endif // GUIFEATURES_H
