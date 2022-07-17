import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


ColumnLayout{
    id: container

    property bool isError: false
    property alias text: text.text

    signal okClicked()

    RowLayout{
        id: row
        Layout.alignment: Qt.AlignHCenter
        Layout.fillWidth: true
        spacing: 10

        Image{
            id: image
            source: container.isError ?
                                "qrc:/img/error.png" :
                                "qrc:/img/info.png"

            fillMode: Image.PreserveAspectFit
        }
        Item{Layout.preferredWidth: 1}

        Text{
            id: text
            font.pointSize: 12
            Layout.preferredWidth: container.width - image.paintedWidth*2
            wrapMode: Text.Wrap
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
        }

    }

    Button{
        text: "OK"
        onClicked: okClicked()
        Layout.alignment: Qt.AlignHCenter
        implicitHeight: 30
        implicitWidth: 100
    }
}
