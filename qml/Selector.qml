import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import SilverSwift.Model 0.1

Item{
    width: parent.width
    signal aircraftClicked(var aircraft)

    ScrollView{
        id: scroll

        property int marginsPx: 30
        property int sideSize: Math.min(width, height)/(selector.columns) - marginsPx
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

        anchors.fill: parent

        Grid{
            id: selector
            x: (scroll.width - width)/2
            columns: 3
            enabled: app_instance.isValid
            spacing: scroll.marginsPx



            Repeater{
                model: ListModel{
                    ListElement{source: "qrc:/img/a-10c.png";   text: "A-10C"; dir: "A-10C"}
                    ListElement{source: "qrc:/img/a-10cii.png"; text: "A-10CII"; dir: "A-10C_2"}
                    ListElement{source: "qrc:/img/f-16.png";    text: "F-16C"; dir: "F-16C"}
                    ListElement{source: "qrc:/img/fa-18c.png";  text: "F/A-18C"; dir: "FA-18C"}
                    ListElement{source: "qrc:/img/m-2000c.png"; text: "M-2000C"; dir: "M-2000C"}
                    ListElement{source: "qrc:/img/av-8n.png";   text: "AV-8B"; dir: "AV8BNA"}
                    ListElement{source: "qrc:/img/jf-17.png";   text: "JF-17"; dir: "JF-17"}
                }

                SelectorItemDelegate{
                    width: scroll.sideSize
                    height: scroll.sideSize
                    source: model.source
                    text: model.text
                    enabled: app_instance.installInfo.instaledModules.includes(model.dir)
                    onClicked: {
                        app_instance.onAircraftClicked(model.dir)

                        stack.push("qrc:/qml/CMSEditor.qml")
                        stack.currentItem.onApplyClicked.connect(()=>{app_instance.apply(dir)})
                        stack.currentItem.onRestoreClicked.connect(()=>{app_instance.restore(dir)})
                        stack.currentItem.onResetClicked.connect(()=>{app_instance.reset(dir)})

                        aircraftClicked(model.text)
                    }
                }
            }

        }
    }

}




