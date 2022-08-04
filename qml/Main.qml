import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.settings
import SilverSwift.Model 0.1

ApplicationWindow {
    id: window
    visible: true
    minimumHeight: 600
    minimumWidth: 900

    title: qsTr("YOPT - Your Own Presets Tweaker for DCS")

    function showHome(){
        navbar.state = "select"
        stack.pop()
    }

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
        showHome()
        stack.currentItem.aircraftClicked.connect(
                    (txt)=>{
                        navbar.text = txt
                        navbar.state = "edit"
                    })
        app_instance.onShowSettings.connect(showSettings)
        showHome()
        app_instance.onCompletedSlot()
    }

    Settings {
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }

    Facade{
        id: app_instance
        onError: (details)=>{info.showError(details)}
        onInfo: (details)=>{info.showInfo(details)}
        onModelError: showHome()
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
            text: qsTr("Lorem ipsum dolor sit amet...")
            onLinkActivated: (link)=>{Qt.openUrlExternally(link)}
        }
    }

    header: NavBar{
        id: navbar
        onHomeClicked: showHome()
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
