import QtQuick 2.15
import QtQuick.Controls 2.15
import SilverSwift.Model 0.1

ApplicationWindow {
    id: window
    visible: true
    minimumHeight: 800
    minimumWidth: 600

    title: qsTr("DCS CMS preprogrammer tool")

    function showSettings(){
        stack.push("qrc:/qml/SettingsPage.qml")
        stack.currentItem.visibleChanged.connect(settingsAccepted)
        stack.currentItem.onBackupClicked.connect(app_instance.doForcedBackup)
        navbar.state = "settings"
    }

    function settingsAccepted(){
        app_instance.validateSettings()
    }

    Component.onCompleted: {
        stack.push("qrc:/qml/Selector.qml")
        stack.currentItem.aircraftClicked.connect(
                    (txt)=>{
                        navbar.text = txt
                        navbar.state = "edit"
                    })
        app_instance.onShowSettings.connect(showSettings)
        app_instance.onCompletedSlot()
    }

    InfoOverlay{
        id: info
        width: window.width
        height: window.height/2
        y: Math.round((parent.height - height) / 2)
    }

    Dialog {
        id: about
        anchors.centerIn: parent
        title: qsTr("About")
        modal: true
        standardButtons: Dialog.Ok
        closePolicy: Popup.NoAutoClose
        Overlay.modal: Rectangle { color: "#BBCCDDEE" }

        Label {
            anchors.fill: parent
            wrapMode: Text.WordWrap
            text: qsTr("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.")
        }
    }

    Facade{
        id: app_instance
        onError: (details)=>{info.showError(details)}
        onInfo: (details)=>{info.showInfo(details)}
    }

    header: NavBar{
        id: navbar
        onHomeClicked: stack.pop()
        onSettingsClicked: showSettings()

    }

    menuBar: AppMenuBar {
        onAboutTiggered: about.open()
    }

    StackView {
        id: stack
        anchors.fill: parent
        anchors.margins: 10
        clip: true
    }
}
