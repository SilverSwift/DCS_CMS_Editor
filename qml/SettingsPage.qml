import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs

Item{
    signal okClicked()
    signal backupClicked()

    Item{
        width: parent.width*0.8
        height: parent.height/3
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: parent.width/10

        ColumnLayout {
            anchors.fill: parent
            anchors.centerIn: parent
            Layout.alignment: Qt.AlignHCenter

            DirectoryPicker{
                id: rootDir
                title: qsTr("DCS root dir")
                Layout.fillWidth: true
                folder: app_instance.installInfo.dcsRootDir
                onFolderChanged: app_instance.installInfo.dcsRootDir = folder
            }

            DirectoryPicker{
                id: savesDir
                title: qsTr("DCS saves dir")
                Layout.fillWidth: true
                folder: app_instance.installInfo.dcsSavesDir
                onFolderChanged: app_instance.installInfo.dcsSavesDir = folder

            }
            GroupBox{
                title: qsTr("Backup current profiles")
                Layout.fillWidth: true
                ColumnLayout{
                    anchors.fill: parent
                    Text{
                        text: qsTr("Backup description")
                        Layout.preferredWidth: parent.width
                        wrapMode: Text.WordWrap
                    }

                    Button{
                        //TODO: disable if config invalid
                        text: qsTr("Backup")
                        implicitHeight: 30
                        implicitWidth: 100
                        Layout.alignment: Qt.AlignHCenter
                        onClicked: backupClicked()
                    }
                }
            }

            Button{
                Layout.alignment: Qt.AlignHCenter
                text: "OK"
                onClicked: okClicked()
                implicitHeight: 30
                implicitWidth: 100
            }
        }
    }
}
