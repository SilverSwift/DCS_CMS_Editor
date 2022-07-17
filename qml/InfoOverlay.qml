import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Popup {
    id: popup
    y: Math.round((parent.height - height) / 2)

    width: window.width
    height: window.height/4

    modal: true
    closePolicy: Popup.NoAutoClose
    Overlay.modal: Rectangle { color: "#BBCCDDEE" }

    function showError(txt) {
        container.isError = true
        text.text = txt
        visible = true
    }

    function showInfo(txt) {
        container.isError = false
        text.text = txt
        visible = true
    }


    ColumnLayout{
        id: container
        property bool isError: false
        anchors.fill: parent
        anchors.margins: 20

        RowLayout{


            Image{
                id: image
                source: container.isError ?
                                    "qrc:/img/error.png" :
                                    "qrc:/img/info.png"

                fillMode: Image.PreserveAspectFit
            }

            Text{
                id: text
                font.pointSize: 12
                Layout.fillHeight: true
                Layout.preferredWidth: popup.width - 2*image.width

                wrapMode: Text.WordWrap

                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
            }

        }

        Button{
            text: "OK"
            onClicked: popup.close()
            Layout.alignment: Qt.AlignHCenter
            implicitHeight: 30
            implicitWidth: 100
        }
    }

}
