import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtMultimedia 5.8
import QtQuick.Dialogs 1.2

Window {
    visible: true
    width: 1280
    minimumWidth: 1280
    maximumWidth: 1280
    minimumHeight: 650
    maximumHeight: 650
    height: 650
    title: "Top 100 Songs on iTunes"
    Component.onCompleted: xmlparser.getXMLFile()

    Window {
        id: messageDialog
        title: "Please wait"
        width: 350
        maximumWidth: 350
        minimumWidth: 350
        height: 120
        maximumHeight: 120
        minimumHeight: 120
        property int tracksLoaded: xmlparser.tracksLoaded
        onTracksLoadedChanged:
        {
            if (tracksLoaded === 1)
            {
                messageDialog.close()
            }
            else if (tracksLoaded === 2)
            {
                messageDialog.title = "Restart Application"
                warningText.text = "Could not load, please restart application."
                busyIndicator.running = false
            }
        }
        Rectangle {
            anchors.fill: parent
            color: "white"
            Text {
                id: warningText
                x: 52
                y: 20
                font.pixelSize: 14
                text: "Please wait while the tracks are loaded."
            }
            BusyIndicator {
                id: busyIndicator
                x: 150
                y: 55
                running: true
            }
        }

        Component.onCompleted: visible = true
    }

    Image {
        source: "Images/main_background.jpg"
    }

    Rectangle {
        id: mainRectangle
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        anchors.rightMargin: 20
        color: "transparent"

        TableView {
            id: songsTableView
            anchors.top: mainRectangle.top
            anchors.left: mainRectangle.left
            anchors.leftMargin: 20
            anchors.topMargin: 80
            implicitWidth: 900
            implicitHeight: 450
            model: trackviewmodel
            opacity: 0.7
            onCurrentRowChanged: {
                console.log(songsTableView.currentRow)
                guifeatures.changeImageURL(songsTableView.currentRow)
                guifeatures.changeAudioURL(songsTableView.currentRow)
                playMusic.play()
            }

            TableViewColumn {
                role: "title"
                title: "Title"
                width: 200
            }
            TableViewColumn {
                role: "artist"
                title: "Artist"
                width: 200
            }
            TableViewColumn {
                role: "price"
                title: "Price"
                width: 100
            }
            TableViewColumn {
                role: "rights"
                title: "Rights"
                width: 370
            }
        }

        Image {
            id: selectSongImage
            anchors.top: songsTableView.top
            anchors.left: songsTableView.right
            anchors.leftMargin: 90
            anchors.topMargin: 30
            source: guifeatures.currentTrackImageURL
        }
        Button {
            id: selectSongButton
            anchors.top: selectSongImage.bottom
            anchors.topMargin: 20
            anchors.leftMargin: 40
            anchors.left: selectSongImage.left
            text: "Random Song"
            function getRandomArbitrary(min, max) {
              return Math.floor(Math.random() * (max - min)) + min;
            }
            onClicked: {
                var number = getRandomArbitrary(0, songsTableView.rowCount)
                songsTableView.selection.clear()
                songsTableView.selection.select(number)
                songsTableView.currentRow = number
            }
        }
        MediaPlayer {
            id: playMusic
            source: guifeatures.currentTrackAudioURL
        }

        Button {
            text: "Close"
            x: 1160
            y: 590
            onClicked: {
                Qt.quit()
            }
        }

    }
}
