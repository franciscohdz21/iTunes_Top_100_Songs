#include "trackviewmodel.h"

TrackViewModel &TrackViewModel::Instance()
{
    static TrackViewModel instance;
    return instance;
}
QVariant TrackViewModel::data(const QModelIndex &index, int role) const
{
    if (m_tracks.isEmpty())
        return QVariant();
    switch(role)
    {
    case TitleRole:
        return m_tracks.at(index.row()).getTitle();
    case ArtistRole:
        return m_tracks.at(index.row()).getArtist();
    case RightsRole:
        return m_tracks.at(index.row()).getRights();
    case PriceRole:
        return m_tracks.at(index.row()).getPrice();
    case AudioURLRole:
        return m_tracks.at(index.row()).getAudioURL();
    case ImageURLRole:
        return m_tracks.at(index.row()).getImageURL();
    default:
        return QVariant();
    }
    return QVariant();
}
int TrackViewModel::rowCount(const QModelIndex &parent) const
{
    return m_tracks.size();
}
void TrackViewModel::appendTrack(TrackData track)
{
    m_tracks.append(track);
}
void TrackViewModel::refresh()
{
    beginResetModel();
    endResetModel();
}
QVector<TrackData> TrackViewModel::getTracks() const
{
    return m_tracks;
}
QHash<int, QByteArray> TrackViewModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[ArtistRole] = "artist";
    roles[RightsRole] = "rights";
    roles[PriceRole] = "price";
    roles[AudioURLRole] = "audioURL";
    roles[ImageURLRole] = "imageURL";
    return roles;
}
TrackViewModel::TrackViewModel()
{

}
