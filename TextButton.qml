import QtQuick;

BasicButton{
      id: root;
      Text{
            id: m_content;
            visible: true
            antialiasing: root.antialiasing; smooth: root.smooth;
            anchors.fill: parent;
            text: "";
            wrapMode: Text.Wrap;
            fontSizeMode: Text.Fit;
            textFormat: Text.PlainText;
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
      }
      property alias content: m_content;
      property alias text: m_content.text;
      property alias textColor: m_content.color;
}