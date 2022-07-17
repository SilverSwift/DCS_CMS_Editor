import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Popup {
    id: popup

    modal: true
    closePolicy: Popup.NoAutoClose
    Overlay.modal: Rectangle { color: "#BBCCDDEE" }

    function showError(txt) {
        show(txt, true)
    }

    function showInfo(txt) {
        show(txt, false)
    }

    function show(txt, isError) {
        popup.visible = true

        stackContainer.push("qrc:/qml/InfoOverlayItem.qml",
                            StackView.Immediate)

        stackContainer.currentItem.text = txt
        stackContainer.currentItem.isError = isError
        stackContainer.currentItem.onOkClicked.connect(
                    ()=>{
                        if (stackContainer.depth > 1)
                            stackContainer.pop(StackView.Immediate)
                        else{
                            stackContainer.clear()
                            popup.visible = false
                        }
                    })

    }

    StackView{
        id: stackContainer
        anchors.fill: parent
    }

}
