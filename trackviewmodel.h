#ifndef TRACKVIEWMODEL_H
#define TRACKVIEWMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QVector>
#include <trackdata.h>

class TrackViewModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TrackRoles {
        TitleRole = Qt::UserRole + 1,
        ArtistRole,
        RightsRole,
        PriceRole,
        AudioURLRole,
        ImageURLRole
    };

    ~TrackViewModel()=default;
    static TrackViewModel &Instance();

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    void appendTrack(TrackData track);
    void refresh();
    QVector<TrackData> getTracks()const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    TrackViewModel();
    TrackViewModel(TrackViewModel const&)=delete;
    void operator = (TrackViewModel const&)=delete;

    QVector<TrackData> m_tracks;
};

#endif // TRACKVIEWMODEL_H
