import QtQuick 2.15
import QtQuick.Controls 2.15
import SilverSwift.Model 0.1

ApplicationWindow {
    id: window
    visible: true
    minimumHeight: 800
    minimumWidth: 600

    function showSettings(){
        stack.push("qrc:/qml/SettingsPage.qml")
        stack.currentItem.onOkClicked.connect(settingsAccepted)
        stack.currentItem.onBackupClicked.connect(app_instance.doForcedBackup)
    }

    function settingsAccepted(){
        stack.pop()
        app_instance.validateSettings()
    }

    Component.onCompleted: {
        stack.push("qrc:/qml/Selector.qml")
        stack.currentItem.onSettingsClicked.connect(showSettings)
        app_instance.onShowSettings.connect(showSettings)
        app_instance.onCompletedSlot()
    }

    InfoOverlay{
        id: info
        width: window.width
        height: window.height/2
        y: Math.round((parent.height - height) / 2)
    }

    Facade{
        id: app_instance
        onError: (details)=>{info.showError(details)}
        onInfo: (details)=>{info.showInfo(details)}
    }

    menuBar: MenuBar {
        // ...
    }

    StackView {
        id: stack
        anchors.fill: parent
        anchors.margins: 10
        clip: true
    }
}