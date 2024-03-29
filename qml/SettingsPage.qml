import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item{
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
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                    }

                    Button{
                        text: qsTr("Backup")
                        implicitHeight: 30
                        implicitWidth: 100
                        Layout.alignment: Qt.AlignRight
                        onClicked: backupClicked()
                    }
                }
            }
        }
    }
}
