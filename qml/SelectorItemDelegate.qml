import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: delegate
    property alias source: image.source
    property alias text: button.text
    property int size : Math.min(width, height)

    signal clicked()

    Item{
        implicitHeight: delegate.size
        implicitWidth: delegate.size
        anchors.centerIn: delegate

        Rectangle{
            anchors.fill: parent
            anchors.margins: width/20
            border.color: "black"
            border.width: 1
            radius: width/10

            color: "transparent"
        }

        Rectangle{
            id: container
            anchors.centerIn: parent
            anchors.fill: parent
            anchors.margins: parent.width/10
            color: "transparent"

            Image{
                id: image
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                smooth: true
            }
        }

        Button{
            id: button
            implicitHeight: delegate.size/5
            implicitWidth: delegate.size/3
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: container.bottom

            ToolTip.visible: hovered
            ToolTip.delay: 1000
            ToolTip.text: qsTr("Open CMS program editor for %1").arg(text)

            font.pixelSize: width/6

            onClicked: delegate.clicked()
        }
    }
}
